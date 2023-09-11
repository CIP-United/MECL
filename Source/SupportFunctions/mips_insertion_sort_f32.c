/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_insertion_sort_f32.c
 * Description:  Floating point insertion sort
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

#include "dsp/support_functions.h"
#include "mips_sorting.h"

/**
  @ingroup groupSupport
 */

/**
  @addtogroup Sorting
  @{
 */

/**
   * @private
   * @param[in]  S          points to an instance of the sorting structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   *
   * @par        Algorithm
   *               The insertion sort is a simple sorting algorithm that
   *               reads all the element of the input array and removes one element 
   *               at a time, finds the location it belongs in the final sorted list, 
   *               and inserts it there. 
   *
   * @par          It's an in-place algorithm. In order to obtain an out-of-place
   *               function, a memcpy of the source vector is performed.
   */

void mips_insertion_sort_f32(
  const mips_sort_instance_f32 * S, 
        f32 *pSrc, 
        f32* pDst, 
        uint32_t blockSize)
{
    f32 * pA;
    uint8_t dir = S->dir;
    uint32_t i, j;
    f32 temp;

    if(pSrc != pDst) // out-of-place
    {   
        memcpy(pDst, pSrc, blockSize*sizeof(f32) );
        pA = pDst;
    }
    else
        pA = pSrc;
 
    // Real all the element of the input array
    for(i=0; i<blockSize; i++)
    {
	// Move the i-th element to the right position
        for (j = i; j>0 && dir==(pA[j]<pA[j-1]); j--)
        {
	    // Swap
            temp = pA[j];
	    pA[j] = pA[j-1];
	    pA[j-1] = temp;
        }
    }
} 

/**
  @} end of Sorting group
 */
