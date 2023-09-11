/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_quaternion_normalize_f32.c
 * Description:  Floating-point quaternion normalization
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
  @defgroup QuatNormalized Quaternion normalization

  Compute a normalized quaternion.
 */

/**
  @addtogroup QuatNormalized
  @{
 */

/**
  @brief         Floating-point normalization of quaternions.
  @param[in]     pInputQuaternions            points to the input vector of quaternions
  @param[out]    pNormalizedQuaternions       points to the output vector of normalized quaternions
  @param[in]     nbQuaternions                number of quaternions in each vector
  @return        none
 */


void mips_quaternion_normalize_f32(const f32 *pInputQuaternions, 
    f32 *pNormalizedQuaternions, 
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
      temp = sqrtf(temp);

      pNormalizedQuaternions[4 * i + 0] = pInputQuaternions[4 * i + 0] / temp;
      pNormalizedQuaternions[4 * i + 1] = pInputQuaternions[4 * i + 1] / temp;
      pNormalizedQuaternions[4 * i + 2] = pInputQuaternions[4 * i + 2] / temp;
      pNormalizedQuaternions[4 * i + 3] = pInputQuaternions[4 * i + 3] / temp;
   }
}

/**
  @} end of QuatNormalized group
 */
