/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_rfft_fast_f64.c
 * Description:  RFFT & RIFFT Double precision Floating point process function
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

void stage_rfft_f64(
  const mips_rfft_fast_instance_f64 * S,
        f64 * p,
        f64 * pOut)
{
        uint32_t  k;                                /* Loop Counter */
        f64 twR, twI;                         /* RFFT Twiddle coefficients */
  const f64 * pCoeff = S->pTwiddleRFFT;       /* Points to RFFT Twiddle factors */
        f64 *pA = p;                          /* increasing pointer */
        f64 *pB = p;                          /* decreasing pointer */
        f64 xAR, xAI, xBR, xBI;               /* temporary variables */
        f64 t1a, t1b;                         /* temporary variables */
        f64 p0, p1, p2, p3;                   /* temporary variables */


   k = (S->Sint).fftLen - 1;

   /* Pack first and last sample of the frequency domain together */

   xBR = pB[0];
   xBI = pB[1];
   xAR = pA[0];
   xAI = pA[1];

   twR = *pCoeff++ ;
   twI = *pCoeff++ ;

   // U1 = XA(1) + XB(1); % It is real
   t1a = xBR + xAR  ;

   // U2 = XB(1) - XA(1); % It is imaginary
   t1b = xBI + xAI  ;

   // real(tw * (xB - xA)) = twR * (xBR - xAR) - twI * (xBI - xAI);
   // imag(tw * (xB - xA)) = twI * (xBR - xAR) + twR * (xBI - xAI);
   *pOut++ = 0.5 * ( t1a + t1b );
   *pOut++ = 0.5 * ( t1a - t1b );

   // XA(1) = 1/2*( U1 - imag(U2) +  i*( U1 +imag(U2) ));
   pB  = p + 2*k;
   pA += 2;

   do
   {
      /*
         function X = my_split_rfft(X, ifftFlag)
         % X is a series of real numbers
         L  = length(X);
         XC = X(1:2:end) +i*X(2:2:end);
         XA = fft(XC);
         XB = conj(XA([1 end:-1:2]));
         TW = i*exp(-2*pi*i*[0:L/2-1]/L).';
         for l = 2:L/2
            XA(l) = 1/2 * (XA(l) + XB(l) + TW(l) * (XB(l) - XA(l)));
         end
         XA(1) = 1/2* (XA(1) + XB(1) + TW(1) * (XB(1) - XA(1))) + i*( 1/2*( XA(1) + XB(1) + i*( XA(1) - XB(1))));
         X = XA;
      */

      xBI = pB[1];
      xBR = pB[0];
      xAR = pA[0];
      xAI = pA[1];

      twR = *pCoeff++;
      twI = *pCoeff++;

      t1a = xBR - xAR ;
      t1b = xBI + xAI ;

      // real(tw * (xB - xA)) = twR * (xBR - xAR) - twI * (xBI - xAI);
      // imag(tw * (xB - xA)) = twI * (xBR - xAR) + twR * (xBI - xAI);
      p0 = twR * t1a;
      p1 = twI * t1a;
      p2 = twR * t1b;
      p3 = twI * t1b;

      *pOut++ = 0.5 * (xAR + xBR + p0 + p3 ); //xAR
      *pOut++ = 0.5 * (xAI - xBI + p1 - p2 ); //xAI

      pA += 2;
      pB -= 2;
      k--;
   } while (k > 0U);
}

/* Prepares data for inverse cfft */
void merge_rfft_f64(
  const mips_rfft_fast_instance_f64 * S,
        f64 * p,
        f64 * pOut)
{
        uint32_t  k;                                /* Loop Counter */
        f64 twR, twI;                         /* RFFT Twiddle coefficients */
  const f64 *pCoeff = S->pTwiddleRFFT;        /* Points to RFFT Twiddle factors */
        f64 *pA = p;                          /* increasing pointer */
        f64 *pB = p;                          /* decreasing pointer */
        f64 xAR, xAI, xBR, xBI;               /* temporary variables */
        f64 t1a, t1b, r, s, t, u;             /* temporary variables */

   k = (S->Sint).fftLen - 1;

   xAR = pA[0];
   xAI = pA[1];

   pCoeff += 2 ;

   *pOut++ = 0.5 * ( xAR + xAI );
   *pOut++ = 0.5 * ( xAR - xAI );

   pB  =  p + 2*k ;
   pA +=  2	   ;

   while (k > 0U)
   {
      /* G is half of the frequency complex spectrum */
      //for k = 2:N
      //    Xk(k) = 1/2 * (G(k) + conj(G(N-k+2)) + Tw(k)*( G(k) - conj(G(N-k+2))));
      xBI =   pB[1]    ;
      xBR =   pB[0]    ;
      xAR =  pA[0];
      xAI =  pA[1];

      twR = *pCoeff++;
      twI = *pCoeff++;

      t1a = xAR - xBR ;
      t1b = xAI + xBI ;

      r = twR * t1a;
      s = twI * t1b;
      t = twI * t1a;
      u = twR * t1b;

      // real(tw * (xA - xB)) = twR * (xAR - xBR) - twI * (xAI - xBI);
      // imag(tw * (xA - xB)) = twI * (xAR - xBR) + twR * (xAI - xBI);
      *pOut++ = 0.5 * (xAR + xBR - r - s ); //xAR
      *pOut++ = 0.5 * (xAI - xBI + t - u ); //xAI

      pA += 2;
      pB -= 2;
      k--;
   }

}

/**
  @ingroup groupTransforms
*/


/**
  @addtogroup RealFFT
  @{
*/

/**
  @brief         Processing function for the Double Precision floating-point real FFT.
  @param[in]     S         points to an mips_rfft_fast_instance_f64 structure
  @param[in]     p         points to input buffer (Source buffer is modified by this function.)
  @param[in]     pOut      points to output buffer
  @param[in]     ifftFlag
                   - value = 0: RFFT
                   - value = 1: RIFFT
  @return        none
*/

void mips_rfft_fast_f64(
  mips_rfft_fast_instance_f64 * S,
  f64 * p,
  f64 * pOut,
  uint8_t ifftFlag)
{
   mips_cfft_instance_f64 * Sint = &(S->Sint);
   Sint->fftLen = S->fftLenRFFT / 2;

   /* Calculation of Real FFT */
   if (ifftFlag)
   {
      /*  Real FFT compression */
      merge_rfft_f64(S, p, pOut);

      /* Complex radix-4 IFFT process */
      mips_cfft_f64( Sint, pOut, ifftFlag, 1);
   }
   else
   {
      /* Calculation of RFFT of input */
      mips_cfft_f64( Sint, p, ifftFlag, 1);

      /*  Real FFT extraction */
      stage_rfft_f64(S, p, pOut);
   }
}

/**
* @} end of RealFFT group
*/
