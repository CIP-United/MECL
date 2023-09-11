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
 * @addtogroup Kullback-Leibler
 * @{
 */


/**
 * @brief Kullback-Leibler
 *
 * Distribution A may contain 0 with Neon version.
 * Result will be right but some exception flags will be set.
 *
 * Distribution B must not contain 0 probability.
 *
 * @param[in]  *pSrcA         points to an array of input values for probaility distribution A.
 * @param[in]  *pSrcB         points to an array of input values for probaility distribution B.
 * @param[in]  blockSize      number of samples in the input array.
 * @return Kullback-Leibler divergence D(A || B)
 *
 */
f32 mips_kullback_leibler_f32(const f32 * pSrcA,const f32 * pSrcB,uint32_t blockSize)
{
    const f32 *pInA, *pInB;
    uint32_t blkCnt;
    f32 accum, pA,pB;
 
    pInA = pSrcA;
    pInB = pSrcB;
    blkCnt = blockSize;

    accum = 0.0f;

    while(blkCnt > 0)
    {
       pA = *pInA++;
       pB = *pInB++;
       accum += pA * logf(pB / pA);
       
       blkCnt--;
    
    }

    return(-accum);
}

/**
 * @} end of Kullback-Leibler group
 */
