/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_quaternion_product_f32.c
 * Description:  Floating-point quaternion product
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

#include "dsp/quaternion_math_functions.h"
#include <math.h>

/**
  @ingroup groupQuaternionMath
 */

/**
  @defgroup QuatProd Quaternion Product

  Compute the product of quaternions.
 */

/**
  @ingroup QuatProd
 */

/**
  @defgroup QuatProdVect Elementwise Quaternion Product

  Compute the elementwise product of quaternions.
 */

/**
  @addtogroup QuatProdVect
  @{
 */

/**
  @brief         Floating-point elementwise product two quaternions.
  @param[in]     qa                  first array of quaternions
  @param[in]     qb                  second array of quaternions
  @param[out]    qr                   elementwise product of quaternions
  @param[in]     nbQuaternions       number of quaternions in the array
  @return        none
 */


void mips_quaternion_product_f32(const f32 *qa, 
    const f32 *qb, 
    f32 *qr,
    uint32_t nbQuaternions)
{
   uint32_t i;
   for(i=0; i < nbQuaternions; i++)
   {
     mips_quaternion_product_single_f32(qa, qb, qr);

     qa += 4;
     qb += 4;
     qr += 4;
   }
}

/**
  @} end of QuatProdVect group
 */
