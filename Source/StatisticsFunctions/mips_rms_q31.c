/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_rms_q31.c
 * Description:  Root Mean Square of the elements of a Q31 vector
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
  @brief         Root Mean Square of the elements of a Q31 vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    root mean square value returned here
  @return        none

  @par           Scaling and Overflow Behavior
                   The function is implemented using an internal 64-bit accumulator.
                   The input is represented in 1.31 format, and intermediate multiplication
                   yields a 2.62 format.
                   The accumulator maintains full precision of the intermediate multiplication results,
                   but provides only a single guard bit.
                   There is no saturation on intermediate additions.
                   If the accumulator overflows, it wraps around and distorts the result.
                   In order to avoid overflows completely, the input signal must be scaled down by
                   log2(blockSize) bits, as a total of blockSize additions are performed internally.
                   Finally, the 2.62 accumulator is right shifted by 31 bits to yield a 1.31 format value.
 */
#if defined(MIPS_MATH_DSP)

void mips_rms_q31(
  const q31 * pSrc,
        uint32_t blockSize,
        q31 * pResult)
{
    q63 pow = 0.0f;
    q31 normalizedPower;
    mips_power_q31(pSrc, blockSize, &pow);

    normalizedPower=clip_q63_to_q31((pow / (q63) blockSize) >> 17);
    mips_sqrt_q31(normalizedPower, pResult);

}

#else
void mips_rms_q31(
  const q31 * pSrc,
        uint32_t blockSize,
        q31 * pResult)
{
        uint32_t blkCnt;                               /* Loop counter */
        uint64_t sum = 0;                              /* Temporary result storage (can get never negative. changed type from q63 to uint64 */
        q31 in;                                      /* Temporary variable to store input value */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1] */

    in = *pSrc++;
    /* Compute sum of squares and store result in a temporary variable, sum. */
    sum += ((q63) in * in);

    in = *pSrc++;
    sum += ((q63) in * in);

    in = *pSrc++;
    sum += ((q63) in * in);

    in = *pSrc++;
    sum += ((q63) in * in);

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
    sum += ((q63) in * in);

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Convert data in 2.62 to 1.31 by 31 right shifts and saturate */
  /* Compute Rms and store result in destination vector */
  mips_sqrt_q31(clip_q63_to_q31((sum / (q63) blockSize) >> 31), pResult);
}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of RMS group
 */
