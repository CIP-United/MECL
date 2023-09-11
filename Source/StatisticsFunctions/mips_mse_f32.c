/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mis_mse_f32.c
 * Description:  Floating point mean square error
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
  @brief         Mean square error between two floating point vectors.
  @param[in]     pSrcA       points to the first input vector
  @param[in]     pSrcB       points to the second input vector
  @param[in]     blockSize   number of samples in input vector
  @param[out]    pResult      mean square error
  @return        none
 */

void mips_mse_f32(
    const f32 * pSrcA,
    const f32 * pSrcB,
    uint32_t    blockSize,
    f32 * pResult)

{
  uint32_t blkCnt;                               /* Loop counter */
  f32 inA, inB;
  f32 sum = 0.0f;                          /* Temporary return variable */
#if defined (MIPS_MATH_LOOPUNROLL)
  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = (blockSize) >> 2;

  /* First part of the processing with loop unrolling. Compute 4 outputs at a time.
   ** a second loop below computes the remaining 1 to 3 samples. */
  while (blkCnt > 0U)
  {

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = inA - inB;
    sum += inA * inA;

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = inA - inB;
    sum += inA * inA;

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = inA - inB;
    sum += inA * inA;

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = inA - inB;
    sum += inA * inA;

    /* Decrement loop counter */
    blkCnt--;
  }

  
  /* Loop unrolling: Compute remaining outputs */
  blkCnt = (blockSize) & 3;
#else
  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;
#endif
  while (blkCnt > 0U)
  {
    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = inA - inB;
    sum += inA * inA;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Store result in destination buffer */
  *pResult = sum / blockSize;
}

/**
  @} end of MSE group
 */
