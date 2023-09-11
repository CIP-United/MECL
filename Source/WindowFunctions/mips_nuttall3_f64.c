/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_nuttall3_f64.c
 * Description:  Floating-point (f64) Nuttall3 window
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
  @ingroup WindowNUTTALL3
 */

/**
  @brief         Nuttall3 window generating function (f64).
  @param[out]    pDst       points to the output generated window
  @param[in]     blockSize  number of samples in the window
  @return        none
 
  @par Parameters of the window
  
  | Parameter                             | Value              |
  | ------------------------------------: | -----------------: |
  | Peak sidelobe level                   |           46.7 dB  |
  | Normalized equivalent noise bandwidth |       1.9444 bins  |
  | 3 dB bandwidth                        |       1.8496 bins  |
  | Flatness                              |         -0.863 dB  |
  | Recommended overlap                   |            64.7 %  |

 */



void mips_nuttall3_f64(
        f64 * pDst,
        uint32_t blockSize)
{
   f64 k = 2. / ((f64) blockSize);
   f64 w;

   for(uint32_t i=0;i<blockSize;i++)
   {
     w = PI_F64 * i * k;
     w = 0.375 - 0.5 * cos (w) + 0.125 * cos (2 * w);
        
     pDst[i] = w;
   }
}

/**
  @} end of WindowNormal group
 */

