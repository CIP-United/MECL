/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_not_u32.c
 * Description:  uint32_t bitwise NOT
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

#include "dsp/basic_math_functions.h"

/**
  @ingroup groupMath
 */

/**
  @addtogroup Not
  @{
 */

/**
  @brief         Compute the logical bitwise NOT of a fixed-point vector.
  @param[in]     pSrc       points to input vector 
  @param[out]    pDst       points to output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */

void mips_not_u32(
    const uint32_t * pSrc,
          uint32_t * pDst,
          uint32_t blockSize)
{
    uint32_t blkCnt;      /* Loop counter */

    blkCnt = blockSize;


    while (blkCnt > 0U)
    {
        *pDst++ = ~(*pSrc++);

        /* Decrement the loop counter */
        blkCnt--;
    }
}

/**
  @} end of Not group
 */
