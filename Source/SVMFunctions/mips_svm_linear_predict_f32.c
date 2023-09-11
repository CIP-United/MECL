/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_svm_linear_predict_f32.c
 * Description:  SVM Linear Classifier
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
 * @addtogroup linearsvm
 * @{
 */


/**
 * @brief SVM linear prediction
 * @param[in]    S          Pointer to an instance of the linear SVM structure.
 * @param[in]    in         Pointer to input vector
 * @param[out]   pResult    Decision value
 * @return none.
 *
 */

void mips_svm_linear_predict_f32(
    const mips_svm_linear_instance_f32 *S,
    const f32 * in,
    int32_t * pResult)
{
    f32 sum=S->intercept;
    f32 dot=0;
    uint32_t i,j;
    const f32 *pSupport = S->supportVectors;

    for(i=0; i < S->nbOfSupportVectors; i++)
    {
        dot=0;
        for(j=0; j < S->vectorDimension; j++)
        {
            dot = dot + in[j]* *pSupport++;
        }
        sum += S->dualCoefficients[i] * dot;
    }
    *pResult=S->classes[STEP(sum)];
}


/**
 * @} end of linearsvm group
 */
