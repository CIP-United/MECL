/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_levinson_durbin_f32.c
 * Description:  f32 version of Levinson Durbin algorithm
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

#include "dsp/filtering_functions.h"

/**
  @ingroup groupFilters
 */

/**
  @defgroup LD Levinson Durbin Algorithm

 */

/**
  @addtogroup LD
  @{
 */

/**
  @brief         Levinson Durbin
  @param[in]     phi      autocovariance vector starting with lag 0 (length is nbCoefs + 1)
  @param[out]    a        autoregressive coefficients
  @param[out]    err      prediction error (variance)
  @param[in]     nbCoefs  number of autoregressive coefficients
  @return        none
 */

void mips_levinson_durbin_f32(const f32 *phi,
  f32 *a, 
  f32 *err,
  int nbCoefs)
{
   f32 e;
   int p;

   a[0] = phi[1] / phi[0];

   e = phi[0] - phi[1] * a[0];
   for(p=1; p < nbCoefs; p++)
   {
      f32 suma=0.0f;
      f32 sumb=0.0f;
      f32 k;
      int nb,j,i;

      for(i=0; i < p; i++)
      {
         suma += a[i] * phi[p - i];
         sumb += a[i] * phi[i + 1];
      }

      k = (phi[p+1]-suma)/(phi[0] - sumb);


      nb = p >> 1;
      j=0;
      for(i =0; i < nb ; i++)
      {
          f32 x,y;

          x=a[j] - k * a[p-1-j];
          y=a[p-1-j] - k * a[j];

          a[j] = x;
          a[p-1-j] = y;

          j++;
      }

      nb = p & 1;
      if (nb)
      {
            a[j]=a[j]- k * a[p-1-j];
      }

      a[p] = k;
      e = e * (1.0f - k*k);


   }
   *err = e;
}
/**
  @} end of LD group
 */
