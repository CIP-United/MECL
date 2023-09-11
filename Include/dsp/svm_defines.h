/******************************************************************************
 * @file     svm_defines.h
 * @brief    Public header file for MIPS Embedded Compute Library
 * @version  V1.0.0
 * @date     31 Augest 2023
 *
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

 
#ifndef _SVM_DEFINES_H_
#define _SVM_DEFINES_H_

/**
 * @brief Struct for specifying SVM Kernel
 */
typedef enum
{
    MIPS_ML_KERNEL_LINEAR = 0,
             /**< Linear kernel */
    MIPS_ML_KERNEL_POLYNOMIAL = 1,
             /**< Polynomial kernel */
    MIPS_ML_KERNEL_RBF = 2,
             /**< Radial Basis Function kernel */
    MIPS_ML_KERNEL_SIGMOID = 3
             /**< Sigmoid kernel */
} mips_ml_kernel_type;

#endif
