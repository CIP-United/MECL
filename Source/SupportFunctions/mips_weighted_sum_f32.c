/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_weighted_sum_f32.c
 * Description:  Weighted Sum
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

#include <limits.h>
#include <math.h>

#include "dsp/support_functions.h"

/**
 * @addtogroup weightedsum
 * @{
 */


/**
 * @brief Weighted sum
 *
 *
 * @param[in]    *in           Array of input values.
 * @param[in]    *weigths      Weights
 * @param[in]    blockSize     Number of samples in the input array.
 * @return       Weighted sum
 *
 */


f32 mips_weighted_sum_f32(const f32 *in, const f32 *weigths, uint32_t blockSize)
{

    f32 accum1, accum2;
    const f32 *pIn, *pW;
    uint32_t blkCnt;


    pIn = in;
    pW = weigths;

    accum1=0.0f;
    accum2=0.0f;

    blkCnt = blockSize;
    while(blkCnt > 0)
    {
        accum1 += *pIn++ * *pW;
        accum2 += *pW++;
        blkCnt--;
    }

    return(accum1 / accum2);
}


/**
 * @} end of weightedsum group
 */
