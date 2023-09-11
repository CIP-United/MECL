
/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_canberra_distance_f32.c
 * Description:  Canberra distance between two vectors
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
  @addtogroup Canberra
  @{
 */


/**
 * @brief        Canberra distance between two vectors
 *
 * This function may divide by zero when samples pA[i] and pB[i] are both zero.
 * The result of the computation will be correct. So the division per zero may be
 * ignored.
 *
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */

f32 mips_canberra_distance_f32(const f32 *pA,const f32 *pB, uint32_t blockSize)
{
   f32 accum=0.0f, tmpA, tmpB,diff,sum;

   while(blockSize > 0)
   {
      tmpA = *pA++;
      tmpB = *pB++;

      diff = fabsf(tmpA - tmpB);
      sum = fabsf(tmpA) + fabsf(tmpB);
      if ((tmpA != 0.0f) || (tmpB != 0.0f))
      {
         accum += (diff / sum);
      }
      blockSize --;
   }
   return(accum);
}


/**
 * @} end of Canberra group
 */
