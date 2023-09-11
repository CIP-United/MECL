/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_power_f64.c
 * Description:  Sum of the squares of the elements of a floating-point vector
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
  @addtogroup power
  @{
 */

/**
  @brief         Sum of the squares of the elements of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    sum of the squares value returned here
  @return        none
 */
void mips_power_f64(
    const f64 * pSrc,
    uint32_t blockSize,
    f64 * pResult)
{
    uint32_t blkCnt;                               /* Loop counter */
    f64 sum = 0.;                          /* Temporary result storage */
    f64 in;                                  /* Temporary variable to store input value */
    
    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;
    
    while (blkCnt > 0U)
    {
        /* C = A[0] * A[0] + A[1] * A[1] + ... + A[blockSize-1] * A[blockSize-1] */
        
        /* Compute Power and store result in a temporary variable, sum. */
        in = *pSrc++;
        sum += in * in;
        
        /* Decrement loop counter */
        blkCnt--;
    }
    
    /* Store result to destination */
    *pResult = sum;
}

/**
  @} end of power group
 */
