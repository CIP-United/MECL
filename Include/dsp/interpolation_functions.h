/******************************************************************************
 * @file     interpolation_functions.h
 * @brief    Public header file for MIPS Embedded Compute Library
 * @version  V1.0.0
 * @date     31 Augest 2023
 ******************************************************************************/
/*
 * Copyright (c) 2010-2020 Arm Limited or its affiliates. All rights reserved.
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

 
#ifndef _INTERPOLATION_FUNCTIONS_H_
#define _INTERPOLATION_FUNCTIONS_H_

#include "mips_math_types.h"
#include "mips_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#ifdef   __cplusplus
extern "C"
{
#endif


/**
 * @defgroup groupInterpolation Interpolation Functions
 * These functions perform 1- and 2-dimensional interpolation of data.
 * Linear interpolation is used for 1-dimensional data and
 * bilinear interpolation is used for 2-dimensional data.
 */


  /**
   * @brief Instance structure for the floating-point Linear Interpolate function.
   */
  typedef struct
  {
          uint32_t nValues;           /**< nValues */
          f32 x1;               /**< x1 */
          f32 xSpacing;         /**< xSpacing */
          f32 *pYData;          /**< pointer to the table of Y values */
  } mips_linear_interp_instance_f32;

  /**
   * @brief Instance structure for the floating-point bilinear interpolation function.
   */
  typedef struct
  {
          uint16_t numRows;   /**< number of rows in the data table. */
          uint16_t numCols;   /**< number of columns in the data table. */
          f32 *pData;   /**< points to the data table. */
  } mips_bilinear_interp_instance_f32;

   /**
   * @brief Instance structure for the Q31 bilinear interpolation function.
   */
  typedef struct
  {
          uint16_t numRows;   /**< number of rows in the data table. */
          uint16_t numCols;   /**< number of columns in the data table. */
          q31 *pData;       /**< points to the data table. */
  } mips_bilinear_interp_instance_q31;

   /**
   * @brief Instance structure for the Q15 bilinear interpolation function.
   */
  typedef struct
  {
          uint16_t numRows;   /**< number of rows in the data table. */
          uint16_t numCols;   /**< number of columns in the data table. */
          q15 *pData;       /**< points to the data table. */
  } mips_bilinear_interp_instance_q15;

   /**
   * @brief Instance structure for the Q15 bilinear interpolation function.
   */
  typedef struct
  {
          uint16_t numRows;   /**< number of rows in the data table. */
          uint16_t numCols;   /**< number of columns in the data table. */
          q7 *pData;        /**< points to the data table. */
  } mips_bilinear_interp_instance_q7;


  /**
   * @brief Struct for specifying cubic spline type
   */
  typedef enum
  {
    MIPS_SPLINE_NATURAL = 0,           /**< Natural spline */
    MIPS_SPLINE_PARABOLIC_RUNOUT = 1   /**< Parabolic runout spline */
  } mips_spline_type;

  /**
   * @brief Instance structure for the floating-point cubic spline interpolation.
   */
  typedef struct
  {
    mips_spline_type type;      /**< Type (boundary conditions) */
    const f32 * x;       /**< x values */
    const f32 * y;       /**< y values */
    uint32_t n_x;              /**< Number of known data points */
    f32 * coeffs;        /**< Coefficients buffer (b,c, and d) */
  } mips_spline_instance_f32;


  /**
   * @brief Processing function for the floating-point cubic spline interpolation.
   * @param[in]  S          points to an instance of the floating-point spline structure.
   * @param[in]  xq         points to the x values ot the interpolated data points.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples of output data.
   */
  void mips_spline_f32(
        mips_spline_instance_f32 * S, 
  const f32 * xq,
        f32 * pDst,
        uint32_t blockSize);

  /**
   * @brief Initialization function for the floating-point cubic spline interpolation.
   * @param[in,out] S        points to an instance of the floating-point spline structure.
   * @param[in]     type     type of cubic spline interpolation (boundary conditions)
   * @param[in]     x        points to the x values of the known data points.
   * @param[in]     y        points to the y values of the known data points.
   * @param[in]     n        number of known data points.
   * @param[in]     coeffs   coefficients array for b, c, and d
   * @param[in]     tempBuffer   buffer array for internal computations
   */
  void mips_spline_init_f32(
          mips_spline_instance_f32 * S,
          mips_spline_type type,
    const f32 * x,
    const f32 * y,
          uint32_t n, 
          f32 * coeffs,
          f32 * tempBuffer);


   /**
   * @brief  Process function for the floating-point Linear Interpolation Function.
   * @param[in,out] S  is an instance of the floating-point Linear Interpolation structure
   * @param[in]     x  input sample to process
   * @return y processed output sample.
   *
   */
  f32 mips_linear_interp_f32(
  mips_linear_interp_instance_f32 * S,
  f32 x);

   /**
   *
   * @brief  Process function for the Q31 Linear Interpolation Function.
   * @param[in] pYData   pointer to Q31 Linear Interpolation table
   * @param[in] x        input sample to process
   * @param[in] nValues  number of table values
   * @return y processed output sample.
   *
   * \par
   * Input sample <code>x</code> is in 12.20 format which contains 12 bits for table index and 20 bits for fractional part.
   * This function can support maximum of table size 2^12.
   *
   */
  q31 mips_linear_interp_q31(
  const q31 * pYData,
  q31 x,
  uint32_t nValues);

  /**
   *
   * @brief  Process function for the Q15 Linear Interpolation Function.
   * @param[in] pYData   pointer to Q15 Linear Interpolation table
   * @param[in] x        input sample to process
   * @param[in] nValues  number of table values
   * @return y processed output sample.
   *
   * \par
   * Input sample <code>x</code> is in 12.20 format which contains 12 bits for table index and 20 bits for fractional part.
   * This function can support maximum of table size 2^12.
   *
   */
  q15 mips_linear_interp_q15(
  const q15 * pYData,
  q31 x,
  uint32_t nValues);

  /**
   *
   * @brief  Process function for the Q7 Linear Interpolation Function.
   * @param[in] pYData   pointer to Q7 Linear Interpolation table
   * @param[in] x        input sample to process
   * @param[in] nValues  number of table values
   * @return y processed output sample.
   *
   * \par
   * Input sample <code>x</code> is in 12.20 format which contains 12 bits for table index and 20 bits for fractional part.
   * This function can support maximum of table size 2^12.
   */
q7 mips_linear_interp_q7(
  const q7 * pYData,
  q31 x,
  uint32_t nValues);

  /**
  * @brief  Floating-point bilinear interpolation.
  * @param[in,out] S  points to an instance of the interpolation structure.
  * @param[in]     X  interpolation coordinate.
  * @param[in]     Y  interpolation coordinate.
  * @return out interpolated value.
  */
  f32 mips_bilinear_interp_f32(
  const mips_bilinear_interp_instance_f32 * S,
  f32 X,
  f32 Y);

  /**
  * @brief  Q31 bilinear interpolation.
  * @param[in,out] S  points to an instance of the interpolation structure.
  * @param[in]     X  interpolation coordinate in 12.20 format.
  * @param[in]     Y  interpolation coordinate in 12.20 format.
  * @return out interpolated value.
  */
  q31 mips_bilinear_interp_q31(
  mips_bilinear_interp_instance_q31 * S,
  q31 X,
  q31 Y);


  /**
  * @brief  Q15 bilinear interpolation.
  * @param[in,out] S  points to an instance of the interpolation structure.
  * @param[in]     X  interpolation coordinate in 12.20 format.
  * @param[in]     Y  interpolation coordinate in 12.20 format.
  * @return out interpolated value.
  */
  q15 mips_bilinear_interp_q15(
  mips_bilinear_interp_instance_q15 * S,
  q31 X,
  q31 Y);

  /**
  * @brief  Q7 bilinear interpolation.
  * @param[in,out] S  points to an instance of the interpolation structure.
  * @param[in]     X  interpolation coordinate in 12.20 format.
  * @param[in]     Y  interpolation coordinate in 12.20 format.
  * @return out interpolated value.
  */
  q7 mips_bilinear_interp_q7(
  mips_bilinear_interp_instance_q7 * S,
  q31 X,
  q31 Y);


#ifdef   __cplusplus
}
#endif

#endif /* ifndef _INTERPOLATION_FUNCTIONS_H_ */
