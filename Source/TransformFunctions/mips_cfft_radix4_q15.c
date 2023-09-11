/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cfft_radix4_q15.c
 * Description:  This file has function definition of Radix-4 FFT & IFFT function and
 *               In-place bit reversal using bit reversal table
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


void mips_radix4_butterfly_q15(
        q15 * pSrc16,
        uint32_t fftLen,
  const q15 * pCoef16,
        uint32_t twidCoefModifier);

void mips_radix4_butterfly_inverse_q15(
        q15 * pSrc16,
        uint32_t fftLen,
  const q15 * pCoef16,
        uint32_t twidCoefModifier);

void mips_bitreversal_q15(
        q15 * pSrc,
        uint32_t fftLen,
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
  @brief               Processing function for the Q15 CFFT/CIFFT.
  @deprecated          Do not use this function.  It has been superseded by \ref mips_cfft_q15 and will be removed in the future.
  @param[in]     S     points to an instance of the Q15 CFFT/CIFFT structure.
  @param[in,out] pSrc  points to the complex data buffer. Processing occurs in-place.
  @return        none
 
  @par Input and output formats:
                 Internally input is downscaled by 2 for every stage to avoid saturations inside CFFT/CIFFT process.
                 Hence the output format is different for different FFT sizes.
                 The input and output formats for different FFT sizes and number of bits to upscale are mentioned in the tables below for CFFT and CIFFT:
  @par
                
| CFFT Size | Input format  | Output format | Number of bits to upscale |
| --------: | ------------: | ------------: | ------------------------: |
| 16        | 1.15          | 5.11          | 4                         |
| 64        | 1.15          | 7.9           | 6                         |
| 256       | 1.15          | 9.7           | 8                         |
| 1024      | 1.15          | 11.5          | 10                        |

| CIFFT Size | Input format  | Output format | Number of bits to upscale |
| ---------: | ------------: | ------------: | ------------------------: |
| 16         | 1.15          | 5.11          | 0                         |
| 64         | 1.15          | 7.9           | 0                         |
| 256        | 1.15          | 9.7           | 0                         |
| 1024       | 1.15          | 11.5          | 0                         |

 */

void mips_cfft_radix4_q15(
  const mips_cfft_radix4_instance_q15 * S,
        q15 * pSrc)
{
  if (S->ifftFlag == 1U)
  {
    /*  Complex IFFT radix-4  */
    mips_radix4_butterfly_inverse_q15(pSrc, S->fftLen, S->pTwiddle, S->twidCoefModifier);
  }
  else
  {
    /*  Complex FFT radix-4  */
    mips_radix4_butterfly_q15(pSrc, S->fftLen, S->pTwiddle, S->twidCoefModifier);
  }

  if (S->bitReverseFlag == 1U)
  {
    /*  Bit Reversal */
    mips_bitreversal_q15(pSrc, S->fftLen, S->bitRevFactor, S->pBitRevTable);
  }

}

/**
  @} end of ComplexFFT group
 */

/*
 * Radix-4 FFT algorithm used is :
 *
 * Input real and imaginary data:
 * x(n) = xa + j * ya
 * x(n+N/4 ) = xb + j * yb
 * x(n+N/2 ) = xc + j * yc
 * x(n+3N 4) = xd + j * yd
 *
 *
 * Output real and imaginary data:
 * x(4r) = xa'+ j * ya'
 * x(4r+1) = xb'+ j * yb'
 * x(4r+2) = xc'+ j * yc'
 * x(4r+3) = xd'+ j * yd'
 *
 *
 * Twiddle factors for radix-4 FFT:
 * Wn = co1 + j * (- si1)
 * W2n = co2 + j * (- si2)
 * W3n = co3 + j * (- si3)
 
 * The real and imaginary output values for the radix-4 butterfly are
 * xa' = xa + xb + xc + xd
 * ya' = ya + yb + yc + yd
 * xb' = (xa+yb-xc-yd)* co1 + (ya-xb-yc+xd)* (si1)
 * yb' = (ya-xb-yc+xd)* co1 - (xa+yb-xc-yd)* (si1)
 * xc' = (xa-xb+xc-xd)* co2 + (ya-yb+yc-yd)* (si2)
 * yc' = (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2)
 * xd' = (xa-yb-xc+yd)* co3 + (ya+xb-yc-xd)* (si3)
 * yd' = (ya+xb-yc-xd)* co3 - (xa-yb-xc+yd)* (si3)
 *
 */

/**
  @brief         Core function for the Q15 CFFT butterfly process.
  @param[in,out] pSrc16          points to the in-place buffer of Q15 data type
  @param[in]     fftLen           length of the FFT
  @param[in]     pCoef16         points to twiddle coefficient buffer
  @param[in]     twidCoefModifier twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table
  @return        none
 */

void mips_radix4_butterfly_q15(
        q15 * pSrc16,
        uint32_t fftLen,
  const q15 * pCoef16,
        uint32_t twidCoefModifier)
{


        q15 R0, R1, S0, S1, T0, T1, U0, U1;
        q15 Co1, Si1, Co2, Si2, Co3, Si3, out1, out2;
        uint32_t n1, n2, ic, i0, i1, i2, i3, j, k;

  /* Total process is divided into three stages */

  /* process first stage, middle stages, & last stage */

  /*  Initializations for the first stage */
  n2 = fftLen;
  n1 = n2;

  /* n2 = fftLen/4 */
  n2 >>= 2U;

  /* Index for twiddle coefficient */
  ic = 0U;

  /* Index for input read and output write */
  i0 = 0U;
  j = n2;

  /* Input is in 1.15(q15) format */

  /*  start of first stage process */
  do
  {
    /*  Butterfly implementation */

    /*  index calculation for the input as, */
    /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    /*  Reading i0, i0+fftLen/2 inputs */

    /* input is down scale by 4 to avoid overflow */
    /* Read ya (real), xa(imag) input */
    T0 = pSrc16[i0 * 2U] >> 2U;
    T1 = pSrc16[(i0 * 2U) + 1U] >> 2U;

    /* input is down scale by 4 to avoid overflow */
    /* Read yc (real), xc(imag) input */
    S0 = pSrc16[i2 * 2U] >> 2U;
    S1 = pSrc16[(i2 * 2U) + 1U] >> 2U;

    /* R0 = (ya + yc) */
    R0 = __SSAT(T0 + S0, 16U);
    /* R1 = (xa + xc) */
    R1 = __SSAT(T1 + S1, 16U);

    /* S0 = (ya - yc) */
    S0 = __SSAT(T0 - S0, 16);
    /* S1 = (xa - xc) */
    S1 = __SSAT(T1 - S1, 16);

    /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
    /* input is down scale by 4 to avoid overflow */
    /* Read yb (real), xb(imag) input */
    T0 = pSrc16[i1 * 2U] >> 2U;
    T1 = pSrc16[(i1 * 2U) + 1U] >> 2U;

    /* input is down scale by 4 to avoid overflow */
    /* Read yd (real), xd(imag) input */
    U0 = pSrc16[i3 * 2U] >> 2U;
    U1 = pSrc16[(i3 * 2U) + 1] >> 2U;

    /* T0 = (yb + yd) */
    T0 = __SSAT(T0 + U0, 16U);
    /* T1 = (xb + xd) */
    T1 = __SSAT(T1 + U1, 16U);

    /*  writing the butterfly processed i0 sample */
    /* ya' = ya + yb + yc + yd */
    /* xa' = xa + xb + xc + xd */
    pSrc16[i0 * 2U] = (R0 >> 1U) + (T0 >> 1U);
    pSrc16[(i0 * 2U) + 1U] = (R1 >> 1U) + (T1 >> 1U);

    /* R0 = (ya + yc) - (yb + yd) */
    /* R1 = (xa + xc) - (xb + xd) */
    R0 = __SSAT(R0 - T0, 16U);
    R1 = __SSAT(R1 - T1, 16U);

    /* co2 & si2 are read from Coefficient pointer */
    Co2 = pCoef16[2U * ic * 2U];
    Si2 = pCoef16[(2U * ic * 2U) + 1];

    /* xc' = (xa-xb+xc-xd)* co2 + (ya-yb+yc-yd)* (si2) */
    out1 = (q15) ((Co2 * R0 + Si2 * R1) >> 16U);
    /* yc' = (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
    out2 = (q15) ((-Si2 * R0 + Co2 * R1) >> 16U);

    /*  Reading i0+fftLen/4 */
    /* input is down scale by 4 to avoid overflow */
    /* T0 = yb, T1 =  xb */
    T0 = pSrc16[i1 * 2U] >> 2;
    T1 = pSrc16[(i1 * 2U) + 1] >> 2;

    /* writing the butterfly processed i0 + fftLen/4 sample */
    /* writing output(xc', yc') in little endian format */
    pSrc16[i1 * 2U] = out1;
    pSrc16[(i1 * 2U) + 1] = out2;

    /*  Butterfly calculations */
    /* input is down scale by 4 to avoid overflow */
    /* U0 = yd, U1 = xd */
    U0 = pSrc16[i3 * 2U] >> 2;
    U1 = pSrc16[(i3 * 2U) + 1] >> 2;
    /* T0 = yb-yd */
    T0 = __SSAT(T0 - U0, 16);
    /* T1 = xb-xd */
    T1 = __SSAT(T1 - U1, 16);

    /* R1 = (ya-yc) + (xb- xd),  R0 = (xa-xc) - (yb-yd)) */
    R0 = (q15) __SSAT((q31) (S0 - T1), 16);
    R1 = (q15) __SSAT((q31) (S1 + T0), 16);

    /* S1 = (ya-yc) - (xb- xd), S0 = (xa-xc) + (yb-yd)) */
    S0 = (q15) __SSAT(((q31) S0 + T1), 16U);
    S1 = (q15) __SSAT(((q31) S1 - T0), 16U);

    /* co1 & si1 are read from Coefficient pointer */
    Co1 = pCoef16[ic * 2U];
    Si1 = pCoef16[(ic * 2U) + 1];
    /*  Butterfly process for the i0+fftLen/2 sample */
    /* xb' = (xa+yb-xc-yd)* co1 + (ya-xb-yc+xd)* (si1) */
    out1 = (q15) ((Si1 * S1 + Co1 * S0) >> 16);
    /* yb' = (ya-xb-yc+xd)* co1 - (xa+yb-xc-yd)* (si1) */
    out2 = (q15) ((-Si1 * S0 + Co1 * S1) >> 16);

    /* writing output(xb', yb') in little endian format */
    pSrc16[i2 * 2U] = out1;
    pSrc16[(i2 * 2U) + 1] = out2;

    /* Co3 & si3 are read from Coefficient pointer */
    Co3 = pCoef16[3U * (ic * 2U)];
    Si3 = pCoef16[(3U * (ic * 2U)) + 1];
    /*  Butterfly process for the i0+3fftLen/4 sample */
    /* xd' = (xa-yb-xc+yd)* Co3 + (ya+xb-yc-xd)* (si3) */
    out1 = (q15) ((Si3 * R1 + Co3 * R0) >> 16U);
    /* yd' = (ya+xb-yc-xd)* Co3 - (xa-yb-xc+yd)* (si3) */
    out2 = (q15) ((-Si3 * R0 + Co3 * R1) >> 16U);
    /* writing output(xd', yd') in little endian format */
    pSrc16[i3 * 2U] = out1;
    pSrc16[(i3 * 2U) + 1] = out2;

    /*  Twiddle coefficients index modifier */
    ic = ic + twidCoefModifier;

    /*  Updating input index */
    i0 = i0 + 1U;

  } while (--j);
  /* data is in 4.11(q11) format */

  /* end of first stage process */


  /* start of middle stage process */

  /*  Twiddle coefficients index modifier */
  twidCoefModifier <<= 2U;

  /*  Calculation of Middle stage */
  for (k = fftLen / 4U; k > 4U; k >>= 2U)
  {
    /*  Initializations for the middle stage */
    n1 = n2;
    n2 >>= 2U;
    ic = 0U;

    for (j = 0U; j <= (n2 - 1U); j++)
    {
      /*  index calculation for the coefficients */
      Co1 = pCoef16[ic * 2U];
      Si1 = pCoef16[(ic * 2U) + 1U];
      Co2 = pCoef16[2U * (ic * 2U)];
      Si2 = pCoef16[(2U * (ic * 2U)) + 1U];
      Co3 = pCoef16[3U * (ic * 2U)];
      Si3 = pCoef16[(3U * (ic * 2U)) + 1U];

      /*  Twiddle coefficients index modifier */
      ic = ic + twidCoefModifier;

      /*  Butterfly implementation */
      for (i0 = j; i0 < fftLen; i0 += n1)
      {
        /*  index calculation for the input as, */
        /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        /*  Reading i0, i0+fftLen/2 inputs */
        /* Read ya (real), xa(imag) input */
        T0 = pSrc16[i0 * 2U];
        T1 = pSrc16[(i0 * 2U) + 1U];

        /* Read yc (real), xc(imag) input */
        S0 = pSrc16[i2 * 2U];
        S1 = pSrc16[(i2 * 2U) + 1U];

        /* R0 = (ya + yc), R1 = (xa + xc) */
        R0 = __SSAT(T0 + S0, 16);
        R1 = __SSAT(T1 + S1, 16);

        /* S0 = (ya - yc), S1 =(xa - xc) */
        S0 = __SSAT(T0 - S0, 16);
        S1 = __SSAT(T1 - S1, 16);

        /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
        /* Read yb (real), xb(imag) input */
        T0 = pSrc16[i1 * 2U];
        T1 = pSrc16[(i1 * 2U) + 1U];

        /* Read yd (real), xd(imag) input */
        U0 = pSrc16[i3 * 2U];
        U1 = pSrc16[(i3 * 2U) + 1U];


        /* T0 = (yb + yd), T1 = (xb + xd) */
        T0 = __SSAT(T0 + U0, 16);
        T1 = __SSAT(T1 + U1, 16);

        /*  writing the butterfly processed i0 sample */

        /* xa' = xa + xb + xc + xd */
        /* ya' = ya + yb + yc + yd */
        out1 = ((R0 >> 1U) + (T0 >> 1U)) >> 1U;
        out2 = ((R1 >> 1U) + (T1 >> 1U)) >> 1U;

        pSrc16[i0 * 2U] = out1;
        pSrc16[(2U * i0) + 1U] = out2;

        /* R0 = (ya + yc) - (yb + yd), R1 = (xa + xc) - (xb + xd) */
        R0 = (R0 >> 1U) - (T0 >> 1U);
        R1 = (R1 >> 1U) - (T1 >> 1U);

        /* (ya-yb+yc-yd)* (si2) + (xa-xb+xc-xd)* co2 */
        out1 = (q15) ((Co2 * R0 + Si2 * R1) >> 16U);

        /* (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
        out2 = (q15) ((-Si2 * R0 + Co2 * R1) >> 16U);

        /*  Reading i0+3fftLen/4 */
        /* Read yb (real), xb(imag) input */
        T0 = pSrc16[i1 * 2U];
        T1 = pSrc16[(i1 * 2U) + 1U];

        /*  writing the butterfly processed i0 + fftLen/4 sample */
        /* xc' = (xa-xb+xc-xd)* co2 + (ya-yb+yc-yd)* (si2) */
        /* yc' = (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
        pSrc16[i1 * 2U] = out1;
        pSrc16[(i1 * 2U) + 1U] = out2;

        /*  Butterfly calculations */

        /* Read yd (real), xd(imag) input */
        U0 = pSrc16[i3 * 2U];
        U1 = pSrc16[(i3 * 2U) + 1U];

        /* T0 = yb-yd, T1 = xb-xd */
        T0 = __SSAT(T0 - U0, 16);
        T1 = __SSAT(T1 - U1, 16);

        /* R0 = (ya-yc) + (xb- xd), R1 = (xa-xc) - (yb-yd)) */
        R0 = (S0 >> 1U) - (T1 >> 1U);
        R1 = (S1 >> 1U) + (T0 >> 1U);

        /* S0 = (ya-yc) - (xb- xd), S1 = (xa-xc) + (yb-yd)) */
        S0 = (S0 >> 1U) + (T1 >> 1U);
        S1 = (S1 >> 1U) - (T0 >> 1U);

        /*  Butterfly process for the i0+fftLen/2 sample */
        out1 = (q15) ((Co1 * S0 + Si1 * S1) >> 16U);

        out2 = (q15) ((-Si1 * S0 + Co1 * S1) >> 16U);

        /* xb' = (xa+yb-xc-yd)* co1 + (ya-xb-yc+xd)* (si1) */
        /* yb' = (ya-xb-yc+xd)* co1 - (xa+yb-xc-yd)* (si1) */
        pSrc16[i2 * 2U] = out1;
        pSrc16[(i2 * 2U) + 1U] = out2;

        /*  Butterfly process for the i0+3fftLen/4 sample */
        out1 = (q15) ((Si3 * R1 + Co3 * R0) >> 16U);

        out2 = (q15) ((-Si3 * R0 + Co3 * R1) >> 16U);
        /* xd' = (xa-yb-xc+yd)* Co3 + (ya+xb-yc-xd)* (si3) */
        /* yd' = (ya+xb-yc-xd)* Co3 - (xa-yb-xc+yd)* (si3) */
        pSrc16[i3 * 2U] = out1;
        pSrc16[(i3 * 2U) + 1U] = out2;
      }
    }
    /*  Twiddle coefficients index modifier */
    twidCoefModifier <<= 2U;
  }
  /* end of middle stage process */


  /* data is in 10.6(q6) format for the 1024 point */
  /* data is in 8.8(q8) format for the 256 point */
  /* data is in 6.10(q10) format for the 64 point */
  /* data is in 4.12(q12) format for the 16 point */

  /*  Initializations for the last stage */
  n1 = n2;
  n2 >>= 2U;

  /* start of last stage process */

  /*  Butterfly implementation */
  for (i0 = 0U; i0 <= (fftLen - n1); i0 += n1)
  {
    /*  index calculation for the input as, */
    /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    /*  Reading i0, i0+fftLen/2 inputs */
    /* Read ya (real), xa(imag) input */
    T0 = pSrc16[i0 * 2U];
    T1 = pSrc16[(i0 * 2U) + 1U];

    /* Read yc (real), xc(imag) input */
    S0 = pSrc16[i2 * 2U];
    S1 = pSrc16[(i2 * 2U) + 1U];

    /* R0 = (ya + yc), R1 = (xa + xc) */
    R0 = __SSAT(T0 + S0, 16U);
    R1 = __SSAT(T1 + S1, 16U);

    /* S0 = (ya - yc), S1 = (xa - xc) */
    S0 = __SSAT(T0 - S0, 16U);
    S1 = __SSAT(T1 - S1, 16U);

    /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
    /* Read yb (real), xb(imag) input */
    T0 = pSrc16[i1 * 2U];
    T1 = pSrc16[(i1 * 2U) + 1U];
    /* Read yd (real), xd(imag) input */
    U0 = pSrc16[i3 * 2U];
    U1 = pSrc16[(i3 * 2U) + 1U];

    /* T0 = (yb + yd), T1 = (xb + xd)) */
    T0 = __SSAT(T0 + U0, 16U);
    T1 = __SSAT(T1 + U1, 16U);

    /*  writing the butterfly processed i0 sample */
    /* xa' = xa + xb + xc + xd */
    /* ya' = ya + yb + yc + yd */
    pSrc16[i0 * 2U] = (R0 >> 1U) + (T0 >> 1U);
    pSrc16[(i0 * 2U) + 1U] = (R1 >> 1U) + (T1 >> 1U);

    /* R0 = (ya + yc) - (yb + yd), R1 = (xa + xc) - (xb + xd) */
    R0 = (R0 >> 1U) - (T0 >> 1U);
    R1 = (R1 >> 1U) - (T1 >> 1U);
    /* Read yb (real), xb(imag) input */
    T0 = pSrc16[i1 * 2U];
    T1 = pSrc16[(i1 * 2U) + 1U];

    /*  writing the butterfly processed i0 + fftLen/4 sample */
    /* xc' = (xa-xb+xc-xd) */
    /* yc' = (ya-yb+yc-yd) */
    pSrc16[i1 * 2U] = R0;
    pSrc16[(i1 * 2U) + 1U] = R1;

    /* Read yd (real), xd(imag) input */
    U0 = pSrc16[i3 * 2U];
    U1 = pSrc16[(i3 * 2U) + 1U];
    /* T0 = (yb - yd), T1 = (xb - xd)  */
    T0 = __SSAT(T0 - U0, 16U);
    T1 = __SSAT(T1 - U1, 16U);

    /*  writing the butterfly processed i0 + fftLen/2 sample */
    /* xb' = (xa+yb-xc-yd) */
    /* yb' = (ya-xb-yc+xd) */
    pSrc16[i2 * 2U] = (S0 >> 1U) + (T1 >> 1U);
    pSrc16[(i2 * 2U) + 1U] = (S1 >> 1U) - (T0 >> 1U);

    /*  writing the butterfly processed i0 + 3fftLen/4 sample */
    /* xd' = (xa-yb-xc+yd) */
    /* yd' = (ya+xb-yc-xd) */
    pSrc16[i3 * 2U] = (S0 >> 1U) - (T1 >> 1U);
    pSrc16[(i3 * 2U) + 1U] = (S1 >> 1U) + (T0 >> 1U);

  }

  /* end of last stage process */

  /* output is in 11.5(q5) format for the 1024 point */
  /* output is in 9.7(q7) format for the 256 point   */
  /* output is in 7.9(q9) format for the 64 point  */
  /* output is in 5.11(q11) format for the 16 point  */


}


/**
  @brief         Core function for the Q15 CIFFT butterfly process.
  @param[in,out] pSrc16           points to the in-place buffer of Q15 data type
  @param[in]     fftLen           length of the FFT
  @param[in]     pCoef16          points to twiddle coefficient buffer
  @param[in]     twidCoefModifier twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.
  @return        none
 */

/*
 * Radix-4 IFFT algorithm used is :
 *
 * CIFFT uses same twiddle coefficients as CFFT function
 *  x[k] = x[n] + (j)k * x[n + fftLen/4] + (-1)k * x[n+fftLen/2] + (-j)k * x[n+3*fftLen/4]
 *
 *
 * IFFT is implemented with following changes in equations from FFT
 *
 * Input real and imaginary data:
 * x(n) = xa + j * ya
 * x(n+N/4 ) = xb + j * yb
 * x(n+N/2 ) = xc + j * yc
 * x(n+3N 4) = xd + j * yd
 *
 *
 * Output real and imaginary data:
 * x(4r) = xa'+ j * ya'
 * x(4r+1) = xb'+ j * yb'
 * x(4r+2) = xc'+ j * yc'
 * x(4r+3) = xd'+ j * yd'
 *
 *
 * Twiddle factors for radix-4 IFFT:
 * Wn = co1 + j * (si1)
 * W2n = co2 + j * (si2)
 * W3n = co3 + j * (si3)
 
 * The real and imaginary output values for the radix-4 butterfly are
 * xa' = xa + xb + xc + xd
 * ya' = ya + yb + yc + yd
 * xb' = (xa-yb-xc+yd)* co1 - (ya+xb-yc-xd)* (si1)
 * yb' = (ya+xb-yc-xd)* co1 + (xa-yb-xc+yd)* (si1)
 * xc' = (xa-xb+xc-xd)* co2 - (ya-yb+yc-yd)* (si2)
 * yc' = (ya-yb+yc-yd)* co2 + (xa-xb+xc-xd)* (si2)
 * xd' = (xa+yb-xc-yd)* co3 - (ya-xb-yc+xd)* (si3)
 * yd' = (ya-xb-yc+xd)* co3 + (xa+yb-xc-yd)* (si3)
 *
 */

void mips_radix4_butterfly_inverse_q15(
        q15 * pSrc16,
        uint32_t fftLen,
  const q15 * pCoef16,
        uint32_t twidCoefModifier)
{


        q15 R0, R1, S0, S1, T0, T1, U0, U1;
        q15 Co1, Si1, Co2, Si2, Co3, Si3, out1, out2;
        uint32_t n1, n2, ic, i0, i1, i2, i3, j, k;

  /* Total process is divided into three stages */

  /* process first stage, middle stages, & last stage */

  /*  Initializations for the first stage */
  n2 = fftLen;
  n1 = n2;

  /* n2 = fftLen/4 */
  n2 >>= 2U;

  /* Index for twiddle coefficient */
  ic = 0U;

  /* Index for input read and output write */
  i0 = 0U;

  j = n2;

  /* Input is in 1.15(q15) format */

  /*  Start of first stage process */
  do
  {
    /*  Butterfly implementation */

    /*  index calculation for the input as, */
    /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    /*  Reading i0, i0+fftLen/2 inputs */
    /* input is down scale by 4 to avoid overflow */
    /* Read ya (real), xa(imag) input */
    T0 = pSrc16[i0 * 2U] >> 2U;
    T1 = pSrc16[(i0 * 2U) + 1U] >> 2U;
    /* input is down scale by 4 to avoid overflow */
    /* Read yc (real), xc(imag) input */
    S0 = pSrc16[i2 * 2U] >> 2U;
    S1 = pSrc16[(i2 * 2U) + 1U] >> 2U;

    /* R0 = (ya + yc), R1 = (xa + xc) */
    R0 = __SSAT(T0 + S0, 16U);
    R1 = __SSAT(T1 + S1, 16U);
    /* S0 = (ya - yc), S1 = (xa - xc) */
    S0 = __SSAT(T0 - S0, 16U);
    S1 = __SSAT(T1 - S1, 16U);

    /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
    /* input is down scale by 4 to avoid overflow */
    /* Read yb (real), xb(imag) input */
    T0 = pSrc16[i1 * 2U] >> 2U;
    T1 = pSrc16[(i1 * 2U) + 1U] >> 2U;
    /* Read yd (real), xd(imag) input */
    /* input is down scale by 4 to avoid overflow */
    U0 = pSrc16[i3 * 2U] >> 2U;
    U1 = pSrc16[(i3 * 2U) + 1U] >> 2U;

    /* T0 = (yb + yd), T1 = (xb + xd) */
    T0 = __SSAT(T0 + U0, 16U);
    T1 = __SSAT(T1 + U1, 16U);

    /*  writing the butterfly processed i0 sample */
    /* xa' = xa + xb + xc + xd */
    /* ya' = ya + yb + yc + yd */
    pSrc16[i0 * 2U] = (R0 >> 1U) + (T0 >> 1U);
    pSrc16[(i0 * 2U) + 1U] = (R1 >> 1U) + (T1 >> 1U);

    /* R0 = (ya + yc) - (yb + yd), R1 = (xa + xc)- (xb + xd) */
    R0 = __SSAT(R0 - T0, 16U);
    R1 = __SSAT(R1 - T1, 16U);
    /* co2 & si2 are read from Coefficient pointer */
    Co2 = pCoef16[2U * ic * 2U];
    Si2 = pCoef16[(2U * ic * 2U) + 1U];
    /* xc' = (xa-xb+xc-xd)* co2 - (ya-yb+yc-yd)* (si2) */
    out1 = (q15) ((Co2 * R0 - Si2 * R1) >> 16U);
    /* yc' = (ya-yb+yc-yd)* co2 + (xa-xb+xc-xd)* (si2) */
    out2 = (q15) ((Si2 * R0 + Co2 * R1) >> 16U);

    /*  Reading i0+fftLen/4 */
    /* input is down scale by 4 to avoid overflow */
    /* T0 = yb, T1 = xb */
    T0 = pSrc16[i1 * 2U] >> 2U;
    T1 = pSrc16[(i1 * 2U) + 1U] >> 2U;

    /* writing the butterfly processed i0 + fftLen/4 sample */
    /* writing output(xc', yc') in little endian format */
    pSrc16[i1 * 2U] = out1;
    pSrc16[(i1 * 2U) + 1U] = out2;

    /*  Butterfly calculations */
    /* input is down scale by 4 to avoid overflow */
    /* U0 = yd, U1 = xd) */
    U0 = pSrc16[i3 * 2U] >> 2U;
    U1 = pSrc16[(i3 * 2U) + 1U] >> 2U;

    /* T0 = yb-yd, T1 = xb-xd) */
    T0 = __SSAT(T0 - U0, 16U);
    T1 = __SSAT(T1 - U1, 16U);
    /* R0 = (ya-yc) - (xb- xd) , R1 = (xa-xc) + (yb-yd) */
    R0 = (q15) __SSAT((q31) (S0 + T1), 16);
    R1 = (q15) __SSAT((q31) (S1 - T0), 16);
    /* S = (ya-yc) + (xb- xd), S1 = (xa-xc) - (yb-yd) */
    S0 = (q15) __SSAT((q31) (S0 - T1), 16);
    S1 = (q15) __SSAT((q31) (S1 + T0), 16);

    /* co1 & si1 are read from Coefficient pointer */
    Co1 = pCoef16[ic * 2U];
    Si1 = pCoef16[(ic * 2U) + 1U];
    /*  Butterfly process for the i0+fftLen/2 sample */
    /* xb' = (xa-yb-xc+yd)* co1 - (ya+xb-yc-xd)* (si1) */
    out1 = (q15) ((Co1 * S0 - Si1 * S1) >> 16U);
    /* yb' = (ya+xb-yc-xd)* co1 + (xa-yb-xc+yd)* (si1) */
    out2 = (q15) ((Si1 * S0 + Co1 * S1) >> 16U);
    /* writing output(xb', yb') in little endian format */
    pSrc16[i2 * 2U] = out1;
    pSrc16[(i2 * 2U) + 1U] = out2;

    /* Co3 & si3 are read from Coefficient pointer */
    Co3 = pCoef16[3U * ic * 2U];
    Si3 = pCoef16[(3U * ic * 2U) + 1U];
    /*  Butterfly process for the i0+3fftLen/4 sample */
    /* xd' = (xa+yb-xc-yd)* Co3 - (ya-xb-yc+xd)* (si3) */
    out1 = (q15) ((Co3 * R0 - Si3 * R1) >> 16U);
    /* yd' = (ya-xb-yc+xd)* Co3 + (xa+yb-xc-yd)* (si3) */
    out2 = (q15) ((Si3 * R0 + Co3 * R1) >> 16U);
    /* writing output(xd', yd') in little endian format */
    pSrc16[i3 * 2U] = out1;
    pSrc16[(i3 * 2U) + 1U] = out2;

    /*  Twiddle coefficients index modifier */
    ic = ic + twidCoefModifier;

    /*  Updating input index */
    i0 = i0 + 1U;

  } while (--j);

  /*  End of first stage process */

  /* data is in 4.11(q11) format */


  /*  Start of Middle stage process */

  /*  Twiddle coefficients index modifier */
  twidCoefModifier <<= 2U;

  /*  Calculation of Middle stage */
  for (k = fftLen / 4U; k > 4U; k >>= 2U)
  {
    /*  Initializations for the middle stage */
    n1 = n2;
    n2 >>= 2U;
    ic = 0U;

    for (j = 0U; j <= (n2 - 1U); j++)
    {
      /*  index calculation for the coefficients */
      Co1 = pCoef16[ic * 2U];
      Si1 = pCoef16[(ic * 2U) + 1U];
      Co2 = pCoef16[2U * ic * 2U];
      Si2 = pCoef16[2U * ic * 2U + 1U];
      Co3 = pCoef16[3U * ic * 2U];
      Si3 = pCoef16[(3U * ic * 2U) + 1U];

      /*  Twiddle coefficients index modifier */
      ic = ic + twidCoefModifier;

      /*  Butterfly implementation */
      for (i0 = j; i0 < fftLen; i0 += n1)
      {
        /*  index calculation for the input as, */
        /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        /*  Reading i0, i0+fftLen/2 inputs */
        /* Read ya (real), xa(imag) input */
        T0 = pSrc16[i0 * 2U];
        T1 = pSrc16[(i0 * 2U) + 1U];

        /* Read yc (real), xc(imag) input */
        S0 = pSrc16[i2 * 2U];
        S1 = pSrc16[(i2 * 2U) + 1U];


        /* R0 = (ya + yc), R1 = (xa + xc) */
        R0 = __SSAT(T0 + S0, 16U);
        R1 = __SSAT(T1 + S1, 16U);
        /* S0 = (ya - yc), S1 = (xa - xc) */
        S0 = __SSAT(T0 - S0, 16U);
        S1 = __SSAT(T1 - S1, 16U);

        /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
        /* Read yb (real), xb(imag) input */
        T0 = pSrc16[i1 * 2U];
        T1 = pSrc16[(i1 * 2U) + 1U];

        /* Read yd (real), xd(imag) input */
        U0 = pSrc16[i3 * 2U];
        U1 = pSrc16[(i3 * 2U) + 1U];

        /* T0 = (yb + yd), T1 = (xb + xd) */
        T0 = __SSAT(T0 + U0, 16U);
        T1 = __SSAT(T1 + U1, 16U);

        /*  writing the butterfly processed i0 sample */
        /* xa' = xa + xb + xc + xd */
        /* ya' = ya + yb + yc + yd */
        pSrc16[i0 * 2U] = ((R0 >> 1U) + (T0 >> 1U)) >> 1U;
        pSrc16[(i0 * 2U) + 1U] = ((R1 >> 1U) + (T1 >> 1U)) >> 1U;

        /* R0 = (ya + yc) - (yb + yd), R1 = (xa + xc) - (xb + xd) */
        R0 = (R0 >> 1U) - (T0 >> 1U);
        R1 = (R1 >> 1U) - (T1 >> 1U);

        /* (ya-yb+yc-yd)* (si2) - (xa-xb+xc-xd)* co2 */
        out1 = (q15) ((Co2 * R0 - Si2 * R1) >> 16);
        /* (ya-yb+yc-yd)* co2 + (xa-xb+xc-xd)* (si2) */
        out2 = (q15) ((Si2 * R0 + Co2 * R1) >> 16);

        /*  Reading i0+3fftLen/4 */
        /* Read yb (real), xb(imag) input */
        T0 = pSrc16[i1 * 2U];
        T1 = pSrc16[(i1 * 2U) + 1U];

        /*  writing the butterfly processed i0 + fftLen/4 sample */
        /* xc' = (xa-xb+xc-xd)* co2 - (ya-yb+yc-yd)* (si2) */
        /* yc' = (ya-yb+yc-yd)* co2 + (xa-xb+xc-xd)* (si2) */
        pSrc16[i1 * 2U] = out1;
        pSrc16[(i1 * 2U) + 1U] = out2;

        /*  Butterfly calculations */
        /* Read yd (real), xd(imag) input */
        U0 = pSrc16[i3 * 2U];
        U1 = pSrc16[(i3 * 2U) + 1U];

        /* T0 = yb-yd, T1 = xb-xd) */
        T0 = __SSAT(T0 - U0, 16U);
        T1 = __SSAT(T1 - U1, 16U);

        /* R0 = (ya-yc) - (xb- xd) , R1 = (xa-xc) + (yb-yd) */
        R0 = (S0 >> 1U) + (T1 >> 1U);
        R1 = (S1 >> 1U) - (T0 >> 1U);

        /* S1 = (ya-yc) + (xb- xd), S1 = (xa-xc) - (yb-yd) */
        S0 = (S0 >> 1U) - (T1 >> 1U);
        S1 = (S1 >> 1U) + (T0 >> 1U);

        /*  Butterfly process for the i0+fftLen/2 sample */
        out1 = (q15) ((Co1 * S0 - Si1 * S1) >> 16U);
        out2 = (q15) ((Si1 * S0 + Co1 * S1) >> 16U);
        /* xb' = (xa-yb-xc+yd)* co1 - (ya+xb-yc-xd)* (si1) */
        /* yb' = (ya+xb-yc-xd)* co1 + (xa-yb-xc+yd)* (si1) */
        pSrc16[i2 * 2U] = out1;
        pSrc16[(i2 * 2U) + 1U] = out2;

        /*  Butterfly process for the i0+3fftLen/4 sample */
        out1 = (q15) ((Co3 * R0 - Si3 * R1) >> 16U);

        out2 = (q15) ((Si3 * R0 + Co3 * R1) >> 16U);
        /* xd' = (xa+yb-xc-yd)* Co3 - (ya-xb-yc+xd)* (si3) */
        /* yd' = (ya-xb-yc+xd)* Co3 + (xa+yb-xc-yd)* (si3) */
        pSrc16[i3 * 2U] = out1;
        pSrc16[(i3 * 2U) + 1U] = out2;


      }
    }
    /*  Twiddle coefficients index modifier */
    twidCoefModifier <<= 2U;
  }
  /*  End of Middle stages process */


  /* data is in 10.6(q6) format for the 1024 point */
  /* data is in 8.8(q8) format for the 256 point   */
  /* data is in 6.10(q10) format for the 64 point  */
  /* data is in 4.12(q12) format for the 16 point  */

  /* start of last stage process */


  /*  Initializations for the last stage */
  n1 = n2;
  n2 >>= 2U;

  /*  Butterfly implementation */
  for (i0 = 0U; i0 <= (fftLen - n1); i0 += n1)
  {
    /*  index calculation for the input as, */
    /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    /*  Reading i0, i0+fftLen/2 inputs */
    /* Read ya (real), xa(imag) input */
    T0 = pSrc16[i0 * 2U];
    T1 = pSrc16[(i0 * 2U) + 1U];
    /* Read yc (real), xc(imag) input */
    S0 = pSrc16[i2 * 2U];
    S1 = pSrc16[(i2 * 2U) + 1U];

    /* R0 = (ya + yc), R1 = (xa + xc) */
    R0 = __SSAT(T0 + S0, 16U);
    R1 = __SSAT(T1 + S1, 16U);
    /* S0 = (ya - yc), S1 = (xa - xc) */
    S0 = __SSAT(T0 - S0, 16U);
    S1 = __SSAT(T1 - S1, 16U);

    /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
    /* Read yb (real), xb(imag) input */
    T0 = pSrc16[i1 * 2U];
    T1 = pSrc16[(i1 * 2U) + 1U];
    /* Read yd (real), xd(imag) input */
    U0 = pSrc16[i3 * 2U];
    U1 = pSrc16[(i3 * 2U) + 1U];

    /* T0 = (yb + yd), T1 = (xb + xd) */
    T0 = __SSAT(T0 + U0, 16U);
    T1 = __SSAT(T1 + U1, 16U);

    /*  writing the butterfly processed i0 sample */
    /* xa' = xa + xb + xc + xd */
    /* ya' = ya + yb + yc + yd */
    pSrc16[i0 * 2U] = (R0 >> 1U) + (T0 >> 1U);
    pSrc16[(i0 * 2U) + 1U] = (R1 >> 1U) + (T1 >> 1U);

    /* R0 = (ya + yc) - (yb + yd), R1 = (xa + xc) - (xb + xd) */
    R0 = (R0 >> 1U) - (T0 >> 1U);
    R1 = (R1 >> 1U) - (T1 >> 1U);

    /* Read yb (real), xb(imag) input */
    T0 = pSrc16[i1 * 2U];
    T1 = pSrc16[(i1 * 2U) + 1U];

    /*  writing the butterfly processed i0 + fftLen/4 sample */
    /* xc' = (xa-xb+xc-xd) */
    /* yc' = (ya-yb+yc-yd) */
    pSrc16[i1 * 2U] = R0;
    pSrc16[(i1 * 2U) + 1U] = R1;

    /* Read yd (real), xd(imag) input */
    U0 = pSrc16[i3 * 2U];
    U1 = pSrc16[(i3 * 2U) + 1U];
    /* T0 = (yb - yd), T1 = (xb - xd) */
    T0 = __SSAT(T0 - U0, 16U);
    T1 = __SSAT(T1 - U1, 16U);

    /*  writing the butterfly processed i0 + fftLen/2 sample */
    /* xb' = (xa-yb-xc+yd) */
    /* yb' = (ya+xb-yc-xd) */
    pSrc16[i2 * 2U] = (S0 >> 1U) - (T1 >> 1U);
    pSrc16[(i2 * 2U) + 1U] = (S1 >> 1U) + (T0 >> 1U);


    /*  writing the butterfly processed i0 + 3fftLen/4 sample */
    /* xd' = (xa+yb-xc-yd) */
    /* yd' = (ya-xb-yc+xd) */
    pSrc16[i3 * 2U] = (S0 >> 1U) + (T1 >> 1U);
    pSrc16[(i3 * 2U) + 1U] = (S1 >> 1U) - (T0 >> 1U);
  }
  /* end of last stage  process */

  /* output is in 11.5(q5) format for the 1024 point */
  /* output is in 9.7(q7) format for the 256 point   */
  /* output is in 7.9(q9) format for the 64 point  */
  /* output is in 5.11(q11) format for the 16 point  */


}