
/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cityblock_distance_f64.c
 * Description:  Cityblock (Manhattan) distance between two vectors
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

#include "dsp/distance_functions.h"
#include <limits.h>
#include <math.h>

/**
  @addtogroup Manhattan
  @{
 */


/**
 * @brief        Cityblock (Manhattan) distance between two vectors
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */
f64 mips_cityblock_distance_f64(const f64 *pA,const f64 *pB, uint32_t blockSize)
{
    f64 accum,tmpA, tmpB;
    uint32_t blkCnt;
    accum = 0.;
    
    blkCnt = blockSize;

    while(blkCnt > 0)
    {
        tmpA = *pA++;
        tmpB = *pB++;
        accum  += fabs(tmpA - tmpB);
        
        blkCnt--;
    }
    
    return(accum);
}

/**
 * @} end of Manhattan group
 */
