/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_rms_q15.c
 * Description:  Root Mean Square of the elements of a Q15 vector
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
  @addtogroup RMS
  @{
 */

/**
  @brief         Root Mean Square of the elements of a Q15 vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    root mean square value returned here
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
void mips_rms_q15(
  const q15 * pSrc,
        uint32_t blockSize,
        q15 * pResult)
{
    q63 pow = 0.0f;
    q15 normalizedPower;

    mips_power_q15(pSrc, blockSize, &pow);

    normalizedPower=__SSAT((pow / (q63) blockSize) >> 15,16);
    mips_sqrt_q15(normalizedPower, pResult);
}
#else
void mips_rms_q15(
  const q15 * pSrc,
        uint32_t blockSize,
        q15 * pResult)
{
        uint32_t blkCnt;                               /* Loop counter */
        q63 sum = 0;                                 /* Temporary result storage */
        q15 in;                                      /* Temporary variable to store input value */

#if defined (MIPS_MATH_LOOPUNROLL)
        q31 in32;                                    /* Temporary variable to store input value */
#endif

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1] */

    /* Compute sum of squares and store result in a temporary variable. */
    in = *pSrc++;
    sum += ((q31) in * in);

    in = *pSrc++;
    sum += ((q31) in * in);

    in = *pSrc++;
    sum += ((q31) in * in);

    in = *pSrc++;
    sum += ((q31) in * in);

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

    in = *pSrc++;
    /* Compute sum of squares and store result in a temporary variable. */
    sum += ((q31) in * in);

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Truncating and saturating the accumulator to 1.15 format */
  /* Store result in destination */
  mips_sqrt_q15(__SSAT((sum / (q63)blockSize) >> 15, 16), pResult);
}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of RMS group
 */
