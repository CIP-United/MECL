/******************************************************************************
 * @file     basic_math_functions.h
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

 
#ifndef _DEBUG_FUNCTIONS_H_
#define _DEBUG_FUNCTIONS_H_

#include "mips_math_types.h"
#include "mips_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#include "dsp/matrix_functions.h"

#include <stdio.h>

#ifdef   __cplusplus
extern "C"
{
#endif


#define PROW_f32(S,NB)            \
{                                 \
    printf("{%f",(double)(S)[0]);   \
    for(unsigned int i=1;i<(NB) ;i++)       \
    {                             \
       printf(",%f",(double)(S)[i]);\
    }                             \
    printf("}");                  \
};

#define PV_f32(S,V,NB)\
{                     \
    printf("%s=",(S));  \
    PROW_f32((V),(NB));   \
    printf(";\n");    \
};

#define PM_f32(S,M)                                       \
{                                                         \
    printf("%s={",(S));                                     \
    for(unsigned int row=0;row<(M)->numRows;row++)                   \
    {                                                     \
        if (row != 0)                                     \
        {                                                 \
            printf("\n,");                                \
        }                                                 \
        PROW_f32((M)->pData + row * (M)->numCols, (M)->numCols);\
    }                                                     \
    printf("};\n");                                       \
}

#define PROW_f64(S,NB)            \
{                                 \
    printf("{%.20g",(double)(S)[0]);   \
    for(unsigned int i=1;i<(NB) ;i++)       \
    {                             \
       printf(",%.20g",(double)(S)[i]);\
    }                             \
    printf("}");                  \
};

#define PV_f64(S,V,NB) \
{                      \
    printf("%s=",(S)); \
    PROW_f64((V),(NB));\
    printf(";\n");     \
};

#define PM_f64(S,M)                                       \
{                                                         \
    printf("%s={",(S));                                     \
    for(unsigned int row=0;row<(M)->numRows;row++)                   \
    {                                                     \
        if (row != 0)                                     \
        {                                                 \
            printf("\n,");                                \
        }                                                 \
        PROW_f64((M)->pData + row * (M)->numCols, (M)->numCols);\
    }                                                     \
    printf("};\n");                                       \
}

#ifdef   __cplusplus
}
#endif

#endif /* ifndef _DEBUG_FUNCTIONS_H_ */
