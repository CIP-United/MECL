/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_bitonic_sort_f32.c
 * Description:  Floating point bitonic sort
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



static void mips_bitonic_sort_core_f32(f32 *pSrc, uint32_t n, uint8_t dir)
{
    uint32_t step;
    uint32_t k, j;
    f32 *leftPtr, *rightPtr;
    f32 temp;

    step = n>>1;
    leftPtr = pSrc;
    rightPtr = pSrc+n-1;

    for(k=0; k<step; k++)
    {
	if(dir == (*leftPtr > *rightPtr))
	{
            // Swap
	    temp=*leftPtr;
	    *leftPtr=*rightPtr;
	    *rightPtr=temp;
	}

	leftPtr++;  // Move right
	rightPtr--; // Move left
    }

    // Merge
    for(step=(n>>2); step>0; step/=2)
    {
	for(j=0; j<n; j=j+step*2)
	{
	    leftPtr  = pSrc+j;
	    rightPtr = pSrc+j+step;

	    for(k=0; k<step; k++)
	    {
		if(*leftPtr > *rightPtr)
		{
		    // Swap
	    	    temp=*leftPtr;
		    *leftPtr=*rightPtr;
		    *rightPtr=temp;
		}

		leftPtr++;
		rightPtr++;
	    }
	}
    }
}


/**
  @ingroup groupSupport
 */

/**
  @defgroup Sorting Vector sorting algorithms

  Sort the elements of a vector

  There are separate functions for floating-point, Q31, Q15, and Q7 data types.
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
   */
void mips_bitonic_sort_f32(
const mips_sort_instance_f32 * S, 
      f32 * pSrc,
      f32 * pDst, 
      uint32_t blockSize)
{
    uint16_t s, i;
    uint8_t dir = S->dir;

    f32 * pA;

    if(pSrc != pDst) // out-of-place
    {   
        memcpy(pDst, pSrc, blockSize*sizeof(f32) );
        pA = pDst;
    }
    else
        pA = pSrc;


    if( (blockSize & (blockSize-1)) == 0 ) // Powers of 2 only
    {
        for(s=2; s<=blockSize; s=s*2)
        {
    	    for(i=0; i<blockSize; i=i+s)
    	        mips_bitonic_sort_core_f32(pA+i, s, dir);
        }
    }
}

/**
  @} end of Sorting group
 */
