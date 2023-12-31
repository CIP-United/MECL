/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_conv_partial_fast_opt_q15.c
 * Description:  Fast Q15 Partial convolution
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
  @addtogroup PartialConv
  @{
 */

/**
  @brief         Partial convolution of Q15 sequences (fast version).
  @param[in]     pSrcA      points to the first input sequence
  @param[in]     srcALen    length of the first input sequence
  @param[in]     pSrcB      points to the second input sequence
  @param[in]     srcBLen    length of the second input sequence
  @param[out]    pDst       points to the location where the output result is written
  @param[in]     firstIndex is the first output sample to start with
  @param[in]     numPoints  is the number of output points to be computed
  @param[in]     pScratch1  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2
  @param[in]     pScratch2  points to scratch buffer of size min(srcALen, srcBLen)
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS        : Operation successful
                   - \ref MIPS_MATH_ARGUMENT_ERROR : requested subset is not in the range [0 srcALen+srcBLen-2]

  @remark
                   Refer to \ref mips_conv_partial_q15() for a slower implementation of this function which uses a 64-bit accumulator to avoid wrap around distortion.
 */

mips_status mips_conv_partial_fast_opt_q15(
  const q15 * pSrcA,
        uint32_t srcALen,
  const q15 * pSrcB,
        uint32_t srcBLen,
        q15 * pDst,
        uint32_t firstIndex,
        uint32_t numPoints,
        q15 * pScratch1,
        q15 * pScratch2)
{
        q15 *pOut = pDst;                            /* Output pointer */
        q15 *pScr1 = pScratch1;                      /* Temporary pointer for scratch1 */
        q15 *pScr2 = pScratch2;                      /* Temporary pointer for scratch1 */
        q31 acc0;                                    /* Accumulator */
  const q15 *pIn1;                                   /* InputA pointer */
  const q15 *pIn2;                                   /* InputB pointer */
  const q15 *px;                                     /* Intermediate inputA pointer */
        q15 *py;                                     /* Intermediate inputB pointer */
        uint32_t j, k, blkCnt;                         /* Loop counter */
        uint32_t tapCnt;                               /* Loop count */
        mips_status status;                             /* Status variable */
        q31 x1;                                      /* Temporary variables to hold state and coefficient values */
        q31 y1;                                      /* State variables */

#if defined (MIPS_MATH_LOOPUNROLL)
        q31 acc1, acc2, acc3;                        /* Accumulator */
        q31 x2, x3;                                  /* Temporary variables to hold state and coefficient values */
        q31 y2;                                      /* State variables */
#endif

  /* Check for range of output samples to be calculated */
  if ((firstIndex + numPoints) > ((srcALen + (srcBLen - 1U))))
  {
    /* Set status as MIPS_MATH_ARGUMENT_ERROR */
    status = MIPS_MATH_ARGUMENT_ERROR;
  }
  else
  {
    /* The algorithm implementation is based on the lengths of the inputs. */
    /* srcB is always made to slide across srcA. */
    /* So srcBLen is always considered as shorter or equal to srcALen */
    if (srcALen >= srcBLen)
    {
      /* Initialization of inputA pointer */
      pIn1 = pSrcA;

      /* Initialization of inputB pointer */
      pIn2 = pSrcB;
    }
    else
    {
      /* Initialization of inputA pointer */
      pIn1 = pSrcB;

      /* Initialization of inputB pointer */
      pIn2 = pSrcA;

      /* srcBLen is always considered as shorter or equal to srcALen */
      j = srcBLen;
      srcBLen = srcALen;
      srcALen = j;
    }

    /* Temporary pointer for scratch2 */
    py = pScratch2;

    /* pointer to take end of scratch2 buffer */
    pScr2 = pScratch2 + srcBLen - 1;

    /* points to smaller length sequence */
    px = pIn2;

#if defined (MIPS_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 outputs at a time */
    k = srcBLen >> 2U;

    /* Copy smaller length input sequence in reverse order into second scratch buffer */
    while (k > 0U)
    {
      /* copy second buffer in reversal manner */
      *pScr2-- = *px++;
      *pScr2-- = *px++;
      *pScr2-- = *px++;
      *pScr2-- = *px++;

      /* Decrement loop counter */
      k--;
    }

    /* Loop unrolling: Compute remaining outputs */
    k = srcBLen % 0x4U;

#else

    /* Initialize k with number of samples */
    k = srcBLen;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

    while (k > 0U)
    {
      /* copy second buffer in reversal manner for remaining samples */
      *pScr2-- = *px++;

      /* Decrement loop counter */
      k--;
    }

    /* Initialze temporary scratch pointer */
    pScr1 = pScratch1;

    /* Assuming scratch1 buffer is aligned by 32-bit */
    /* Fill (srcBLen - 1U) zeros in scratch buffer */
    mips_fill_q15(0, pScr1, (srcBLen - 1U));

    /* Update temporary scratch pointer */
    pScr1 += (srcBLen - 1U);

    /* Copy bigger length sequence(srcALen) samples in scratch1 buffer */

    /* Copy (srcALen) samples in scratch buffer */
    mips_copy_q15(pIn1, pScr1, srcALen);

    /* Update pointers */
    pScr1 += srcALen;

    /* Fill (srcBLen - 1U) zeros at end of scratch buffer */
    mips_fill_q15(0, pScr1, (srcBLen - 1U));

    /* Update pointer */
    pScr1 += (srcBLen - 1U);

    /* Initialization of pIn2 pointer */
    pIn2 = py;

    pScratch1 += firstIndex;

    pOut = pDst + firstIndex;

    /* Actual convolution process starts here */

#if defined (MIPS_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 outputs at a time */
    blkCnt = (numPoints) >> 2;

    while (blkCnt > 0)
    {
      /* Initialze temporary scratch pointer as scratch1 */
      pScr1 = pScratch1;

      /* Clear Accumlators */
      acc0 = 0;
      acc1 = 0;
      acc2 = 0;
      acc3 = 0;

      /* Read two samples from scratch1 buffer */
      x1 = read_q15x2_ia (&pScr1);

      /* Read next two samples from scratch1 buffer */
      x2 = read_q15x2_ia (&pScr1);

      tapCnt = (srcBLen) >> 2U;

      while (tapCnt > 0U)
      {

        /* Read four samples from smaller buffer */
        y1 = read_q15x2_ia ((q15 **) &pIn2);
        y2 = read_q15x2_ia ((q15 **) &pIn2);

        /* multiply and accumulate */
        acc0 = __SMLAD(x1, y1, acc0);
        acc2 = __SMLAD(x2, y1, acc2);

        /* pack input data */
#ifndef MIPS_MATH_BIG_ENDIAN
        x3 = __PKHBT(x2, x1, 0);
#else
        x3 = __PKHBT(x1, x2, 0);
#endif

        /* multiply and accumulate */
        acc1 = __SMLADX(x3, y1, acc1);

        /* Read next two samples from scratch1 buffer */
        x1 = read_q15x2_ia (&pScr1);

        /* multiply and accumulate */
        acc0 = __SMLAD(x2, y2, acc0);
        acc2 = __SMLAD(x1, y2, acc2);

        /* pack input data */
#ifndef MIPS_MATH_BIG_ENDIAN
        x3 = __PKHBT(x1, x2, 0);
#else
        x3 = __PKHBT(x2, x1, 0);
#endif

        acc3 = __SMLADX(x3, y1, acc3);
        acc1 = __SMLADX(x3, y2, acc1);

        x2 = read_q15x2_ia (&pScr1);

#ifndef MIPS_MATH_BIG_ENDIAN
        x3 = __PKHBT(x2, x1, 0);
#else
        x3 = __PKHBT(x1, x2, 0);
#endif

        /* multiply and accumulate */
        acc3 = __SMLADX(x3, y2, acc3);

        /* Decrement loop counter */
        tapCnt--;
      }

      /* Update scratch pointer for remaining samples of smaller length sequence */
      pScr1 -= 4U;

      /* apply same above for remaining samples of smaller length sequence */
      tapCnt = (srcBLen) & 3U;

      while (tapCnt > 0U)
      {
        /* accumulate the results */
        acc0 += (*pScr1++ * *pIn2);
        acc1 += (*pScr1++ * *pIn2);
        acc2 += (*pScr1++ * *pIn2);
        acc3 += (*pScr1++ * *pIn2++);

        pScr1 -= 3U;

        /* Decrement loop counter */
        tapCnt--;
      }

      blkCnt--;

      /* Store the results in the accumulators in the destination buffer. */
#ifndef  MIPS_MATH_BIG_ENDIAN
      write_q15x2_ia (&pOut, __PKHBT(__SSAT((acc0 >> 15), 16), __SSAT((acc1 >> 15), 16), 16));
      write_q15x2_ia (&pOut, __PKHBT(__SSAT((acc2 >> 15), 16), __SSAT((acc3 >> 15), 16), 16));
#else
      write_q15x2_ia (&pOut, __PKHBT(__SSAT((acc1 >> 15), 16), __SSAT((acc0 >> 15), 16), 16));
      write_q15x2_ia (&pOut, __PKHBT(__SSAT((acc3 >> 15), 16), __SSAT((acc2 >> 15), 16), 16));
#endif /* #ifndef  MIPS_MATH_BIG_ENDIAN */

      /* Initialization of inputB pointer */
      pIn2 = py;

      pScratch1 += 4U;
    }

    /* Loop unrolling: Compute remaining outputs */
    blkCnt = numPoints & 0x3;

#else

    /* Initialize blkCnt with number of samples */
    blkCnt = numPoints;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

    /* Calculate convolution for remaining samples of Bigger length sequence */
    while (blkCnt > 0)
    {
      /* Initialze temporary scratch pointer as scratch1 */
      pScr1 = pScratch1;

      /* Clear Accumlators */
      acc0 = 0;

      tapCnt = (srcBLen) >> 1U;

      while (tapCnt > 0U)
      {
        /* Read next two samples from scratch1 buffer */
        x1 = read_q15x2_ia (&pScr1);

        /* Read two samples from smaller buffer */
        y1 = read_q15x2_ia ((q15 **) &pIn2);

        /* multiply and accumulate */
        acc0 = __SMLAD(x1, y1, acc0);

        /* Decrement loop counter */
        tapCnt--;
      }

      tapCnt = (srcBLen) & 1U;

      /* apply same above for remaining samples of smaller length sequence */
      while (tapCnt > 0U)
      {
        /* accumulate the results */
        acc0 += (*pScr1++ * *pIn2++);

        /* Decrement loop counter */
        tapCnt--;
      }

      blkCnt--;

      /* The result is in 2.30 format.  Convert to 1.15 with saturation.
       ** Then store the output in the destination buffer. */
      *pOut++ = (q15) (__SSAT((acc0 >> 15), 16));

      /* Initialization of inputB pointer */
      pIn2 = py;

      pScratch1 += 1U;

    }

    /* Set status as MIPS_MATH_SUCCESS */
    status = MIPS_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}

/**
  @} end of PartialConv group
 */
