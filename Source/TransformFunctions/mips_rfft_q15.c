/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_rfft_q15.c
 * Description:  RFFT & RIFFT Q15 process function
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

/* ----------------------------------------------------------------------
 * Internal functions prototypes
 * -------------------------------------------------------------------- */

void mips_split_rfft_q15(
        q15 * pSrc,
        uint32_t fftLen,
  const q15 * pATable,
  const q15 * pBTable,
        q15 * pDst,
        uint32_t modifier);

void mips_split_rifft_q15(
        q15 * pSrc,
        uint32_t fftLen,
  const q15 * pATable,
  const q15 * pBTable,
        q15 * pDst,
        uint32_t modifier);

/**
  @addtogroup RealFFT
  @{
 */

/**
  @brief         Processing function for the Q15 RFFT/RIFFT.
  @param[in]     S     points to an instance of the Q15 RFFT/RIFFT structure
  @param[in]     pSrc  points to input buffer (Source buffer is modified by this function.)
  @param[out]    pDst  points to output buffer
  @return        none

  @par           Input an output formats
                   Internally input is downscaled by 2 for every stage to avoid saturations inside CFFT/CIFFT process.
                   Hence the output format is different for different RFFT sizes.
                   The input and output formats for different RFFT sizes and number of bits to upscale are mentioned in the tables below for RFFT and RIFFT:
  @par             Input and Output formats for RFFT Q15

| RFFT Size  | Input Format  | Output Format  | Number of bits to upscale |
| ---------: | ------------: | -------------: | ------------------------: |
| 32         | 1.15          | 5.11           | 5                         |
| 64         | 1.15          | 6.10           | 6                         |
| 128        | 1.15          | 7.9            | 7                         |
| 256        | 1.15          | 8.8            | 8                         |
| 512        | 1.15          | 9.7            | 9                         |
| 1024       | 1.15          | 10.6           | 10                        |
| 2048       | 1.15          | 11.5           | 11                        |
| 4096       | 1.15          | 12.4           | 12                        |
| 8192       | 1.15          | 13.3           | 13                        |
             
  @par             Input and Output formats for RIFFT Q15

| RIFFT Size  | Input Format  | Output Format  | Number of bits to upscale |
| ----------: | ------------: | -------------: | ------------------------: |
| 32          | 1.15          | 5.11           | 0                         |
| 64          | 1.15          | 6.10           | 0                         |
| 128         | 1.15          | 7.9            | 0                         |
| 256         | 1.15          | 8.8            | 0                         |
| 512         | 1.15          | 9.7            | 0                         |
| 1024        | 1.15          | 10.6           | 0                         |
| 2048        | 1.15          | 11.5           | 0                         |
| 4096        | 1.15          | 12.4           | 0                         |
| 8192        | 1.15          | 13.3           | 0                         |
  
  @par
                   If the input buffer is of length N (fftLenReal), the output buffer must have length 2N + 2
                   since it is containing the conjugate part. (N/2 + 1 + N/2 complex samples)
                   The input buffer is modified by this function.
  @par
                   For the RIFFT, the source buffer must have at least length 
                   fftLenReal + 2 which is (N/2 + 1 complex samples). It is not using the conjugate part.
                   The last two elements must be equal to what would be generated
                   by the RFFT:
                     (pSrc[0] - pSrc[1]) >> 1 and 0
 */

void mips_rfft_q15(
  const mips_rfft_instance_q15 * S,
        q15 * pSrc,
        q15 * pDst)
{

  const mips_cfft_instance_q15 *S_CFFT = S->pCfft;

        uint32_t L2 = S->fftLenReal >> 1U;

  /* Calculation of RIFFT of input */
  if (S->ifftFlagR == 1U)
  {
     /*  Real IFFT core process */
     mips_split_rifft_q15 (pSrc, L2, S->pTwiddleAReal, S->pTwiddleBReal, pDst, S->twidCoefRModifier);

     /* Complex IFFT process */
     mips_cfft_q15 (S_CFFT, pDst, S->ifftFlagR, S->bitReverseFlagR);

     mips_shift_q15(pDst, 1, pDst, S->fftLenReal);
  }
  else
  {
     /* Calculation of RFFT of input */

     /* Complex FFT process */
     mips_cfft_q15 (S_CFFT, pSrc, S->ifftFlagR, S->bitReverseFlagR);

     /*  Real FFT core process */
     mips_split_rfft_q15 (pSrc, L2, S->pTwiddleAReal, S->pTwiddleBReal, pDst, S->twidCoefRModifier);
  }

}

/**
  @} end of RealFFT group
 */

/**
  @brief         Core Real FFT process
  @param[in]     pSrc      points to input buffer
  @param[in]     fftLen    length of FFT
  @param[in]     pATable   points to twiddle Coef A buffer
  @param[in]     pBTable   points to twiddle Coef B buffer
  @param[out]    pDst      points to output buffer
  @param[in]     modifier  twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table
  @return        none

  @par
                   The function implements a Real FFT
 */


void mips_split_rfft_q15(
        q15 * pSrc,
        uint32_t fftLen,
  const q15 * pATable,
  const q15 * pBTable,
        q15 * pDst,
        uint32_t modifier)
{       
        uint32_t i;                                    /* Loop Counter */
        q31 outR, outI;                              /* Temporary variables for output */
  const q15 *pCoefA, *pCoefB;                        /* Temporary pointers for twiddle factors */
        q15 *pSrc1, *pSrc2;
#if defined (MIPS_MATH_DSP)
        q15 *pD1, *pD2;
#endif

  /* Init coefficient pointers */
  pCoefA = &pATable[modifier * 2];
  pCoefB = &pBTable[modifier * 2];

  pSrc1 = &pSrc[2];
  pSrc2 = &pSrc[(2U * fftLen) - 2U];

#if defined (MIPS_MATH_DSP)

    i = 1U;
    pD1 = pDst + 2;
    pD2 = pDst + (4U * fftLen) - 2;

    for (i = fftLen - 1; i > 0; i--)
    {
        /*
          outR = (  pSrc[2 * i]             * pATable[2 * i]
                  - pSrc[2 * i + 1]         * pATable[2 * i + 1]
                  + pSrc[2 * n - 2 * i]     * pBTable[2 * i]
                  + pSrc[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);

          outI = (  pIn[2 * i + 1]         * pATable[2 * i]
                  + pIn[2 * i]             * pATable[2 * i + 1]
                  + pIn[2 * n - 2 * i]     * pBTable[2 * i + 1]
                  - pIn[2 * n - 2 * i + 1] * pBTable[2 * i])
         */


#ifndef MIPS_MATH_BIG_ENDIAN
        /* pSrc[2 * i] * pATable[2 * i] - pSrc[2 * i + 1] * pATable[2 * i + 1] */
        outR = __SMUSD(read_q15x2 (pSrc1), read_q15x2((q15 *) pCoefA));
#else
        /* -(pSrc[2 * i + 1] * pATable[2 * i + 1] - pSrc[2 * i] * pATable[2 * i]) */
        outR = -(__SMUSD(read_q15x2 (pSrc1), read_q15x2((q15 *) pCoefA)));
#endif /* #ifndef MIPS_MATH_BIG_ENDIAN */

        /* pSrc[2 * n - 2 * i] * pBTable[2 * i] + pSrc[2 * n - 2 * i + 1] * pBTable[2 * i + 1]) */
        outR = __SMLAD(read_q15x2 (pSrc2), read_q15x2((q15 *) pCoefB), outR) >> 16U;

        /* pIn[2 * n - 2 * i] * pBTable[2 * i + 1] - pIn[2 * n - 2 * i + 1] * pBTable[2 * i] */
#ifndef MIPS_MATH_BIG_ENDIAN
        outI = __SMUSDX(read_q15x2_da (&pSrc2), read_q15x2((q15 *) pCoefB));
#else
        outI = __SMUSDX(read_q15x2 ((q15 *) pCoefB), read_q15x2_da (&pSrc2));
#endif /* #ifndef MIPS_MATH_BIG_ENDIAN */

        /* (pIn[2 * i + 1] * pATable[2 * i] + pIn[2 * i] * pATable[2 * i + 1] */
        outI = __SMLADX(read_q15x2_ia (&pSrc1), read_q15x2 ((q15 *) pCoefA), outI);

        /* write output */
        *pD1++ = (q15) outR;
        *pD1++ = outI >> 16U;

        /* write complex conjugate output */
        pD2[0] = (q15) outR;
        pD2[1] = -(outI >> 16U);
        pD2 -= 2;

        /* update coefficient pointer */
        pCoefB = pCoefB + (2U * modifier);
        pCoefA = pCoefA + (2U * modifier);
    }

    pDst[2U * fftLen]      = (pSrc[0] - pSrc[1]) >> 1U;
    pDst[2U * fftLen + 1U] = 0;

    pDst[0] = (pSrc[0] + pSrc[1]) >> 1U;
    pDst[1] = 0;

#else

    i = 1U;

    while (i < fftLen)
    {
        /*
          outR = (  pSrc[2 * i]             * pATable[2 * i]
                  - pSrc[2 * i + 1]         * pATable[2 * i + 1]
                  + pSrc[2 * n - 2 * i]     * pBTable[2 * i]
                  + pSrc[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);
        */

        outR = *pSrc1 * *pCoefA;
        outR = outR - (*(pSrc1 + 1) * *(pCoefA + 1));
        outR = outR + (*pSrc2 * *pCoefB);
        outR = (outR + (*(pSrc2 + 1) * *(pCoefB + 1))) >> 16;

        /*
          outI = (  pIn[2 * i + 1]         * pATable[2 * i]
                  + pIn[2 * i]             * pATable[2 * i + 1]
                  + pIn[2 * n - 2 * i]     * pBTable[2 * i + 1]
                  - pIn[2 * n - 2 * i + 1] * pBTable[2 * i]);
        */

        outI = *pSrc2 * *(pCoefB + 1);
        outI = outI - (*(pSrc2 + 1) * *pCoefB);
        outI = outI + (*(pSrc1 + 1) * *pCoefA);
        outI = outI + (*pSrc1 * *(pCoefA + 1));

        /* update input pointers */
        pSrc1 += 2U;
        pSrc2 -= 2U;

        /* write output */
        pDst[2U * i] = (q15) outR;
        pDst[2U * i + 1U] = outI >> 16U;

        /* write complex conjugate output */
        pDst[(4U * fftLen) - (2U * i)] = (q15) outR;
        pDst[((4U * fftLen) - (2U * i)) + 1U] = -(outI >> 16U);

        /* update coefficient pointer */
        pCoefB = pCoefB + (2U * modifier);
        pCoefA = pCoefA + (2U * modifier);

        i++;
    }

    pDst[2U * fftLen] = (pSrc[0] - pSrc[1]) >> 1;
    pDst[2U * fftLen + 1U] = 0;

    pDst[0] = (pSrc[0] + pSrc[1]) >> 1;
    pDst[1] = 0;

#endif /* #if defined (MIPS_MATH_DSP) */
}


/**
  @brief         Core Real IFFT process
  @param[in]     pSrc      points to input buffer
  @param[in]     fftLen    length of FFT
  @param[in]     pATable   points to twiddle Coef A buffer
  @param[in]     pBTable   points to twiddle Coef B buffer
  @param[out]    pDst      points to output buffer
  @param[in]     modifier  twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table
  @return        none

  @par
                   The function implements a Real IFFT
 */


void mips_split_rifft_q15(
        q15 * pSrc,
        uint32_t fftLen,
  const q15 * pATable,
  const q15 * pBTable,
        q15 * pDst,
        uint32_t modifier)
{
        uint32_t i;                                    /* Loop Counter */
        q31 outR, outI;                              /* Temporary variables for output */
  const q15 *pCoefA, *pCoefB;                        /* Temporary pointers for twiddle factors */
        q15 *pSrc1, *pSrc2;
        q15 *pDst1 = &pDst[0];

  pCoefA = &pATable[0];
  pCoefB = &pBTable[0];

  pSrc1 = &pSrc[0];
  pSrc2 = &pSrc[2 * fftLen];

  i = fftLen;
  while (i > 0U)
  {
      /*
        outR = (  pIn[2 * i]             * pATable[2 * i]
                + pIn[2 * i + 1]         * pATable[2 * i + 1]
                + pIn[2 * n - 2 * i]     * pBTable[2 * i]
                - pIn[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);

        outI = (  pIn[2 * i + 1]         * pATable[2 * i]
                - pIn[2 * i]             * pATable[2 * i + 1]
                - pIn[2 * n - 2 * i]     * pBTable[2 * i + 1]
                - pIn[2 * n - 2 * i + 1] * pBTable[2 * i]);
       */

#if defined (MIPS_MATH_DSP)

#ifndef MIPS_MATH_BIG_ENDIAN
      /* pIn[2 * n - 2 * i] * pBTable[2 * i] - pIn[2 * n - 2 * i + 1] * pBTable[2 * i + 1]) */
      outR = __SMUSD(read_q15x2(pSrc2), read_q15x2((q15 *) pCoefB));
#else
      /* -(-pIn[2 * n - 2 * i] * pBTable[2 * i] + pIn[2 * n - 2 * i + 1] * pBTable[2 * i + 1])) */
      outR = -(__SMUSD(read_q15x2(pSrc2), read_q15x2((q15 *) pCoefB)));
#endif /* #ifndef MIPS_MATH_BIG_ENDIAN */

      /* pIn[2 * i] * pATable[2 * i] + pIn[2 * i + 1] * pATable[2 * i + 1] + pIn[2 * n - 2 * i] * pBTable[2 * i] */
      outR = __SMLAD(read_q15x2(pSrc1), read_q15x2 ((q15 *) pCoefA), outR) >> 16U;

      /* -pIn[2 * n - 2 * i] * pBTable[2 * i + 1] + pIn[2 * n - 2 * i + 1] * pBTable[2 * i] */
      outI = __SMUADX(read_q15x2_da (&pSrc2), read_q15x2((q15 *) pCoefB));

      /* pIn[2 * i + 1] * pATable[2 * i] - pIn[2 * i] * pATable[2 * i + 1] */
#ifndef MIPS_MATH_BIG_ENDIAN
      outI = __SMLSDX(read_q15x2 ((q15 *) pCoefA), read_q15x2_ia (&pSrc1), -outI);
#else
      outI = __SMLSDX(read_q15x2_ia (&pSrc1), read_q15x2 ((q15 *) pCoefA), -outI);
#endif /* #ifndef MIPS_MATH_BIG_ENDIAN */

      /* write output */
#ifndef MIPS_MATH_BIG_ENDIAN
      write_q15x2_ia (&pDst1, __PKHBT(outR, (outI >> 16U), 16));
#else
      write_q15x2_ia (&pDst1, __PKHBT((outI >> 16U), outR, 16));
#endif /* #ifndef MIPS_MATH_BIG_ENDIAN */


#else  /* #if defined (MIPS_MATH_DSP) */

      outR = *pSrc2 * *pCoefB;
      outR = outR - (*(pSrc2 + 1) * *(pCoefB + 1));
      outR = outR + (*pSrc1 * *pCoefA);
      outR = (outR + (*(pSrc1 + 1) * *(pCoefA + 1))) >> 16;

      outI = *(pSrc1 + 1) * *pCoefA;
      outI = outI - (*pSrc1 * *(pCoefA + 1));
      outI = outI - (*pSrc2 * *(pCoefB + 1));
      outI = outI - (*(pSrc2 + 1) * *(pCoefB));

      /* update input pointers */
      pSrc1 += 2U;
      pSrc2 -= 2U;

      /* write output */
      *pDst1++ = (q15) outR;
      *pDst1++ = (q15) (outI >> 16);

#endif /* #if defined (MIPS_MATH_DSP) */

      /* update coefficient pointer */
      pCoefB = pCoefB + (2 * modifier);
      pCoefA = pCoefA + (2 * modifier);

      i--;
  }

}

