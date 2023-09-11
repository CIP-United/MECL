/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_float_to_f64.c
 * Description:  Converts the elements of the floating-point vector to floating-point 64 bit vector
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

#include "dsp/support_functions.h"




/**
  @ingroup groupSupport
 */

/**
  @addtogroup float_to_x
  @{
 */

/**
  @brief         Converts the elements of the floating-point vector to f64 vector.
  @param[in]     pSrc       points to the f32 input vector
  @param[out]    pDst       points to the f64 output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

 */

void mips_float_to_f64(
  const f32 * pSrc,
        f64 * pDst,
        uint32_t blockSize)

{
    const f32 *pIn = pSrc;      /* Src pointer */
    uint32_t  blkCnt;           /* loop counter */

    /*
     * Loop over blockSize number of values
     */
    blkCnt = blockSize;

    while (blkCnt > 0U)
    {

        *pDst++ = (f64) * pIn++;
        /*
         * Decrement the loop counter
         */
        blkCnt--;
    }
}
  


/**
  @} end of float_to_x group
 */



