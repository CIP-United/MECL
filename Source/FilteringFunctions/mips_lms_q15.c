/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_lms_q15.c
 * Description:  Processing function for Q15 LMS filter
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
  @addtogroup LMS
  @{
 */

/**
  @brief         Processing function for Q15 LMS filter.
  @param[in]     S         points to an instance of the Q15 LMS filter structure
  @param[in]     pSrc      points to the block of input data
  @param[in]     pRef      points to the block of reference data
  @param[out]    pOut      points to the block of output data
  @param[out]    pErr      points to the block of error data
  @param[in]     blockSize number of samples to process
  @return        none

  @par           Scaling and Overflow Behavior
                   The function is implemented using an internal 64-bit accumulator.
                   Both coefficients and state variables are represented in 1.15 format and multiplications yield a 2.30 result.
                   The 2.30 intermediate results are accumulated in a 64-bit accumulator in 34.30 format.
                   There is no risk of internal overflow with this approach and the full precision of intermediate multiplications is preserved.
                   After all additions have been performed, the accumulator is truncated to 34.15 format by discarding low 15 bits.
                   Lastly, the accumulator is saturated to yield a result in 1.15 format.
  @par
                   In this filter, filter coefficients are updated for each sample and
                   the updation of filter cofficients are saturted.
 */

void mips_lms_q15(
  const mips_lms_instance_q15 * S,
  const q15 * pSrc,
        q15 * pRef,
        q15 * pOut,
        q15 * pErr,
        uint32_t blockSize)
{
        q15 *pState = S->pState;                     /* State pointer */
        q15 *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */
        q15 *pStateCurnt;                            /* Points to the current sample of the state */
        q15 *px, *pb;                                /* Temporary pointers for state and coefficient buffers */
        q15 mu = S->mu;                              /* Adaptive factor */
        uint32_t numTaps = S->numTaps;                 /* Number of filter coefficients in the filter */
        uint32_t tapCnt, blkCnt;                       /* Loop counters */
        q63 acc;                                     /* Accumulator */
        q15 e = 0;                                   /* Error of data sample */
        q15 alpha;                                   /* Intermediate constant for taps update */
        q31 coef;                                    /* Temporary variable for coefficient */
        q31 acc_l, acc_h;                            /* Temporary input */
        int32_t lShift = (15 - (int32_t) S->postShift);       /*  Post shift  */
        int32_t uShift = (32 - lShift);

  /* S->pState points to buffer which contains previous frame (numTaps - 1) samples */
  /* pStateCurnt points to the location where the new input data should be written */
  pStateCurnt = &(S->pState[(numTaps - 1U)]);

  /* initialise loop count */
  blkCnt = blockSize;

  while (blkCnt > 0U)
  {
    /* Copy the new input sample into the state buffer */
    *pStateCurnt++ = *pSrc++;

    /* Initialize pState pointer */
    px = pState;

    /* Initialize coefficient pointer */
    pb = pCoeffs;

    /* Set the accumulator to zero */
    acc = 0;

#if defined (MIPS_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 taps at a time. */
    tapCnt = numTaps >> 2U;

    while (tapCnt > 0U)
    {
      /* Perform the multiply-accumulate */
      /* acc +=  b[N] * x[n-N] + b[N-1] * x[n-N-1] */
      acc = __SMLALD(read_q15x2_ia (&px), read_q15x2_ia (&pb), acc);
      acc = __SMLALD(read_q15x2_ia (&px), read_q15x2_ia (&pb), acc);

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Loop unrolling: Compute remaining taps */
    tapCnt = numTaps % 0x4U;

#else

    /* Initialize tapCnt with number of samples */
    tapCnt = numTaps;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

    while (tapCnt > 0U)
    {
      /* Perform the multiply-accumulate */
      acc += (q63) (((q31) (*px++) * (*pb++)));

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* Calc lower part of acc */
    acc_l = acc & 0xffffffff;

    /* Calc upper part of acc */
    acc_h = (acc >> 32) & 0xffffffff;

    /* Apply shift for lower part of acc and upper part of acc */
    acc = (uint32_t) acc_l >> lShift | acc_h << uShift;

    /* Converting the result to 1.15 format and saturate the output */
    acc = __SSAT(acc, 16U);

    /* Store the result from accumulator into the destination buffer. */
    *pOut++ = (q15) acc;

    /* Compute and store error */
    e = *pRef++ - (q15) acc;
    *pErr++ = (q15) e;

    /* Compute alpha i.e. intermediate constant for taps update */
    alpha = (q15) (((q31) e * (mu)) >> 15);

    /* Initialize pState pointer */
    /* Advance state pointer by 1 for the next sample */
    px = pState++;

    /* Initialize coefficient pointer */
    pb = pCoeffs;

#if defined (MIPS_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 taps at a time. */
    tapCnt = numTaps >> 2U;

    /* Update filter coefficients */
    while (tapCnt > 0U)
    {
      coef = (q31) *pb + (((q31) alpha * (*px++)) >> 15);
      *pb++ = (q15) __SSAT((coef), 16);

      coef = (q31) *pb + (((q31) alpha * (*px++)) >> 15);
      *pb++ = (q15) __SSAT((coef), 16);

      coef = (q31) *pb + (((q31) alpha * (*px++)) >> 15);
      *pb++ = (q15) __SSAT((coef), 16);

      coef = (q31) *pb + (((q31) alpha * (*px++)) >> 15);
      *pb++ = (q15) __SSAT((coef), 16);

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Loop unrolling: Compute remaining taps */
    tapCnt = numTaps % 0x4U;

#else

    /* Initialize tapCnt with number of samples */
    tapCnt = numTaps;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

    while (tapCnt > 0U)
    {
      /* Perform the multiply-accumulate */
      coef = (q31) *pb + (((q31) alpha * (*px++)) >> 15);
      *pb++ = (q15) __SSAT((coef), 16);

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Processing is complete.
     Now copy the last numTaps - 1 samples to the start of the state buffer.
     This prepares the state buffer for the next function call. */

  /* Points to the start of the pState buffer */
  pStateCurnt = S->pState;

  /* copy data */
#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 taps at a time. */
  tapCnt = (numTaps - 1U) >> 2U;

  while (tapCnt > 0U)
  {
    write_q15x2_ia (&pStateCurnt, read_q15x2_ia (&pState));
    write_q15x2_ia (&pStateCurnt, read_q15x2_ia (&pState));

    /* Decrement loop counter */
    tapCnt--;
  }

  /* Loop unrolling: Compute remaining taps */
  tapCnt = (numTaps - 1U) % 0x4U;

#else

  /* Initialize tapCnt with number of samples */
  tapCnt = (numTaps - 1U);

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

  while (tapCnt > 0U)
  {
    *pStateCurnt++ = *pState++;

    /* Decrement loop counter */
    tapCnt--;
  }

}

/**
  @} end of LMS group
 */
