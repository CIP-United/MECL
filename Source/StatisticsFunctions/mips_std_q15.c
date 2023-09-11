/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_std_q15.c
 * Description:  Standard deviation of an array of Q15 vector
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
  @brief         Standard deviation of the elements of a Q15 vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    standard deviation value returned here
  @return        none

  @par           Scaling and Overflow Behavior
                   The function is implemented using a 64-bit internal accumulator.
                   The input is represented in 1.15 format.
                   Intermediate multiplication yields a 2.30 format, and this
                   result is added without saturation to a 64-bit accumulator in 34.30 format.
                   With 33 guard bits in the accumulator, there is no risk of overflow, and the
                   full precision of the intermediate multiplication is preserved.
                   Finally, the 34.30 result is truncated to 34.15 format by discarding the lower
                   15 bits, and then saturated to yield a result in 1.15 format.
 */
#if defined(MIPS_MATH_DSP)
void mips_std_q15(
  const q15 * pSrc,
        uint32_t blockSize,
        q15 * pResult)
{
    q15 var=0;

    mips_var_q15(pSrc, blockSize, &var);
    mips_sqrt_q15(var,pResult);
}
#else
void mips_std_q15(
  const q15 * pSrc,
        uint32_t blockSize,
        q15 * pResult)
{
        uint32_t blkCnt;                               /* Loop counter */
        q31 sum = 0;                                 /* Accumulator */
        q31 meanOfSquares, squareOfMean;             /* Square of mean and mean of square */
        q63 sumOfSquares = 0;                        /* Sum of squares */
        q15 in;                                      /* Temporary variable to store input value */

#if defined (MIPS_MATH_LOOPUNROLL)
  q31 in32;                                    /* Temporary variable to store input value */
#endif

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

    /* Compute sum of squares and store result in a temporary variable, sumOfSquares. */
    /* Compute sum and store result in a temporary variable, sum. */
    in = *pSrc++;
    sumOfSquares += (in * in);
    sum += in;

    in = *pSrc++;
    sumOfSquares += (in * in);
    sum += in;

    in = *pSrc++;
    sumOfSquares += (in * in);
    sum += in;

    in = *pSrc++;
    sumOfSquares += (in * in);
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

    in = *pSrc++;
    /* Compute sum of squares and store result in a temporary variable, sumOfSquares. */
    sumOfSquares += (in * in);
    /* Compute sum and store result in a temporary variable, sum. */
    sum += in;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Compute Mean of squares and store result in a temporary variable, meanOfSquares. */
  meanOfSquares = (q31) (sumOfSquares / (q63)(blockSize - 1U));

  /* Compute square of mean */
  squareOfMean = (q31) ((q63) sum * sum / (q63)(blockSize * (blockSize - 1U)));

  /* mean of squares minus the square of mean. */
  /* Compute standard deviation and store result in destination */
  mips_sqrt_q15(__SSAT((meanOfSquares - squareOfMean) >> 15U, 16U), pResult);
}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of STD group
 */
