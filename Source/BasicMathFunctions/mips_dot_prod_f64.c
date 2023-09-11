/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_dot_prod_f64.c
 * Description:  Floating-point dot product
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
  @addtogroup BasicDotProd
  @{
 */

/**
  @brief         Dot product of floating-point vectors.
  @param[in]     pSrcA      points to the first input vector.
  @param[in]     pSrcB      points to the second input vector.
  @param[in]     blockSize  number of samples in each vector.
  @param[out]    result     output result returned here.
  @return        none
 */

      
void mips_dot_prod_f64(
    const f64 * pSrcA,
    const f64 * pSrcB,
    uint32_t blockSize,
    f64 * result)
{
    uint32_t blkCnt;                               /* Loop counter */
    f64 sum = 0.;                            /* Temporary return variable */
    
    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;
    
    while (blkCnt > 0U)
    {
        /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */
        
        /* Calculate dot product and store result in a temporary buffer. */
        sum += (*pSrcA++) * (*pSrcB++);
        
        /* Decrement loop counter */
        blkCnt--;
    }
    
    /* Store result in destination buffer */
    *result = sum;
}

/**
  @} end of BasicDotProd group
 */
