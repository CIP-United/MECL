/******************************************************************************
 * @file     transform_functions.h
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

 
#ifndef _TRANSFORM_FUNCTIONS_H_
#define _TRANSFORM_FUNCTIONS_H_

#include "mips_math_types.h"
#include "mips_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#include "dsp/basic_math_functions.h"
#include "dsp/complex_math_functions.h"

#ifdef   __cplusplus
extern "C"
{
#endif


/**
 * @defgroup groupTransforms Transform Functions
 */


  /**
   * @brief Instance structure for the Q15 CFFT/CIFFT function.
   */
  typedef struct
  {
          uint16_t fftLen;                 /**< length of the FFT. */
          uint8_t ifftFlag;                /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
          uint8_t bitReverseFlag;          /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    const q15 *pTwiddle;                 /**< points to the Sin twiddle factor table. */
    const uint16_t *pBitRevTable;          /**< points to the bit reversal table. */
          uint16_t twidCoefModifier;       /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
          uint16_t bitRevFactor;           /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
  } mips_cfft_radix2_instance_q15;

/* Deprecated */
  mips_status mips_cfft_radix2_init_q15(
        mips_cfft_radix2_instance_q15 * S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);

/* Deprecated */
  void mips_cfft_radix2_q15(
  const mips_cfft_radix2_instance_q15 * S,
        q15 * pSrc);


  /**
   * @brief Instance structure for the Q15 CFFT/CIFFT function.
   */
  typedef struct
  {
          uint16_t fftLen;                 /**< length of the FFT. */
          uint8_t ifftFlag;                /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
          uint8_t bitReverseFlag;          /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    const q15 *pTwiddle;                 /**< points to the twiddle factor table. */
    const uint16_t *pBitRevTable;          /**< points to the bit reversal table. */
          uint16_t twidCoefModifier;       /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
          uint16_t bitRevFactor;           /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
  } mips_cfft_radix4_instance_q15;

/* Deprecated */
  mips_status mips_cfft_radix4_init_q15(
        mips_cfft_radix4_instance_q15 * S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);

/* Deprecated */
  void mips_cfft_radix4_q15(
  const mips_cfft_radix4_instance_q15 * S,
        q15 * pSrc);

  /**
   * @brief Instance structure for the Radix-2 Q31 CFFT/CIFFT function.
   */
  typedef struct
  {
          uint16_t fftLen;                 /**< length of the FFT. */
          uint8_t ifftFlag;                /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
          uint8_t bitReverseFlag;          /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    const q31 *pTwiddle;                 /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;          /**< points to the bit reversal table. */
          uint16_t twidCoefModifier;       /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
          uint16_t bitRevFactor;           /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
  } mips_cfft_radix2_instance_q31;

/* Deprecated */
  mips_status mips_cfft_radix2_init_q31(
        mips_cfft_radix2_instance_q31 * S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);

/* Deprecated */
  void mips_cfft_radix2_q31(
  const mips_cfft_radix2_instance_q31 * S,
        q31 * pSrc);

  /**
   * @brief Instance structure for the Q31 CFFT/CIFFT function.
   */
  typedef struct
  {
          uint16_t fftLen;                 /**< length of the FFT. */
          uint8_t ifftFlag;                /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
          uint8_t bitReverseFlag;          /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    const q31 *pTwiddle;                 /**< points to the twiddle factor table. */
    const uint16_t *pBitRevTable;          /**< points to the bit reversal table. */
          uint16_t twidCoefModifier;       /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
          uint16_t bitRevFactor;           /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
  } mips_cfft_radix4_instance_q31;

/* Deprecated */
  void mips_cfft_radix4_q31(
  const mips_cfft_radix4_instance_q31 * S,
        q31 * pSrc);

/* Deprecated */
  mips_status mips_cfft_radix4_init_q31(
        mips_cfft_radix4_instance_q31 * S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);

  /**
   * @brief Instance structure for the floating-point CFFT/CIFFT function.
   */
  typedef struct
  {
          uint16_t fftLen;                   /**< length of the FFT. */
          uint8_t ifftFlag;                  /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
          uint8_t bitReverseFlag;            /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    const f32 *pTwiddle;               /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;            /**< points to the bit reversal table. */
          uint16_t twidCoefModifier;         /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
          uint16_t bitRevFactor;             /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
          f32 onebyfftLen;             /**< value of 1/fftLen. */
  } mips_cfft_radix2_instance_f32;


/* Deprecated */
  mips_status mips_cfft_radix2_init_f32(
        mips_cfft_radix2_instance_f32 * S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);

/* Deprecated */
  void mips_cfft_radix2_f32(
  const mips_cfft_radix2_instance_f32 * S,
        f32 * pSrc);

  /**
   * @brief Instance structure for the floating-point CFFT/CIFFT function.
   */
  typedef struct
  {
          uint16_t fftLen;                   /**< length of the FFT. */
          uint8_t ifftFlag;                  /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
          uint8_t bitReverseFlag;            /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    const f32 *pTwiddle;               /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;            /**< points to the bit reversal table. */
          uint16_t twidCoefModifier;         /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
          uint16_t bitRevFactor;             /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
          f32 onebyfftLen;             /**< value of 1/fftLen. */
  } mips_cfft_radix4_instance_f32;



/* Deprecated */
  mips_status mips_cfft_radix4_init_f32(
        mips_cfft_radix4_instance_f32 * S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);

/* Deprecated */
  void mips_cfft_radix4_f32(
  const mips_cfft_radix4_instance_f32 * S,
        f32 * pSrc);

  /**
   * @brief Instance structure for the fixed-point CFFT/CIFFT function.
   */
  typedef struct
  {
          uint16_t fftLen;                   /**< length of the FFT. */
    const q15 *pTwiddle;             /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;      /**< points to the bit reversal table. */
          uint16_t bitRevLength;             /**< bit reversal table length. */

  } mips_cfft_instance_q15;

mips_status mips_cfft_init_q15(
  mips_cfft_instance_q15 * S,
  uint16_t fftLen);

void mips_cfft_q15(
    const mips_cfft_instance_q15 * S,
          q15 * p1,
          uint8_t ifftFlag,
          uint8_t bitReverseFlag);

  /**
   * @brief Instance structure for the fixed-point CFFT/CIFFT function.
   */
  typedef struct
  {
          uint16_t fftLen;                   /**< length of the FFT. */
    const q31 *pTwiddle;             /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;      /**< points to the bit reversal table. */
          uint16_t bitRevLength;             /**< bit reversal table length. */

  } mips_cfft_instance_q31;

mips_status mips_cfft_init_q31(
  mips_cfft_instance_q31 * S,
  uint16_t fftLen);

void mips_cfft_q31(
    const mips_cfft_instance_q31 * S,
          q31 * p1,
          uint8_t ifftFlag,
          uint8_t bitReverseFlag);

  /**
   * @brief Instance structure for the floating-point CFFT/CIFFT function.
   */
  typedef struct
  {
          uint16_t fftLen;                   /**< length of the FFT. */
    const f32 *pTwiddle;         /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;      /**< points to the bit reversal table. */
          uint16_t bitRevLength;             /**< bit reversal table length. */

  } mips_cfft_instance_f32;



  mips_status mips_cfft_init_f32(
  mips_cfft_instance_f32 * S,
  uint16_t fftLen);

  void mips_cfft_f32(
  const mips_cfft_instance_f32 * S,
        f32 * p1,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);


  /**
   * @brief Instance structure for the Double Precision Floating-point CFFT/CIFFT function.
   */
  typedef struct
  {
          uint16_t fftLen;                   /**< length of the FFT. */
    const f64 *pTwiddle;         /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;      /**< points to the bit reversal table. */
          uint16_t bitRevLength;             /**< bit reversal table length. */
  } mips_cfft_instance_f64;

  mips_status mips_cfft_init_f64(
  mips_cfft_instance_f64 * S,
  uint16_t fftLen);
  
  void mips_cfft_f64(
  const mips_cfft_instance_f64 * S,
        f64 * p1,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);

  /**
   * @brief Instance structure for the Q15 RFFT/RIFFT function.
   */
  typedef struct
  {
          uint32_t fftLenReal;                      /**< length of the real FFT. */
          uint8_t ifftFlagR;                        /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
          uint8_t bitReverseFlagR;                  /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
          uint32_t twidCoefRModifier;               /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    const q15 *pTwiddleAReal;                     /**< points to the real twiddle factor table. */
    const q15 *pTwiddleBReal;                     /**< points to the imag twiddle factor table. */

    const mips_cfft_instance_q15 *pCfft;       /**< points to the complex FFT instance. */

  } mips_rfft_instance_q15;

  mips_status mips_rfft_init_q15(
        mips_rfft_instance_q15 * S,
        uint32_t fftLenReal,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  void mips_rfft_q15(
  const mips_rfft_instance_q15 * S,
        q15 * pSrc,
        q15 * pDst);

  /**
   * @brief Instance structure for the Q31 RFFT/RIFFT function.
   */
  typedef struct
  {
          uint32_t fftLenReal;                        /**< length of the real FFT. */
          uint8_t ifftFlagR;                          /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
          uint8_t bitReverseFlagR;                    /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
          uint32_t twidCoefRModifier;                 /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    const q31 *pTwiddleAReal;                       /**< points to the real twiddle factor table. */
    const q31 *pTwiddleBReal;                       /**< points to the imag twiddle factor table. */

    const mips_cfft_instance_q31 *pCfft;         /**< points to the complex FFT instance. */

  } mips_rfft_instance_q31;

  mips_status mips_rfft_init_q31(
        mips_rfft_instance_q31 * S,
        uint32_t fftLenReal,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  void mips_rfft_q31(
  const mips_rfft_instance_q31 * S,
        q31 * pSrc,
        q31 * pDst);

  /**
   * @brief Instance structure for the floating-point RFFT/RIFFT function.
   */
  typedef struct
  {
          uint32_t fftLenReal;                        /**< length of the real FFT. */
          uint16_t fftLenBy2;                         /**< length of the complex FFT. */
          uint8_t ifftFlagR;                          /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
          uint8_t bitReverseFlagR;                    /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
          uint32_t twidCoefRModifier;                     /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    const f32 *pTwiddleAReal;                   /**< points to the real twiddle factor table. */
    const f32 *pTwiddleBReal;                   /**< points to the imag twiddle factor table. */
          mips_cfft_radix4_instance_f32 *pCfft;        /**< points to the complex FFT instance. */
  } mips_rfft_instance_f32;

  mips_status mips_rfft_init_f32(
        mips_rfft_instance_f32 * S,
        mips_cfft_radix4_instance_f32 * S_CFFT,
        uint32_t fftLenReal,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  void mips_rfft_f32(
  const mips_rfft_instance_f32 * S,
        f32 * pSrc,
        f32 * pDst);

  /**
   * @brief Instance structure for the Double Precision Floating-point RFFT/RIFFT function.
   */
typedef struct
  {
          mips_cfft_instance_f64 Sint;      /**< Internal CFFT structure. */
          uint16_t fftLenRFFT;             /**< length of the real sequence */
    const f64 * pTwiddleRFFT;        /**< Twiddle factors real stage  */
  } mips_rfft_fast_instance_f64 ;

mips_status mips_rfft_fast_init_f64 (
         mips_rfft_fast_instance_f64 * S,
         uint16_t fftLen);


void mips_rfft_fast_f64(
    mips_rfft_fast_instance_f64 * S,
    f64 * p, f64 * pOut,
    uint8_t ifftFlag);


  /**
   * @brief Instance structure for the floating-point RFFT/RIFFT function.
   */
typedef struct
  {
          mips_cfft_instance_f32 Sint;      /**< Internal CFFT structure. */
          uint16_t fftLenRFFT;             /**< length of the real sequence */
    const f32 * pTwiddleRFFT;        /**< Twiddle factors real stage  */
  } mips_rfft_fast_instance_f32 ;

mips_status mips_rfft_fast_init_f32 (
         mips_rfft_fast_instance_f32 * S,
         uint16_t fftLen);


  void mips_rfft_fast_f32(
        const mips_rfft_fast_instance_f32 * S,
        f32 * p, f32 * pOut,
        uint8_t ifftFlag);

  /**
   * @brief Instance structure for the floating-point DCT4/IDCT4 function.
   */
  typedef struct
  {
          uint16_t N;                          /**< length of the DCT4. */
          uint16_t Nby2;                       /**< half of the length of the DCT4. */
          f32 normalize;                 /**< normalizing factor. */
    const f32 *pTwiddle;                 /**< points to the twiddle factor table. */
    const f32 *pCosFactor;               /**< points to the cosFactor table. */
          mips_rfft_instance_f32 *pRfft;        /**< points to the real FFT instance. */
          mips_cfft_radix4_instance_f32 *pCfft; /**< points to the complex FFT instance. */
  } mips_dct4_instance_f32;


  /**
   * @brief  Initialization function for the floating-point DCT4/IDCT4.
   * @param[in,out] S          points to an instance of floating-point DCT4/IDCT4 structure.
   * @param[in]     S_RFFT     points to an instance of floating-point RFFT/RIFFT structure.
   * @param[in]     S_CFFT     points to an instance of floating-point CFFT/CIFFT structure.
   * @param[in]     N          length of the DCT4.
   * @param[in]     Nby2       half of the length of the DCT4.
   * @param[in]     normalize  normalizing factor.
   * @return      mips_status function returns MIPS_MATH_SUCCESS if initialization is successful or MIPS_MATH_ARGUMENT_ERROR if <code>fftLenReal</code> is not a supported transform length.
   */
  mips_status mips_dct4_init_f32(
        mips_dct4_instance_f32 * S,
        mips_rfft_instance_f32 * S_RFFT,
        mips_cfft_radix4_instance_f32 * S_CFFT,
        uint16_t N,
        uint16_t Nby2,
        f32 normalize);


  /**
   * @brief Processing function for the floating-point DCT4/IDCT4.
   * @param[in]     S              points to an instance of the floating-point DCT4/IDCT4 structure.
   * @param[in]     pState         points to state buffer.
   * @param[in,out] pInlineBuffer  points to the in-place input and output buffer.
   */
  void mips_dct4_f32(
  const mips_dct4_instance_f32 * S,
        f32 * pState,
        f32 * pInlineBuffer);


  /**
   * @brief Instance structure for the Q31 DCT4/IDCT4 function.
   */
  typedef struct
  {
          uint16_t N;                          /**< length of the DCT4. */
          uint16_t Nby2;                       /**< half of the length of the DCT4. */
          q31 normalize;                     /**< normalizing factor. */
    const q31 *pTwiddle;                     /**< points to the twiddle factor table. */
    const q31 *pCosFactor;                   /**< points to the cosFactor table. */
          mips_rfft_instance_q31 *pRfft;        /**< points to the real FFT instance. */
          mips_cfft_radix4_instance_q31 *pCfft; /**< points to the complex FFT instance. */
  } mips_dct4_instance_q31;


  /**
   * @brief  Initialization function for the Q31 DCT4/IDCT4.
   * @param[in,out] S          points to an instance of Q31 DCT4/IDCT4 structure.
   * @param[in]     S_RFFT     points to an instance of Q31 RFFT/RIFFT structure
   * @param[in]     S_CFFT     points to an instance of Q31 CFFT/CIFFT structure
   * @param[in]     N          length of the DCT4.
   * @param[in]     Nby2       half of the length of the DCT4.
   * @param[in]     normalize  normalizing factor.
   * @return      mips_status function returns MIPS_MATH_SUCCESS if initialization is successful or MIPS_MATH_ARGUMENT_ERROR if <code>N</code> is not a supported transform length.
   */
  mips_status mips_dct4_init_q31(
        mips_dct4_instance_q31 * S,
        mips_rfft_instance_q31 * S_RFFT,
        mips_cfft_radix4_instance_q31 * S_CFFT,
        uint16_t N,
        uint16_t Nby2,
        q31 normalize);


  /**
   * @brief Processing function for the Q31 DCT4/IDCT4.
   * @param[in]     S              points to an instance of the Q31 DCT4 structure.
   * @param[in]     pState         points to state buffer.
   * @param[in,out] pInlineBuffer  points to the in-place input and output buffer.
   */
  void mips_dct4_q31(
  const mips_dct4_instance_q31 * S,
        q31 * pState,
        q31 * pInlineBuffer);


  /**
   * @brief Instance structure for the Q15 DCT4/IDCT4 function.
   */
  typedef struct
  {
          uint16_t N;                          /**< length of the DCT4. */
          uint16_t Nby2;                       /**< half of the length of the DCT4. */
          q15 normalize;                     /**< normalizing factor. */
    const q15 *pTwiddle;                     /**< points to the twiddle factor table. */
    const q15 *pCosFactor;                   /**< points to the cosFactor table. */
          mips_rfft_instance_q15 *pRfft;        /**< points to the real FFT instance. */
          mips_cfft_radix4_instance_q15 *pCfft; /**< points to the complex FFT instance. */
  } mips_dct4_instance_q15;


  /**
   * @brief  Initialization function for the Q15 DCT4/IDCT4.
   * @param[in,out] S          points to an instance of Q15 DCT4/IDCT4 structure.
   * @param[in]     S_RFFT     points to an instance of Q15 RFFT/RIFFT structure.
   * @param[in]     S_CFFT     points to an instance of Q15 CFFT/CIFFT structure.
   * @param[in]     N          length of the DCT4.
   * @param[in]     Nby2       half of the length of the DCT4.
   * @param[in]     normalize  normalizing factor.
   * @return      mips_status function returns MIPS_MATH_SUCCESS if initialization is successful or MIPS_MATH_ARGUMENT_ERROR if <code>N</code> is not a supported transform length.
   */
  mips_status mips_dct4_init_q15(
        mips_dct4_instance_q15 * S,
        mips_rfft_instance_q15 * S_RFFT,
        mips_cfft_radix4_instance_q15 * S_CFFT,
        uint16_t N,
        uint16_t Nby2,
        q15 normalize);


  /**
   * @brief Processing function for the Q15 DCT4/IDCT4.
   * @param[in]     S              points to an instance of the Q15 DCT4 structure.
   * @param[in]     pState         points to state buffer.
   * @param[in,out] pInlineBuffer  points to the in-place input and output buffer.
   */
  void mips_dct4_q15(
  const mips_dct4_instance_q15 * S,
        q15 * pState,
        q15 * pInlineBuffer);

  /**
   * @brief Instance structure for the Floating-point MFCC function.
   */
typedef struct
  {
     const f32 *dctCoefs; /**< Internal DCT coefficients */
     const f32 *filterCoefs; /**< Internal Mel filter coefficients */ 
     const f32 *windowCoefs; /**< Windowing coefficients */ 
     const uint32_t *filterPos; /**< Internal Mel filter positions in spectrum */ 
     const uint32_t *filterLengths; /**< Internal Mel filter  lengths */ 
     uint32_t fftLen; /**< FFT length */
     uint32_t nbMelFilters; /**< Number of Mel filters */
     uint32_t nbDctOutputs; /**< Number of DCT outputs */
#if defined(MIPS_MFCC_CFFT_BASED)
     /* Implementation of the MFCC is using a CFFT */
     mips_cfft_instance_f32 cfft; /**< Internal CFFT instance */
#else
     /* Implementation of the MFCC is using a RFFT (default) */
     mips_rfft_fast_instance_f32 rfft;
#endif
  } mips_mfcc_instance_f32 ;

mips_status mips_mfcc_init_f32(
  mips_mfcc_instance_f32 * S,
  uint32_t fftLen,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const f32 *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const f32 *filterCoefs,
  const f32 *windowCoefs
  );


/**
  @brief         MFCC F32
  @param[in]    S       points to the mfcc instance structure
  @param[in]     pSrc points to the input samples
  @param[out]     pDst  points to the output MFCC values
  @param[inout]     pTmp  points to a temporary buffer of complex
  @return        none
 */
  void mips_mfcc_f32(
  const mips_mfcc_instance_f32 * S,
  f32 *pSrc,
  f32 *pDst,
  f32 *pTmp
  );

typedef struct
  {
     const q31 *dctCoefs; /**< Internal DCT coefficients */
     const q31 *filterCoefs; /**< Internal Mel filter coefficients */ 
     const q31 *windowCoefs; /**< Windowing coefficients */ 
     const uint32_t *filterPos; /**< Internal Mel filter positions in spectrum */ 
     const uint32_t *filterLengths; /**< Internal Mel filter  lengths */ 
     uint32_t fftLen; /**< FFT length */
     uint32_t nbMelFilters; /**< Number of Mel filters */
     uint32_t nbDctOutputs; /**< Number of DCT outputs */
#if defined(MIPS_MFCC_CFFT_BASED)
     /* Implementation of the MFCC is using a CFFT */
     mips_cfft_instance_q31 cfft; /**< Internal CFFT instance */
#else
     /* Implementation of the MFCC is using a RFFT (default) */
     mips_rfft_instance_q31 rfft;
#endif
  } mips_mfcc_instance_q31 ;

mips_status mips_mfcc_init_q31(
  mips_mfcc_instance_q31 * S,
  uint32_t fftLen,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q31 *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q31 *filterCoefs,
  const q31 *windowCoefs
  );


/**
  @brief         MFCC Q31
  @param[in]    S       points to the mfcc instance structure
  @param[in]     pSrc points to the input samples
  @param[out]     pDst  points to the output MFCC values
  @param[inout]     pTmp  points to a temporary buffer of complex
  @return        none
 */
  mips_status mips_mfcc_q31(
  const mips_mfcc_instance_q31 * S,
  q31 *pSrc,
  q31 *pDst,
  q31 *pTmp
  );

typedef struct
  {
     const q15 *dctCoefs; /**< Internal DCT coefficients */
     const q15 *filterCoefs; /**< Internal Mel filter coefficients */ 
     const q15 *windowCoefs; /**< Windowing coefficients */ 
     const uint32_t *filterPos; /**< Internal Mel filter positions in spectrum */ 
     const uint32_t *filterLengths; /**< Internal Mel filter  lengths */ 
     uint32_t fftLen; /**< FFT length */
     uint32_t nbMelFilters; /**< Number of Mel filters */
     uint32_t nbDctOutputs; /**< Number of DCT outputs */
#if defined(MIPS_MFCC_CFFT_BASED)
     /* Implementation of the MFCC is using a CFFT */
     mips_cfft_instance_q15 cfft; /**< Internal CFFT instance */
#else
     /* Implementation of the MFCC is using a RFFT (default) */
     mips_rfft_instance_q15 rfft;
#endif
  } mips_mfcc_instance_q15 ;

mips_status mips_mfcc_init_q15(
  mips_mfcc_instance_q15 * S,
  uint32_t fftLen,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q15 *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q15 *filterCoefs,
  const q15 *windowCoefs
  );


/**
  @brief         MFCC Q15
  @param[in]    S       points to the mfcc instance structure
  @param[in]     pSrc points to the input samples
  @param[out]     pDst  points to the output MFCC values in q8.7 format
  @param[inout]     pTmp  points to a temporary buffer of complex
  @return        error status
 */
  mips_status mips_mfcc_q15(
  const mips_mfcc_instance_q15 * S,
  q15 *pSrc,
  q15 *pDst,
  q31 *pTmp
  );


#ifdef   __cplusplus
}
#endif

#endif /* ifndef _TRANSFORM_FUNCTIONS_H_ */