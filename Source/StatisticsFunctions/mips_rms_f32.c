/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_rms_f32.c
 * Description:  Root mean square value of the elements of a floating-point vector
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
  @defgroup RMS Root mean square (RMS)

  Calculates the Root Mean Square of the elements in the input vector.
  The underlying algorithm is used:

  <pre>
      Result = sqrt(((pSrc[0] * pSrc[0] + pSrc[1] * pSrc[1] + ... + pSrc[blockSize-1] * pSrc[blockSize-1]) / blockSize));
  </pre>

  There are separate functions for floating point, Q31, and Q15 data types.
 */

/**
  @addtogroup RMS
  @{
 */

/**
  @brief         Root Mean Square of the elements of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    root mean square value returned here
  @return        none
 */
void mips_rms_f32(
  const f32 * pSrc,
        uint32_t blockSize,
        f32 * pResult)
{
        uint32_t blkCnt;                               /* Loop counter */
        f32 sum = 0.0f;                          /* Temporary result storage */
        f32 in;                                  /* Temporary variable to store input value */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1] */

    in = *pSrc++;
    /* Compute sum of squares and store result in a temporary variable, sum. */
    sum += in * in;

    in = *pSrc++;
    sum += in * in;

    in = *pSrc++;
    sum += in * in;

    in = *pSrc++;
    sum += in * in;

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
    sum += ( in * in);

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Compute Rms and store result in destination */
  mips_sqrt_f32(sum / (f32) blockSize, pResult);
}

/**
  @} end of RMS group
 */
