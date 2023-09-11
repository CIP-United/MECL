/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_var_f64.c
 * Description:  Variance of the elements of a floating-point vector
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
  @addtogroup variance
  @{
 */

/**
  @brief         Variance of the elements of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    variance value returned here
  @return        none
 */
void mips_var_f64(
    const f64 * pSrc,
    uint32_t blockSize,
    f64 * pResult)
{
    
    uint32_t blkCnt;                               /* Loop counter */
    f64 fSum = 0.;
    f64 fMean, fValue;
    const f64 * pInput = pSrc;
    
    if (blockSize <= 1U)
    {
        *pResult = 0;
        return;
    }
    mips_mean_f64(pInput, blockSize, &fMean);
    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;

    while (blkCnt > 0U)
    {
        fValue = *pInput++ - fMean;
        fSum += fValue * fValue;
        
        /* Decrement loop counter */
        blkCnt--;
    }
    
    /* Variance */
    *pResult = fSum / (f64)(blockSize - 1.);
}

/**
  @} end of variance group
 */
