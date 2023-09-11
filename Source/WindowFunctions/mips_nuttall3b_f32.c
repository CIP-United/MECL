/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_nuttall3b_f32.c
 * Description:  Floating-point (f32) Nuttall3b window
 *
 * $Date:        31 Augest 2023
 * $Revision:    V1.0.0
 *
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2022 ARM Limited or its affiliates. All rights reserved.
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

#include "dsp/window_functions.h"
#include "dsp/fast_math_functions.h"
#include <math.h>

/**
  @ingroup groupWindow
 */




/**
  @addtogroup WindowNormal
  @{
 */

/**
  @defgroup WindowNUTTALL3B Nuttall3b window function (71.5 dB)

 */

/**
  @ingroup WindowNUTTALL3B
 */

/**
  @brief         Nuttall3b window generating function (f32).
  @param[out]    pDst       points to the output generated window
  @param[in]     blockSize  number of samples in the window
  @return        none
 
  @par Parameters of the window
  
  | Parameter                             | Value              |
  | ------------------------------------: | -----------------: |
  | Peak sidelobe level                   |           71.5 dB  |
  | Normalized equivalent noise bandwidth |       1.7037 bins  |
  | 3 dB bandwidth                        |       1.6162 bins  |
  | Flatness                              |        -1.1352 dB  |
  | Recommended overlap                   |            59.8 %  |

 */



void mips_nuttall3b_f32(
        f32 * pDst,
        uint32_t blockSize)
{
   f32 k = 2.0f / ((f32) blockSize);
   f32 w;

   for(uint32_t i=0;i<blockSize;i++)
   {
     w = PI * i * k;
     w = 0.4243801f - 0.4973406f * cosf (w) + 0.0782793f * cosf (2.f * w);
        
     pDst[i] = w;
   }
}

/**
  @} end of WindowNormal group
 */

