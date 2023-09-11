/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cfft_q15.c
 * Description:  Combined Radix Decimation in Q15 Frequency CFFT processing function
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



extern void mips_radix4_butterfly_q15(
        q15 * pSrc,
        uint32_t fftLen,
  const q15 * pCoef,
        uint32_t twidCoefModifier);

extern void mips_radix4_butterfly_inverse_q15(
        q15 * pSrc,
        uint32_t fftLen,
  const q15 * pCoef,
        uint32_t twidCoefModifier);

extern void mips_bitreversal_16(
        uint16_t * pSrc,
  const uint16_t bitRevLen,
  const uint16_t * pBitRevTable);

void mips_cfft_radix4by2_q15(
        q15 * pSrc,
        uint32_t fftLen,
  const q15 * pCoef);

void mips_cfft_radix4by2_inverse_q15(
        q15 * pSrc,
        uint32_t fftLen,
  const q15 * pCoef);

/**
  @ingroup groupTransforms
 */

/**
  @addtogroup ComplexFFT
  @{
 */

/**
  @brief         Processing function for Q15 complex FFT.
  @param[in]     S               points to an instance of Q15 CFFT structure
  @param[in,out] p1              points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place
  @param[in]     ifftFlag       flag that selects transform direction
                   - value = 0: forward transform
                   - value = 1: inverse transform
  @param[in]     bitReverseFlag flag that enables / disables bit reversal of output
                   - value = 0: disables bit reversal of output
                   - value = 1: enables bit reversal of output
  @return        none
 */

void mips_cfft_q15(
  const mips_cfft_instance_q15 * S,
        q15 * p1,
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
       mips_radix4_butterfly_inverse_q15 ( p1, L, (q15*)S->pTwiddle, 1 );
       break;

     case 32:
     case 128:
     case 512:
     case 2048:
       mips_cfft_radix4by2_inverse_q15 ( p1, L, S->pTwiddle );
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
       mips_radix4_butterfly_q15  ( p1, L, (q15*)S->pTwiddle, 1 );
       break;

     case 32:
     case 128:
     case 512:
     case 2048:
       mips_cfft_radix4by2_q15  ( p1, L, S->pTwiddle );
       break;
     }
  }

  if ( bitReverseFlag )
    mips_bitreversal_16 ((uint16_t*) p1, S->bitRevLength, S->pBitRevTable);
}

/**
  @} end of ComplexFFT group
 */

void mips_cfft_radix4by2_q15(
        q15 * pSrc,
        uint32_t fftLen,
  const q15 * pCoef)
{
        uint32_t i;
        uint32_t n2;
        q15 p0, p1, p2, p3;

        uint32_t l;
        q15 xt, yt, cosVal, sinVal;

  n2 = fftLen >> 1U;



  for (i = 0; i < n2; i++)
  {
     cosVal = pCoef[2 * i];
     sinVal = pCoef[2 * i + 1];

     l = i + n2;

     xt =           (pSrc[2 * i] >> 1U) - (pSrc[2 * l] >> 1U);
     pSrc[2 * i] = ((pSrc[2 * i] >> 1U) + (pSrc[2 * l] >> 1U)) >> 1U;

     yt =               (pSrc[2 * i + 1] >> 1U) - (pSrc[2 * l + 1] >> 1U);
     pSrc[2 * i + 1] = ((pSrc[2 * l + 1] >> 1U) + (pSrc[2 * i + 1] >> 1U)) >> 1U;

     pSrc[2 * l]     = (((int16_t) (((q31) xt * cosVal) >> 16U)) +
                        ((int16_t) (((q31) yt * sinVal) >> 16U))  );

     pSrc[2 * l + 1] = (((int16_t) (((q31) yt * cosVal) >> 16U)) -
                        ((int16_t) (((q31) xt * sinVal) >> 16U))   );
  }


  /* first col */
  mips_radix4_butterfly_q15( pSrc,          n2, (q15*)pCoef, 2U);

  /* second col */
  mips_radix4_butterfly_q15( pSrc + fftLen, n2, (q15*)pCoef, 2U);

  n2 = fftLen >> 1U;
  for (i = 0; i < n2; i++)
  {
     p0 = pSrc[4 * i + 0];
     p1 = pSrc[4 * i + 1];
     p2 = pSrc[4 * i + 2];
     p3 = pSrc[4 * i + 3];

     p0 <<= 1U;
     p1 <<= 1U;
     p2 <<= 1U;
     p3 <<= 1U;

     pSrc[4 * i + 0] = p0;
     pSrc[4 * i + 1] = p1;
     pSrc[4 * i + 2] = p2;
     pSrc[4 * i + 3] = p3;
  }

}

void mips_cfft_radix4by2_inverse_q15(
        q15 * pSrc,
        uint32_t fftLen,
  const q15 * pCoef)
{
        uint32_t i;
        uint32_t n2;
        q15 p0, p1, p2, p3;

        uint32_t l;
        q15 xt, yt, cosVal, sinVal;

  n2 = fftLen >> 1U;


  for (i = 0; i < n2; i++)
  {
     cosVal = pCoef[2 * i];
     sinVal = pCoef[2 * i + 1];

     l = i + n2;

     xt =           (pSrc[2 * i] >> 1U) - (pSrc[2 * l] >> 1U);
     pSrc[2 * i] = ((pSrc[2 * i] >> 1U) + (pSrc[2 * l] >> 1U)) >> 1U;

     yt =               (pSrc[2 * i + 1] >> 1U) - (pSrc[2 * l + 1] >> 1U);
     pSrc[2 * i + 1] = ((pSrc[2 * l + 1] >> 1U) + (pSrc[2 * i + 1] >> 1U)) >> 1U;

     pSrc[2 * l]      = (((int16_t) (((q31) xt * cosVal) >> 16U)) -
                         ((int16_t) (((q31) yt * sinVal) >> 16U))  );

     pSrc[2 * l + 1] = (((int16_t) (((q31) yt * cosVal) >> 16U)) +
                        ((int16_t) (((q31) xt * sinVal) >> 16U))  );
  }


  /* first col */
  mips_radix4_butterfly_inverse_q15( pSrc,          n2, (q15*)pCoef, 2U);

  /* second col */
  mips_radix4_butterfly_inverse_q15( pSrc + fftLen, n2, (q15*)pCoef, 2U);

  n2 = fftLen >> 1U;
  for (i = 0; i < n2; i++)
  {
     p0 = pSrc[4 * i + 0];
     p1 = pSrc[4 * i + 1];
     p2 = pSrc[4 * i + 2];
     p3 = pSrc[4 * i + 3];

     p0 <<= 1U;
     p1 <<= 1U;
     p2 <<= 1U;
     p3 <<= 1U;

     pSrc[4 * i + 0] = p0;
     pSrc[4 * i + 1] = p1;
     pSrc[4 * i + 2] = p2;
     pSrc[4 * i + 3] = p3;
  }
}


