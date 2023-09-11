/******************************************************************************
 * @file     fast_math_functions.h
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

 
#ifndef _FAST_MATH_FUNCTIONS_H_
#define _FAST_MATH_FUNCTIONS_H_

#include "mips_math_types.h"
#include "mips_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#include "dsp/basic_math_functions.h"

#include <math.h>

#ifdef   __cplusplus
extern "C"
{
#endif

  /**
   * @brief Macros required for SINE and COSINE Fast math approximations
   */

#define FAST_MATH_TABLE_SIZE  512
#define FAST_MATH_Q31_SHIFT   (32 - 10)
#define FAST_MATH_Q15_SHIFT   (16 - 10)
  
#ifndef PI
  #define PI               3.14159265358979f
#endif

#ifndef PI_F64 
  #define PI_F64 3.14159265358979323846
#endif



/**
 * @defgroup groupFastMath Fast Math Functions
 * This set of functions provides a fast approximation to sine, cosine, and square root.
 * As compared to most of the other functions in the MECL math library, the fast math functions
 * operate on individual values and not arrays.
 * There are separate functions for Q15, Q31, and floating-point data.
 *
 */


   /**
   * @brief  Fast approximation to the trigonometric sine function for floating-point data.
   * @param[in] x  input value in radians.
   * @return  sin(x).
   */
  f32 mips_sin_f32(
  f32 x);


  /**
   * @brief  Fast approximation to the trigonometric sine function for Q31 data.
   * @param[in] x  Scaled input value in radians.
   * @return  sin(x).
   */
  q31 mips_sin_q31(
  q31 x);

  /**
   * @brief  Fast approximation to the trigonometric sine function for Q15 data.
   * @param[in] x  Scaled input value in radians.
   * @return  sin(x).
   */
  q15 mips_sin_q15(
  q15 x);


  /**
   * @brief  Fast approximation to the trigonometric cosine function for floating-point data.
   * @param[in] x  input value in radians.
   * @return  cos(x).
   */
  f32 mips_cos_f32(
  f32 x);


  /**
   * @brief Fast approximation to the trigonometric cosine function for Q31 data.
   * @param[in] x  Scaled input value in radians.
   * @return  cos(x).
   */
  q31 mips_cos_q31(
  q31 x);


  /**
   * @brief  Fast approximation to the trigonometric cosine function for Q15 data.
   * @param[in] x  Scaled input value in radians.
   * @return  cos(x).
   */
  q15 mips_cos_q15(
  q15 x);


/**
  @brief         Floating-point vector of log values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
  void mips_vlog_f32(
  const f32 * pSrc,
        f32 * pDst,
        uint32_t blockSize);



/**
  @brief         Floating-point vector of log values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
  void mips_vlog_f64(
  const f64 * pSrc,
        f64 * pDst,
        uint32_t blockSize);



  /**
   * @brief  q31 vector of log values.
   * @param[in]     pSrc       points to the input vector in q31
   * @param[out]    pDst       points to the output vector in q5.26
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void mips_vlog_q31(const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize);

  /**
   * @brief  q15 vector of log values.
   * @param[in]     pSrc       points to the input vector in q15
   * @param[out]    pDst       points to the output vector in q4.11
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void mips_vlog_q15(const q15 * pSrc,
        q15 * pDst,
        uint32_t blockSize);



/**
  @brief         Floating-point vector of exp values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
  void mips_vexp_f32(
  const f32 * pSrc,
        f32 * pDst,
        uint32_t blockSize);



/**
  @brief         Floating-point vector of exp values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
  void mips_vexp_f64(
  const f64 * pSrc,
		f64 * pDst,
		uint32_t blockSize);



 /**
   * @defgroup SQRT Square Root
   *
   * Computes the square root of a number.
   * There are separate functions for Q15, Q31, and floating-point data types.
   * The square root function is computed using the Newton-Raphson algorithm.
   * This is an iterative algorithm of the form:
   * <pre>
   *      x1 = x0 - f(x0)/f'(x0)
   * </pre>
   * where <code>x1</code> is the current estimate,
   * <code>x0</code> is the previous estimate, and
   * <code>f'(x0)</code> is the derivative of <code>f()</code> evaluated at <code>x0</code>.
   * For the square root function, the algorithm reduces to:
   * <pre>
   *     x0 = in/2                         [initial guess]
   *     x1 = 1/2 * ( x0 + in / x0)        [each iteration]
   * </pre>
   */


  /**
   * @addtogroup SQRT
   * @{
   */

/**
  @brief         Floating-point square root function.
  @param[in]     in    input value
  @param[out]    pOut  square root of input value
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS        : input value is positive
                   - \ref MIPS_MATH_ARGUMENT_ERROR : input value is negative; *pOut is set to 0
 */
__STATIC_FORCEINLINE mips_status mips_sqrt_f32(
  const f32 in,
  f32 * pOut)
  {
    if (in >= 0.0f)
    {
      *pOut = sqrtf(in);
      return (MIPS_MATH_SUCCESS);
    }
    else
    {
      *pOut = 0.0f;
      return (MIPS_MATH_ARGUMENT_ERROR);
    }
  }


/**
  @brief         Q31 square root function.
  @param[in]     in    input value.  The range of the input value is [0 +1) or 0x00000000 to 0x7FFFFFFF
  @param[out]    pOut  points to square root of input value
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS        : input value is positive
                   - \ref MIPS_MATH_ARGUMENT_ERROR : input value is negative; *pOut is set to 0
 */
mips_status mips_sqrt_q31(
  q31 in,
  q31 * pOut);


/**
  @brief         Q15 square root function.
  @param[in]     in    input value.  The range of the input value is [0 +1) or 0x0000 to 0x7FFF
  @param[out]    pOut  points to square root of input value
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS        : input value is positive
                   - \ref MIPS_MATH_ARGUMENT_ERROR : input value is negative; *pOut is set to 0
 */
mips_status mips_sqrt_q15(
  q15 in,
  q15 * pOut);



  /**
   * @} end of SQRT group
   */

  /**
  @brief         Fixed point division
  @param[in]     numerator    Numerator
  @param[in]     denominator  Denominator
  @param[out]    quotient     Quotient value normalized between -1.0 and 1.0
  @param[out]    shift        Shift left value to get the unnormalized quotient
  @return        error status

  When dividing by 0, an error MIPS_MATH_NANINF is returned. And the quotient is forced
  to the saturated negative or positive value.
 */

mips_status mips_divide_q15(q15 numerator,
  q15 denominator,
  q15 *quotient,
  int16_t *shift);

  /**
  @brief         Fixed point division
  @param[in]     numerator    Numerator
  @param[in]     denominator  Denominator
  @param[out]    quotient     Quotient value normalized between -1.0 and 1.0
  @param[out]    shift        Shift left value to get the unnormalized quotient
  @return        error status

  When dividing by 0, an error MIPS_MATH_NANINF is returned. And the quotient is forced
  to the saturated negative or positive value.
 */

mips_status mips_divide_q31(q31 numerator,
  q31 denominator,
  q31 *quotient,
  int16_t *shift);



  /**
     @brief  Arc tangent in radian of y/x using sign of x and y to determine right quadrant.
     @param[in]   y  y coordinate
     @param[in]   x  x coordinate
     @param[out]  result  Result
     @return  error status.
   */
  mips_status mips_atan2_f32(f32 y,f32 x,f32 *result);


  /**
     @brief  Arc tangent in radian of y/x using sign of x and y to determine right quadrant.
     @param[in]   y  y coordinate
     @param[in]   x  x coordinate
     @param[out]  result  Result in Q2.29
     @return  error status.
   */
  mips_status mips_atan2_q31(q31 y,q31 x,q31 *result);

  /**
     @brief  Arc tangent in radian of y/x using sign of x and y to determine right quadrant.
     @param[in]   y  y coordinate
     @param[in]   x  x coordinate
     @param[out]  result  Result in Q2.13
     @return  error status.
   */
  mips_status mips_atan2_q15(q15 y,q15 x,q15 *result);

#ifdef   __cplusplus
}
#endif

#endif /* ifndef _FAST_MATH_FUNCTIONS_H_ */
