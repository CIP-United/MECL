/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_logsumexp_f32.c
 * Description:  LogSumExp
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
#include <limits.h>
#include <math.h>


/**
 * @addtogroup Entropy
 * @{
 */


/**
 * @brief Entropy
 *
 * @param[in]  pSrcA        Array of input values.
 * @param[in]  blockSize    Number of samples in the input array.
 * @return     Entropy      -Sum(p ln p)
 *
 */

f32 mips_entropy_f32(const f32 * pSrcA,uint32_t blockSize)
{
    const f32 *pIn;
    uint32_t blkCnt;
    f32 accum, p;
 
    pIn = pSrcA;
    blkCnt = blockSize;

    accum = 0.0f;

    while(blkCnt > 0)
    {
       p = *pIn++;
       accum += p * logf(p);
       
       blkCnt--;
    
    }

    return(-accum);
}


/**
 * @} end of Entropy group
 */
