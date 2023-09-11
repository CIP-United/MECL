/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mse_f64.c
 * Description:  Double floating point mean square error
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
  @brief         Mean square error between two double floating point vectors.
  @param[in]     pSrcA       points to the first input vector
  @param[in]     pSrcB       points to the second input vector
  @param[in]     blockSize   number of samples in input vector
  @param[out]    pResult      mean square error
  @return        none
 */

void mips_mse_f64(
    const f64 * pSrcA,
    const f64 * pSrcB,
    uint32_t blockSize,
    f64 * pResult)

{
    
    uint32_t blkCnt;                               /* Loop counter */
    f64 inA, inB;
    f64 sum = 0.0;

#if defined (MIPS_MATH_LOOPUNROLL)
    blkCnt = (blockSize) >> 1;
    
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
        
        /* Decrement loop counter */
        blkCnt--;
    }
    
    
    /* Loop unrolling: Compute remaining outputs */
    blkCnt = (blockSize) & 1;
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
