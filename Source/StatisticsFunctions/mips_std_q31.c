/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_std_q31.c
 * Description:  Standard deviation of the elements of a Q31 vector
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

#include "dsp/statistics_functions.h"

/**
  @ingroup groupStats
 */

/**
  @addtogroup STD
  @{
 */

/**
  @brief         Standard deviation of the elements of a Q31 vector.
  @param[in]     pSrc       points to the input vector.
  @param[in]     blockSize  number of samples in input vector.
  @param[out]    pResult    standard deviation value returned here.
  @return        none

  @par           Scaling and Overflow Behavior
                   The function is implemented using an internal 64-bit accumulator.
                   The input is represented in 1.31 format, which is then downshifted by 8 bits
                   which yields 1.23, and intermediate multiplication yields a 2.46 format.
                   The accumulator maintains full precision of the intermediate multiplication results,
                   but provides only a 16 guard bits.
                   There is no saturation on intermediate additions.
                   If the accumulator overflows it wraps around and distorts the result.
                   In order to avoid overflows completely the input signal must be scaled down by
                   log2(blockSize)-8 bits, as a total of blockSize additions are performed internally.
                   After division, internal variables should be Q18.46
                   Finally, the 18.46 accumulator is right shifted by 15 bits to yield a 1.31 format value.
 */
#if defined(MIPS_MATH_DSP)
void mips_std_q31(
  const q31 * pSrc,
        uint32_t blockSize,
        q31 * pResult)
{
    q31 var=0;

    mips_var_q31(pSrc, blockSize, &var);
    mips_sqrt_q31(var, pResult);
}
#else
void mips_std_q31(
  const q31 * pSrc,
        uint32_t blockSize,
        q31 * pResult)
{
        uint32_t blkCnt;                               /* Loop counter */
        q63 sum = 0;                                 /* Accumulator */
        q63 meanOfSquares, squareOfMean;             /* Square of mean and mean of square */
        q63 sumOfSquares = 0;                        /* Sum of squares */
        q31 in;                                      /* Temporary variable to store input value */

  if (blockSize <= 1U)
  {
    *pResult = 0;
    return;
  }

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1] */
    /* C = A[0] + A[1] + ... + A[blockSize-1] */

    in = *pSrc++ >> 8U;
    /* Compute sum of squares and store result in a temporary variable, sumOfSquares. */
    sumOfSquares += ((q63) (in) * (in));
    /* Compute sum and store result in a temporary variable, sum. */
    sum += in;

    in = *pSrc++ >> 8U;
    sumOfSquares += ((q63) (in) * (in));
    sum += in;

    in = *pSrc++ >> 8U;
    sumOfSquares += ((q63) (in) * (in));
    sum += in;

    in = *pSrc++ >> 8U;
    sumOfSquares += ((q63) (in) * (in));
    sum += in;

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
    /* C = A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1] */
    /* C = A[0] + A[1] + ... + A[blockSize-1] */

    in = *pSrc++ >> 8U;
    /* Compute sum of squares and store result in a temporary variable, sumOfSquares. */
    sumOfSquares += ((q63) (in) * (in));
    /* Compute sum and store result in a temporary variable, sum. */
    sum += in;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Compute Mean of squares and store result in a temporary variable, meanOfSquares. */
  meanOfSquares = (sumOfSquares / (q63)(blockSize - 1U));

  /* Compute square of mean */
  squareOfMean = ( sum * sum / (q63)(blockSize * (blockSize - 1U)));

  /* Compute standard deviation and store result in destination */
  mips_sqrt_q31((meanOfSquares - squareOfMean) >> 15U, pResult);
}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of STD group
 */
