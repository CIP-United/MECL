/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_svm_linear_init_f32.c
 * Description:  SVM Linear Instance Initialization
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

#include "dsp/svm_functions.h"
#include <limits.h>
#include <math.h>

/**
 * @defgroup groupSVM SVM Functions
 *
 */

/**
  @ingroup groupSVM
 */

/**
  @defgroup linearsvm Linear SVM

  Linear SVM classifier
 */

/**
 * @addtogroup linearsvm
 * @{
 */


/**
 * @brief        SVM linear instance init function
 *
 * Classes are integer used as output of the function (instead of having -1,1
 * as class values).
 *
 * @param[in]    S                      Parameters for the SVM function
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
  const int32_t *classes)
{
   S->nbOfSupportVectors = nbOfSupportVectors;
   S->vectorDimension = vectorDimension;
   S->intercept = intercept;
   S->dualCoefficients = dualCoefficients;
   S->supportVectors = supportVectors;
   S->classes = classes;
}



/**
 * @} end of linearsvm group
 */