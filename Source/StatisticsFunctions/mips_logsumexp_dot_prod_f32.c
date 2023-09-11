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
 * @addtogroup LogSumExp
 * @{
 */


/**
 * @brief Dot product with log arithmetic
 *
 * Vectors are containing the log of the samples
 *
 * @param[in]       *pSrcA points to the first input vector
 * @param[in]       *pSrcB points to the second input vector
 * @param[in]       blockSize number of samples in each vector
 * @param[in]       *pTmpBuffer temporary buffer of length blockSize
 * @return The log of the dot product.
 *
 */


f32 mips_logsumexp_dot_prod_f32(const f32 * pSrcA,
  const f32 * pSrcB,
  uint32_t blockSize,
  f32 *pTmpBuffer)
{
    f32 result;
    mips_add_f32((f32*)pSrcA, (f32*)pSrcB, pTmpBuffer, blockSize);

    result = mips_logsumexp_f32(pTmpBuffer, blockSize);
    return(result);
}

/**
 * @} end of LogSumExp group
 */
