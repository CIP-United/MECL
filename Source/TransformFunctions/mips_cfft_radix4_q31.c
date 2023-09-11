/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cfft_radix4_q31.c
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

void mips_radix4_butterfly_inverse_q31(
        q31 * pSrc,
        uint32_t fftLen,
  const q31 * pCoef,
        uint32_t twidCoefModifier);

void mips_radix4_butterfly_q31(
        q31 * pSrc,
        uint32_t fftLen,
  const q31 * pCoef,
        uint32_t twidCoefModifier);

void mips_bitreversal_q31(
        q31 * pSrc,
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
  @brief         Processing function for the Q31 CFFT/CIFFT.
  @deprecated    Do not use this function.  It has been superseded by \ref mips_cfft_q31 and will be removed in the future.
  @param[in]     S    points to an instance of the Q31 CFFT/CIFFT structure
  @param[in,out] pSrc points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place
  @return        none
 
  @par Input and output formats:
                 Internally input is downscaled by 2 for every stage to avoid saturations inside CFFT/CIFFT process.
                 Hence the output format is different for different FFT sizes.
                 The input and output formats for different FFT sizes and number of bits to upscale are mentioned in the tables below for CFFT and CIFFT:
  @par

| CFFT Size | Input format  | Output format | Number of bits to upscale |
| --------: | ------------: | ------------: | ------------------------: |
| 16        | 1.31          | 5.27          | 4                         |
| 64        | 1.31          | 7.25          | 6                         |
| 256       | 1.31          | 9.23          | 8                         |
| 1024      | 1.31          | 11.21         | 10                        |

| CIFFT Size | Input format  | Output format | Number of bits to upscale |
| ---------: | ------------: | ------------: | ------------------------: |
| 16         | 1.31          | 5.27          | 0                         |
| 64         | 1.31          | 7.25          | 0                         |
| 256        | 1.31          | 9.23          | 0                         |
| 1024       | 1.31          | 11.21         | 0                         |

 */

void mips_cfft_radix4_q31(
  const mips_cfft_radix4_instance_q31 * S,
        q31 * pSrc)
{
  if (S->ifftFlag == 1U)
  {
    /* Complex IFFT radix-4 */
    mips_radix4_butterfly_inverse_q31(pSrc, S->fftLen, S->pTwiddle, S->twidCoefModifier);
  }
  else
  {
    /* Complex FFT radix-4 */
    mips_radix4_butterfly_q31(pSrc, S->fftLen, S->pTwiddle, S->twidCoefModifier);
  }

  if (S->bitReverseFlag == 1U)
  {
    /*  Bit Reversal */
    mips_bitreversal_q31(pSrc, S->fftLen, S->bitRevFactor, S->pBitRevTable);
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
 *
 *  Butterfly implementation:
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
  @brief         Core function for the Q31 CFFT butterfly process.
  @param[in,out] pSrc             points to the in-place buffer of Q31 data type.
  @param[in]     fftLen           length of the FFT.
  @param[in]     pCoef            points to twiddle coefficient buffer.
  @param[in]     twidCoefModifier twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.
  @return        none
 */

void mips_radix4_butterfly_q31(
        q31 * pSrc,
        uint32_t fftLen,
  const q31 * pCoef,
        uint32_t twidCoefModifier)
{
        uint32_t n1, n2, ia1, ia2, ia3, i0, i1, i2, i3, j, k;
        q31 t1, t2, r1, r2, s1, s2, co1, co2, co3, si1, si2, si3;
        
        q31 xa, xb, xc, xd;
        q31 ya, yb, yc, yd;
        q31 xa_out, xb_out, xc_out, xd_out;
        q31 ya_out, yb_out, yc_out, yd_out;
        
        q31 *ptr1;

  /* Total process is divided into three stages */

  /* process first stage, middle stages, & last stage */


  /* start of first stage process */

  /*  Initializations for the first stage */
  n2 = fftLen;
  n1 = n2;
  /* n2 = fftLen/4 */
  n2 >>= 2U;
  i0 = 0U;
  ia1 = 0U;

  j = n2;

  /*  Calculation of first stage */
  do
  {
    /*  index calculation for the input as, */
    /*  pSrc[i0 + 0], pSrc[i0 + fftLen/4], pSrc[i0 + fftLen/2U], pSrc[i0 + 3fftLen/4] */
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    /* input is in 1.31(q31) format and provide 4 guard bits for the input */

    /*  Butterfly implementation */
    /* xa + xc */
    r1 = (pSrc[(2U * i0)] >> 4U) + (pSrc[(2U * i2)] >> 4U);
    /* xa - xc */
    r2 = (pSrc[(2U * i0)] >> 4U) - (pSrc[(2U * i2)] >> 4U);

    /* xb + xd */
    t1 = (pSrc[(2U * i1)] >> 4U) + (pSrc[(2U * i3)] >> 4U);

    /* ya + yc */
    s1 = (pSrc[(2U * i0) + 1U] >> 4U) + (pSrc[(2U * i2) + 1U] >> 4U);
    /* ya - yc */
    s2 = (pSrc[(2U * i0) + 1U] >> 4U) - (pSrc[(2U * i2) + 1U] >> 4U);

    /* xa' = xa + xb + xc + xd */
    pSrc[2U * i0] = (r1 + t1);
    /* (xa + xc) - (xb + xd) */
    r1 = r1 - t1;
    /* yb + yd */
    t2 = (pSrc[(2U * i1) + 1U] >> 4U) + (pSrc[(2U * i3) + 1U] >> 4U);

    /* ya' = ya + yb + yc + yd */
    pSrc[(2U * i0) + 1U] = (s1 + t2);

    /* (ya + yc) - (yb + yd) */
    s1 = s1 - t2;

    /* yb - yd */
    t1 = (pSrc[(2U * i1) + 1U] >> 4U) - (pSrc[(2U * i3) + 1U] >> 4U);
    /* xb - xd */
    t2 = (pSrc[(2U * i1)] >> 4U) - (pSrc[(2U * i3)] >> 4U);

    /*  index calculation for the coefficients */
    ia2 = 2U * ia1;
    co2 = pCoef[(ia2 * 2U)];
    si2 = pCoef[(ia2 * 2U) + 1U];

    /* xc' = (xa-xb+xc-xd)co2 + (ya-yb+yc-yd)(si2) */
    pSrc[2U * i1] = (((int32_t) (((q63) r1 * co2) >> 32)) +
                     ((int32_t) (((q63) s1 * si2) >> 32))) << 1U;

    /* yc' = (ya-yb+yc-yd)co2 - (xa-xb+xc-xd)(si2) */
    pSrc[(2U * i1) + 1U] = (((int32_t) (((q63) s1 * co2) >> 32)) -
                            ((int32_t) (((q63) r1 * si2) >> 32))) << 1U;

    /* (xa - xc) + (yb - yd) */
    r1 = r2 + t1;
    /* (xa - xc) - (yb - yd) */
    r2 = r2 - t1;

    /* (ya - yc) - (xb - xd) */
    s1 = s2 - t2;
    /* (ya - yc) + (xb - xd) */
    s2 = s2 + t2;

    co1 = pCoef[(ia1 * 2U)];
    si1 = pCoef[(ia1 * 2U) + 1U];

    /* xb' = (xa+yb-xc-yd)co1 + (ya-xb-yc+xd)(si1) */
    pSrc[2U * i2] = (((int32_t) (((q63) r1 * co1) >> 32)) +
                     ((int32_t) (((q63) s1 * si1) >> 32))) << 1U;

    /* yb' = (ya-xb-yc+xd)co1 - (xa+yb-xc-yd)(si1) */
    pSrc[(2U * i2) + 1U] = (((int32_t) (((q63) s1 * co1) >> 32)) -
                            ((int32_t) (((q63) r1 * si1) >> 32))) << 1U;

    /*  index calculation for the coefficients */
    ia3 = 3U * ia1;
    co3 = pCoef[(ia3 * 2U)];
    si3 = pCoef[(ia3 * 2U) + 1U];

    /* xd' = (xa-yb-xc+yd)co3 + (ya+xb-yc-xd)(si3) */
    pSrc[2U * i3] = (((int32_t) (((q63) r2 * co3) >> 32)) +
                     ((int32_t) (((q63) s2 * si3) >> 32))) << 1U;

    /* yd' = (ya+xb-yc-xd)co3 - (xa-yb-xc+yd)(si3) */
    pSrc[(2U * i3) + 1U] = (((int32_t) (((q63) s2 * co3) >> 32)) -
                            ((int32_t) (((q63) r2 * si3) >> 32))) << 1U;

    /*  Twiddle coefficients index modifier */
    ia1 = ia1 + twidCoefModifier;

    /*  Updating input index */
    i0 = i0 + 1U;

  } while (--j);

  /* end of first stage process */

  /* data is in 5.27(q27) format */


  /* start of Middle stages process */


  /* each stage in middle stages provides two down scaling of the input */

  twidCoefModifier <<= 2U;


  for (k = fftLen / 4U; k > 4U; k >>= 2U)
  {
    /*  Initializations for the first stage */
    n1 = n2;
    n2 >>= 2U;
    ia1 = 0U;

    /*  Calculation of first stage */
    for (j = 0U; j <= (n2 - 1U); j++)
    {
      /*  index calculation for the coefficients */
      ia2 = ia1 + ia1;
      ia3 = ia2 + ia1;
      co1 = pCoef[(ia1 * 2U)];
      si1 = pCoef[(ia1 * 2U) + 1U];
      co2 = pCoef[(ia2 * 2U)];
      si2 = pCoef[(ia2 * 2U) + 1U];
      co3 = pCoef[(ia3 * 2U)];
      si3 = pCoef[(ia3 * 2U) + 1U];
      /*  Twiddle coefficients index modifier */
      ia1 = ia1 + twidCoefModifier;

      for (i0 = j; i0 < fftLen; i0 += n1)
      {
        /*  index calculation for the input as, */
        /*  pSrc[i0 + 0], pSrc[i0 + fftLen/4], pSrc[i0 + fftLen/2U], pSrc[i0 + 3fftLen/4] */
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        /*  Butterfly implementation */
        /* xa + xc */
        r1 = pSrc[2U * i0] + pSrc[2U * i2];
        /* xa - xc */
        r2 = pSrc[2U * i0] - pSrc[2U * i2];

        /* ya + yc */
        s1 = pSrc[(2U * i0) + 1U] + pSrc[(2U * i2) + 1U];
        /* ya - yc */
        s2 = pSrc[(2U * i0) + 1U] - pSrc[(2U * i2) + 1U];

        /* xb + xd */
        t1 = pSrc[2U * i1] + pSrc[2U * i3];

        /* xa' = xa + xb + xc + xd */
        pSrc[2U * i0] = (r1 + t1) >> 2U;
        /* xa + xc -(xb + xd) */
        r1 = r1 - t1;

        /* yb + yd */
        t2 = pSrc[(2U * i1) + 1U] + pSrc[(2U * i3) + 1U];
        /* ya' = ya + yb + yc + yd */
        pSrc[(2U * i0) + 1U] = (s1 + t2) >> 2U;

        /* (ya + yc) - (yb + yd) */
        s1 = s1 - t2;

        /* (yb - yd) */
        t1 = pSrc[(2U * i1) + 1U] - pSrc[(2U * i3) + 1U];
        /* (xb - xd) */
        t2 = pSrc[2U * i1] - pSrc[2U * i3];

        /* xc' = (xa-xb+xc-xd)co2 + (ya-yb+yc-yd)(si2) */
        pSrc[2U * i1] = (((int32_t) (((q63) r1 * co2) >> 32)) +
                         ((int32_t) (((q63) s1 * si2) >> 32))) >> 1U;

        /* yc' = (ya-yb+yc-yd)co2 - (xa-xb+xc-xd)(si2) */
        pSrc[(2U * i1) + 1U] = (((int32_t) (((q63) s1 * co2) >> 32)) -
                                ((int32_t) (((q63) r1 * si2) >> 32))) >> 1U;

        /* (xa - xc) + (yb - yd) */
        r1 = r2 + t1;
        /* (xa - xc) - (yb - yd) */
        r2 = r2 - t1;

        /* (ya - yc) -  (xb - xd) */
        s1 = s2 - t2;
        /* (ya - yc) +  (xb - xd) */
        s2 = s2 + t2;

        /* xb' = (xa+yb-xc-yd)co1 + (ya-xb-yc+xd)(si1) */
        pSrc[2U * i2] = (((int32_t) (((q63) r1 * co1) >> 32)) +
                         ((int32_t) (((q63) s1 * si1) >> 32))) >> 1U;

        /* yb' = (ya-xb-yc+xd)co1 - (xa+yb-xc-yd)(si1) */
        pSrc[(2U * i2) + 1U] = (((int32_t) (((q63) s1 * co1) >> 32)) -
                                ((int32_t) (((q63) r1 * si1) >> 32))) >> 1U;

        /* xd' = (xa-yb-xc+yd)co3 + (ya+xb-yc-xd)(si3) */
        pSrc[2U * i3] = (((int32_t) (((q63) r2 * co3) >> 32)) +
                         ((int32_t) (((q63) s2 * si3) >> 32))) >> 1U;

        /* yd' = (ya+xb-yc-xd)co3 - (xa-yb-xc+yd)(si3) */
        pSrc[(2U * i3) + 1U] = (((int32_t) (((q63) s2 * co3) >> 32)) -
                                ((int32_t) (((q63) r2 * si3) >> 32))) >> 1U;
      }
    }
    twidCoefModifier <<= 2U;
  }

  /* End of Middle stages process */

  /* data is in 11.21(q21) format for the 1024 point as there are 3 middle stages */
  /* data is in 9.23(q23) format for the 256 point as there are 2 middle stages */
  /* data is in 7.25(q25) format for the 64 point as there are 1 middle stage */
  /* data is in 5.27(q27) format for the 16 point as there are no middle stages */


  /* start of Last stage process */
  /*  Initializations for the last stage */
  j = fftLen >> 2;
  ptr1 = &pSrc[0];

  /*  Calculations of last stage */
  do
  {
    /* Read xa (real), ya(imag) input */
    xa = *ptr1++;
    ya = *ptr1++;

    /* Read xb (real), yb(imag) input */
    xb = *ptr1++;
    yb = *ptr1++;

    /* Read xc (real), yc(imag) input */
    xc = *ptr1++;
    yc = *ptr1++;

    /* Read xc (real), yc(imag) input */
    xd = *ptr1++;
    yd = *ptr1++;

    /* xa' = xa + xb + xc + xd */
    xa_out = xa + xb + xc + xd;

    /* ya' = ya + yb + yc + yd */
    ya_out = ya + yb + yc + yd;

    /* pointer updation for writing */
    ptr1 = ptr1 - 8U;

    /* writing xa' and ya' */
    *ptr1++ = xa_out;
    *ptr1++ = ya_out;

    xc_out = (xa - xb + xc - xd);
    yc_out = (ya - yb + yc - yd);

    /* writing xc' and yc' */
    *ptr1++ = xc_out;
    *ptr1++ = yc_out;

    xb_out = (xa + yb - xc - yd);
    yb_out = (ya - xb - yc + xd);

    /* writing xb' and yb' */
    *ptr1++ = xb_out;
    *ptr1++ = yb_out;

    xd_out = (xa - yb - xc + yd);
    yd_out = (ya + xb - yc - xd);

    /* writing xd' and yd' */
    *ptr1++ = xd_out;
    *ptr1++ = yd_out;


  } while (--j);

  /* output is in 11.21(q21) format for the 1024 point */
  /* output is in 9.23(q23) format for the 256 point */
  /* output is in 7.25(q25) format for the 64 point */
  /* output is in 5.27(q27) format for the 16 point */

  /* End of last stage process */

}


/**
  @brief         Core function for the Q31 CIFFT butterfly process.
  @param[in,out] pSrc             points to the in-place buffer of Q31 data type.
  @param[in]     fftLen           length of the FFT.
  @param[in]     pCoef            points to twiddle coefficient buffer.
  @param[in]     twidCoefModifier twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.
  @return        none
 */

/*
 * Radix-4 IFFT algorithm used is :
 *
 * CIFFT uses same twiddle coefficients as CFFT Function
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

void mips_radix4_butterfly_inverse_q31(
        q31 * pSrc,
        uint32_t fftLen,
  const q31 * pCoef,
        uint32_t twidCoefModifier)
{
        uint32_t n1, n2, ia1, ia2, ia3, i0, i1, i2, i3, j, k;
        q31 t1, t2, r1, r2, s1, s2, co1, co2, co3, si1, si2, si3;
        q31 xa, xb, xc, xd;
        q31 ya, yb, yc, yd;
        q31 xa_out, xb_out, xc_out, xd_out;
        q31 ya_out, yb_out, yc_out, yd_out;
        
        q31 *ptr1;

  /* input is be 1.31(q31) format for all FFT sizes */
  /* Total process is divided into three stages */
  /* process first stage, middle stages, & last stage */

  /* Start of first stage process */

  /* Initializations for the first stage */
  n2 = fftLen;
  n1 = n2;
  /* n2 = fftLen/4 */
  n2 >>= 2U;
  i0 = 0U;
  ia1 = 0U;

  j = n2;

  do
  {
    /* input is in 1.31(q31) format and provide 4 guard bits for the input */

    /*  index calculation for the input as, */
    /*  pSrc[i0 + 0], pSrc[i0 + fftLen/4], pSrc[i0 + fftLen/2U], pSrc[i0 + 3fftLen/4] */
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    /*  Butterfly implementation */
    /* xa + xc */
    r1 = (pSrc[2U * i0] >> 4U) + (pSrc[2U * i2] >> 4U);
    /* xa - xc */
    r2 = (pSrc[2U * i0] >> 4U) - (pSrc[2U * i2] >> 4U);

    /* xb + xd */
    t1 = (pSrc[2U * i1] >> 4U) + (pSrc[2U * i3] >> 4U);

    /* ya + yc */
    s1 = (pSrc[(2U * i0) + 1U] >> 4U) + (pSrc[(2U * i2) + 1U] >> 4U);
    /* ya - yc */
    s2 = (pSrc[(2U * i0) + 1U] >> 4U) - (pSrc[(2U * i2) + 1U] >> 4U);

    /* xa' = xa + xb + xc + xd */
    pSrc[2U * i0] = (r1 + t1);
    /* (xa + xc) - (xb + xd) */
    r1 = r1 - t1;
    /* yb + yd */
    t2 = (pSrc[(2U * i1) + 1U] >> 4U) + (pSrc[(2U * i3) + 1U] >> 4U);
    /* ya' = ya + yb + yc + yd */
    pSrc[(2U * i0) + 1U] = (s1 + t2);

    /* (ya + yc) - (yb + yd) */
    s1 = s1 - t2;

    /* yb - yd */
    t1 = (pSrc[(2U * i1) + 1U] >> 4U) - (pSrc[(2U * i3) + 1U] >> 4U);
    /* xb - xd */
    t2 = (pSrc[2U * i1] >> 4U) - (pSrc[2U * i3] >> 4U);

    /*  index calculation for the coefficients */
    ia2 = 2U * ia1;
    co2 = pCoef[ia2 * 2U];
    si2 = pCoef[(ia2 * 2U) + 1U];

    /* xc' = (xa-xb+xc-xd)co2 - (ya-yb+yc-yd)(si2) */
    pSrc[2U * i1] = (((int32_t) (((q63) r1 * co2) >> 32)) -
                     ((int32_t) (((q63) s1 * si2) >> 32))) << 1U;

    /* yc' = (ya-yb+yc-yd)co2 + (xa-xb+xc-xd)(si2) */
    pSrc[2U * i1 + 1U] = (((int32_t) (((q63) s1 * co2) >> 32)) +
                          ((int32_t) (((q63) r1 * si2) >> 32))) << 1U;

    /* (xa - xc) - (yb - yd) */
    r1 = r2 - t1;
    /* (xa - xc) + (yb - yd) */
    r2 = r2 + t1;

    /* (ya - yc) + (xb - xd) */
    s1 = s2 + t2;
    /* (ya - yc) - (xb - xd) */
    s2 = s2 - t2;

    co1 = pCoef[ia1 * 2U];
    si1 = pCoef[(ia1 * 2U) + 1U];

    /* xb' = (xa+yb-xc-yd)co1 - (ya-xb-yc+xd)(si1) */
    pSrc[2U * i2] = (((int32_t) (((q63) r1 * co1) >> 32)) -
                     ((int32_t) (((q63) s1 * si1) >> 32))) << 1U;

    /* yb' = (ya-xb-yc+xd)co1 + (xa+yb-xc-yd)(si1) */
    pSrc[(2U * i2) + 1U] = (((int32_t) (((q63) s1 * co1) >> 32)) +
                            ((int32_t) (((q63) r1 * si1) >> 32))) << 1U;

    /*  index calculation for the coefficients */
    ia3 = 3U * ia1;
    co3 = pCoef[ia3 * 2U];
    si3 = pCoef[(ia3 * 2U) + 1U];

    /* xd' = (xa-yb-xc+yd)co3 - (ya+xb-yc-xd)(si3) */
    pSrc[2U * i3] = (((int32_t) (((q63) r2 * co3) >> 32)) -
                     ((int32_t) (((q63) s2 * si3) >> 32))) << 1U;

    /* yd' = (ya+xb-yc-xd)co3 + (xa-yb-xc+yd)(si3) */
    pSrc[(2U * i3) + 1U] = (((int32_t) (((q63) s2 * co3) >> 32)) +
                            ((int32_t) (((q63) r2 * si3) >> 32))) << 1U;

    /*  Twiddle coefficients index modifier */
    ia1 = ia1 + twidCoefModifier;

    /*  Updating input index */
    i0 = i0 + 1U;

  } while (--j);

  /* data is in 5.27(q27) format */
  /* each stage provides two down scaling of the input */


  /* Start of Middle stages process */

  twidCoefModifier <<= 2U;

  /*  Calculation of second stage to excluding last stage */
  for (k = fftLen / 4U; k > 4U; k >>= 2U)
  {
    /*  Initializations for the first stage */
    n1 = n2;
    n2 >>= 2U;
    ia1 = 0U;

    for (j = 0; j <= (n2 - 1U); j++)
    {
      /*  index calculation for the coefficients */
      ia2 = ia1 + ia1;
      ia3 = ia2 + ia1;
      co1 = pCoef[(ia1 * 2U)];
      si1 = pCoef[(ia1 * 2U) + 1U];
      co2 = pCoef[(ia2 * 2U)];
      si2 = pCoef[(ia2 * 2U) + 1U];
      co3 = pCoef[(ia3 * 2U)];
      si3 = pCoef[(ia3 * 2U) + 1U];
      /*  Twiddle coefficients index modifier */
      ia1 = ia1 + twidCoefModifier;

      for (i0 = j; i0 < fftLen; i0 += n1)
      {
        /*  index calculation for the input as, */
        /*  pSrc[i0 + 0], pSrc[i0 + fftLen/4], pSrc[i0 + fftLen/2U], pSrc[i0 + 3fftLen/4] */
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        /*  Butterfly implementation */
        /* xa + xc */
        r1 = pSrc[2U * i0] + pSrc[2U * i2];
        /* xa - xc */
        r2 = pSrc[2U * i0] - pSrc[2U * i2];

        /* ya + yc */
        s1 = pSrc[(2U * i0) + 1U] + pSrc[(2U * i2) + 1U];
        /* ya - yc */
        s2 = pSrc[(2U * i0) + 1U] - pSrc[(2U * i2) + 1U];

        /* xb + xd */
        t1 = pSrc[2U * i1] + pSrc[2U * i3];

        /* xa' = xa + xb + xc + xd */
        pSrc[2U * i0] = (r1 + t1) >> 2U;
        /* xa + xc -(xb + xd) */
        r1 = r1 - t1;
        /* yb + yd */
        t2 = pSrc[(2U * i1) + 1U] + pSrc[(2U * i3) + 1U];
        /* ya' = ya + yb + yc + yd */
        pSrc[(2U * i0) + 1U] = (s1 + t2) >> 2U;

        /* (ya + yc) - (yb + yd) */
        s1 = s1 - t2;

        /* (yb - yd) */
        t1 = pSrc[(2U * i1) + 1U] - pSrc[(2U * i3) + 1U];
        /* (xb - xd) */
        t2 = pSrc[2U * i1] - pSrc[2U * i3];

        /* xc' = (xa-xb+xc-xd)co2 - (ya-yb+yc-yd)(si2) */
        pSrc[2U * i1] = (((int32_t) (((q63) r1 * co2) >> 32U)) -
                         ((int32_t) (((q63) s1 * si2) >> 32U))) >> 1U;

        /* yc' = (ya-yb+yc-yd)co2 + (xa-xb+xc-xd)(si2) */
        pSrc[(2U * i1) + 1U] = (((int32_t) (((q63) s1 * co2) >> 32U)) +
                                ((int32_t) (((q63) r1 * si2) >> 32U))) >> 1U;

        /* (xa - xc) - (yb - yd) */
        r1 = r2 - t1;
        /* (xa - xc) + (yb - yd) */
        r2 = r2 + t1;

        /* (ya - yc) +  (xb - xd) */
        s1 = s2 + t2;
        /* (ya - yc) -  (xb - xd) */
        s2 = s2 - t2;

        /* xb' = (xa+yb-xc-yd)co1 - (ya-xb-yc+xd)(si1) */
        pSrc[2U * i2] = (((int32_t) (((q63) r1 * co1) >> 32)) -
                         ((int32_t) (((q63) s1 * si1) >> 32))) >> 1U;

        /* yb' = (ya-xb-yc+xd)co1 + (xa+yb-xc-yd)(si1) */
        pSrc[(2U * i2) + 1U] = (((int32_t) (((q63) s1 * co1) >> 32)) +
                                ((int32_t) (((q63) r1 * si1) >> 32))) >> 1U;

        /* xd' = (xa-yb-xc+yd)co3 - (ya+xb-yc-xd)(si3) */
        pSrc[(2U * i3)] = (((int32_t) (((q63) r2 * co3) >> 32)) -
                           ((int32_t) (((q63) s2 * si3) >> 32))) >> 1U;

        /* yd' = (ya+xb-yc-xd)co3 + (xa-yb-xc+yd)(si3) */
        pSrc[(2U * i3) + 1U] = (((int32_t) (((q63) s2 * co3) >> 32)) +
                                ((int32_t) (((q63) r2 * si3) >> 32))) >> 1U;
      }
    }
    twidCoefModifier <<= 2U;
  }

  /* End of Middle stages process */

  /* data is in 11.21(q21) format for the 1024 point as there are 3 middle stages */
  /* data is in 9.23(q23) format for the 256 point as there are 2 middle stages */
  /* data is in 7.25(q25) format for the 64 point as there are 1 middle stage */
  /* data is in 5.27(q27) format for the 16 point as there are no middle stages */


  /* Start of last stage process */


  /*  Initializations for the last stage */
  j = fftLen >> 2;
  ptr1 = &pSrc[0];

  /*  Calculations of last stage */
  do
  {
    /* Read xa (real), ya(imag) input */
    xa = *ptr1++;
    ya = *ptr1++;

    /* Read xb (real), yb(imag) input */
    xb = *ptr1++;
    yb = *ptr1++;

    /* Read xc (real), yc(imag) input */
    xc = *ptr1++;
    yc = *ptr1++;

    /* Read xc (real), yc(imag) input */
    xd = *ptr1++;
    yd = *ptr1++;

    /* xa' = xa + xb + xc + xd */
    xa_out = xa + xb + xc + xd;

    /* ya' = ya + yb + yc + yd */
    ya_out = ya + yb + yc + yd;

    /* pointer updation for writing */
    ptr1 = ptr1 - 8U;

    /* writing xa' and ya' */
    *ptr1++ = xa_out;
    *ptr1++ = ya_out;

    xc_out = (xa - xb + xc - xd);
    yc_out = (ya - yb + yc - yd);

    /* writing xc' and yc' */
    *ptr1++ = xc_out;
    *ptr1++ = yc_out;

    xb_out = (xa - yb - xc + yd);
    yb_out = (ya + xb - yc - xd);

    /* writing xb' and yb' */
    *ptr1++ = xb_out;
    *ptr1++ = yb_out;

    xd_out = (xa + yb - xc - yd);
    yd_out = (ya - xb - yc + xd);

    /* writing xd' and yd' */
    *ptr1++ = xd_out;
    *ptr1++ = yd_out;

  } while (--j);

  /* output is in 11.21(q21) format for the 1024 point */
  /* output is in 9.23(q23) format for the 256 point */
  /* output is in 7.25(q25) format for the 64 point */
  /* output is in 5.27(q27) format for the 16 point */

  /* End of last stage process */
}
