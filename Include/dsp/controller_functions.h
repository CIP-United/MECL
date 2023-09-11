/******************************************************************************
 * @file     controller_functions.h
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

 
#ifndef _CONTROLLER_FUNCTIONS_H_
#define _CONTROLLER_FUNCTIONS_H_

#include "mips_math_types.h"
#include "mips_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#ifdef   __cplusplus
extern "C"
{
#endif

  /**
   * @brief Macros required for SINE and COSINE Controller functions
   */

#define CONTROLLER_Q31_SHIFT  (32 - 9)
  /* 1.31(q31) Fixed value of 2/360 */
  /* -1 to +1 is divided into 360 values so total spacing is (2/360) */
#define INPUT_SPACING         0xB60B61
  
/**
 * @defgroup groupController Controller Functions
 */


/**
  @ingroup groupController
 */

/**
  @defgroup SinCos Sine Cosine

  Computes the trigonometric sine and cosine values using a combination of table lookup
  and linear interpolation.
  There are separate functions for Q31 and floating-point data types.
  The input to the floating-point version is in degrees while the
  fixed-point Q31 have a scaled input with the range
  [-1 0.9999] mapping to [-180 +180] degrees.

  The floating point function also allows values that are out of the usual range. When this happens, the function will
  take extra time to adjust the input value to the range of [-180 180].

  The result is accurate to 5 digits after the decimal point.

  The implementation is based on table lookup using 360 values together with linear interpolation.
  The steps used are:
   -# Calculation of the nearest integer table index.
   -# Compute the fractional portion (fract) of the input.
   -# Fetch the value corresponding to \c index from sine table to \c y0 and also value from \c index+1 to \c y1.
   -# Sine value is computed as <code> *psinVal = y0 + (fract * (y1 - y0))</code>.
   -# Fetch the value corresponding to \c index from cosine table to \c y0 and also value from \c index+1 to \c y1.
   -# Cosine value is computed as <code> *pcosVal = y0 + (fract * (y1 - y0))</code>.
 */
 
/**
   * @brief  Floating-point sin_cos function.
   * @param[in]  theta   input value in degrees
   * @param[out] pSinVal  points to the processed sine output.
   * @param[out] pCosVal  points to the processed cos output.
   */
  void mips_sin_cos_f32(
        f32 theta,
        f32 * pSinVal,
        f32 * pCosVal);


  /**
   * @brief  Q31 sin_cos function.
   * @param[in]  theta    scaled input value in degrees
   * @param[out] pSinVal  points to the processed sine output.
   * @param[out] pCosVal  points to the processed cosine output.
   */
  void mips_sin_cos_q31(
        q31 theta,
        q31 * pSinVal,
        q31 * pCosVal);


/**
  @ingroup groupController
 */
  
/**
   * @defgroup PID PID Motor Control
   *
   * A Proportional Integral Derivative (PID) controller is a generic feedback control
   * loop mechanism widely used in industrial control systems.
   * A PID controller is the most commonly used type of feedback controller.
   *
   * This set of functions implements (PID) controllers
   * for Q15, Q31, and floating-point data types.  The functions operate on a single sample
   * of data and each call to the function returns a single processed value.
   * <code>S</code> points to an instance of the PID control data structure.  <code>in</code>
   * is the input sample value. The functions return the output value.
   *
   * \par Algorithm:
   * <pre>
   *    y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
   *    A0 = Kp + Ki + Kd
   *    A1 = (-Kp ) - (2 * Kd )
   *    A2 = Kd
   * </pre>
   *
   * \par
   * where \c Kp is proportional constant, \c Ki is Integral constant and \c Kd is Derivative constant
   *
   * \par
   * \image html PID.gif "Proportional Integral Derivative Controller"
   *
   * \par
   * The PID controller calculates an "error" value as the difference between
   * the measured output and the reference input.
   * The controller attempts to minimize the error by adjusting the process control inputs.
   * The proportional value determines the reaction to the current error,
   * the integral value determines the reaction based on the sum of recent errors,
   * and the derivative value determines the reaction based on the rate at which the error has been changing.
   *
   * \par Instance Structure
   * The Gains A0, A1, A2 and state variables for a PID controller are stored together in an instance data structure.
   * A separate instance structure must be defined for each PID Controller.
   * There are separate instance structure declarations for each of the 3 supported data types.
   *
   * \par Reset Functions
   * There is also an associated reset function for each data type which clears the state array.
   *
   * \par Initialization Functions
   * There is also an associated initialization function for each data type.
   * The initialization function performs the following operations:
   * - Initializes the Gains A0, A1, A2 from Kp,Ki, Kd gains.
   * - Zeros out the values in the state buffer.
   *
   * \par
   * Instance structure cannot be placed into a const data section and it is recommended to use the initialization function.
   *
   * \par Fixed-Point Behavior
   * Care must be taken when using the fixed-point versions of the PID Controller functions.
   * In particular, the overflow and saturation behavior of the accumulator used in each function must be considered.
   * Refer to the function specific documentation below for usage guidelines.
   */


  /**
   * @ingroup PID
   * @brief Instance structure for the Q15 PID Control.
   */
  typedef struct
  {
          q15 A0;           /**< The derived gain, A0 = Kp + Ki + Kd . */
          q15 A1;           /**< The derived gain A1 = -Kp - 2Kd */
          q15 A2;           /**< The derived gain A1 = Kd. */
          q15 state[3];     /**< The state array of length 3. */
          q15 Kp;           /**< The proportional gain. */
          q15 Ki;           /**< The integral gain. */
          q15 Kd;           /**< The derivative gain. */
  } mips_pid_instance_q15;

  /**
   * @ingroup PID
   * @brief Instance structure for the Q31 PID Control.
   */
  typedef struct
  {
          q31 A0;            /**< The derived gain, A0 = Kp + Ki + Kd . */
          q31 A1;            /**< The derived gain, A1 = -Kp - 2Kd. */
          q31 A2;            /**< The derived gain, A2 = Kd . */
          q31 state[3];      /**< The state array of length 3. */
          q31 Kp;            /**< The proportional gain. */
          q31 Ki;            /**< The integral gain. */
          q31 Kd;            /**< The derivative gain. */
  } mips_pid_instance_q31;

  /**
   * @ingroup PID
   * @brief Instance structure for the floating-point PID Control.
   */
  typedef struct
  {
          f32 A0;          /**< The derived gain, A0 = Kp + Ki + Kd . */
          f32 A1;          /**< The derived gain, A1 = -Kp - 2Kd. */
          f32 A2;          /**< The derived gain, A2 = Kd . */
          f32 state[3];    /**< The state array of length 3. */
          f32 Kp;          /**< The proportional gain. */
          f32 Ki;          /**< The integral gain. */
          f32 Kd;          /**< The derivative gain. */
  } mips_pid_instance_f32;



  /**
   * @brief  Initialization function for the floating-point PID Control.
   * @param[in,out] S               points to an instance of the PID structure.
   * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.
   */
  void mips_pid_init_f32(
        mips_pid_instance_f32 * S,
        int32_t resetStateFlag);


  /**
   * @brief  Reset function for the floating-point PID Control.
   * @param[in,out] S  is an instance of the floating-point PID Control structure
   */
  void mips_pid_reset_f32(
        mips_pid_instance_f32 * S);


  /**
   * @brief  Initialization function for the Q31 PID Control.
   * @param[in,out] S               points to an instance of the Q15 PID structure.
   * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.
   */
  void mips_pid_init_q31(
        mips_pid_instance_q31 * S,
        int32_t resetStateFlag);


  /**
   * @brief  Reset function for the Q31 PID Control.
   * @param[in,out] S   points to an instance of the Q31 PID Control structure
   */

  void mips_pid_reset_q31(
        mips_pid_instance_q31 * S);


  /**
   * @brief  Initialization function for the Q15 PID Control.
   * @param[in,out] S               points to an instance of the Q15 PID structure.
   * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.
   */
  void mips_pid_init_q15(
        mips_pid_instance_q15 * S,
        int32_t resetStateFlag);


  /**
   * @brief  Reset function for the Q15 PID Control.
   * @param[in,out] S  points to an instance of the q15 PID Control structure
   */
  void mips_pid_reset_q15(
        mips_pid_instance_q15 * S);





  /**
   * @ingroup PID
   * @brief         Process function for the floating-point PID Control.
   * @param[in,out] S   is an instance of the floating-point PID Control structure
   * @param[in]     in  input sample to process
   * @return        processed output sample.
   */
  __STATIC_FORCEINLINE f32 mips_pid_f32(
  mips_pid_instance_f32 * S,
  f32 in)
  {
    f32 out;

    /* y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]  */
    out = (S->A0 * in) +
      (S->A1 * S->state[0]) + (S->A2 * S->state[1]) + (S->state[2]);

    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

    /* return to application */
    return (out);

  }

/**
  @ingroup PID
  @brief         Process function for the Q31 PID Control.
  @param[in,out] S  points to an instance of the Q31 PID Control structure
  @param[in]     in  input sample to process
  @return        processed output sample.

  \par Scaling and Overflow Behavior
         The function is implemented using an internal 64-bit accumulator.
         The accumulator has a 2.62 format and maintains full precision of the intermediate multiplication results but provides only a single guard bit.
         Thus, if the accumulator result overflows it wraps around rather than clip.
         In order to avoid overflows completely the input signal must be scaled down by 2 bits as there are four additions.
         After all multiply-accumulates are performed, the 2.62 accumulator is truncated to 1.32 format and then saturated to 1.31 format.
 */
__STATIC_FORCEINLINE q31 mips_pid_q31(
  mips_pid_instance_q31 * S,
  q31 in)
  {
    q63 acc;
    q31 out;

    /* acc = A0 * x[n]  */
    acc = (q63) S->A0 * in;

    /* acc += A1 * x[n-1] */
    acc += (q63) S->A1 * S->state[0];

    /* acc += A2 * x[n-2]  */
    acc += (q63) S->A2 * S->state[1];

    /* convert output to 1.31 format to add y[n-1] */
    out = (q31) (acc >> 31U);

    /* out += y[n-1] */
    out += S->state[2];

    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

    /* return to application */
    return (out);
  }


/**
  @ingroup PID
  @brief         Process function for the Q15 PID Control.
  @param[in,out] S   points to an instance of the Q15 PID Control structure
  @param[in]     in  input sample to process
  @return        processed output sample.

  \par Scaling and Overflow Behavior
         The function is implemented using a 64-bit internal accumulator.
         Both Gains and state variables are represented in 1.15 format and multiplications yield a 2.30 result.
         The 2.30 intermediate results are accumulated in a 64-bit accumulator in 34.30 format.
         There is no risk of internal overflow with this approach and the full precision of intermediate multiplications is preserved.
         After all additions have been performed, the accumulator is truncated to 34.15 format by discarding low 15 bits.
         Lastly, the accumulator is saturated to yield a result in 1.15 format.
 */
__STATIC_FORCEINLINE q15 mips_pid_q15(
  mips_pid_instance_q15 * S,
  q15 in)
  {
    q63 acc;
    q15 out;

    /* acc = A0 * x[n]  */
    acc = ((q31) S->A0) * in;

    /* acc += A1 * x[n-1] + A2 * x[n-2]  */
    acc += (q31) S->A1 * S->state[0];
    acc += (q31) S->A2 * S->state[1];

    /* acc += y[n-1] */
    acc += (q31) S->state[2] << 15;

    /* saturate the output */
    out = (q15) (__SSAT((q31)(acc >> 15), 16));

    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

    /* return to application */
    return (out);
  }



  /**
   * @ingroup groupController
   */

  /**
   * @defgroup park Vector Park Transform
   *
   * Forward Park transform converts the input two-coordinate vector to flux and torque components.
   * The Park transform can be used to realize the transformation of the <code>Ialpha</code> and the <code>Ibeta</code> currents
   * from the stationary to the moving reference frame and control the spatial relationship between
   * the stator vector current and rotor flux vector.
   * If we consider the d axis aligned with the rotor flux, the diagram below shows the
   * current vector and the relationship from the two reference frames:
   * \image html park.gif "Stator current space vector and its component in (a,b) and in the d,q rotating reference frame"
   *
   * The function operates on a single sample of data and each call to the function returns the processed output.
   * The library provides separate functions for Q31 and floating-point data types.
   * \par Algorithm
   * \image html parkFormula.gif
   * where <code>Ialpha</code> and <code>Ibeta</code> are the stator vector components,
   * <code>pId</code> and <code>pIq</code> are rotor vector components and <code>cosVal</code> and <code>sinVal</code> are the
   * cosine and sine values of theta (rotor flux position).
   * \par Fixed-Point Behavior
   * Care must be taken when using the Q31 version of the Park transform.
   * In particular, the overflow and saturation behavior of the accumulator used must be considered.
   * Refer to the function specific documentation below for usage guidelines.
   */

 

  /**
   * @ingroup park
   * @brief Floating-point Park transform
   * @param[in]  Ialpha  input two-phase vector coordinate alpha
   * @param[in]  Ibeta   input two-phase vector coordinate beta
   * @param[out] pId     points to output   rotor reference frame d
   * @param[out] pIq     points to output   rotor reference frame q
   * @param[in]  sinVal  sine value of rotation angle theta
   * @param[in]  cosVal  cosine value of rotation angle theta
   * @return     none
   *
   * The function implements the forward Park transform.
   *
   */
  __STATIC_FORCEINLINE void mips_park_f32(
  f32 Ialpha,
  f32 Ibeta,
  f32 * pId,
  f32 * pIq,
  f32 sinVal,
  f32 cosVal)
  {
    /* Calculate pId using the equation, pId = Ialpha * cosVal + Ibeta * sinVal */
    *pId = Ialpha * cosVal + Ibeta * sinVal;

    /* Calculate pIq using the equation, pIq = - Ialpha * sinVal + Ibeta * cosVal */
    *pIq = -Ialpha * sinVal + Ibeta * cosVal;
  }


/**
  @ingroup park
  @brief  Park transform for Q31 version
  @param[in]  Ialpha  input two-phase vector coordinate alpha
  @param[in]  Ibeta   input two-phase vector coordinate beta
  @param[out] pId     points to output rotor reference frame d
  @param[out] pIq     points to output rotor reference frame q
  @param[in]  sinVal  sine value of rotation angle theta
  @param[in]  cosVal  cosine value of rotation angle theta
  @return     none

  \par Scaling and Overflow Behavior
         The function is implemented using an internal 32-bit accumulator.
         The accumulator maintains 1.31 format by truncating lower 31 bits of the intermediate multiplication in 2.62 format.
         There is saturation on the addition and subtraction, hence there is no risk of overflow.
 */
__STATIC_FORCEINLINE void mips_park_q31(
  q31 Ialpha,
  q31 Ibeta,
  q31 * pId,
  q31 * pIq,
  q31 sinVal,
  q31 cosVal)
  {
    q31 product1, product2;                    /* Temporary variables used to store intermediate results */
    q31 product3, product4;                    /* Temporary variables used to store intermediate results */

    /* Intermediate product is calculated by (Ialpha * cosVal) */
    product1 = (q31) (((q63) (Ialpha) * (cosVal)) >> 31);

    /* Intermediate product is calculated by (Ibeta * sinVal) */
    product2 = (q31) (((q63) (Ibeta) * (sinVal)) >> 31);


    /* Intermediate product is calculated by (Ialpha * sinVal) */
    product3 = (q31) (((q63) (Ialpha) * (sinVal)) >> 31);

    /* Intermediate product is calculated by (Ibeta * cosVal) */
    product4 = (q31) (((q63) (Ibeta) * (cosVal)) >> 31);

    /* Calculate pId by adding the two intermediate products 1 and 2 */
    *pId = __QADD(product1, product2);

    /* Calculate pIq by subtracting the two intermediate products 3 from 4 */
    *pIq = __QSUB(product4, product3);
  }



  /**
   * @ingroup groupController
   */

  /**
   * @defgroup inv_park Vector Inverse Park transform
   * Inverse Park transform converts the input flux and torque components to two-coordinate vector.
   *
   * The function operates on a single sample of data and each call to the function returns the processed output.
   * The library provides separate functions for Q31 and floating-point data types.
   * \par Algorithm
   * \image html parkInvFormula.gif
   * where <code>pIalpha</code> and <code>pIbeta</code> are the stator vector components,
   * <code>Id</code> and <code>Iq</code> are rotor vector components and <code>cosVal</code> and <code>sinVal</code> are the
   * cosine and sine values of theta (rotor flux position).
   * \par Fixed-Point Behavior
   * Care must be taken when using the Q31 version of the Park transform.
   * In particular, the overflow and saturation behavior of the accumulator used must be considered.
   * Refer to the function specific documentation below for usage guidelines.
   */

  

   /**
   * @ingroup inv_park
   * @brief  Floating-point Inverse Park transform
   * @param[in]  Id       input coordinate of rotor reference frame d
   * @param[in]  Iq       input coordinate of rotor reference frame q
   * @param[out] pIalpha  points to output two-phase orthogonal vector axis alpha
   * @param[out] pIbeta   points to output two-phase orthogonal vector axis beta
   * @param[in]  sinVal   sine value of rotation angle theta
   * @param[in]  cosVal   cosine value of rotation angle theta
   * @return     none
   */
  __STATIC_FORCEINLINE void mips_inv_park_f32(
  f32 Id,
  f32 Iq,
  f32 * pIalpha,
  f32 * pIbeta,
  f32 sinVal,
  f32 cosVal)
  {
    /* Calculate pIalpha using the equation, pIalpha = Id * cosVal - Iq * sinVal */
    *pIalpha = Id * cosVal - Iq * sinVal;

    /* Calculate pIbeta using the equation, pIbeta = Id * sinVal + Iq * cosVal */
    *pIbeta = Id * sinVal + Iq * cosVal;
  }


/**
  @ingroup inv_park
  @brief  Inverse Park transform for   Q31 version
  @param[in]  Id       input coordinate of rotor reference frame d
  @param[in]  Iq       input coordinate of rotor reference frame q
  @param[out] pIalpha  points to output two-phase orthogonal vector axis alpha
  @param[out] pIbeta   points to output two-phase orthogonal vector axis beta
  @param[in]  sinVal   sine value of rotation angle theta
  @param[in]  cosVal   cosine value of rotation angle theta
  @return     none

  @par Scaling and Overflow Behavior
         The function is implemented using an internal 32-bit accumulator.
         The accumulator maintains 1.31 format by truncating lower 31 bits of the intermediate multiplication in 2.62 format.
         There is saturation on the addition, hence there is no risk of overflow.
 */
__STATIC_FORCEINLINE void mips_inv_park_q31(
  q31 Id,
  q31 Iq,
  q31 * pIalpha,
  q31 * pIbeta,
  q31 sinVal,
  q31 cosVal)
  {
    q31 product1, product2;                    /* Temporary variables used to store intermediate results */
    q31 product3, product4;                    /* Temporary variables used to store intermediate results */

    /* Intermediate product is calculated by (Id * cosVal) */
    product1 = (q31) (((q63) (Id) * (cosVal)) >> 31);

    /* Intermediate product is calculated by (Iq * sinVal) */
    product2 = (q31) (((q63) (Iq) * (sinVal)) >> 31);


    /* Intermediate product is calculated by (Id * sinVal) */
    product3 = (q31) (((q63) (Id) * (sinVal)) >> 31);

    /* Intermediate product is calculated by (Iq * cosVal) */
    product4 = (q31) (((q63) (Iq) * (cosVal)) >> 31);

    /* Calculate pIalpha by using the two intermediate products 1 and 2 */
    *pIalpha = __QSUB(product1, product2);

    /* Calculate pIbeta by using the two intermediate products 3 and 4 */
    *pIbeta = __QADD(product4, product3);
  }


/**
   * @ingroup groupController
   */

  /**
   * @defgroup clarke Vector Clarke Transform
   * Forward Clarke transform converts the instantaneous stator phases into a two-coordinate time invariant vector.
   * Generally the Clarke transform uses three-phase currents <code>Ia, Ib and Ic</code> to calculate currents
   * in the two-phase orthogonal stator axis <code>Ialpha</code> and <code>Ibeta</code>.
   * When <code>Ialpha</code> is superposed with <code>Ia</code> as shown in the figure below
   * \image html clarke.gif Stator current space vector and its components in (a,b).
   * and <code>Ia + Ib + Ic = 0</code>, in this condition <code>Ialpha</code> and <code>Ibeta</code>
   * can be calculated using only <code>Ia</code> and <code>Ib</code>.
   *
   * The function operates on a single sample of data and each call to the function returns the processed output.
   * The library provides separate functions for Q31 and floating-point data types.
   * \par Algorithm
   * \image html clarkeFormula.gif
   * where <code>Ia</code> and <code>Ib</code> are the instantaneous stator phases and
   * <code>pIalpha</code> and <code>pIbeta</code> are the two coordinates of time invariant vector.
   * \par Fixed-Point Behavior
   * Care must be taken when using the Q31 version of the Clarke transform.
   * In particular, the overflow and saturation behavior of the accumulator used must be considered.
   * Refer to the function specific documentation below for usage guidelines.
   */


  /**
   *
   * @ingroup clarke
   * @brief  Floating-point Clarke transform
   * @param[in]  Ia       input three-phase coordinate <code>a</code>
   * @param[in]  Ib       input three-phase coordinate <code>b</code>
   * @param[out] pIalpha  points to output two-phase orthogonal vector axis alpha
   * @param[out] pIbeta   points to output two-phase orthogonal vector axis beta
   * @return        none
   */
  __STATIC_FORCEINLINE void mips_clarke_f32(
  f32 Ia,
  f32 Ib,
  f32 * pIalpha,
  f32 * pIbeta)
  {
    /* Calculate pIalpha using the equation, pIalpha = Ia */
    *pIalpha = Ia;

    /* Calculate pIbeta using the equation, pIbeta = (1/sqrt(3)) * Ia + (2/sqrt(3)) * Ib */
    *pIbeta = (0.57735026919f * Ia + 1.15470053838f * Ib);
  }


/**
  @ingroup clarke
  @brief  Clarke transform for Q31 version
  @param[in]  Ia       input three-phase coordinate <code>a</code>
  @param[in]  Ib       input three-phase coordinate <code>b</code>
  @param[out] pIalpha  points to output two-phase orthogonal vector axis alpha
  @param[out] pIbeta   points to output two-phase orthogonal vector axis beta
  @return     none

  \par Scaling and Overflow Behavior
         The function is implemented using an internal 32-bit accumulator.
         The accumulator maintains 1.31 format by truncating lower 31 bits of the intermediate multiplication in 2.62 format.
         There is saturation on the addition, hence there is no risk of overflow.
 */
__STATIC_FORCEINLINE void mips_clarke_q31(
  q31 Ia,
  q31 Ib,
  q31 * pIalpha,
  q31 * pIbeta)
  {
    q31 product1, product2;                    /* Temporary variables used to store intermediate results */

    /* Calculating pIalpha from Ia by equation pIalpha = Ia */
    *pIalpha = Ia;

    /* Intermediate product is calculated by (1/(sqrt(3)) * Ia) */
    product1 = (q31) (((q63) Ia * 0x24F34E8B) >> 30);

    /* Intermediate product is calculated by (2/sqrt(3) * Ib) */
    product2 = (q31) (((q63) Ib * 0x49E69D16) >> 30);

    /* pIbeta is calculated by adding the intermediate products */
    *pIbeta = __QADD(product1, product2);
  }



  /**
   * @ingroup groupController
   */

  /**
   * @defgroup inv_clarke Vector Inverse Clarke Transform
   * Inverse Clarke transform converts the two-coordinate time invariant vector into instantaneous stator phases.
   *
   * The function operates on a single sample of data and each call to the function returns the processed output.
   * The library provides separate functions for Q31 and floating-point data types.
   * \par Algorithm
   * \image html clarkeInvFormula.gif
   * where <code>pIa</code> and <code>pIb</code> are the instantaneous stator phases and
   * <code>Ialpha</code> and <code>Ibeta</code> are the two coordinates of time invariant vector.
   * \par Fixed-Point Behavior
   * Care must be taken when using the Q31 version of the Clarke transform.
   * In particular, the overflow and saturation behavior of the accumulator used must be considered.
   * Refer to the function specific documentation below for usage guidelines.
   */

 

   /**
   * @ingroup inv_clarke
   * @brief  Floating-point Inverse Clarke transform
   * @param[in]  Ialpha  input two-phase orthogonal vector axis alpha
   * @param[in]  Ibeta   input two-phase orthogonal vector axis beta
   * @param[out] pIa     points to output three-phase coordinate <code>a</code>
   * @param[out] pIb     points to output three-phase coordinate <code>b</code>
   * @return     none
   */
  __STATIC_FORCEINLINE void mips_inv_clarke_f32(
  f32 Ialpha,
  f32 Ibeta,
  f32 * pIa,
  f32 * pIb)
  {
    /* Calculating pIa from Ialpha by equation pIa = Ialpha */
    *pIa = Ialpha;

    /* Calculating pIb from Ialpha and Ibeta by equation pIb = -(1/2) * Ialpha + (sqrt(3)/2) * Ibeta */
    *pIb = -0.5f * Ialpha + 0.8660254039f * Ibeta;
  }


/**
  @ingroup inv_clarke
  @brief  Inverse Clarke transform for Q31 version
  @param[in]  Ialpha  input two-phase orthogonal vector axis alpha
  @param[in]  Ibeta   input two-phase orthogonal vector axis beta
  @param[out] pIa     points to output three-phase coordinate <code>a</code>
  @param[out] pIb     points to output three-phase coordinate <code>b</code>
  @return     none

  \par Scaling and Overflow Behavior
         The function is implemented using an internal 32-bit accumulator.
         The accumulator maintains 1.31 format by truncating lower 31 bits of the intermediate multiplication in 2.62 format.
         There is saturation on the subtraction, hence there is no risk of overflow.
 */
__STATIC_FORCEINLINE void mips_inv_clarke_q31(
  q31 Ialpha,
  q31 Ibeta,
  q31 * pIa,
  q31 * pIb)
  {
    q31 product1, product2;                    /* Temporary variables used to store intermediate results */

    /* Calculating pIa from Ialpha by equation pIa = Ialpha */
    *pIa = Ialpha;

    /* Intermediate product is calculated by (1/(2*sqrt(3)) * Ia) */
    product1 = (q31) (((q63) (Ialpha) * (0x40000000)) >> 31);

    /* Intermediate product is calculated by (1/sqrt(3) * pIb) */
    product2 = (q31) (((q63) (Ibeta) * (0x6ED9EBA1)) >> 31);

    /* pIb is calculated by subtracting the products */
    *pIb = __QSUB(product2, product1);
  }





  
#ifdef   __cplusplus
}
#endif

#endif /* ifndef _CONTROLLER_FUNCTIONS_H_ */
