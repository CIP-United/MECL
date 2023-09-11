/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_hft144d_f32.c
 * Description:  Floating-point (f32) Hft144d window
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
  @addtogroup WindowFlat
  @{
 */

/**
  @defgroup WindowHFT144D Hft144d window function (144.1 dB)

 */

/**
  @ingroup WindowHFT144D
 */

/**
  @brief         Hft144d window generating function (f32).
  @param[out]    pDst       points to the output generated window
  @param[in]     blockSize  number of samples in the window
  @return        none
 
  @par Parameters of the window
  
  | Parameter                             | Value              |
  | ------------------------------------: | -----------------: |
  | Peak sidelobe level                   |          144.1 dB  |
  | Normalized equivalent noise bandwidth |       4.5386 bins  |
  | 3 dB bandwidth                        |       4.4697 bins  |
  | Flatness                              |         0.0021 dB  |
  | Recommended overlap                   |            79.9 %  |

Included in MECL with authorization from professor
Gerhard Heinzel.

@par Original article:
Spectrum and spectral density estimation by the Discrete Fourier
transform (DFT), including a comprehensive list of window
functions and some new 
flat-top windows.

@par Authors: 
G. Heinzel, A. Rudiger and R. Schilling,
Max-Planck-Institut fur Gravitationsphysik
(Albert-Einstein-Institut)
Teilinstitut Hannover
 */



void mips_hft144d_f32(
        f32 * pDst,
        uint32_t blockSize)
{
   f32 k = 2.0f / ((f32) blockSize);
   f32 w;

   for(uint32_t i=0;i<blockSize;i++)
   {
     w = PI * (i * k);
        w =
    (1.0f -
     1.96760033f * cosf (w) +
     1.57983607f * cosf (2.f * w) -
     0.81123644f * cosf (3.f * w) +
     0.22583558f * cosf (4.f * w) -
     0.02773848f * cosf (5.f * w) + 0.00090360f * cosf (6.f * w));
   
     pDst[i] = w;
   }
}

/**
  @} end of WindowFlat group
 */

