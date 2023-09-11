/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_max_no_idx_f64.c
 * Description:  Maximum value of a floating-point vector without returning the index
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
  @addtogroup Max
  @{
 */

/**
  @brief         Maximum value of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    maximum value returned here
  @return        none
 */
void mips_max_no_idx_f64(
    const f64 *pSrc,
    uint32_t   blockSize,
    f64 *pResult)
{
    f64   maxValue = F64_MIN;
    f64   newVal;
    
    while (blockSize > 0U)
    {
        newVal = *pSrc++;
        
        /* compare for the maximum value */
        if (maxValue < newVal)
        {
            /* Update the maximum value and it's index */
            maxValue = newVal;
        }
        
        blockSize --;
    }
    
    *pResult = maxValue;
}


/**
  @} end of Max group
 */
