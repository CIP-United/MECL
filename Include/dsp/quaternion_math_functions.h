/******************************************************************************
 * @file     quaternion_math_functions.h
 * @brief    Public header file for MIPS Embedded Compute Library
 * @version  V1.0.0
 * @date     31 Augest 2023
 *
 ******************************************************************************/
/*
 * Copyright (c) 2010-2021 ARM Limited or its affiliates. All rights reserved.
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

 
#ifndef _QUATERNION_MATH_FUNCTIONS_H_
#define _QUATERNION_MATH_FUNCTIONS_H_

#include "mips_math_types.h"
#include "mips_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"


#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @defgroup groupQuaternionMath Quaternion Math Functions
 * Functions to operates on quaternions and convert between a
 * rotation and quaternion representation.
 */


/**
  @brief         Floating-point quaternion Norm.
  @param[in]     pInputQuaternions       points to the input vector of quaternions
  @param[out]    pNorms                  points to the output vector of norms
  @param[in]     nbQuaternions           number of quaternions in each vector
  @return        none
 */



void mips_quaternion_norm_f32(const f32 *pInputQuaternions, 
    f32 *pNorms,
    uint32_t nbQuaternions);


/**
  @brief         Floating-point quaternion inverse.
  @param[in]     pInputQuaternions            points to the input vector of quaternions
  @param[out]    pInverseQuaternions          points to the output vector of inverse quaternions
  @param[in]     nbQuaternions                number of quaternions in each vector
  @return        none
 */

void mips_quaternion_inverse_f32(const f32 *pInputQuaternions, 
    f32 *pInverseQuaternions, 
    uint32_t nbQuaternions);

/**
  @brief         Floating-point quaternion conjugates.
  @param[in]     pInputQuaternions            points to the input vector of quaternions
  @param[out]    pConjugateQuaternions        points to the output vector of conjugate quaternions
  @param[in]     nbQuaternions                number of quaternions in each vector
  @return        none
 */
void mips_quaternion_conjugate_f32(const f32 *inputQuaternions, 
    f32 *pConjugateQuaternions, 
    uint32_t nbQuaternions);

/**
  @brief         Floating-point normalization of quaternions.
  @param[in]     pInputQuaternions            points to the input vector of quaternions
  @param[out]    pNormalizedQuaternions       points to the output vector of normalized quaternions
  @param[in]     nbQuaternions                number of quaternions in each vector
  @return        none
 */
void mips_quaternion_normalize_f32(const f32 *inputQuaternions, 
    f32 *pNormalizedQuaternions, 
    uint32_t nbQuaternions);


/**
  @brief         Floating-point product of two quaternions.
  @param[in]     qa       First quaternion
  @param[in]     qb       Second quaternion
  @param[out]    r        Product of two quaternions
  @return        none
 */
void mips_quaternion_product_single_f32(const f32 *qa, 
    const f32 *qb, 
    f32 *r);

/**
  @brief         Floating-point elementwise product two quaternions.
  @param[in]     qa                  First array of quaternions
  @param[in]     qb                  Second array of quaternions
  @param[out]    r                   Elementwise product of quaternions
  @param[in]     nbQuaternions       Number of quaternions in the array
  @return        none
 */
void mips_quaternion_product_f32(const f32 *qa, 
    const f32 *qb, 
    f32 *r,
    uint32_t nbQuaternions);

/**
 * @brief Conversion of quaternion to equivalent rotation matrix.
 * @param[in]       pInputQuaternions points to an array of normalized quaternions
 * @param[out]      pOutputRotations points to an array of 3x3 rotations (in row order)
 * @param[in]       nbQuaternions in the array
 * @return none.
 *
 * <b>Format of rotation matrix</b>
 * \par
 * The quaternion a + ib + jc + kd is converted into rotation matrix:
 *   a^2 + b^2 - c^2 - d^2                 2bc - 2ad                 2bd + 2ac
 *               2bc + 2ad     a^2 - b^2 + c^2 - d^2                 2cd - 2ab
 *               2bd - 2ac                 2cd + 2ab     a^2 - b^2 - c^2 + d^2
 *
 * Rotation matrix is saved in row order : R00 R01 R02 R10 R11 R12 R20 R21 R22
 */
void mips_quaternion2rotation_f32(const f32 *pInputQuaternions, 
    f32 *pOutputRotations, 
    uint32_t nbQuaternions);

/**
 * @brief Conversion of a rotation matrix to equivalent quaternion.
 * @param[in]       pInputRotations points to an array 3x3 rotation matrix (in row order)
 * @param[out]      pOutputQuaternions points to an array of quaternions
 * @param[in]       nbQuaternions in the array
 * @return none.
*/
void mips_rotation2quaternion_f32(const f32 *pInputRotations, 
    f32 *pOutputQuaternions,  
    uint32_t nbQuaternions);

#ifdef   __cplusplus
}
#endif

#endif /* ifndef _QUATERNION_MATH_FUNCTIONS_H_ */
