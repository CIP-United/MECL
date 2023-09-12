/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_fir_q31.c
 * Description:  Q31 FIR filter processing function
 *
 * $Date:        31 Augest 2023
 * $Revision:    V1.0.0
 *
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2021 ARM Limited or its affiliates. All rights reserved.
 * Copyright (C) 2023 CIP United Co. Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "dsp/filtering_functions.h"


/**
  @ingroup groupFilters
 */

/**
  @addtogroup FIR
  @{
 */

/**
  @brief         Processing function for Q31 FIR filter.
  @param[in]     S          points to an instance of the Q31 FIR filter structure
  @param[in]     pSrc       points to the block of input data
  @param[out]    pDst       points to the block of output data
  @param[in]     blockSize  number of samples to process
  @return        none

  @par           Scaling and Overflow Behavior
                   The function is implemented using an internal 64-bit accumulator.
                   The accumulator has a 2.62 format and maintains full precision of the intermediate multiplication results but provides only a single guard bit.
                   Thus, if the accumulator result overflows it wraps around rather than clip.
                   In order to avoid overflows completely the input signal must be scaled down by log2(numTaps) bits.
                   After all multiply-accumulates are performed, the 2.62 accumulator is right shifted by 31 bits and saturated to 1.31 format to yield the final result.

 @remark
                   Refer to \ref mips_fir_fast_q31() for a faster but less precise implementation of this filter.
 */
void mips_fir_q31(
  const mips_fir_instance_q31 * S,
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize)
{
        q31 *pState = S->pState;                     /* State pointer */
  const q31 *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */
        q31 *pStateCurnt;                            /* Points to the current sample of the state */
        q31 *px;                                     /* Temporary pointer for state buffer */
  const q31 *pb;                                     /* Temporary pointer for coefficient buffer */
        q63 acc0;                                    /* Accumulator */
        uint32_t numTaps = S->numTaps;                 /* Number of filter coefficients in the filter */
        uint32_t i, tapCnt, blkCnt;                    /* Loop counters */

#if defined (MIPS_MATH_LOOPUNROLL)
        q63 acc1, acc2;                              /* Accumulators */
        q31 x0, x1, x2;                              /* Temporary variables to hold state values */
        q31 c0;                                      /* Temporary variable to hold coefficient value */
#endif

  /* S->pState points to state array which contains previous frame (numTaps - 1) samples */
  /* pStateCurnt points to the location where the new input data should be written */
  pStateCurnt = &(S->pState[(numTaps - 1U)]);

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 output values simultaneously.
   * The variables acc0 ... acc3 hold output values that are being computed:
   *
   *    acc0 =  b[numTaps-1] * x[n-numTaps-1] + b[numTaps-2] * x[n-numTaps-2] + b[numTaps-3] * x[n-numTaps-3] +...+ b[0] * x[0]
   *    acc1 =  b[numTaps-1] * x[n-numTaps]   + b[numTaps-2] * x[n-numTaps-1] + b[numTaps-3] * x[n-numTaps-2] +...+ b[0] * x[1]
   *    acc2 =  b[numTaps-1] * x[n-numTaps+1] + b[numTaps-2] * x[n-numTaps]   + b[numTaps-3] * x[n-numTaps-1] +...+ b[0] * x[2]
   *    acc3 =  b[numTaps-1] * x[n-numTaps+2] + b[numTaps-2] * x[n-numTaps+1] + b[numTaps-3] * x[n-numTaps]   +...+ b[0] * x[3]
   */

  blkCnt = blockSize / 3;

  while (blkCnt > 0U)
  {
    /* Copy 3 new input samples into the state buffer. */
    *pStateCurnt++ = *pSrc++;
    *pStateCurnt++ = *pSrc++;
    *pStateCurnt++ = *pSrc++;

    /* Set all accumulators to zero */
    acc0 = 0;
    acc1 = 0;
    acc2 = 0;

    /* Initialize state pointer */
    px = pState;

    /* Initialize coefficient pointer */
    pb = pCoeffs;

    /* Read the first 2 samples from the state buffer: x[n-numTaps], x[n-numTaps-1] */
    x0 = *px++;
    x1 = *px++;

    /* Loop unrolling: process 3 taps at a time. */
    tapCnt = numTaps / 3;

    while (tapCnt > 0U)
    {
      /* Read the b[numTaps] coefficient */
      c0 = *pb;

      /* Read x[n-numTaps-2] sample */
      x2 = *(px++);

      /* Perform the multiply-accumulates */
      acc0 += ((q63) x0 * c0);
      acc1 += ((q63) x1 * c0);
      acc2 += ((q63) x2 * c0);

      /* Read the coefficient and state */
      c0 = *(pb + 1U);
      x0 = *(px++);

      /* Perform the multiply-accumulates */
      acc0 += ((q63) x1 * c0);
      acc1 += ((q63) x2 * c0);
      acc2 += ((q63) x0 * c0);

      /* Read the coefficient and state */
      c0 = *(pb + 2U);
      x1 = *(px++);

      /* update coefficient pointer */
      pb += 3U;

      /* Perform the multiply-accumulates */
      acc0 += ((q63) x2 * c0);
      acc1 += ((q63) x0 * c0);
      acc2 += ((q63) x1 * c0);

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    tapCnt = numTaps % 0x3U;

    while (tapCnt > 0U)
    {
      /* Read coefficients */
      c0 = *(pb++);

      /* Fetch 1 state variable */
      x2 = *(px++);

      /* Perform the multiply-accumulates */
      acc0 += ((q63) x0 * c0);
      acc1 += ((q63) x1 * c0);
      acc2 += ((q63) x2 * c0);

      /* Reuse the present sample states for next sample */
      x0 = x1;
      x1 = x2;

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Advance the state pointer by 3 to process the next group of 3 samples */
    pState = pState + 3;

    /* The result is in 2.30 format. Convert to 1.31 and store in destination buffer. */
    *pDst++ = (q31) (acc0 >> 31U);
    *pDst++ = (q31) (acc1 >> 31U);
    *pDst++ = (q31) (acc2 >> 31U);

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining output samples */
  blkCnt = blockSize % 0x3U;

#else

  /* Initialize blkCnt with number of taps */
  blkCnt = blockSize;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

  while (blkCnt > 0U)
  {
    /* Copy one sample at a time into state buffer */
    *pStateCurnt++ = *pSrc++;

    /* Set the accumulator to zero */
    acc0 = 0;

    /* Initialize state pointer */
    px = pState;

    /* Initialize Coefficient pointer */
    pb = pCoeffs;

    i = numTaps;

    /* Perform the multiply-accumulates */
    do
    {
      /* acc =  b[numTaps-1] * x[n-numTaps-1] + b[numTaps-2] * x[n-numTaps-2] + b[numTaps-3] * x[n-numTaps-3] +...+ b[0] * x[0] */
      acc0 += (q63) *px++ * *pb++;

      i--;
    } while (i > 0U);

    /* Result is in 2.62 format. Convert to 1.31 and store in destination buffer. */
    *pDst++ = (q31) (acc0 >> 31U);

    /* Advance state pointer by 1 for the next sample */
    pState = pState + 1U;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Processing is complete.
     Now copy the last numTaps - 1 samples to the start of the state buffer.
     This prepares the state buffer for the next function call. */

  /* Points to the start of the state buffer */
  pStateCurnt = S->pState;

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 taps at a time */
  tapCnt = (numTaps - 1U) >> 2U;

  /* Copy data */
  while (tapCnt > 0U)
  {
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;

    /* Decrement loop counter */
    tapCnt--;
  }

  /* Calculate remaining number of copies */
  tapCnt = (numTaps - 1U) % 0x4U;

#else

  /* Initialize tapCnt with number of taps */
  tapCnt = (numTaps - 1U);

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

  /* Copy remaining data */
  while (tapCnt > 0U)
  {
    *pStateCurnt++ = *pState++;

    /* Decrement loop counter */
    tapCnt--;
  }

}

/**
  @} end of FIR group
 */
