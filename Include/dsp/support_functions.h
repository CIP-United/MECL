/******************************************************************************
 * @file     support_functions.h
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

 
#ifndef _SUPPORT_FUNCTIONS_H_
#define _SUPPORT_FUNCTIONS_H_

#include "mips_math_types.h"
#include "mips_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @defgroup groupSupport Support Functions
 */


/**
   * @brief Converts the elements of the 64 bit floating-point vector to floating-point vector.
   * @param[in]  pSrc       points to the floating-point 64 input vector
   * @param[out] pDst       points to the floating-point output vector
   * @param[in]  blockSize  length of the input vector
   */
  void mips_f64_to_float(
  const f64 * pSrc,
        f32 * pDst,
        uint32_t blockSize);

/**
   * @brief Converts the elements of the 64 bit floating-point vector to Q31 vector.
   * @param[in]  pSrc       points to the floating-point 64 input vector
   * @param[out] pDst       points to the Q31 output vector
   * @param[in]  blockSize  length of the input vector
   */
  void mips_f64_to_q31(
  const f64 * pSrc,
        q31 * pDst,
        uint32_t blockSize);

/**
   * @brief Converts the elements of the 64 bit floating-point vector to Q15 vector.
   * @param[in]  pSrc       points to the floating-point 64 input vector
   * @param[out] pDst       points to the Q15 output vector
   * @param[in]  blockSize  length of the input vector
   */
  void mips_f64_to_q15(
  const f64 * pSrc,
        q15 * pDst,
        uint32_t blockSize);

/**
   * @brief Converts the elements of the 64 bit floating-point vector to Q7 vector.
   * @param[in]  pSrc       points to the floating-point 64 input vector
   * @param[out] pDst       points to the Q7 output vector
   * @param[in]  blockSize  length of the input vector
   */
  void mips_f64_to_q7(
  const f64 * pSrc,
        q7 * pDst,
        uint32_t blockSize);



/**
   * @brief Converts the elements of the floating-point  vector to 64 bit floating-point  vector.
   * @param[in]  pSrc       points to the floating-point input vector
   * @param[out] pDst       points to the 64 bit floating-point output vector
   * @param[in]  blockSize  length of the input vector
   */
  void mips_float_to_f64(
  const f32 * pSrc,
        f64 * pDst,
        uint32_t blockSize);

/**
   * @brief Converts the elements of the floating-point vector to Q31 vector.
   * @param[in]  pSrc       points to the floating-point input vector
   * @param[out] pDst       points to the Q31 output vector
   * @param[in]  blockSize  length of the input vector
   */
  void mips_float_to_q31(
  const f32 * pSrc,
        q31 * pDst,
        uint32_t blockSize);


  /**
   * @brief Converts the elements of the floating-point vector to Q15 vector.
   * @param[in]  pSrc       points to the floating-point input vector
   * @param[out] pDst       points to the Q15 output vector
   * @param[in]  blockSize  length of the input vector
   */
  void mips_float_to_q15(
  const f32 * pSrc,
        q15 * pDst,
        uint32_t blockSize);


  /**
   * @brief Converts the elements of the floating-point vector to Q7 vector.
   * @param[in]  pSrc       points to the floating-point input vector
   * @param[out] pDst       points to the Q7 output vector
   * @param[in]  blockSize  length of the input vector
   */
  void mips_float_to_q7(
  const f32 * pSrc,
        q7 * pDst,
        uint32_t blockSize);

/**
 * @brief  Converts the elements of the Q31 vector to 64 bit floating-point vector.
 * @param[in]  pSrc       is input pointer
 * @param[out] pDst       is output pointer
 * @param[in]  blockSize  is the number of samples to process
 */
void mips_q31_to_f64(
const q31 * pSrc,
      f64 * pDst,
      uint32_t blockSize);

  /**
   * @brief  Converts the elements of the Q31 vector to floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[out] pDst       is output pointer
   * @param[in]  blockSize  is the number of samples to process
   */
  void mips_q31_to_float(
  const q31 * pSrc,
        f32 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Converts the elements of the Q31 vector to Q15 vector.
   * @param[in]  pSrc       is input pointer
   * @param[out] pDst       is output pointer
   * @param[in]  blockSize  is the number of samples to process
   */
  void mips_q31_to_q15(
  const q31 * pSrc,
        q15 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Converts the elements of the Q31 vector to Q7 vector.
   * @param[in]  pSrc       is input pointer
   * @param[out] pDst       is output pointer
   * @param[in]  blockSize  is the number of samples to process
   */
  void mips_q31_to_q7(
  const q31 * pSrc,
        q7 * pDst,
        uint32_t blockSize);

/**
 * @brief  Converts the elements of the Q15 vector to 64 bit floating-point vector.
 * @param[in]  pSrc       is input pointer
 * @param[out] pDst       is output pointer
 * @param[in]  blockSize  is the number of samples to process
 */
void mips_q15_to_f64(
const q15 * pSrc,
      f64 * pDst,
      uint32_t blockSize);

  /**
   * @brief  Converts the elements of the Q15 vector to floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[out] pDst       is output pointer
   * @param[in]  blockSize  is the number of samples to process
   */
  void mips_q15_to_float(
  const q15 * pSrc,
        f32 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Converts the elements of the Q15 vector to Q31 vector.
   * @param[in]  pSrc       is input pointer
   * @param[out] pDst       is output pointer
   * @param[in]  blockSize  is the number of samples to process
   */
  void mips_q15_to_q31(
  const q15 * pSrc,
        q31 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Converts the elements of the Q15 vector to Q7 vector.
   * @param[in]  pSrc       is input pointer
   * @param[out] pDst       is output pointer
   * @param[in]  blockSize  is the number of samples to process
   */
  void mips_q15_to_q7(
  const q15 * pSrc,
        q7 * pDst,
        uint32_t blockSize);

/**
 * @brief  Converts the elements of the Q7 vector to 64 bit floating-point vector.
 * @param[in]  pSrc       is input pointer
 * @param[out] pDst       is output pointer
 * @param[in]  blockSize  is the number of samples to process
 */
void mips_q7_to_f64(
const q7 * pSrc,
      f64 * pDst,
      uint32_t blockSize);

  /**
   * @brief  Converts the elements of the Q7 vector to floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[out] pDst       is output pointer
   * @param[in]  blockSize  is the number of samples to process
   */
  void mips_q7_to_float(
  const q7 * pSrc,
        f32 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Converts the elements of the Q7 vector to Q31 vector.
   * @param[in]  pSrc       input pointer
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void mips_q7_to_q31(
  const q7 * pSrc,
        q31 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Converts the elements of the Q7 vector to Q15 vector.
   * @param[in]  pSrc       input pointer
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void mips_q7_to_q15(
  const q7 * pSrc,
        q15 * pDst,
        uint32_t blockSize);




  
  /**
   * @brief Struct for specifying sorting algorithm
   */
  typedef enum
  {
    MIPS_SORT_BITONIC   = 0,
             /**< Bitonic sort   */
    MIPS_SORT_BUBBLE    = 1,
             /**< Bubble sort    */
    MIPS_SORT_HEAP      = 2,
             /**< Heap sort      */
    MIPS_SORT_INSERTION = 3,
             /**< Insertion sort */
    MIPS_SORT_QUICK     = 4,
             /**< Quick sort     */
    MIPS_SORT_SELECTION = 5
             /**< Selection sort */
  } mips_sort_alg;

  /**
   * @brief Struct for specifying sorting algorithm
   */
  typedef enum
  {
    MIPS_SORT_DESCENDING = 0,
             /**< Descending order (9 to 0) */
    MIPS_SORT_ASCENDING = 1
             /**< Ascending order (0 to 9) */
  } mips_sort_dir;

  /**
   * @brief Instance structure for the sorting algorithms.
   */
  typedef struct            
  {
    mips_sort_alg alg;        /**< Sorting algorithm selected */
    mips_sort_dir dir;        /**< Sorting order (direction)  */
  } mips_sort_instance_f32;  

  /**
   * @param[in]  S          points to an instance of the sorting structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void mips_sort_f32(
    const mips_sort_instance_f32 * S, 
          f32 * pSrc, 
          f32 * pDst, 
          uint32_t blockSize);

  /**
   * @param[in,out]  S            points to an instance of the sorting structure.
   * @param[in]      alg          Selected algorithm.
   * @param[in]      dir          Sorting order.
   */
  void mips_sort_init_f32(
    mips_sort_instance_f32 * S, 
    mips_sort_alg alg, 
    mips_sort_dir dir); 

  /**
   * @brief Instance structure for the sorting algorithms.
   */
  typedef struct            
  {
    mips_sort_dir dir;        /**< Sorting order (direction)  */
    f32 * buffer;      /**< Working buffer */
  } mips_merge_sort_instance_f32;  

  /**
   * @param[in]      S          points to an instance of the sorting structure.
   * @param[in,out]  pSrc       points to the block of input data.
   * @param[out]     pDst       points to the block of output data
   * @param[in]      blockSize  number of samples to process.
   */
  void mips_merge_sort_f32(
    const mips_merge_sort_instance_f32 * S,
          f32 *pSrc,
          f32 *pDst,
          uint32_t blockSize);

  /**
   * @param[in,out]  S            points to an instance of the sorting structure.
   * @param[in]      dir          Sorting order.
   * @param[in]      buffer       Working buffer.
   */
  void mips_merge_sort_init_f32(
    mips_merge_sort_instance_f32 * S,
    mips_sort_dir dir,
    f32 * buffer);

 
 
  /**
   * @brief  Copies the elements of a floating-point vector.
   * @param[in]  pSrc       input pointer
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void mips_copy_f32(
  const f32 * pSrc,
        f32 * pDst,
        uint32_t blockSize);

 
 
  /**
   * @brief  Copies the elements of a floating-point vector.
   * @param[in]  pSrc       input pointer
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void mips_copy_f64(
  const f64 * pSrc,
        f64 * pDst,
        uint32_t blockSize);



  /**
   * @brief  Copies the elements of a Q7 vector.
   * @param[in]  pSrc       input pointer
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void mips_copy_q7(
  const q7 * pSrc,
        q7 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Copies the elements of a Q15 vector.
   * @param[in]  pSrc       input pointer
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void mips_copy_q15(
  const q15 * pSrc,
        q15 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Copies the elements of a Q31 vector.
   * @param[in]  pSrc       input pointer
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void mips_copy_q31(
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Fills a constant value into a floating-point vector.
   * @param[in]  value      input value to be filled
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void mips_fill_f32(
        f32 value,
        f32 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Fills a constant value into a floating-point vector.
   * @param[in]  value      input value to be filled
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void mips_fill_f64(
        f64 value,
        f64 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Fills a constant value into a Q7 vector.
   * @param[in]  value      input value to be filled
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void mips_fill_q7(
        q7 value,
        q7 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Fills a constant value into a Q15 vector.
   * @param[in]  value      input value to be filled
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void mips_fill_q15(
        q15 value,
        q15 * pDst,
        uint32_t blockSize);


  /**
   * @brief  Fills a constant value into a Q31 vector.
   * @param[in]  value      input value to be filled
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void mips_fill_q31(
        q31 value,
        q31 * pDst,
        uint32_t blockSize);







/**
 * @brief Weighted sum
 *
 *
 * @param[in]    *in           Array of input values.
 * @param[in]    *weigths      Weights
 * @param[in]    blockSize     Number of samples in the input array.
 * @return Weighted sum
 *
 */
f32 mips_weighted_sum_f32(const f32 *in
  , const f32 *weigths
  , uint32_t blockSize);


/**
 * @brief Barycenter
 *
 *
 * @param[in]    in         List of vectors
 * @param[in]    weights    Weights of the vectors
 * @param[out]   out        Barycenter
 * @param[in]    nbVectors  Number of vectors
 * @param[in]    vecDim     Dimension of space (vector dimension)
 * @return       None
 *
 */
void mips_barycenter_f32(const f32 *in
  , const f32 *weights
  , f32 *out
  , uint32_t nbVectors
  , uint32_t vecDim);



#ifdef   __cplusplus
}
#endif

#endif /* ifndef _SUPPORT_FUNCTIONS_H_ */
