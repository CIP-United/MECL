/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_quaternion2rotation_f32.c
 * Description:  Floating-point quaternion 2 rotation conversion
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
  @defgroup QuatConv Quaternion conversions

  Conversions between quaternion and rotation representations.
 */

/**
  @ingroup QuatConv
 */

/**
  @defgroup QuatRot Quaternion to Rotation

  Conversions from quaternion to rotation.
 */

/**
  @addtogroup QuatRot
  @{
 */

/**
   @brief Conversion of quaternion to equivalent rotation matrix.
   @param[in]       pInputQuaternions points to an array of normalized quaternions
   @param[out]      pOutputRotations points to an array of 3x3 rotations (in row order)
   @param[in]       nbQuaternions number of quaternions in the array
   @return none.
  
   @par
   Format of rotation matrix
   
   
   The quaternion a + ib + jc + kd is converted into rotation matrix:
   <pre>
     a^2 + b^2 - c^2 - d^2                 2bc - 2ad                 2bd + 2ac
                 2bc + 2ad     a^2 - b^2 + c^2 - d^2                 2cd - 2ab
                 2bd - 2ac                 2cd + 2ab     a^2 - b^2 - c^2 + d^2
   </pre>
   Rotation matrix is saved in row order : R00 R01 R02 R10 R11 R12 R20 R21 R22
 */


void mips_quaternion2rotation_f32(const f32 *pInputQuaternions, 
    f32 *pOutputRotations, 
    uint32_t nbQuaternions)
{
   uint32_t nb;
   for(nb=0; nb < nbQuaternions; nb++)
   {
        f32 q00 = SQ(pInputQuaternions[0 + nb * 4]);
        f32 q11 = SQ(pInputQuaternions[1 + nb * 4]);
        f32 q22 = SQ(pInputQuaternions[2 + nb * 4]);
        f32 q33 = SQ(pInputQuaternions[3 + nb * 4]);
        f32 q01 =  pInputQuaternions[0 + nb * 4]*pInputQuaternions[1 + nb * 4];
        f32 q02 =  pInputQuaternions[0 + nb * 4]*pInputQuaternions[2 + nb * 4];
        f32 q03 =  pInputQuaternions[0 + nb * 4]*pInputQuaternions[3 + nb * 4];
        f32 q12 =  pInputQuaternions[1 + nb * 4]*pInputQuaternions[2 + nb * 4];
        f32 q13 =  pInputQuaternions[1 + nb * 4]*pInputQuaternions[3 + nb * 4];
        f32 q23 =  pInputQuaternions[2 + nb * 4]*pInputQuaternions[3 + nb * 4];

        f32 xx = q00 + q11 - q22 - q33;
        f32 yy = q00 - q11 + q22 - q33;
        f32 zz = q00 - q11 - q22 + q33;
        f32 xy = 2*(q12 - q03);
        f32 xz = 2*(q13 + q02);
        f32 yx = 2*(q12 + q03);
        f32 yz = 2*(q23 - q01);
        f32 zx = 2*(q13 - q02);
        f32 zy = 2*(q23 + q01);

        pOutputRotations[0 + nb * 9] = xx; pOutputRotations[1 + nb * 9] = xy; pOutputRotations[2 + nb * 9] = xz;
        pOutputRotations[3 + nb * 9] = yx; pOutputRotations[4 + nb * 9] = yy; pOutputRotations[5 + nb * 9] = yz;
        pOutputRotations[6 + nb * 9] = zx; pOutputRotations[7 + nb * 9] = zy; pOutputRotations[8 + nb * 9] = zz;
   }
}

/**
  @} end of QuatRot group
 */
