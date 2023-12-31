/******************************************************************************
 * @file     filtering_functions.h
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

 
#ifndef _FILTERING_FUNCTIONS_H_
#define _FILTERING_FUNCTIONS_H_

#include "mips_math_types.h"
#include "mips_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#include "dsp/support_functions.h"
#include "dsp/fast_math_functions.h"

#ifdef   __cplusplus
extern "C"
{
#endif



#define DELTA_Q31          ((q31)(0x100))
#define DELTA_Q15          ((q15)0x5)

/**
 * @defgroup groupFilters Filtering Functions
 */
    
  /**
   * @brief Instance structure for the Q7 FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;        /**< number of filter coefficients in the filter. */
          q7 *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const q7 *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
  } mips_fir_instance_q7;

  /**
   * @brief Instance structure for the Q15 FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;         /**< number of filter coefficients in the filter. */
          q15 *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const q15 *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
  } mips_fir_instance_q15;

  /**
   * @brief Instance structure for the Q31 FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;         /**< number of filter coefficients in the filter. */
          q31 *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const q31 *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps. */
  } mips_fir_instance_q31;

  /**
   * @brief Instance structure for the floating-point FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< number of filter coefficients in the filter. */
          f32 *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const f32 *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
  } mips_fir_instance_f32;

  /**
   * @brief Instance structure for the floating-point FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< number of filter coefficients in the filter. */
          f64 *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const f64 *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
  } mips_fir_instance_f64;

  /**
   * @brief Processing function for the Q7 FIR filter.
   * @param[in]  S          points to an instance of the Q7 FIR filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_fir_q7(
  const mips_fir_instance_q7 * S,
  const q7 * pSrc,
        q7 * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the Q7 FIR filter.
   * @param[in,out] S          points to an instance of the Q7 FIR structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed.
   *
   * For the 128-bits SIMD version, the coefficient length must be a multiple of 16.
   * You can pad with zeros if you have less coefficients.
   */
  void mips_fir_init_q7(
        mips_fir_instance_q7 * S,
        uint16_t numTaps,
  const q7 * pCoeffs,
        q7 * pState,
        uint32_t blockSize);

  /**
   * @brief Processing function for the Q15 FIR filter.
   * @param[in]  S          points to an instance of the Q15 FIR structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_fir_q15(
  const mips_fir_instance_q15 * S,
  const q15 * pSrc,
        q15 * pDst,
        uint32_t blockSize);

  /**
   * @brief Processing function for the fast Q15 FIR filter (fast version).
   * @param[in]  S          points to an instance of the Q15 FIR filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_fir_fast_q15(
  const mips_fir_instance_q15 * S,
  const q15 * pSrc,
        q15 * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the Q15 FIR filter.
   * @param[in,out] S          points to an instance of the Q15 FIR filter structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter. Must be even and greater than or equal to 4.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed at a time.
   * @return     The function returns either
   * <code>MIPS_MATH_SUCCESS</code> if initialization was successful or
   * <code>MIPS_MATH_ARGUMENT_ERROR</code> if <code>numTaps</code> is not a supported value.
   *
   * For the 128-bits SIMD version, the coefficient length must be a multiple of 8.
   * You can pad with zeros if you have less coefficients.
   *
   */
  mips_status mips_fir_init_q15(
        mips_fir_instance_q15 * S,
        uint16_t numTaps,
  const q15 * pCoeffs,
        q15 * pState,
        uint32_t blockSize);

  /**
   * @brief Processing function for the Q31 FIR filter.
   * @param[in]  S          points to an instance of the Q31 FIR filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_fir_q31(
  const mips_fir_instance_q31 * S,
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize);

  /**
   * @brief Processing function for the fast Q31 FIR filter (fast version).
   * @param[in]  S          points to an instance of the Q31 FIR filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_fir_fast_q31(
  const mips_fir_instance_q31 * S,
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the Q31 FIR filter.
   * @param[in,out] S          points to an instance of the Q31 FIR structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed at a time.
   *
   * For the 128-bits SIMD version, the coefficient length must be a multiple of 4.
   * You can pad with zeros if you have less coefficients.
   */
  void mips_fir_init_q31(
        mips_fir_instance_q31 * S,
        uint16_t numTaps,
  const q31 * pCoeffs,
        q31 * pState,
        uint32_t blockSize);

  /**
   * @brief Processing function for the floating-point FIR filter.
   * @param[in]  S          points to an instance of the floating-point FIR structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_fir_f32(
  const mips_fir_instance_f32 * S,
  const f32 * pSrc,
        f32 * pDst,
        uint32_t blockSize);

  /**
   * @brief Processing function for the floating-point FIR filter.
   * @param[in]  S          points to an instance of the floating-point FIR structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_fir_f64(
  const mips_fir_instance_f64 * S,
  const f64 * pSrc,
        f64 * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the floating-point FIR filter.
   * @param[in,out] S          points to an instance of the floating-point FIR filter structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed at a time.
   */
  void mips_fir_init_f32(
        mips_fir_instance_f32 * S,
        uint16_t numTaps,
  const f32 * pCoeffs,
        f32 * pState,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the floating-point FIR filter.
   * @param[in,out] S          points to an instance of the floating-point FIR filter structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed at a time.
   */
  void mips_fir_init_f64(
        mips_fir_instance_f64 * S,
        uint16_t numTaps,
  const f64 * pCoeffs,
        f64 * pState,
        uint32_t blockSize);

  /**
   * @brief Instance structure for the Q15 Biquad cascade filter.
   */
  typedef struct
  {
          int8_t numStages;        /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          q15 *pState;           /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    const q15 *pCoeffs;          /**< Points to the array of coefficients.  The array is of length 5*numStages. */
          int8_t postShift;        /**< Additional shift, in bits, applied to each output sample. */
  } mips_biquad_casd_df1_inst_q15;

  /**
   * @brief Instance structure for the Q31 Biquad cascade filter.
   */
  typedef struct
  {
          uint32_t numStages;      /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          q31 *pState;           /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    const q31 *pCoeffs;          /**< Points to the array of coefficients.  The array is of length 5*numStages. */
          uint8_t postShift;       /**< Additional shift, in bits, applied to each output sample. */
  } mips_biquad_casd_df1_inst_q31;

  /**
   * @brief Instance structure for the floating-point Biquad cascade filter.
   */
  typedef struct
  {
          uint32_t numStages;      /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          f32 *pState;       /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    const f32 *pCoeffs;      /**< Points to the array of coefficients.  The array is of length 5*numStages. */
  } mips_biquad_casd_df1_inst_f32;

#if defined(MIPS_MATH_MSA)
  /**
   * @brief Instance structure for the modified Biquad coefs required by vectorized code.
   */
  typedef struct
  {
      f32 coeffs[8][4]; /**< Points to the array of modified coefficients.  The array is of length 32. There is one per stage */
  } mips_biquad_mod_coef_f32;
#endif 

  /**
   * @brief Processing function for the Q15 Biquad cascade filter.
   * @param[in]  S          points to an instance of the Q15 Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_biquad_cascade_df1_q15(
  const mips_biquad_casd_df1_inst_q15 * S,
  const q15 * pSrc,
        q15 * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the Q15 Biquad cascade filter.
   * @param[in,out] S          points to an instance of the Q15 Biquad cascade structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     postShift  Shift to be applied to the output. Varies according to the coefficients format
   */
  void mips_biquad_cascade_df1_init_q15(
        mips_biquad_casd_df1_inst_q15 * S,
        uint8_t numStages,
  const q15 * pCoeffs,
        q15 * pState,
        int8_t postShift);

  /**
   * @brief Fast but less precise processing function for the Q15 Biquad cascade filter for Cortex-M3 and Cortex-M4.
   * @param[in]  S          points to an instance of the Q15 Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_biquad_cascade_df1_fast_q15(
  const mips_biquad_casd_df1_inst_q15 * S,
  const q15 * pSrc,
        q15 * pDst,
        uint32_t blockSize);

  /**
   * @brief Processing function for the Q31 Biquad cascade filter
   * @param[in]  S          points to an instance of the Q31 Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_biquad_cascade_df1_q31(
  const mips_biquad_casd_df1_inst_q31 * S,
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize);

  /**
   * @brief Fast but less precise processing function for the Q31 Biquad cascade filter for Cortex-M3 and Cortex-M4.
   * @param[in]  S          points to an instance of the Q31 Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_biquad_cascade_df1_fast_q31(
  const mips_biquad_casd_df1_inst_q31 * S,
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the Q31 Biquad cascade filter.
   * @param[in,out] S          points to an instance of the Q31 Biquad cascade structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     postShift  Shift to be applied to the output. Varies according to the coefficients format
   */
  void mips_biquad_cascade_df1_init_q31(
        mips_biquad_casd_df1_inst_q31 * S,
        uint8_t numStages,
  const q31 * pCoeffs,
        q31 * pState,
        int8_t postShift);

  /**
   * @brief Processing function for the floating-point Biquad cascade filter.
   * @param[in]  S          points to an instance of the floating-point Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_biquad_cascade_df1_f32(
  const mips_biquad_casd_df1_inst_f32 * S,
  const f32 * pSrc,
        f32 * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the floating-point Biquad cascade filter.
   * @param[in,out] S          points to an instance of the floating-point Biquad cascade structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pCoeffsMod points to the modified filter coefficients (only 128-bits SIMD version).
   * @param[in]     pState     points to the state buffer.
   */
#if defined(MIPS_MATH_MSA)
  void mips_biquad_cascade_df1_msa_init_f32(
      mips_biquad_casd_df1_inst_f32 * S,
      uint8_t numStages,
      const f32 * pCoeffs, 
      mips_biquad_mod_coef_f32 * pCoeffsMod, 
      f32 * pState);
#endif
  
  void mips_biquad_cascade_df1_init_f32(
        mips_biquad_casd_df1_inst_f32 * S,
        uint8_t numStages,
  const f32 * pCoeffs,
        f32 * pState);


/**
 * @brief Convolution of floating-point sequences.
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the location where the output result is written.  Length srcALen+srcBLen-1.
 */
  void mips_conv_f32(
  const f32 * pSrcA,
        uint32_t srcALen,
  const f32 * pSrcB,
        uint32_t srcBLen,
        f32 * pDst);


  /**
   * @brief Convolution of Q15 sequences.
   * @param[in]  pSrcA      points to the first input sequence.
   * @param[in]  srcALen    length of the first input sequence.
   * @param[in]  pSrcB      points to the second input sequence.
   * @param[in]  srcBLen    length of the second input sequence.
   * @param[out] pDst       points to the block of output data  Length srcALen+srcBLen-1.
   * @param[in]  pScratch1  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2  points to scratch buffer of size min(srcALen, srcBLen).
   */
  void mips_conv_opt_q15(
  const q15 * pSrcA,
        uint32_t srcALen,
  const q15 * pSrcB,
        uint32_t srcBLen,
        q15 * pDst,
        q15 * pScratch1,
        q15 * pScratch2);


/**
 * @brief Convolution of Q15 sequences.
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the location where the output result is written.  Length srcALen+srcBLen-1.
 */
  void mips_conv_q15(
  const q15 * pSrcA,
        uint32_t srcALen,
  const q15 * pSrcB,
        uint32_t srcBLen,
        q15 * pDst);


  /**
   * @brief Convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
   */
  void mips_conv_fast_q15(
  const q15 * pSrcA,
        uint32_t srcALen,
  const q15 * pSrcB,
        uint32_t srcBLen,
        q15 * pDst);


  /**
   * @brief Convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA      points to the first input sequence.
   * @param[in]  srcALen    length of the first input sequence.
   * @param[in]  pSrcB      points to the second input sequence.
   * @param[in]  srcBLen    length of the second input sequence.
   * @param[out] pDst       points to the block of output data  Length srcALen+srcBLen-1.
   * @param[in]  pScratch1  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2  points to scratch buffer of size min(srcALen, srcBLen).
   */
  void mips_conv_fast_opt_q15(
  const q15 * pSrcA,
        uint32_t srcALen,
  const q15 * pSrcB,
        uint32_t srcBLen,
        q15 * pDst,
        q15 * pScratch1,
        q15 * pScratch2);


  /**
   * @brief Convolution of Q31 sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
   */
  void mips_conv_q31(
  const q31 * pSrcA,
        uint32_t srcALen,
  const q31 * pSrcB,
        uint32_t srcBLen,
        q31 * pDst);


  /**
   * @brief Convolution of Q31 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
   */
  void mips_conv_fast_q31(
  const q31 * pSrcA,
        uint32_t srcALen,
  const q31 * pSrcB,
        uint32_t srcBLen,
        q31 * pDst);


    /**
   * @brief Convolution of Q7 sequences.
   * @param[in]  pSrcA      points to the first input sequence.
   * @param[in]  srcALen    length of the first input sequence.
   * @param[in]  pSrcB      points to the second input sequence.
   * @param[in]  srcBLen    length of the second input sequence.
   * @param[out] pDst       points to the block of output data  Length srcALen+srcBLen-1.
   * @param[in]  pScratch1  points to scratch buffer(of type q15) of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2  points to scratch buffer (of type q15) of size min(srcALen, srcBLen).
   */
  void mips_conv_opt_q7(
  const q7 * pSrcA,
        uint32_t srcALen,
  const q7 * pSrcB,
        uint32_t srcBLen,
        q7 * pDst,
        q15 * pScratch1,
        q15 * pScratch2);


  /**
   * @brief Convolution of Q7 sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
   */
  void mips_conv_q7(
  const q7 * pSrcA,
        uint32_t srcALen,
  const q7 * pSrcB,
        uint32_t srcBLen,
        q7 * pDst);


  /**
   * @brief Partial convolution of floating-point sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either MIPS_MATH_SUCCESS if the function completed correctly or MIPS_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  mips_status mips_conv_partial_f32(
  const f32 * pSrcA,
        uint32_t srcALen,
  const f32 * pSrcB,
        uint32_t srcBLen,
        f32 * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);


  /**
   * @brief Partial convolution of Q15 sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @param[in]  pScratch1   points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2   points to scratch buffer of size min(srcALen, srcBLen).
   * @return  Returns either MIPS_MATH_SUCCESS if the function completed correctly or MIPS_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  mips_status mips_conv_partial_opt_q15(
  const q15 * pSrcA,
        uint32_t srcALen,
  const q15 * pSrcB,
        uint32_t srcBLen,
        q15 * pDst,
        uint32_t firstIndex,
        uint32_t numPoints,
        q15 * pScratch1,
        q15 * pScratch2);


  /**
   * @brief Partial convolution of Q15 sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either MIPS_MATH_SUCCESS if the function completed correctly or MIPS_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  mips_status mips_conv_partial_q15(
  const q15 * pSrcA,
        uint32_t srcALen,
  const q15 * pSrcB,
        uint32_t srcBLen,
        q15 * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);


  /**
   * @brief Partial convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either MIPS_MATH_SUCCESS if the function completed correctly or MIPS_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  mips_status mips_conv_partial_fast_q15(
  const q15 * pSrcA,
        uint32_t srcALen,
  const q15 * pSrcB,
        uint32_t srcBLen,
        q15 * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);


  /**
   * @brief Partial convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @param[in]  pScratch1   points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2   points to scratch buffer of size min(srcALen, srcBLen).
   * @return  Returns either MIPS_MATH_SUCCESS if the function completed correctly or MIPS_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  mips_status mips_conv_partial_fast_opt_q15(
  const q15 * pSrcA,
        uint32_t srcALen,
  const q15 * pSrcB,
        uint32_t srcBLen,
        q15 * pDst,
        uint32_t firstIndex,
        uint32_t numPoints,
        q15 * pScratch1,
        q15 * pScratch2);


  /**
   * @brief Partial convolution of Q31 sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either MIPS_MATH_SUCCESS if the function completed correctly or MIPS_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  mips_status mips_conv_partial_q31(
  const q31 * pSrcA,
        uint32_t srcALen,
  const q31 * pSrcB,
        uint32_t srcBLen,
        q31 * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);


  /**
   * @brief Partial convolution of Q31 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either MIPS_MATH_SUCCESS if the function completed correctly or MIPS_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  mips_status mips_conv_partial_fast_q31(
  const q31 * pSrcA,
        uint32_t srcALen,
  const q31 * pSrcB,
        uint32_t srcBLen,
        q31 * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);


  /**
   * @brief Partial convolution of Q7 sequences
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @param[in]  pScratch1   points to scratch buffer(of type q15) of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2   points to scratch buffer (of type q15) of size min(srcALen, srcBLen).
   * @return  Returns either MIPS_MATH_SUCCESS if the function completed correctly or MIPS_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  mips_status mips_conv_partial_opt_q7(
  const q7 * pSrcA,
        uint32_t srcALen,
  const q7 * pSrcB,
        uint32_t srcBLen,
        q7 * pDst,
        uint32_t firstIndex,
        uint32_t numPoints,
        q15 * pScratch1,
        q15 * pScratch2);


/**
   * @brief Partial convolution of Q7 sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either MIPS_MATH_SUCCESS if the function completed correctly or MIPS_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  mips_status mips_conv_partial_q7(
  const q7 * pSrcA,
        uint32_t srcALen,
  const q7 * pSrcB,
        uint32_t srcBLen,
        q7 * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);


  /**
   * @brief Instance structure for the Q15 FIR decimator.
   */
  typedef struct
  {
          uint8_t M;                  /**< decimation factor. */
          uint16_t numTaps;           /**< number of coefficients in the filter. */
    const q15 *pCoeffs;             /**< points to the coefficient array. The array is of length numTaps.*/
          q15 *pState;              /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
  } mips_fir_decimate_instance_q15;

  /**
   * @brief Instance structure for the Q31 FIR decimator.
   */
  typedef struct
  {
          uint8_t M;                  /**< decimation factor. */
          uint16_t numTaps;           /**< number of coefficients in the filter. */
    const q31 *pCoeffs;             /**< points to the coefficient array. The array is of length numTaps.*/
          q31 *pState;              /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
  } mips_fir_decimate_instance_q31;

/**
  @brief Instance structure for floating-point FIR decimator.
 */
typedef struct
  {
          uint8_t M;                  /**< decimation factor. */
          uint16_t numTaps;           /**< number of coefficients in the filter. */
    const f32 *pCoeffs;         /**< points to the coefficient array. The array is of length numTaps.*/
          f32 *pState;          /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
  } mips_fir_decimate_instance_f32;


/**
  @brief         Processing function for floating-point FIR decimator.
  @param[in]     S         points to an instance of the floating-point FIR decimator structure
  @param[in]     pSrc      points to the block of input data
  @param[out]    pDst      points to the block of output data
  @param[in]     blockSize number of samples to process
 */
void mips_fir_decimate_f32(
  const mips_fir_decimate_instance_f32 * S,
  const f32 * pSrc,
        f32 * pDst,
        uint32_t blockSize);


/**
  @brief         Initialization function for the floating-point FIR decimator.
  @param[in,out] S          points to an instance of the floating-point FIR decimator structure
  @param[in]     numTaps    number of coefficients in the filter
  @param[in]     M          decimation factor
  @param[in]     pCoeffs    points to the filter coefficients
  @param[in]     pState     points to the state buffer
  @param[in]     blockSize  number of input samples to process per call
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS      : Operation successful
                   - \ref MIPS_MATH_LENGTH_ERROR : <code>blockSize</code> is not a multiple of <code>M</code>
 */
mips_status mips_fir_decimate_init_f32(
        mips_fir_decimate_instance_f32 * S,
        uint16_t numTaps,
        uint8_t M,
  const f32 * pCoeffs,
        f32 * pState,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q15 FIR decimator.
   * @param[in]  S          points to an instance of the Q15 FIR decimator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void mips_fir_decimate_q15(
  const mips_fir_decimate_instance_q15 * S,
  const q15 * pSrc,
        q15 * pDst,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q15 FIR decimator (fast variant) for Cortex-M3 and Cortex-M4.
   * @param[in]  S          points to an instance of the Q15 FIR decimator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void mips_fir_decimate_fast_q15(
  const mips_fir_decimate_instance_q15 * S,
  const q15 * pSrc,
        q15 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q15 FIR decimator.
   * @param[in,out] S          points to an instance of the Q15 FIR decimator structure.
   * @param[in]     numTaps    number of coefficients in the filter.
   * @param[in]     M          decimation factor.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return    The function returns MIPS_MATH_SUCCESS if initialization is successful or MIPS_MATH_LENGTH_ERROR if
   * <code>blockSize</code> is not a multiple of <code>M</code>.
   */
  mips_status mips_fir_decimate_init_q15(
        mips_fir_decimate_instance_q15 * S,
        uint16_t numTaps,
        uint8_t M,
  const q15 * pCoeffs,
        q15 * pState,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 FIR decimator.
   * @param[in]  S     points to an instance of the Q31 FIR decimator structure.
   * @param[in]  pSrc  points to the block of input data.
   * @param[out] pDst  points to the block of output data
   * @param[in] blockSize number of input samples to process per call.
   */
  void mips_fir_decimate_q31(
  const mips_fir_decimate_instance_q31 * S,
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize);

  /**
   * @brief Processing function for the Q31 FIR decimator (fast variant) for Cortex-M3 and Cortex-M4.
   * @param[in]  S          points to an instance of the Q31 FIR decimator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void mips_fir_decimate_fast_q31(
  const mips_fir_decimate_instance_q31 * S,
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q31 FIR decimator.
   * @param[in,out] S          points to an instance of the Q31 FIR decimator structure.
   * @param[in]     numTaps    number of coefficients in the filter.
   * @param[in]     M          decimation factor.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return    The function returns MIPS_MATH_SUCCESS if initialization is successful or MIPS_MATH_LENGTH_ERROR if
   * <code>blockSize</code> is not a multiple of <code>M</code>.
   */
  mips_status mips_fir_decimate_init_q31(
        mips_fir_decimate_instance_q31 * S,
        uint16_t numTaps,
        uint8_t M,
  const q31 * pCoeffs,
        q31 * pState,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the Q15 FIR interpolator.
   */
  typedef struct
  {
        uint8_t L;                      /**< upsample factor. */
        uint16_t phaseLength;           /**< length of each polyphase filter component. */
  const q15 *pCoeffs;                 /**< points to the coefficient array. The array is of length L*phaseLength. */
        q15 *pState;                  /**< points to the state variable array. The array is of length blockSize+phaseLength-1. */
  } mips_fir_interpolate_instance_q15;

  /**
   * @brief Instance structure for the Q31 FIR interpolator.
   */
  typedef struct
  {
        uint8_t L;                      /**< upsample factor. */
        uint16_t phaseLength;           /**< length of each polyphase filter component. */
  const q31 *pCoeffs;                 /**< points to the coefficient array. The array is of length L*phaseLength. */
        q31 *pState;                  /**< points to the state variable array. The array is of length blockSize+phaseLength-1. */
  } mips_fir_interpolate_instance_q31;

  /**
   * @brief Instance structure for the floating-point FIR interpolator.
   */
  typedef struct
  {
        uint8_t L;                     /**< upsample factor. */
        uint16_t phaseLength;          /**< length of each polyphase filter component. */
  const f32 *pCoeffs;            /**< points to the coefficient array. The array is of length L*phaseLength. */
        f32 *pState;             /**< points to the state variable array. The array is of length phaseLength+numTaps-1. */
  } mips_fir_interpolate_instance_f32;


  /**
   * @brief Processing function for the Q15 FIR interpolator.
   * @param[in]  S          points to an instance of the Q15 FIR interpolator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void mips_fir_interpolate_q15(
  const mips_fir_interpolate_instance_q15 * S,
  const q15 * pSrc,
        q15 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q15 FIR interpolator.
   * @param[in,out] S          points to an instance of the Q15 FIR interpolator structure.
   * @param[in]     L          upsample factor.
   * @param[in]     numTaps    number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficient buffer.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return        The function returns MIPS_MATH_SUCCESS if initialization is successful or MIPS_MATH_LENGTH_ERROR if
   * the filter length <code>numTaps</code> is not a multiple of the interpolation factor <code>L</code>.
   */
  mips_status mips_fir_interpolate_init_q15(
        mips_fir_interpolate_instance_q15 * S,
        uint8_t L,
        uint16_t numTaps,
  const q15 * pCoeffs,
        q15 * pState,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 FIR interpolator.
   * @param[in]  S          points to an instance of the Q15 FIR interpolator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void mips_fir_interpolate_q31(
  const mips_fir_interpolate_instance_q31 * S,
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q31 FIR interpolator.
   * @param[in,out] S          points to an instance of the Q31 FIR interpolator structure.
   * @param[in]     L          upsample factor.
   * @param[in]     numTaps    number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficient buffer.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return        The function returns MIPS_MATH_SUCCESS if initialization is successful or MIPS_MATH_LENGTH_ERROR if
   * the filter length <code>numTaps</code> is not a multiple of the interpolation factor <code>L</code>.
   */
  mips_status mips_fir_interpolate_init_q31(
        mips_fir_interpolate_instance_q31 * S,
        uint8_t L,
        uint16_t numTaps,
  const q31 * pCoeffs,
        q31 * pState,
        uint32_t blockSize);


  /**
   * @brief Processing function for the floating-point FIR interpolator.
   * @param[in]  S          points to an instance of the floating-point FIR interpolator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void mips_fir_interpolate_f32(
  const mips_fir_interpolate_instance_f32 * S,
  const f32 * pSrc,
        f32 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the floating-point FIR interpolator.
   * @param[in,out] S          points to an instance of the floating-point FIR interpolator structure.
   * @param[in]     L          upsample factor.
   * @param[in]     numTaps    number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficient buffer.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return        The function returns MIPS_MATH_SUCCESS if initialization is successful or MIPS_MATH_LENGTH_ERROR if
   * the filter length <code>numTaps</code> is not a multiple of the interpolation factor <code>L</code>.
   */
  mips_status mips_fir_interpolate_init_f32(
        mips_fir_interpolate_instance_f32 * S,
        uint8_t L,
        uint16_t numTaps,
  const f32 * pCoeffs,
        f32 * pState,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the high precision Q31 Biquad cascade filter.
   */
  typedef struct
  {
          uint8_t numStages;       /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          q63 *pState;           /**< points to the array of state coefficients.  The array is of length 4*numStages. */
    const q31 *pCoeffs;          /**< points to the array of coefficients.  The array is of length 5*numStages. */
          uint8_t postShift;       /**< additional shift, in bits, applied to each output sample. */
  } mips_biquad_cas_df1_32x64_ins_q31;


  /**
   * @param[in]  S          points to an instance of the high precision Q31 Biquad cascade filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_biquad_cas_df1_32x64_q31(
  const mips_biquad_cas_df1_32x64_ins_q31 * S,
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize);


  /**
   * @param[in,out] S          points to an instance of the high precision Q31 Biquad cascade filter structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     postShift  shift to be applied to the output. Varies according to the coefficients format
   */
  void mips_biquad_cas_df1_32x64_init_q31(
        mips_biquad_cas_df1_32x64_ins_q31 * S,
        uint8_t numStages,
  const q31 * pCoeffs,
        q63 * pState,
        uint8_t postShift);


  /**
   * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
   */
  typedef struct
  {
          uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          f32 *pState;         /**< points to the array of state coefficients.  The array is of length 2*numStages. */
    const f32 *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
  } mips_biquad_cascade_df2T_instance_f32;

  /**
   * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
   */
  typedef struct
  {
          uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          f32 *pState;         /**< points to the array of state coefficients.  The array is of length 4*numStages. */
    const f32 *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
  } mips_biquad_cascade_stereo_df2T_instance_f32;

  /**
   * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
   */
  typedef struct
  {
          uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          f64 *pState;         /**< points to the array of state coefficients.  The array is of length 2*numStages. */
    const f64 *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
  } mips_biquad_cascade_df2T_instance_f64;


  /**
   * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in]  S          points to an instance of the filter data structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_biquad_cascade_df2T_f32(
  const mips_biquad_cascade_df2T_instance_f32 * S,
  const f32 * pSrc,
        f32 * pDst,
        uint32_t blockSize);


  /**
   * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter. 2 channels
   * @param[in]  S          points to an instance of the filter data structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_biquad_cascade_stereo_df2T_f32(
  const mips_biquad_cascade_stereo_df2T_instance_f32 * S,
  const f32 * pSrc,
        f32 * pDst,
        uint32_t blockSize);


  /**
   * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in]  S          points to an instance of the filter data structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_biquad_cascade_df2T_f64(
  const mips_biquad_cascade_df2T_instance_f64 * S,
  const f64 * pSrc,
        f64 * pDst,
        uint32_t blockSize);


#if defined(MIPS_MATH_MSA) 
/**
  @brief         Compute new coefficient arrays for use in vectorized filter (Neon only).
  @param[in]     numStages         number of 2nd order stages in the filter.
  @param[in]     pCoeffs           points to the original filter coefficients.
  @param[in]     pComputedCoeffs   points to the new computed coefficients for the vectorized version.
  @return        none
*/
void mips_biquad_cascade_df2T_compute_coefs_f32(
  uint8_t numStages,
  const f32 * pCoeffs,
  f32 * pComputedCoeffs);
#endif
  /**
   * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in,out] S          points to an instance of the filter data structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   */
  void mips_biquad_cascade_df2T_init_f32(
        mips_biquad_cascade_df2T_instance_f32 * S,
        uint8_t numStages,
  const f32 * pCoeffs,
        f32 * pState);


  /**
   * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in,out] S          points to an instance of the filter data structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   */
  void mips_biquad_cascade_stereo_df2T_init_f32(
        mips_biquad_cascade_stereo_df2T_instance_f32 * S,
        uint8_t numStages,
  const f32 * pCoeffs,
        f32 * pState);


  /**
   * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in,out] S          points to an instance of the filter data structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   */
  void mips_biquad_cascade_df2T_init_f64(
        mips_biquad_cascade_df2T_instance_f64 * S,
        uint8_t numStages,
        const f64 * pCoeffs,
        f64 * pState);


  /**
   * @brief Instance structure for the Q15 FIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of filter stages. */
          q15 *pState;                       /**< points to the state variable array. The array is of length numStages. */
    const q15 *pCoeffs;                      /**< points to the coefficient array. The array is of length numStages. */
  } mips_fir_lattice_instance_q15;

  /**
   * @brief Instance structure for the Q31 FIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of filter stages. */
          q31 *pState;                       /**< points to the state variable array. The array is of length numStages. */
    const q31 *pCoeffs;                      /**< points to the coefficient array. The array is of length numStages. */
  } mips_fir_lattice_instance_q31;

  /**
   * @brief Instance structure for the floating-point FIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of filter stages. */
          f32 *pState;                   /**< points to the state variable array. The array is of length numStages. */
    const f32 *pCoeffs;                  /**< points to the coefficient array. The array is of length numStages. */
  } mips_fir_lattice_instance_f32;


  /**
   * @brief Initialization function for the Q15 FIR lattice filter.
   * @param[in] S          points to an instance of the Q15 FIR lattice structure.
   * @param[in] numStages  number of filter stages.
   * @param[in] pCoeffs    points to the coefficient buffer.  The array is of length numStages.
   * @param[in] pState     points to the state buffer.  The array is of length numStages.
   */
  void mips_fir_lattice_init_q15(
        mips_fir_lattice_instance_q15 * S,
        uint16_t numStages,
  const q15 * pCoeffs,
        q15 * pState);


  /**
   * @brief Processing function for the Q15 FIR lattice filter.
   * @param[in]  S          points to an instance of the Q15 FIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_fir_lattice_q15(
  const mips_fir_lattice_instance_q15 * S,
  const q15 * pSrc,
        q15 * pDst,
        uint32_t blockSize);


  /**
   * @brief Initialization function for the Q31 FIR lattice filter.
   * @param[in] S          points to an instance of the Q31 FIR lattice structure.
   * @param[in] numStages  number of filter stages.
   * @param[in] pCoeffs    points to the coefficient buffer.  The array is of length numStages.
   * @param[in] pState     points to the state buffer.   The array is of length numStages.
   */
  void mips_fir_lattice_init_q31(
        mips_fir_lattice_instance_q31 * S,
        uint16_t numStages,
  const q31 * pCoeffs,
        q31 * pState);


  /**
   * @brief Processing function for the Q31 FIR lattice filter.
   * @param[in]  S          points to an instance of the Q31 FIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_fir_lattice_q31(
  const mips_fir_lattice_instance_q31 * S,
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize);


/**
 * @brief Initialization function for the floating-point FIR lattice filter.
 * @param[in] S          points to an instance of the floating-point FIR lattice structure.
 * @param[in] numStages  number of filter stages.
 * @param[in] pCoeffs    points to the coefficient buffer.  The array is of length numStages.
 * @param[in] pState     points to the state buffer.  The array is of length numStages.
 */
  void mips_fir_lattice_init_f32(
        mips_fir_lattice_instance_f32 * S,
        uint16_t numStages,
  const f32 * pCoeffs,
        f32 * pState);


  /**
   * @brief Processing function for the floating-point FIR lattice filter.
   * @param[in]  S          points to an instance of the floating-point FIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_fir_lattice_f32(
  const mips_fir_lattice_instance_f32 * S,
  const f32 * pSrc,
        f32 * pDst,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the Q15 IIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of stages in the filter. */
          q15 *pState;                       /**< points to the state variable array. The array is of length numStages+blockSize. */
          q15 *pkCoeffs;                     /**< points to the reflection coefficient array. The array is of length numStages. */
          q15 *pvCoeffs;                     /**< points to the ladder coefficient array. The array is of length numStages+1. */
  } mips_iir_lattice_instance_q15;

  /**
   * @brief Instance structure for the Q31 IIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of stages in the filter. */
          q31 *pState;                       /**< points to the state variable array. The array is of length numStages+blockSize. */
          q31 *pkCoeffs;                     /**< points to the reflection coefficient array. The array is of length numStages. */
          q31 *pvCoeffs;                     /**< points to the ladder coefficient array. The array is of length numStages+1. */
  } mips_iir_lattice_instance_q31;

  /**
   * @brief Instance structure for the floating-point IIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of stages in the filter. */
          f32 *pState;                   /**< points to the state variable array. The array is of length numStages+blockSize. */
          f32 *pkCoeffs;                 /**< points to the reflection coefficient array. The array is of length numStages. */
          f32 *pvCoeffs;                 /**< points to the ladder coefficient array. The array is of length numStages+1. */
  } mips_iir_lattice_instance_f32;


  /**
   * @brief Processing function for the floating-point IIR lattice filter.
   * @param[in]  S          points to an instance of the floating-point IIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_iir_lattice_f32(
  const mips_iir_lattice_instance_f32 * S,
  const f32 * pSrc,
        f32 * pDst,
        uint32_t blockSize);


  /**
   * @brief Initialization function for the floating-point IIR lattice filter.
   * @param[in] S          points to an instance of the floating-point IIR lattice structure.
   * @param[in] numStages  number of stages in the filter.
   * @param[in] pkCoeffs   points to the reflection coefficient buffer.  The array is of length numStages.
   * @param[in] pvCoeffs   points to the ladder coefficient buffer.  The array is of length numStages+1.
   * @param[in] pState     points to the state buffer.  The array is of length numStages+blockSize-1.
   * @param[in] blockSize  number of samples to process.
   */
  void mips_iir_lattice_init_f32(
        mips_iir_lattice_instance_f32 * S,
        uint16_t numStages,
        f32 * pkCoeffs,
        f32 * pvCoeffs,
        f32 * pState,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 IIR lattice filter.
   * @param[in]  S          points to an instance of the Q31 IIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_iir_lattice_q31(
  const mips_iir_lattice_instance_q31 * S,
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize);


  /**
   * @brief Initialization function for the Q31 IIR lattice filter.
   * @param[in] S          points to an instance of the Q31 IIR lattice structure.
   * @param[in] numStages  number of stages in the filter.
   * @param[in] pkCoeffs   points to the reflection coefficient buffer.  The array is of length numStages.
   * @param[in] pvCoeffs   points to the ladder coefficient buffer.  The array is of length numStages+1.
   * @param[in] pState     points to the state buffer.  The array is of length numStages+blockSize.
   * @param[in] blockSize  number of samples to process.
   */
  void mips_iir_lattice_init_q31(
        mips_iir_lattice_instance_q31 * S,
        uint16_t numStages,
        q31 * pkCoeffs,
        q31 * pvCoeffs,
        q31 * pState,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q15 IIR lattice filter.
   * @param[in]  S          points to an instance of the Q15 IIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_iir_lattice_q15(
  const mips_iir_lattice_instance_q15 * S,
  const q15 * pSrc,
        q15 * pDst,
        uint32_t blockSize);


/**
 * @brief Initialization function for the Q15 IIR lattice filter.
 * @param[in] S          points to an instance of the fixed-point Q15 IIR lattice structure.
 * @param[in] numStages  number of stages in the filter.
 * @param[in] pkCoeffs   points to reflection coefficient buffer.  The array is of length numStages.
 * @param[in] pvCoeffs   points to ladder coefficient buffer.  The array is of length numStages+1.
 * @param[in] pState     points to state buffer.  The array is of length numStages+blockSize.
 * @param[in] blockSize  number of samples to process per call.
 */
  void mips_iir_lattice_init_q15(
        mips_iir_lattice_instance_q15 * S,
        uint16_t numStages,
        q15 * pkCoeffs,
        q15 * pvCoeffs,
        q15 * pState,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the floating-point LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;    /**< number of coefficients in the filter. */
          f32 *pState;   /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          f32 *pCoeffs;  /**< points to the coefficient array. The array is of length numTaps. */
          f32 mu;        /**< step size that controls filter coefficient updates. */
  } mips_lms_instance_f32;


  /**
   * @brief Processing function for floating-point LMS filter.
   * @param[in]  S          points to an instance of the floating-point LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_lms_f32(
  const mips_lms_instance_f32 * S,
  const f32 * pSrc,
        f32 * pRef,
        f32 * pOut,
        f32 * pErr,
        uint32_t blockSize);


  /**
   * @brief Initialization function for floating-point LMS filter.
   * @param[in] S          points to an instance of the floating-point LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to the coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   */
  void mips_lms_init_f32(
        mips_lms_instance_f32 * S,
        uint16_t numTaps,
        f32 * pCoeffs,
        f32 * pState,
        f32 mu,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the Q15 LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;    /**< number of coefficients in the filter. */
          q15 *pState;       /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          q15 *pCoeffs;      /**< points to the coefficient array. The array is of length numTaps. */
          q15 mu;            /**< step size that controls filter coefficient updates. */
          uint32_t postShift;  /**< bit shift applied to coefficients. */
  } mips_lms_instance_q15;


  /**
   * @brief Initialization function for the Q15 LMS filter.
   * @param[in] S          points to an instance of the Q15 LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to the coefficient buffer.
   * @param[in] pState     points to the state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   * @param[in] postShift  bit shift applied to coefficients.
   */
  void mips_lms_init_q15(
        mips_lms_instance_q15 * S,
        uint16_t numTaps,
        q15 * pCoeffs,
        q15 * pState,
        q15 mu,
        uint32_t blockSize,
        uint32_t postShift);


  /**
   * @brief Processing function for Q15 LMS filter.
   * @param[in]  S          points to an instance of the Q15 LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_lms_q15(
  const mips_lms_instance_q15 * S,
  const q15 * pSrc,
        q15 * pRef,
        q15 * pOut,
        q15 * pErr,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the Q31 LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;    /**< number of coefficients in the filter. */
          q31 *pState;       /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          q31 *pCoeffs;      /**< points to the coefficient array. The array is of length numTaps. */
          q31 mu;            /**< step size that controls filter coefficient updates. */
          uint32_t postShift;  /**< bit shift applied to coefficients. */
  } mips_lms_instance_q31;


  /**
   * @brief Processing function for Q31 LMS filter.
   * @param[in]  S          points to an instance of the Q15 LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_lms_q31(
  const mips_lms_instance_q31 * S,
  const q31 * pSrc,
        q31 * pRef,
        q31 * pOut,
        q31 * pErr,
        uint32_t blockSize);


  /**
   * @brief Initialization function for Q31 LMS filter.
   * @param[in] S          points to an instance of the Q31 LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   * @param[in] postShift  bit shift applied to coefficients.
   */
  void mips_lms_init_q31(
        mips_lms_instance_q31 * S,
        uint16_t numTaps,
        q31 * pCoeffs,
        q31 * pState,
        q31 mu,
        uint32_t blockSize,
        uint32_t postShift);


  /**
   * @brief Instance structure for the floating-point normalized LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< number of coefficients in the filter. */
          f32 *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          f32 *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
          f32 mu;         /**< step size that control filter coefficient updates. */
          f32 energy;     /**< saves previous frame energy. */
          f32 x0;         /**< saves previous input sample. */
  } mips_lms_norm_instance_f32;


  /**
   * @brief Processing function for floating-point normalized LMS filter.
   * @param[in]  S          points to an instance of the floating-point normalized LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_lms_norm_f32(
        mips_lms_norm_instance_f32 * S,
  const f32 * pSrc,
        f32 * pRef,
        f32 * pOut,
        f32 * pErr,
        uint32_t blockSize);


  /**
   * @brief Initialization function for floating-point normalized LMS filter.
   * @param[in] S          points to an instance of the floating-point LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   */
  void mips_lms_norm_init_f32(
        mips_lms_norm_instance_f32 * S,
        uint16_t numTaps,
        f32 * pCoeffs,
        f32 * pState,
        f32 mu,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the Q31 normalized LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< number of coefficients in the filter. */
          q31 *pState;        /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          q31 *pCoeffs;       /**< points to the coefficient array. The array is of length numTaps. */
          q31 mu;             /**< step size that controls filter coefficient updates. */
          uint8_t postShift;    /**< bit shift applied to coefficients. */
    const q31 *recipTable;    /**< points to the reciprocal initial value table. */
          q31 energy;         /**< saves previous frame energy. */
          q31 x0;             /**< saves previous input sample. */
  } mips_lms_norm_instance_q31;


  /**
   * @brief Processing function for Q31 normalized LMS filter.
   * @param[in]  S          points to an instance of the Q31 normalized LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_lms_norm_q31(
        mips_lms_norm_instance_q31 * S,
  const q31 * pSrc,
        q31 * pRef,
        q31 * pOut,
        q31 * pErr,
        uint32_t blockSize);


  /**
   * @brief Initialization function for Q31 normalized LMS filter.
   * @param[in] S          points to an instance of the Q31 normalized LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   * @param[in] postShift  bit shift applied to coefficients.
   */
  void mips_lms_norm_init_q31(
        mips_lms_norm_instance_q31 * S,
        uint16_t numTaps,
        q31 * pCoeffs,
        q31 * pState,
        q31 mu,
        uint32_t blockSize,
        uint8_t postShift);


  /**
   * @brief Instance structure for the Q15 normalized LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< Number of coefficients in the filter. */
          q15 *pState;        /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          q15 *pCoeffs;       /**< points to the coefficient array. The array is of length numTaps. */
          q15 mu;             /**< step size that controls filter coefficient updates. */
          uint8_t postShift;    /**< bit shift applied to coefficients. */
    const q15 *recipTable;    /**< Points to the reciprocal initial value table. */
          q15 energy;         /**< saves previous frame energy. */
          q15 x0;             /**< saves previous input sample. */
  } mips_lms_norm_instance_q15;


  /**
   * @brief Processing function for Q15 normalized LMS filter.
   * @param[in]  S          points to an instance of the Q15 normalized LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_lms_norm_q15(
        mips_lms_norm_instance_q15 * S,
  const q15 * pSrc,
        q15 * pRef,
        q15 * pOut,
        q15 * pErr,
        uint32_t blockSize);


  /**
   * @brief Initialization function for Q15 normalized LMS filter.
   * @param[in] S          points to an instance of the Q15 normalized LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   * @param[in] postShift  bit shift applied to coefficients.
   */
  void mips_lms_norm_init_q15(
        mips_lms_norm_instance_q15 * S,
        uint16_t numTaps,
        q15 * pCoeffs,
        q15 * pState,
        q15 mu,
        uint32_t blockSize,
        uint8_t postShift);


  /**
   * @brief Correlation of floating-point sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */
  void mips_correlate_f32(
  const f32 * pSrcA,
        uint32_t srcALen,
  const f32 * pSrcB,
        uint32_t srcBLen,
        f32 * pDst);


  /**
   * @brief Correlation of floating-point sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */
  void mips_correlate_f64(
  const f64 * pSrcA,
        uint32_t srcALen,
  const f64 * pSrcB,
        uint32_t srcBLen,
        f64 * pDst);


/**
 @brief Correlation of Q15 sequences
 @param[in]  pSrcA     points to the first input sequence
 @param[in]  srcALen   length of the first input sequence
 @param[in]  pSrcB     points to the second input sequence
 @param[in]  srcBLen   length of the second input sequence
 @param[out] pDst      points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
 @param[in]  pScratch  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
*/
void mips_correlate_opt_q15(
  const q15 * pSrcA,
        uint32_t srcALen,
  const q15 * pSrcB,
        uint32_t srcBLen,
        q15 * pDst,
        q15 * pScratch);


/**
  @brief Correlation of Q15 sequences.
  @param[in]  pSrcA    points to the first input sequence
  @param[in]  srcALen  length of the first input sequence
  @param[in]  pSrcB    points to the second input sequence
  @param[in]  srcBLen  length of the second input sequence
  @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
 */
  void mips_correlate_q15(
  const q15 * pSrcA,
        uint32_t srcALen,
  const q15 * pSrcB,
        uint32_t srcBLen,
        q15 * pDst);


/**
  @brief         Correlation of Q15 sequences (fast version).
  @param[in]     pSrcA      points to the first input sequence
  @param[in]     srcALen    length of the first input sequence
  @param[in]     pSrcB      points to the second input sequence
  @param[in]     srcBLen    length of the second input sequence
  @param[out]    pDst       points to the location where the output result is written.  Length 2 * max(srcALen, srcBLen) - 1.
  @return        none
 */
void mips_correlate_fast_q15(
  const q15 * pSrcA,
        uint32_t srcALen,
  const q15 * pSrcB,
        uint32_t srcBLen,
        q15 * pDst);


/**
  @brief Correlation of Q15 sequences (fast version).
  @param[in]  pSrcA     points to the first input sequence.
  @param[in]  srcALen   length of the first input sequence.
  @param[in]  pSrcB     points to the second input sequence.
  @param[in]  srcBLen   length of the second input sequence.
  @param[out] pDst      points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
  @param[in]  pScratch  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
 */
void mips_correlate_fast_opt_q15(
  const q15 * pSrcA,
        uint32_t srcALen,
  const q15 * pSrcB,
        uint32_t srcBLen,
        q15 * pDst,
        q15 * pScratch);


  /**
   * @brief Correlation of Q31 sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */
  void mips_correlate_q31(
  const q31 * pSrcA,
        uint32_t srcALen,
  const q31 * pSrcB,
        uint32_t srcBLen,
        q31 * pDst);


/**
  @brief Correlation of Q31 sequences (fast version).
  @param[in]  pSrcA    points to the first input sequence
  @param[in]  srcALen  length of the first input sequence
  @param[in]  pSrcB    points to the second input sequence
  @param[in]  srcBLen  length of the second input sequence
  @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
 */
void mips_correlate_fast_q31(
  const q31 * pSrcA,
        uint32_t srcALen,
  const q31 * pSrcB,
        uint32_t srcBLen,
        q31 * pDst);


 /**
   * @brief Correlation of Q7 sequences.
   * @param[in]  pSrcA      points to the first input sequence.
   * @param[in]  srcALen    length of the first input sequence.
   * @param[in]  pSrcB      points to the second input sequence.
   * @param[in]  srcBLen    length of the second input sequence.
   * @param[out] pDst       points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   * @param[in]  pScratch1  points to scratch buffer(of type q15) of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2  points to scratch buffer (of type q15) of size min(srcALen, srcBLen).
   */
  void mips_correlate_opt_q7(
  const q7 * pSrcA,
        uint32_t srcALen,
  const q7 * pSrcB,
        uint32_t srcBLen,
        q7 * pDst,
        q15 * pScratch1,
        q15 * pScratch2);


  /**
   * @brief Correlation of Q7 sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */
  void mips_correlate_q7(
  const q7 * pSrcA,
        uint32_t srcALen,
  const q7 * pSrcB,
        uint32_t srcBLen,
        q7 * pDst);


  /**
   * @brief Instance structure for the floating-point sparse FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;             /**< number of coefficients in the filter. */
          uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
          f32 *pState;            /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const f32 *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
          uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
          int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } mips_fir_sparse_instance_f32;

  /**
   * @brief Instance structure for the Q31 sparse FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;             /**< number of coefficients in the filter. */
          uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
          q31 *pState;                /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const q31 *pCoeffs;               /**< points to the coefficient array. The array is of length numTaps.*/
          uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
          int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } mips_fir_sparse_instance_q31;

  /**
   * @brief Instance structure for the Q15 sparse FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;             /**< number of coefficients in the filter. */
          uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
          q15 *pState;                /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const q15 *pCoeffs;               /**< points to the coefficient array. The array is of length numTaps.*/
          uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
          int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } mips_fir_sparse_instance_q15;

  /**
   * @brief Instance structure for the Q7 sparse FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;             /**< number of coefficients in the filter. */
          uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
          q7 *pState;                 /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const q7 *pCoeffs;                /**< points to the coefficient array. The array is of length numTaps.*/
          uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
          int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } mips_fir_sparse_instance_q7;


  /**
   * @brief Processing function for the floating-point sparse FIR filter.
   * @param[in]  S           points to an instance of the floating-point sparse FIR structure.
   * @param[in]  pSrc        points to the block of input data.
   * @param[out] pDst        points to the block of output data
   * @param[in]  pScratchIn  points to a temporary buffer of size blockSize.
   * @param[in]  blockSize   number of input samples to process per call.
   */
  void mips_fir_sparse_f32(
        mips_fir_sparse_instance_f32 * S,
  const f32 * pSrc,
        f32 * pDst,
        f32 * pScratchIn,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the floating-point sparse FIR filter.
   * @param[in,out] S          points to an instance of the floating-point sparse FIR structure.
   * @param[in]     numTaps    number of nonzero coefficients in the filter.
   * @param[in]     pCoeffs    points to the array of filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     pTapDelay  points to the array of offset times.
   * @param[in]     maxDelay   maximum offset time supported.
   * @param[in]     blockSize  number of samples that will be processed per block.
   */
  void mips_fir_sparse_init_f32(
        mips_fir_sparse_instance_f32 * S,
        uint16_t numTaps,
  const f32 * pCoeffs,
        f32 * pState,
        int32_t * pTapDelay,
        uint16_t maxDelay,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 sparse FIR filter.
   * @param[in]  S           points to an instance of the Q31 sparse FIR structure.
   * @param[in]  pSrc        points to the block of input data.
   * @param[out] pDst        points to the block of output data
   * @param[in]  pScratchIn  points to a temporary buffer of size blockSize.
   * @param[in]  blockSize   number of input samples to process per call.
   */
  void mips_fir_sparse_q31(
        mips_fir_sparse_instance_q31 * S,
  const q31 * pSrc,
        q31 * pDst,
        q31 * pScratchIn,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q31 sparse FIR filter.
   * @param[in,out] S          points to an instance of the Q31 sparse FIR structure.
   * @param[in]     numTaps    number of nonzero coefficients in the filter.
   * @param[in]     pCoeffs    points to the array of filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     pTapDelay  points to the array of offset times.
   * @param[in]     maxDelay   maximum offset time supported.
   * @param[in]     blockSize  number of samples that will be processed per block.
   */
  void mips_fir_sparse_init_q31(
        mips_fir_sparse_instance_q31 * S,
        uint16_t numTaps,
  const q31 * pCoeffs,
        q31 * pState,
        int32_t * pTapDelay,
        uint16_t maxDelay,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q15 sparse FIR filter.
   * @param[in]  S            points to an instance of the Q15 sparse FIR structure.
   * @param[in]  pSrc         points to the block of input data.
   * @param[out] pDst         points to the block of output data
   * @param[in]  pScratchIn   points to a temporary buffer of size blockSize.
   * @param[in]  pScratchOut  points to a temporary buffer of size blockSize.
   * @param[in]  blockSize    number of input samples to process per call.
   */
  void mips_fir_sparse_q15(
        mips_fir_sparse_instance_q15 * S,
  const q15 * pSrc,
        q15 * pDst,
        q15 * pScratchIn,
        q31 * pScratchOut,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q15 sparse FIR filter.
   * @param[in,out] S          points to an instance of the Q15 sparse FIR structure.
   * @param[in]     numTaps    number of nonzero coefficients in the filter.
   * @param[in]     pCoeffs    points to the array of filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     pTapDelay  points to the array of offset times.
   * @param[in]     maxDelay   maximum offset time supported.
   * @param[in]     blockSize  number of samples that will be processed per block.
   */
  void mips_fir_sparse_init_q15(
        mips_fir_sparse_instance_q15 * S,
        uint16_t numTaps,
  const q15 * pCoeffs,
        q15 * pState,
        int32_t * pTapDelay,
        uint16_t maxDelay,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q7 sparse FIR filter.
   * @param[in]  S            points to an instance of the Q7 sparse FIR structure.
   * @param[in]  pSrc         points to the block of input data.
   * @param[out] pDst         points to the block of output data
   * @param[in]  pScratchIn   points to a temporary buffer of size blockSize.
   * @param[in]  pScratchOut  points to a temporary buffer of size blockSize.
   * @param[in]  blockSize    number of input samples to process per call.
   */
  void mips_fir_sparse_q7(
        mips_fir_sparse_instance_q7 * S,
  const q7 * pSrc,
        q7 * pDst,
        q7 * pScratchIn,
        q31 * pScratchOut,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q7 sparse FIR filter.
   * @param[in,out] S          points to an instance of the Q7 sparse FIR structure.
   * @param[in]     numTaps    number of nonzero coefficients in the filter.
   * @param[in]     pCoeffs    points to the array of filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     pTapDelay  points to the array of offset times.
   * @param[in]     maxDelay   maximum offset time supported.
   * @param[in]     blockSize  number of samples that will be processed per block.
   */
  void mips_fir_sparse_init_q7(
        mips_fir_sparse_instance_q7 * S,
        uint16_t numTaps,
  const q7 * pCoeffs,
        q7 * pState,
        int32_t * pTapDelay,
        uint16_t maxDelay,
        uint32_t blockSize);




 

  /**
   * @brief floating-point Circular write function.
   */
  __STATIC_FORCEINLINE void mips_circularWrite_f32(
  int32_t * circBuffer,
  int32_t L,
  uint16_t * writeOffset,
  int32_t bufferInc,
  const int32_t * src,
  int32_t srcInc,
  uint32_t blockSize)
  {
    uint32_t i = 0U;
    int32_t wOffset;

    /* Copy the value of Index pointer that points
     * to the current location where the input samples to be copied */
    wOffset = *writeOffset;

    /* Loop over the blockSize */
    i = blockSize;

    while (i > 0U)
    {
      /* copy the input sample to the circular buffer */
      circBuffer[wOffset] = *src;

      /* Update the input pointer */
      src += srcInc;

      /* Circularly update wOffset.  Watch out for positive and negative value */
      wOffset += bufferInc;
      if (wOffset >= L)
        wOffset -= L;

      /* Decrement the loop counter */
      i--;
    }

    /* Update the index pointer */
    *writeOffset = (uint16_t)wOffset;
  }



  /**
   * @brief floating-point Circular Read function.
   */
  __STATIC_FORCEINLINE void mips_circularRead_f32(
  int32_t * circBuffer,
  int32_t L,
  int32_t * readOffset,
  int32_t bufferInc,
  int32_t * dst,
  int32_t * dst_base,
  int32_t dst_length,
  int32_t dstInc,
  uint32_t blockSize)
  {
    uint32_t i = 0U;
    int32_t rOffset;
    int32_t* dst_end;

    /* Copy the value of Index pointer that points
     * to the current location from where the input samples to be read */
    rOffset = *readOffset;
    dst_end = dst_base + dst_length;

    /* Loop over the blockSize */
    i = blockSize;

    while (i > 0U)
    {
      /* copy the sample from the circular buffer to the destination buffer */
      *dst = circBuffer[rOffset];

      /* Update the input pointer */
      dst += dstInc;

      if (dst == dst_end)
      {
        dst = dst_base;
      }

      /* Circularly update rOffset.  Watch out for positive and negative value  */
      rOffset += bufferInc;

      if (rOffset >= L)
      {
        rOffset -= L;
      }

      /* Decrement the loop counter */
      i--;
    }

    /* Update the index pointer */
    *readOffset = rOffset;
  }


  /**
   * @brief Q15 Circular write function.
   */
  __STATIC_FORCEINLINE void mips_circularWrite_q15(
  q15 * circBuffer,
  int32_t L,
  uint16_t * writeOffset,
  int32_t bufferInc,
  const q15 * src,
  int32_t srcInc,
  uint32_t blockSize)
  {
    uint32_t i = 0U;
    int32_t wOffset;

    /* Copy the value of Index pointer that points
     * to the current location where the input samples to be copied */
    wOffset = *writeOffset;

    /* Loop over the blockSize */
    i = blockSize;

    while (i > 0U)
    {
      /* copy the input sample to the circular buffer */
      circBuffer[wOffset] = *src;

      /* Update the input pointer */
      src += srcInc;

      /* Circularly update wOffset.  Watch out for positive and negative value */
      wOffset += bufferInc;
      if (wOffset >= L)
        wOffset -= L;

      /* Decrement the loop counter */
      i--;
    }

    /* Update the index pointer */
    *writeOffset = (uint16_t)wOffset;
  }


  /**
   * @brief Q15 Circular Read function.
   */
  __STATIC_FORCEINLINE void mips_circularRead_q15(
  q15 * circBuffer,
  int32_t L,
  int32_t * readOffset,
  int32_t bufferInc,
  q15 * dst,
  q15 * dst_base,
  int32_t dst_length,
  int32_t dstInc,
  uint32_t blockSize)
  {
    uint32_t i = 0;
    int32_t rOffset;
    q15* dst_end;

    /* Copy the value of Index pointer that points
     * to the current location from where the input samples to be read */
    rOffset = *readOffset;

    dst_end = dst_base + dst_length;

    /* Loop over the blockSize */
    i = blockSize;

    while (i > 0U)
    {
      /* copy the sample from the circular buffer to the destination buffer */
      *dst = circBuffer[rOffset];

      /* Update the input pointer */
      dst += dstInc;

      if (dst == dst_end)
      {
        dst = dst_base;
      }

      /* Circularly update wOffset.  Watch out for positive and negative value */
      rOffset += bufferInc;

      if (rOffset >= L)
      {
        rOffset -= L;
      }

      /* Decrement the loop counter */
      i--;
    }

    /* Update the index pointer */
    *readOffset = rOffset;
  }


  /**
   * @brief Q7 Circular write function.
   */
  __STATIC_FORCEINLINE void mips_circularWrite_q7(
  q7 * circBuffer,
  int32_t L,
  uint16_t * writeOffset,
  int32_t bufferInc,
  const q7 * src,
  int32_t srcInc,
  uint32_t blockSize)
  {
    uint32_t i = 0U;
    int32_t wOffset;

    /* Copy the value of Index pointer that points
     * to the current location where the input samples to be copied */
    wOffset = *writeOffset;

    /* Loop over the blockSize */
    i = blockSize;

    while (i > 0U)
    {
      /* copy the input sample to the circular buffer */
      circBuffer[wOffset] = *src;

      /* Update the input pointer */
      src += srcInc;

      /* Circularly update wOffset.  Watch out for positive and negative value */
      wOffset += bufferInc;
      if (wOffset >= L)
        wOffset -= L;

      /* Decrement the loop counter */
      i--;
    }

    /* Update the index pointer */
    *writeOffset = (uint16_t)wOffset;
  }


  /**
   * @brief Q7 Circular Read function.
   */
  __STATIC_FORCEINLINE void mips_circularRead_q7(
  q7 * circBuffer,
  int32_t L,
  int32_t * readOffset,
  int32_t bufferInc,
  q7 * dst,
  q7 * dst_base,
  int32_t dst_length,
  int32_t dstInc,
  uint32_t blockSize)
  {
    uint32_t i = 0;
    int32_t rOffset;
    q7* dst_end;

    /* Copy the value of Index pointer that points
     * to the current location from where the input samples to be read */
    rOffset = *readOffset;

    dst_end = dst_base + dst_length;

    /* Loop over the blockSize */
    i = blockSize;

    while (i > 0U)
    {
      /* copy the sample from the circular buffer to the destination buffer */
      *dst = circBuffer[rOffset];

      /* Update the input pointer */
      dst += dstInc;

      if (dst == dst_end)
      {
        dst = dst_base;
      }

      /* Circularly update rOffset.  Watch out for positive and negative value */
      rOffset += bufferInc;

      if (rOffset >= L)
      {
        rOffset -= L;
      }

      /* Decrement the loop counter */
      i--;
    }

    /* Update the index pointer */
    *readOffset = rOffset;
  }


/**
  @brief         Levinson Durbin
  @param[in]     phi      autocovariance vector starting with lag 0 (length is nbCoefs + 1)
  @param[out]    a        autoregressive coefficients
  @param[out]    err      prediction error (variance)
  @param[in]     nbCoefs  number of autoregressive coefficients
  @return        none
 */
void mips_levinson_durbin_f32(const f32 *phi,
  f32 *a, 
  f32 *err,
  int nbCoefs);


/**
  @brief         Levinson Durbin
  @param[in]     phi      autocovariance vector starting with lag 0 (length is nbCoefs + 1)
  @param[out]    a        autoregressive coefficients
  @param[out]    err      prediction error (variance)
  @param[in]     nbCoefs  number of autoregressive coefficients
  @return        none
 */
void mips_levinson_durbin_q31(const q31 *phi,
  q31 *a, 
  q31 *err,
  int nbCoefs);

#ifdef   __cplusplus
}
#endif

#endif /* ifndef _FILTERING_FUNCTIONS_H_ */
