/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_fir_sparse_q15.c
 * Description:  Q15 sparse FIR filter processing function
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
  @addtogroup FIR_Sparse
  @{
 */

/**
  @brief         Processing function for the Q15 sparse FIR filter.
  @param[in]     S           points to an instance of the Q15 sparse FIR structure
  @param[in]     pSrc        points to the block of input data
  @param[out]    pDst        points to the block of output data
  @param[in]     pScratchIn  points to a temporary buffer of size blockSize
  @param[in]     pScratchOut points to a temporary buffer of size blockSize
  @param[in]     blockSize   number of input samples to process per call
  @return        none

  @par           Scaling and Overflow Behavior
                   The function is implemented using an internal 32-bit accumulator.
                   The 1.15 x 1.15 multiplications yield a 2.30 result and these are added to a 2.30 accumulator.
                   Thus the full precision of the multiplications is maintained but there is only a single guard bit in the accumulator.
                   If the accumulator result overflows it will wrap around rather than saturate.
                   After all multiply-accumulates are performed, the 2.30 accumulator is truncated to 2.15 format and then saturated to 1.15 format.
                   In order to avoid overflows the input signal or coefficients must be scaled down by log2(numTaps) bits.
 */

void mips_fir_sparse_q15(
        mips_fir_sparse_instance_q15 * S,
  const q15 * pSrc,
        q15 * pDst,
        q15 * pScratchIn,
        q31 * pScratchOut,
        uint32_t blockSize)
{
        q15 *pState = S->pState;                     /* State pointer */
  const q15 *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */
        q15 *px;                                     /* Temporary pointers for scratch buffer */
        q15 *py = pState;                            /* Temporary pointers for state buffer */
        q15 *pb = pScratchIn;                        /* Temporary pointers for scratch buffer */
        q15 *pOut = pDst;                            /* Working pointer for output */
        int32_t *pTapDelay = S->pTapDelay;             /* Pointer to the array containing offset of the non-zero tap values. */
        uint32_t delaySize = S->maxDelay + blockSize;  /* state length */
        uint16_t numTaps = S->numTaps;                 /* Number of filter coefficients in the filter  */
        int32_t readIndex;                             /* Read index of the state buffer */
        uint32_t tapCnt, blkCnt;                       /* loop counters */
        q31 *pScr2 = pScratchOut;                    /* Working pointer for scratch buffer of output values */
        q15 coeff = *pCoeffs++;                      /* Read the first coefficient value */

#if defined (MIPS_MATH_LOOPUNROLL)
        q31 in1, in2;                                /* Temporary variables */
#endif

  /* BlockSize of Input samples are copied into the state buffer */
  /* StateIndex points to the starting position to write in the state buffer */
  mips_circularWrite_q15(py, (int32_t) delaySize, &S->stateIndex, 1,pSrc, 1, blockSize);

  /* Loop over the number of taps. */
  tapCnt = numTaps;

  /* Read Index, from where the state buffer should be read, is calculated. */
  readIndex = (int32_t) (S->stateIndex - blockSize) - *pTapDelay++;

  /* Wraparound of readIndex */
  if (readIndex < 0)
  {
    readIndex += (int32_t) delaySize;
  }

  /* Working pointer for state buffer is updated */
  py = pState;

  /* blockSize samples are read from the state buffer */
  mips_circularRead_q15(py, (int32_t) delaySize, &readIndex, 1,
                       pb, pb, (int32_t) blockSize, 1, blockSize);

  /* Working pointer for the scratch buffer of state values */
  px = pb;

  /* Working pointer for scratch buffer of output values */
  pScratchOut = pScr2;


#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time. */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* Perform multiplication and store in the scratch buffer */
    *pScratchOut++ = ((q31) *px++ * coeff);
    *pScratchOut++ = ((q31) *px++ * coeff);
    *pScratchOut++ = ((q31) *px++ * coeff);
    *pScratchOut++ = ((q31) *px++ * coeff);

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = blockSize % 0x4U;

#else

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

  while (blkCnt > 0U)
  {
    /* Perform Multiplication and store in the scratch buffer */
    *pScratchOut++ = ((q31) *px++ * coeff);

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Load the coefficient value and
   * increment the coefficient buffer for the next set of state values */
  coeff = *pCoeffs++;

  /* Read Index, from where the state buffer should be read, is calculated. */
  readIndex = (int32_t) (S->stateIndex - blockSize) - *pTapDelay++;

  /* Wraparound of readIndex */
  if (readIndex < 0)
  {
    readIndex += (int32_t) delaySize;
  }

  /* Loop over the number of taps. */
  tapCnt = (uint32_t) numTaps - 2U;

  while (tapCnt > 0U)
  {
    /* Working pointer for state buffer is updated */
    py = pState;

    /* blockSize samples are read from the state buffer */
    mips_circularRead_q15(py, (int32_t) delaySize, &readIndex, 1,
                         pb, pb, (int32_t) blockSize, 1, blockSize);

    /* Working pointer for the scratch buffer of state values */
    px = pb;

    /* Working pointer for scratch buffer of output values */
    pScratchOut = pScr2;


#if defined (MIPS_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 outputs at a time. */
    blkCnt = blockSize >> 2U;

    while (blkCnt > 0U)
    {
      /* Perform Multiply-Accumulate */
      *pScratchOut++ += (q31) *px++ * coeff;
      *pScratchOut++ += (q31) *px++ * coeff;
      *pScratchOut++ += (q31) *px++ * coeff;
      *pScratchOut++ += (q31) *px++ * coeff;

      /* Decrement loop counter */
      blkCnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    blkCnt = blockSize % 0x4U;

#else

    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

    while (blkCnt > 0U)
    {
      /* Perform Multiply-Accumulate */
      *pScratchOut++ += (q31) *px++ * coeff;

      /* Decrement loop counter */
      blkCnt--;
    }

    /* Load the coefficient value and
     * increment the coefficient buffer for the next set of state values */
    coeff = *pCoeffs++;

    /* Read Index, from where the state buffer should be read, is calculated. */
    readIndex = (int32_t) (S->stateIndex - blockSize) - *pTapDelay++;

    /* Wraparound of readIndex */
    if (readIndex < 0)
    {
      readIndex += (int32_t) delaySize;
    }

    /* Decrement loop counter */
    tapCnt--;
  }

  /* Compute last tap without the final read of pTapDelay */

  /* Working pointer for state buffer is updated */
  py = pState;

  /* blockSize samples are read from the state buffer */
  mips_circularRead_q15(py, (int32_t) delaySize, &readIndex, 1,
                       pb, pb, (int32_t) blockSize, 1, blockSize);

  /* Working pointer for the scratch buffer of state values */
  px = pb;

  /* Working pointer for scratch buffer of output values */
  pScratchOut = pScr2;


#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time. */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* Perform Multiply-Accumulate */
    *pScratchOut++ += (q31) *px++ * coeff;
    *pScratchOut++ += (q31) *px++ * coeff;
    *pScratchOut++ += (q31) *px++ * coeff;
    *pScratchOut++ += (q31) *px++ * coeff;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = blockSize % 0x4U;

#else

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

  while (blkCnt > 0U)
  {
    /* Perform Multiply-Accumulate */
    *pScratchOut++ += (q31) *px++ * coeff;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* All the output values are in pScratchOut buffer.
     Convert them into 1.15 format, saturate and store in the destination buffer. */
#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time. */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    in1 = *pScr2++;
    in2 = *pScr2++;

#ifndef MIPS_MATH_BIG_ENDIAN
    write_q15x2_ia (&pOut, __PKHBT((q15) __SSAT(in1 >> 15, 16), (q15) __SSAT(in2 >> 15, 16), 16));
#else
    write_q15x2_ia (&pOut, __PKHBT((q15) __SSAT(in2 >> 15, 16), (q15) __SSAT(in1 >> 15, 16), 16));
#endif /* #ifndef MIPS_MATH_BIG_ENDIAN */

    in1 = *pScr2++;
    in2 = *pScr2++;

#ifndef MIPS_MATH_BIG_ENDIAN
    write_q15x2_ia (&pOut, __PKHBT((q15) __SSAT(in1 >> 15, 16), (q15) __SSAT(in2 >> 15, 16), 16));
#else
    write_q15x2_ia (&pOut, __PKHBT((q15) __SSAT(in2 >> 15, 16), (q15) __SSAT(in1 >> 15, 16), 16));
#endif /* #ifndef MIPS_MATH_BIG_ENDIAN */

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = blockSize % 0x4U;

#else

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

  while (blkCnt > 0U)
  {
    *pOut++ = (q15) __SSAT(*pScr2++ >> 15, 16);

    /* Decrement loop counter */
    blkCnt--;
  }

}

/**
  @} end of FIR_Sparse group
 */
