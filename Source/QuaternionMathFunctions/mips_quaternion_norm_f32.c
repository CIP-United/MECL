/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_quaternion_norm_f32.c
 * Description:  Floating-point quaternion Norm
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
  @defgroup QuatNorm Quaternion Norm

  Compute the norm of a quaternion.
 */

/**
  @addtogroup QuatNorm
  @{
 */

/**
  @brief         Floating-point quaternion Norm.
  @param[in]     pInputQuaternions       points to the input vector of quaternions
  @param[out]    pNorms                  points to the output vector of norms
  @param[in]     nbQuaternions           number of quaternions in the input vector
  @return        none
 */



void mips_quaternion_norm_f32(const f32 *pInputQuaternions, 
  f32 *pNorms,
  uint32_t nbQuaternions)
{
   f32 temp;
   uint32_t i;

   for(i=0; i < nbQuaternions; i++)
   {
      temp = SQ(pInputQuaternions[4 * i + 0]) +
             SQ(pInputQuaternions[4 * i + 1]) +
             SQ(pInputQuaternions[4 * i + 2]) +
             SQ(pInputQuaternions[4 * i + 3]);
      pNorms[i] = sqrtf(temp);
   }
}

/**
  @} end of QuatNorm group
 */
