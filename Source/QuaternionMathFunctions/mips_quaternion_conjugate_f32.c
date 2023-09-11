/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_quaternion_conjugate_f32.c
 * Description:  Floating-point quaternion conjugate
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
  @defgroup QuatConjugate Quaternion Conjugate

  Compute the conjugate of a quaternion.
 */

/**
  @addtogroup QuatConjugate
  @{
 */

/**
  @brief         Floating-point quaternion conjugates.
  @param[in]     pInputQuaternions            points to the input vector of quaternions
  @param[out]    pConjugateQuaternions        points to the output vector of conjugate quaternions
  @param[in]     nbQuaternions                number of quaternions in each vector
  @return        none
 */



void mips_quaternion_conjugate_f32(const f32 *pInputQuaternions, 
    f32 *pConjugateQuaternions, 
    uint32_t nbQuaternions)
{
   uint32_t i;
   for(i=0; i < nbQuaternions; i++)
   {

      pConjugateQuaternions[4 * i + 0] = pInputQuaternions[4 * i + 0];
      pConjugateQuaternions[4 * i + 1] = -pInputQuaternions[4 * i + 1];
      pConjugateQuaternions[4 * i + 2] = -pInputQuaternions[4 * i + 2];
      pConjugateQuaternions[4 * i + 3] = -pInputQuaternions[4 * i + 3];
   }
}

/**
  @} end of QuatConjugate group
 */
