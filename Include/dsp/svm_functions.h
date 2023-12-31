/******************************************************************************
 * @file     svm_functions.h
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

 
#ifndef _SVM_FUNCTIONS_H_
#define _SVM_FUNCTIONS_H_

#include "mips_math_types.h"
#include "mips_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"
#include "dsp/svm_defines.h"

#ifdef   __cplusplus
extern "C"
{
#endif

#define STEP(x) (x) <= 0 ? 0 : 1

/**
 * @defgroup groupSVM SVM Functions
 * This set of functions is implementing SVM classification on 2 classes.
 * The training must be done from scikit-learn. The parameters can be easily
 * generated from the scikit-learn object. Some examples are given in
 * DSP/Testing/PatternGeneration/SVM.py
 *
 * If more than 2 classes are needed, the functions in this folder 
 * will have to be used, as building blocks, to do multi-class classification.
 *
 * No multi-class classification is provided in this SVM folder.
 * 
 */

/**
 * @brief Integer exponentiation
 * @param[in]    x           value
 * @param[in]    nb          integer exponent >= 1
 * @return x^nb
 *
 */
__STATIC_INLINE f32 mips_exponent_f32(f32 x, int32_t nb)
{
    f32 r = x;
    nb --;
    while(nb > 0)
    {
        r = r * x;
        nb--;
    }
    return(r);
}

  



/**
 * @brief Instance structure for linear SVM prediction function.
 */
typedef struct
{
  uint32_t        nbOfSupportVectors;     /**< Number of support vectors */
  uint32_t        vectorDimension;        /**< Dimension of vector space */
  f32       intercept;              /**< Intercept */
  const f32 *dualCoefficients;      /**< Dual coefficients */
  const f32 *supportVectors;        /**< Support vectors */
  const int32_t   *classes;               /**< The two SVM classes */
} mips_svm_linear_instance_f32;


/**
 * @brief Instance structure for polynomial SVM prediction function.
 */
typedef struct
{
  uint32_t        nbOfSupportVectors;     /**< Number of support vectors */
  uint32_t        vectorDimension;        /**< Dimension of vector space */
  f32       intercept;              /**< Intercept */
  const f32 *dualCoefficients;      /**< Dual coefficients */
  const f32 *supportVectors;        /**< Support vectors */
  const int32_t   *classes;               /**< The two SVM classes */
  int32_t         degree;                 /**< Polynomial degree */
  f32       coef0;                  /**< Polynomial constant */
  f32       gamma;                  /**< Gamma factor */
} mips_svm_polynomial_instance_f32;

/**
 * @brief Instance structure for rbf SVM prediction function.
 */
typedef struct
{
  uint32_t        nbOfSupportVectors;     /**< Number of support vectors */
  uint32_t        vectorDimension;        /**< Dimension of vector space */
  f32       intercept;              /**< Intercept */
  const f32 *dualCoefficients;      /**< Dual coefficients */
  const f32 *supportVectors;        /**< Support vectors */
  const int32_t   *classes;               /**< The two SVM classes */
  f32       gamma;                  /**< Gamma factor */
} mips_svm_rbf_instance_f32;

/**
 * @brief Instance structure for sigmoid SVM prediction function.
 */
typedef struct
{
  uint32_t        nbOfSupportVectors;     /**< Number of support vectors */
  uint32_t        vectorDimension;        /**< Dimension of vector space */
  f32       intercept;              /**< Intercept */
  const f32 *dualCoefficients;      /**< Dual coefficients */
  const f32 *supportVectors;        /**< Support vectors */
  const int32_t   *classes;               /**< The two SVM classes */
  f32       coef0;                  /**< Independent constant */
  f32       gamma;                  /**< Gamma factor */
} mips_svm_sigmoid_instance_f32;

/**
 * @brief        SVM linear instance init function
 * @param[in]    S                      Parameters for SVM functions
 * @param[in]    nbOfSupportVectors     Number of support vectors
 * @param[in]    vectorDimension        Dimension of vector space
 * @param[in]    intercept              Intercept
 * @param[in]    dualCoefficients       Array of dual coefficients
 * @param[in]    supportVectors         Array of support vectors
 * @param[in]    classes                Array of 2 classes ID
 * @return none.
 *
 */


void mips_svm_linear_init_f32(mips_svm_linear_instance_f32 *S, 
  uint32_t nbOfSupportVectors,
  uint32_t vectorDimension,
  f32 intercept,
  const f32 *dualCoefficients,
  const f32 *supportVectors,
  const int32_t  *classes);

/**
 * @brief SVM linear prediction
 * @param[in]    S          Pointer to an instance of the linear SVM structure.
 * @param[in]    in         Pointer to input vector
 * @param[out]   pResult    Decision value
 * @return none.
 *
 */
  
void mips_svm_linear_predict_f32(const mips_svm_linear_instance_f32 *S, 
   const f32 * in, 
   int32_t * pResult);


/**
 * @brief        SVM polynomial instance init function
 * @param[in]    S                      points to an instance of the polynomial SVM structure.
 * @param[in]    nbOfSupportVectors     Number of support vectors
 * @param[in]    vectorDimension        Dimension of vector space
 * @param[in]    intercept              Intercept
 * @param[in]    dualCoefficients       Array of dual coefficients
 * @param[in]    supportVectors         Array of support vectors
 * @param[in]    classes                Array of 2 classes ID
 * @param[in]    degree                 Polynomial degree
 * @param[in]    coef0                  coeff0 (scikit-learn terminology)
 * @param[in]    gamma                  gamma (scikit-learn terminology)
 * @return none.
 *
 */


void mips_svm_polynomial_init_f32(mips_svm_polynomial_instance_f32 *S, 
  uint32_t nbOfSupportVectors,
  uint32_t vectorDimension,
  f32 intercept,
  const f32 *dualCoefficients,
  const f32 *supportVectors,
  const int32_t   *classes,
  int32_t      degree,
  f32 coef0,
  f32 gamma
  );

/**
 * @brief SVM polynomial prediction
 * @param[in]    S          Pointer to an instance of the polynomial SVM structure.
 * @param[in]    in         Pointer to input vector
 * @param[out]   pResult    Decision value
 * @return none.
 *
 */
void mips_svm_polynomial_predict_f32(const mips_svm_polynomial_instance_f32 *S, 
   const f32 * in, 
   int32_t * pResult);


/**
 * @brief        SVM radial basis function instance init function
 * @param[in]    S                      points to an instance of the polynomial SVM structure.
 * @param[in]    nbOfSupportVectors     Number of support vectors
 * @param[in]    vectorDimension        Dimension of vector space
 * @param[in]    intercept              Intercept
 * @param[in]    dualCoefficients       Array of dual coefficients
 * @param[in]    supportVectors         Array of support vectors
 * @param[in]    classes                Array of 2 classes ID
 * @param[in]    gamma                  gamma (scikit-learn terminology)
 * @return none.
 *
 */

void mips_svm_rbf_init_f32(mips_svm_rbf_instance_f32 *S, 
  uint32_t nbOfSupportVectors,
  uint32_t vectorDimension,
  f32 intercept,
  const f32 *dualCoefficients,
  const f32 *supportVectors,
  const int32_t   *classes,
  f32 gamma
  );

/**
 * @brief SVM rbf prediction
 * @param[in]    S         Pointer to an instance of the rbf SVM structure.
 * @param[in]    in        Pointer to input vector
 * @param[out]   pResult   decision value
 * @return none.
 *
 */
void mips_svm_rbf_predict_f32(const mips_svm_rbf_instance_f32 *S, 
   const f32 * in, 
   int32_t * pResult);

/**
 * @brief        SVM sigmoid instance init function
 * @param[in]    S                      points to an instance of the rbf SVM structure.
 * @param[in]    nbOfSupportVectors     Number of support vectors
 * @param[in]    vectorDimension        Dimension of vector space
 * @param[in]    intercept              Intercept
 * @param[in]    dualCoefficients       Array of dual coefficients
 * @param[in]    supportVectors         Array of support vectors
 * @param[in]    classes                Array of 2 classes ID
 * @param[in]    coef0                  coeff0 (scikit-learn terminology)
 * @param[in]    gamma                  gamma (scikit-learn terminology)
 * @return none.
 *
 */

void mips_svm_sigmoid_init_f32(mips_svm_sigmoid_instance_f32 *S, 
  uint32_t nbOfSupportVectors,
  uint32_t vectorDimension,
  f32 intercept,
  const f32 *dualCoefficients,
  const f32 *supportVectors,
  const int32_t   *classes,
  f32 coef0,
  f32 gamma
  );

/**
 * @brief SVM sigmoid prediction
 * @param[in]    S        Pointer to an instance of the rbf SVM structure.
 * @param[in]    in       Pointer to input vector
 * @param[out]   pResult  Decision value
 * @return none.
 *
 */
void mips_svm_sigmoid_predict_f32(const mips_svm_sigmoid_instance_f32 *S, 
   const f32 * in, 
   int32_t * pResult);




#ifdef   __cplusplus
}
#endif

#endif /* ifndef _SVM_FUNCTIONS_H_ */
