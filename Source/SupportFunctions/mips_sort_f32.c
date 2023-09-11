/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_sort_f32.c
 * Description:  Floating point sort
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

#include "mips_sorting.h"

/**
  @ingroup groupSupport
 */

/**
  @addtogroup Sorting
  @{
 */


/**
 * @brief Generic sorting function
 *
 * @param[in]  S          points to an instance of the sorting structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */

void mips_sort_f32(
  const mips_sort_instance_f32 * S, 
        f32 * pSrc, 
        f32 * pDst, 
        uint32_t blockSize)
{
    switch(S->alg)
    {
        case MIPS_SORT_BITONIC:
        mips_bitonic_sort_f32(S, pSrc, pDst, blockSize);
        break;

        case MIPS_SORT_BUBBLE:
        mips_bubble_sort_f32(S, pSrc, pDst, blockSize);
        break;

        case MIPS_SORT_HEAP:
        mips_heap_sort_f32(S, pSrc, pDst, blockSize);
        break;

        case MIPS_SORT_INSERTION:
        mips_insertion_sort_f32(S, pSrc, pDst, blockSize);
        break;

        case MIPS_SORT_QUICK:
        mips_quick_sort_f32(S, pSrc, pDst, blockSize);
        break;

        case MIPS_SORT_SELECTION:
        mips_selection_sort_f32(S, pSrc, pDst, blockSize);
        break;
    }
}

/**
  @} end of Sorting group
 */
