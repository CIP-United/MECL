/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mse_q31.c
 * Description:  Mean square error between two Q31 vectors
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
  @addtogroup MSE
  @{
 */

/**
  @brief         Mean square error between two Q31 vectors.
  @param[in]     pSrcA       points to the first input vector
  @param[in]     pSrcB       points to the second input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    mean square error
  @return        none
 */

void mips_mse_q31(
  const q31 * pSrcA,
  const q31 * pSrcB,
        uint32_t blockSize,
        q31 * pResult)
{
        uint32_t blkCnt;                               /* Loop counter */
        q63 sum = 0;                                 /* Temporary result storage */

        q31 inA32,inB32;                                    /* Temporary variable to store packed input value */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    inA32 = *pSrcA++ >> 1;
    inB32 = *pSrcB++ >> 1;
    inA32 = __QSUB(inA32, inB32);
    sum += ((q63) inA32 * inA32) >> 14U;

    inA32 = *pSrcA++ >> 1;
    inB32 = *pSrcB++ >> 1;
    inA32 = __QSUB(inA32, inB32);
    sum += ((q63) inA32 * inA32) >> 14U;

    inA32 = *pSrcA++ >> 1;
    inB32 = *pSrcB++ >> 1;
    inA32 = __QSUB(inA32, inB32);
    sum += ((q63) inA32 * inA32) >> 14U;

    inA32 = *pSrcA++ >> 1;
    inB32 = *pSrcB++ >> 1;
    inA32 = __QSUB(inA32, inB32);
    sum += ((q63) inA32 * inA32) >> 14U;


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
    inA32 = *pSrcA++ >> 1;
    inB32 = *pSrcB++ >> 1;
    inA32 = __QSUB(inA32, inB32);
    sum += ((q63) inA32 * inA32) >> 14U;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Store result in q31 format */
  *pResult = (q31) ((sum / blockSize)>>15);
}

/**
  @} end of MSE group
 */
