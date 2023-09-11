
/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cosine_distance_f32.c
 * Description:  Cosine distance between two vectors
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

#include "dsp/distance_functions.h"
#include <limits.h>
#include <math.h>


/**
  @addtogroup CosineDist
  @{
 */



/**
 * @brief        Cosine distance between two vectors
 *
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 * @par           Description
 *                  cosine_distance(u,v) is 1 - u . v / (Norm(u) Norm(v))
 */

f32 mips_cosine_distance_f32(const f32 *pA,const f32 *pB, uint32_t blockSize)
{
    f32 pwra,pwrb,dot,tmp;

    mips_power_f32(pA, blockSize, &pwra);
    mips_power_f32(pB, blockSize, &pwrb);

    mips_dot_prod_f32(pA,pB,blockSize,&dot);

    mips_sqrt_f32(pwra * pwrb, &tmp);
    return(1.0f - dot / tmp);

}



/**
 * @} end of CosineDist group
 */
