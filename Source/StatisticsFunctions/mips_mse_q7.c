/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mse_q7.c
 * Description:  Mean square error between two Q7 vectors
 *
 * $Date:        31 Augest 2023
 * $Revision:    V1.0.0
 *
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2022 ARM Limited or its affiliates. All rights reserved.
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
  @defgroup MSE Mean Square Error

  Calculates the mean square error between two vectors.

 */

/**
  @addtogroup MSE
  @{
 */

/**
  @brief         Mean square error between two Q7 vectors.
  @param[in]     pSrcA       points to the first input vector
  @param[in]     pSrcB       points to the second input vector
  @param[in]     blockSize   number of samples in input vector
  @param[out]    pResult     mean square error
  @return        none
 */

void mips_mse_q7(
  const q7 * pSrcA,
  const q7 * pSrcB,
        uint32_t blockSize,
        q7 * pResult)
{
        uint32_t blkCnt;                               /* Loop counter */
        q31 sum = 0;                                 /* Temporary result storage */
        q7 inA,inB;                                       /* Temporary variable to store input value */


#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    inA = *pSrcA++ >> 1;
    inB = *pSrcB++ >> 1;
    inA = (q7) __SSAT((q15) inA - (q15)inB, 8);
    sum += ((q15) inA * inA);

    inA = *pSrcA++ >> 1;
    inB = *pSrcB++ >> 1;
    inA = (q7) __SSAT((q15) inA - (q15)inB, 8);
    sum += ((q15) inA * inA);

    inA = *pSrcA++ >> 1;
    inB = *pSrcB++ >> 1;
    inA = (q7) __SSAT((q15) inA - (q15)inB, 8);
    sum += ((q15) inA * inA);

    inA = *pSrcA++ >> 1;
    inB = *pSrcB++ >> 1;
    inA = (q7) __SSAT((q15) inA - (q15)inB, 8);
    sum += ((q15) inA * inA);

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
    inA = *pSrcA++ >> 1;
    inB = *pSrcB++ >> 1;

    inA = (q7) __SSAT((q15) inA - (q15)inB, 8);
    sum += ((q15) inA * inA);

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Store result in q7 format */
  *pResult = (q7) __SSAT((q15) (sum / blockSize)>>5, 8);;
}

/**
  @} end of MSE group
 */
