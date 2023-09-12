/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cfft_radix2_f32.c
 * Description:  Radix-2 Decimation in Frequency CFFT & CIFFT Floating point processing function
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

void mips_radix2_butterfly_f32(
        f32 * pSrc,
        uint32_t fftLen,
  const f32 * pCoef,
        uint16_t twidCoefModifier);

void mips_radix2_butterfly_inverse_f32(
        f32 * pSrc,
        uint32_t fftLen,
  const f32 * pCoef,
        uint16_t twidCoefModifier,
        f32 onebyfftLen);

extern void mips_bitreversal_f32(
        f32 * pSrc,
        uint16_t fftSize,
        uint16_t bitRevFactor,
  const uint16_t * pBitRevTab);

/**
  @ingroup groupTransforms
 */

/**
  @addtogroup ComplexFFT
  @{
 */

/**
  @brief         Radix-2 CFFT/CIFFT.
  @deprecated    Do not use this function. It has been superseded by \ref mips_cfft_f32 and will be removed in the future
  @param[in]     S    points to an instance of the floating-point Radix-2 CFFT/CIFFT structure
  @param[in,out] pSrc points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place
  @return        none
 */

void mips_cfft_radix2_f32(
const mips_cfft_radix2_instance_f32 * S,
      f32 * pSrc)
{

   if (S->ifftFlag == 1U)
   {
      /* Complex IFFT radix-2 */
      mips_radix2_butterfly_inverse_f32(pSrc, S->fftLen, S->pTwiddle,
      S->twidCoefModifier, S->onebyfftLen);
   }
   else
   {
      /* Complex FFT radix-2 */
      mips_radix2_butterfly_f32(pSrc, S->fftLen, S->pTwiddle,
      S->twidCoefModifier);
   }

   if (S->bitReverseFlag == 1U)
   {
      /* Bit Reversal */
      mips_bitreversal_f32(pSrc, S->fftLen, S->bitRevFactor, S->pBitRevTable);
   }

}


/**
  @} end of ComplexFFT group
 */



/* ----------------------------------------------------------------------
 ** Internal helper function used by the FFTs
 ** ------------------------------------------------------------------- */

/**
  brief  Core function for the floating-point CFFT butterfly process.
  param[in,out] pSrc             points to in-place buffer of floating-point data type
  param[in]     fftLen           length of the FFT
  param[in]     pCoef            points to twiddle coefficient buffer
  param[in]     twidCoefModifier twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table
  return        none
 */

void mips_radix2_butterfly_f32(
        f32 * pSrc,
        uint32_t fftLen,
  const f32 * pCoef,
        uint16_t twidCoefModifier)
{

        uint32_t i, j, k, l;
        uint32_t n1, n2, ia;
        f32 xt, yt, cosVal, sinVal;
        f32 p0, p1, p2, p3;
        f32 a0, a1;

#if defined (MIPS_MATH_DSP)

   /*  Initializations for the first stage */
   n2 = fftLen >> 1;
   ia = 0;
   i = 0;

   // loop for groups
   for (k = n2; k > 0; k--)
   {
      cosVal = pCoef[ia * 2];
      sinVal = pCoef[(ia * 2) + 1];

      /*  Twiddle coefficients index modifier */
      ia += twidCoefModifier;

      /*  index calculation for the input as, */
      /*  pSrc[i + 0], pSrc[i + fftLen/1] */
      l = i + n2;

      /*  Butterfly implementation */
      a0 = pSrc[2 * i] + pSrc[2 * l];
      xt = pSrc[2 * i] - pSrc[2 * l];

      yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
      a1 = pSrc[2 * l + 1] + pSrc[2 * i + 1];

      p0 = xt * cosVal;
      p1 = yt * sinVal;
      p2 = yt * cosVal;
      p3 = xt * sinVal;

      pSrc[2 * i]     = a0;
      pSrc[2 * i + 1] = a1;

      pSrc[2 * l]     = p0 + p1;
      pSrc[2 * l + 1] = p2 - p3;

      i++;
   }                             // groups loop end

   twidCoefModifier <<= 1U;

   // loop for stage
   for (k = n2; k > 2; k = k >> 1)
   {
      n1 = n2;
      n2 = n2 >> 1;
      ia = 0;

      // loop for groups
      j = 0;
      do
      {
         cosVal = pCoef[ia * 2];
         sinVal = pCoef[(ia * 2) + 1];
         ia += twidCoefModifier;

         // loop for butterfly
         i = j;
         do
         {
            l = i + n2;
            a0 = pSrc[2 * i] + pSrc[2 * l];
            xt = pSrc[2 * i] - pSrc[2 * l];

            yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
            a1 = pSrc[2 * l + 1] + pSrc[2 * i + 1];

            p0 = xt * cosVal;
            p1 = yt * sinVal;
            p2 = yt * cosVal;
            p3 = xt * sinVal;

            pSrc[2 * i] = a0;
            pSrc[2 * i + 1] = a1;

            pSrc[2 * l]     = p0 + p1;
            pSrc[2 * l + 1] = p2 - p3;

            i += n1;
         } while ( i < fftLen );                        // butterfly loop end
         j++;
      } while ( j < n2);                          // groups loop end
      twidCoefModifier <<= 1U;
   }                             // stages loop end

   // loop for butterfly
   for (i = 0; i < fftLen; i += 2)
   {
      a0 = pSrc[2 * i] + pSrc[2 * i + 2];
      xt = pSrc[2 * i] - pSrc[2 * i + 2];

      yt = pSrc[2 * i + 1] - pSrc[2 * i + 3];
      a1 = pSrc[2 * i + 3] + pSrc[2 * i + 1];

      pSrc[2 * i] = a0;
      pSrc[2 * i + 1] = a1;
      pSrc[2 * i + 2] = xt;
      pSrc[2 * i + 3] = yt;
   }                             // groups loop end

#else /* #if defined (MIPS_MATH_DSP) */

   n2 = fftLen;

   // loop for stage
   for (k = fftLen; k > 1; k = k >> 1)
   {
      n1 = n2;
      n2 = n2 >> 1;
      ia = 0;

      // loop for groups
      j = 0;
      do
      {
         cosVal = pCoef[ia * 2];
         sinVal = pCoef[(ia * 2) + 1];
         ia += twidCoefModifier;

         // loop for butterfly
         i = j;
         do
         {
            l = i + n2;
            a0 = pSrc[2 * i] + pSrc[2 * l];
            xt = pSrc[2 * i] - pSrc[2 * l];

            yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
            a1 = pSrc[2 * l + 1] + pSrc[2 * i + 1];

            p0 = xt * cosVal;
            p1 = yt * sinVal;
            p2 = yt * cosVal;
            p3 = xt * sinVal;

            pSrc[2 * i] = a0;
            pSrc[2 * i + 1] = a1;

            pSrc[2 * l]     = p0 + p1;
            pSrc[2 * l + 1] = p2 - p3;

            i += n1;
         } while (i < fftLen);
         j++;
      } while (j < n2);
      twidCoefModifier <<= 1U;
   }

#endif /* #if defined (MIPS_MATH_DSP) */

}


void mips_radix2_butterfly_inverse_f32(
        f32 * pSrc,
        uint32_t fftLen,
  const f32 * pCoef,
        uint16_t twidCoefModifier,
        f32 onebyfftLen)
{

        uint32_t i, j, k, l;
        uint32_t n1, n2, ia;
        f32 xt, yt, cosVal, sinVal;
        f32 p0, p1, p2, p3;
        f32 a0, a1;

#if defined (MIPS_MATH_DSP)

   n2 = fftLen >> 1;
   ia = 0;

   // loop for groups
   for (i = 0; i < n2; i++)
   {
      cosVal = pCoef[ia * 2];
      sinVal = pCoef[(ia * 2) + 1];
      ia += twidCoefModifier;

      l = i + n2;
      a0 = pSrc[2 * i] + pSrc[2 * l];
      xt = pSrc[2 * i] - pSrc[2 * l];

      yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
      a1 = pSrc[2 * l + 1] + pSrc[2 * i + 1];

      p0 = xt * cosVal;
      p1 = yt * sinVal;
      p2 = yt * cosVal;
      p3 = xt * sinVal;

      pSrc[2 * i] = a0;
      pSrc[2 * i + 1] = a1;

      pSrc[2 * l]     = p0 - p1;
      pSrc[2 * l + 1] = p2 + p3;
   }                             // groups loop end

   twidCoefModifier <<= 1U;

   // loop for stage
   for (k = fftLen / 2; k > 2; k = k >> 1)
   {
      n1 = n2;
      n2 = n2 >> 1;
      ia = 0;

      // loop for groups
      j = 0;
      do
      {
         cosVal = pCoef[ia * 2];
         sinVal = pCoef[(ia * 2) + 1];
         ia += twidCoefModifier;

         // loop for butterfly
         i = j;
         do
         {
            l = i + n2;
            a0 = pSrc[2 * i] + pSrc[2 * l];
            xt = pSrc[2 * i] - pSrc[2 * l];

            yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
            a1 = pSrc[2 * l + 1] + pSrc[2 * i + 1];

            p0 = xt * cosVal;
            p1 = yt * sinVal;
            p2 = yt * cosVal;
            p3 = xt * sinVal;

            pSrc[2 * i] = a0;
            pSrc[2 * i + 1] = a1;

            pSrc[2 * l]     = p0 - p1;
            pSrc[2 * l + 1] = p2 + p3;

            i += n1;
         } while ( i < fftLen );                 // butterfly loop end
         j++;
      } while (j < n2);                      // groups loop end

      twidCoefModifier <<= 1U;
   }                             // stages loop end

   // loop for butterfly
   for (i = 0; i < fftLen; i += 2)
   {
      a0 = pSrc[2 * i] + pSrc[2 * i + 2];
      xt = pSrc[2 * i] - pSrc[2 * i + 2];

      a1 = pSrc[2 * i + 3] + pSrc[2 * i + 1];
      yt = pSrc[2 * i + 1] - pSrc[2 * i + 3];

      p0 = a0 * onebyfftLen;
      p2 = xt * onebyfftLen;
      p1 = a1 * onebyfftLen;
      p3 = yt * onebyfftLen;

      pSrc[2 * i] = p0;
      pSrc[2 * i + 1] = p1;
      pSrc[2 * i + 2] = p2;
      pSrc[2 * i + 3] = p3;
   }                             // butterfly loop end

#else /* #if defined (MIPS_MATH_DSP) */

   n2 = fftLen;

   // loop for stage
   for (k = fftLen; k > 2; k = k >> 1)
   {
      n1 = n2;
      n2 = n2 >> 1;
      ia = 0;

      // loop for groups
      j = 0;
      do
      {
         cosVal = pCoef[ia * 2];
         sinVal = pCoef[(ia * 2) + 1];
         ia = ia + twidCoefModifier;

         // loop for butterfly
         i = j;
         do
         {
            l = i + n2;
            a0 = pSrc[2 * i] + pSrc[2 * l];
            xt = pSrc[2 * i] - pSrc[2 * l];

            yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
            a1 = pSrc[2 * l + 1] + pSrc[2 * i + 1];

            p0 = xt * cosVal;
            p1 = yt * sinVal;
            p2 = yt * cosVal;
            p3 = xt * sinVal;

            pSrc[2 * i] = a0;
            pSrc[2 * i + 1] = a1;

            pSrc[2 * l]     = p0 - p1;
            pSrc[2 * l + 1] = p2 + p3;

            i += n1;
         } while ( i < fftLen );                    // butterfly loop end
         j++;
      } while ( j < n2 );                      // groups loop end

      twidCoefModifier = twidCoefModifier << 1U;
   }                             // stages loop end

   n1 = n2;
   n2 = n2 >> 1;

   // loop for butterfly
   for (i = 0; i < fftLen; i += n1)
   {
      l = i + n2;

      a0 = pSrc[2 * i] + pSrc[2 * l];
      xt = pSrc[2 * i] - pSrc[2 * l];

      a1 = pSrc[2 * l + 1] + pSrc[2 * i + 1];
      yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];

      p0 = a0 * onebyfftLen;
      p2 = xt * onebyfftLen;
      p1 = a1 * onebyfftLen;
      p3 = yt * onebyfftLen;

      pSrc[2 * i] = p0;
      pSrc[2 * l] = p2;

      pSrc[2 * i + 1] = p1;
      pSrc[2 * l + 1] = p3;
   }                             // butterfly loop end

#endif /* #if defined (MIPS_MATH_DSP) */

}
