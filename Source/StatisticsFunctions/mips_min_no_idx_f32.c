/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_min_no_idx_f32.c
 * Description:  Minimum value of a floating-point vector without returning the index
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
  @addtogroup Min
  @{
 */

/**
  @brief         Minimum value of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    minimum value returned here
  @return        none
 */

void mips_min_no_idx_f32(
    const f32 *pSrc,
    uint32_t   blockSize,
    f32 *pResult)
{
   f32   minValue = F32_MAX;
   f32   newVal;

   while (blockSize > 0U)
   {
       newVal = *pSrc++;
   
       /* compare for the minimum value */
       if (minValue > newVal)
       {
           /* Update the minimum value and it's index */
           minValue = newVal;
       }
   
       blockSize --;
   }
    
   *pResult = minValue;
}


/**
  @} end of Min group
 */
