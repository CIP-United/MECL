/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cfft_q31.c
 * Description:  Combined Radix Decimation in Frequency CFFT fixed point processing function
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

#include "dsp/transform_functions.h"





extern void mips_radix4_butterfly_q31(
        q31 * pSrc,
        uint32_t fftLen,
  const q31 * pCoef,
        uint32_t twidCoefModifier);

extern void mips_radix4_butterfly_inverse_q31(
        q31 * pSrc,
        uint32_t fftLen,
  const q31 * pCoef,
        uint32_t twidCoefModifier);

extern void mips_bitreversal_32(
        uint32_t * pSrc,
  const uint16_t bitRevLen,
  const uint16_t * pBitRevTable);

void mips_cfft_radix4by2_q31(
        q31 * pSrc,
        uint32_t fftLen,
  const q31 * pCoef);

void mips_cfft_radix4by2_inverse_q31(
        q31 * pSrc,
        uint32_t fftLen,
  const q31 * pCoef);


/**
  @ingroup groupTransforms
 */

/**
  @addtogroup ComplexFFT
  @{
 */

/**
  @brief         Processing function for the Q31 complex FFT.
  @param[in]     S               points to an instance of the fixed-point CFFT structure
  @param[in,out] p1              points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place
  @param[in]     ifftFlag       flag that selects transform direction
                   - value = 0: forward transform
                   - value = 1: inverse transform
  @param[in]     bitReverseFlag flag that enables / disables bit reversal of output
                   - value = 0: disables bit reversal of output
                   - value = 1: enables bit reversal of output
  @return        none
 */
void mips_cfft_q31(
  const mips_cfft_instance_q31 * S,
        q31 * p1,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag)
{
  uint32_t L = S->fftLen;

  if (ifftFlag == 1U)
  {
     switch (L)
     {
     case 16:
     case 64:
     case 256:
     case 1024:
     case 4096:
       mips_radix4_butterfly_inverse_q31 ( p1, L, (q31*)S->pTwiddle, 1 );
       break;

     case 32:
     case 128:
     case 512:
     case 2048:
       mips_cfft_radix4by2_inverse_q31 ( p1, L, S->pTwiddle );
       break;
     }
  }
  else
  {
     switch (L)
     {
     case 16:
     case 64:
     case 256:
     case 1024:
     case 4096:
       mips_radix4_butterfly_q31 ( p1, L, (q31*)S->pTwiddle, 1 );
       break;

     case 32:
     case 128:
     case 512:
     case 2048:
       mips_cfft_radix4by2_q31 ( p1, L, S->pTwiddle );
       break;
     }
  }

  if ( bitReverseFlag )
    mips_bitreversal_32 ((uint32_t*) p1, S->bitRevLength, S->pBitRevTable);
}

/**
  @} end of ComplexFFT group
 */

void mips_cfft_radix4by2_q31(
        q31 * pSrc,
        uint32_t fftLen,
  const q31 * pCoef)
{
        uint32_t i, l;
        uint32_t n2;
        q31 xt, yt, cosVal, sinVal;
        q31 p0, p1;

  n2 = fftLen >> 1U;
  for (i = 0; i < n2; i++)
  {
     cosVal = pCoef[2 * i];
     sinVal = pCoef[2 * i + 1];

     l = i + n2;

     xt =          (pSrc[2 * i] >> 2U) - (pSrc[2 * l] >> 2U);
     pSrc[2 * i] = (pSrc[2 * i] >> 2U) + (pSrc[2 * l] >> 2U);

     yt =              (pSrc[2 * i + 1] >> 2U) - (pSrc[2 * l + 1] >> 2U);
     pSrc[2 * i + 1] = (pSrc[2 * l + 1] >> 2U) + (pSrc[2 * i + 1] >> 2U);

     mult_32x32_keep32_R(p0, xt, cosVal);
     mult_32x32_keep32_R(p1, yt, cosVal);
     multAcc_32x32_keep32_R(p0, yt, sinVal);
     multSub_32x32_keep32_R(p1, xt, sinVal);

     pSrc[2 * l]     = p0 << 1;
     pSrc[2 * l + 1] = p1 << 1;
  }


  /* first col */
  mips_radix4_butterfly_q31 (pSrc,          n2, (q31*)pCoef, 2U);

  /* second col */
  mips_radix4_butterfly_q31 (pSrc + fftLen, n2, (q31*)pCoef, 2U);

  n2 = fftLen >> 1U;
  for (i = 0; i < n2; i++)
  {
     p0 = pSrc[4 * i + 0];
     p1 = pSrc[4 * i + 1];
     xt = pSrc[4 * i + 2];
     yt = pSrc[4 * i + 3];

     p0 <<= 1U;
     p1 <<= 1U;
     xt <<= 1U;
     yt <<= 1U;

     pSrc[4 * i + 0] = p0;
     pSrc[4 * i + 1] = p1;
     pSrc[4 * i + 2] = xt;
     pSrc[4 * i + 3] = yt;
  }

}

void mips_cfft_radix4by2_inverse_q31(
        q31 * pSrc,
        uint32_t fftLen,
  const q31 * pCoef)
{
  uint32_t i, l;
  uint32_t n2;
  q31 xt, yt, cosVal, sinVal;
  q31 p0, p1;

  n2 = fftLen >> 1U;
  for (i = 0; i < n2; i++)
  {
     cosVal = pCoef[2 * i];
     sinVal = pCoef[2 * i + 1];

     l = i + n2;

     xt =          (pSrc[2 * i] >> 2U) - (pSrc[2 * l] >> 2U);
     pSrc[2 * i] = (pSrc[2 * i] >> 2U) + (pSrc[2 * l] >> 2U);

     yt =              (pSrc[2 * i + 1] >> 2U) - (pSrc[2 * l + 1] >> 2U);
     pSrc[2 * i + 1] = (pSrc[2 * l + 1] >> 2U) + (pSrc[2 * i + 1] >> 2U);

     mult_32x32_keep32_R(p0, xt, cosVal);
     mult_32x32_keep32_R(p1, yt, cosVal);
     multSub_32x32_keep32_R(p0, yt, sinVal);
     multAcc_32x32_keep32_R(p1, xt, sinVal);

     pSrc[2 * l]     = p0 << 1U;
     pSrc[2 * l + 1] = p1 << 1U;
  }

  /* first col */
  mips_radix4_butterfly_inverse_q31( pSrc,          n2, (q31*)pCoef, 2U);

  /* second col */
  mips_radix4_butterfly_inverse_q31( pSrc + fftLen, n2, (q31*)pCoef, 2U);

  n2 = fftLen >> 1U;
  for (i = 0; i < n2; i++)
  {
     p0 = pSrc[4 * i + 0];
     p1 = pSrc[4 * i + 1];
     xt = pSrc[4 * i + 2];
     yt = pSrc[4 * i + 3];

     p0 <<= 1U;
     p1 <<= 1U;
     xt <<= 1U;
     yt <<= 1U;

     pSrc[4 * i + 0] = p0;
     pSrc[4 * i + 1] = p1;
     pSrc[4 * i + 2] = xt;
     pSrc[4 * i + 3] = yt;
  }
}

