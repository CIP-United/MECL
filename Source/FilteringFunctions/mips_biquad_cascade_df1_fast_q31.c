/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_biquad_cascade_df1_fast_q31.c
 * Description:  Processing function for the Q31 Fast Biquad cascade DirectFormI(DF1) filter
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
  @addtogroup BiquadCascadeDF1
  @{
 */

/**
  @brief         Processing function for the Q31 Biquad cascade filter (fast variant).
  @param[in]     S         points to an instance of the Q31 Biquad cascade structure
  @param[in]     pSrc      points to the block of input data
  @param[out]    pDst      points to the block of output data
  @param[in]     blockSize number of samples to process per call
  @return        none

  @par           Scaling and Overflow Behavior
                   This function is optimized for speed at the expense of fixed-point precision and overflow protection.
                   The result of each 1.31 x 1.31 multiplication is truncated to 2.30 format.
                   These intermediate results are added to a 2.30 accumulator.
                   Finally, the accumulator is saturated and converted to a 1.31 result.
                   The fast version has the same overflow behavior as the standard version and provides less precision since it discards the low 32 bits of each multiplication result.
                   In order to avoid overflows completely the input signal must be scaled down by two bits and lie in the range [-0.25 +0.25). Use the intialization function
                   mips_biquad_cascade_df1_init_q31() to initialize filter structure.
  @remark
                   Refer to \ref mips_biquad_cascade_df1_q31() for a slower implementation of this function
                   which uses 64-bit accumulation to provide higher precision. Both the slow and the fast versions use the same instance structure.
                   Use the function \ref mips_biquad_cascade_df1_init_q31() to initialize the filter structure.
 */

void mips_biquad_cascade_df1_fast_q31(
  const mips_biquad_casd_df1_inst_q31 * S,
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize)
{
  const q31 *pIn = pSrc;                             /* Source pointer */
        q31 *pOut = pDst;                            /* Destination pointer */
        q31 *pState = S->pState;                     /* pState pointer */
  const q31 *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */
        q31 acc = 0;                                 /* Accumulator */
        q31 b0, b1, b2, a1, a2;                      /* Filter coefficients */
        q31 Xn1, Xn2, Yn1, Yn2;                      /* Filter pState variables */
        q31 Xn;                                      /* Temporary input */
        int32_t shift = (int32_t) S->postShift + 1;    /* Shift to be applied to the output */
        uint32_t sample, stage = S->numStages;         /* Loop counters */

  do
  {
    /* Reading the coefficients */
    b0 = *pCoeffs++;
    b1 = *pCoeffs++;
    b2 = *pCoeffs++;
    a1 = *pCoeffs++;
    a2 = *pCoeffs++;

    /* Reading the pState values */
    Xn1 = pState[0];
    Xn2 = pState[1];
    Yn1 = pState[2];
    Yn2 = pState[3];

#if defined (MIPS_MATH_LOOPUNROLL)

    /* Apply loop unrolling and compute 4 output values simultaneously. */
    /* Variables acc ... acc3 hold output values that are being computed:
     *
     * acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2]
     */

    /* Loop unrolling: Compute 4 outputs at a time */
    sample = blockSize >> 2U;

    while (sample > 0U)
    {
      /* Read the input */
      Xn = *pIn;

      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */
      /* acc =  b0 * x[n] */
      /* acc = (q31) (((q63) b1 * Xn1) >> 32);*/
      mult_32x32_keep32_R(acc, b1, Xn1);
      /* acc +=  b1 * x[n-1] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) b0 * (Xn))) >> 32);*/
      multAcc_32x32_keep32_R(acc, b0, Xn);
      /* acc +=  b[2] * x[n-2] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) b2 * (Xn2))) >> 32);*/
      multAcc_32x32_keep32_R(acc, b2, Xn2);
      /* acc +=  a1 * y[n-1] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) a1 * (Yn1))) >> 32);*/
      multAcc_32x32_keep32_R(acc, a1, Yn1);
      /* acc +=  a2 * y[n-2] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) a2 * (Yn2))) >> 32);*/
      multAcc_32x32_keep32_R(acc, a2, Yn2);

      /* The result is converted to 1.31 , Yn2 variable is reused */
      Yn2 = acc << shift;

      /* Read the second input */
      Xn2 = *(pIn + 1U);

      /* Store the output in the destination buffer. */
      *pOut = Yn2;

      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */
      /* acc =  b0 * x[n] */
      /* acc = (q31) (((q63) b0 * (Xn2)) >> 32);*/
      mult_32x32_keep32_R(acc, b0, Xn2);
      /* acc +=  b1 * x[n-1] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) b1 * (Xn))) >> 32);*/
      multAcc_32x32_keep32_R(acc, b1, Xn);
      /* acc +=  b[2] * x[n-2] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) b2 * (Xn1))) >> 32);*/
      multAcc_32x32_keep32_R(acc, b2, Xn1);
      /* acc +=  a1 * y[n-1] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) a1 * (Yn2))) >> 32);*/
      multAcc_32x32_keep32_R(acc, a1, Yn2);
      /* acc +=  a2 * y[n-2] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) a2 * (Yn1))) >> 32);*/
      multAcc_32x32_keep32_R(acc, a2, Yn1);

      /* The result is converted to 1.31, Yn1 variable is reused  */
      Yn1 = acc << shift;

      /* Read the third input  */
      Xn1 = *(pIn + 2U);

      /* Store the output in the destination buffer. */
      *(pOut + 1U) = Yn1;

      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */
      /* acc =  b0 * x[n] */
      /* acc = (q31) (((q63) b0 * (Xn1)) >> 32);*/
      mult_32x32_keep32_R(acc, b0, Xn1);
      /* acc +=  b1 * x[n-1] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) b1 * (Xn2))) >> 32);*/
      multAcc_32x32_keep32_R(acc, b1, Xn2);
      /* acc +=  b[2] * x[n-2] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) b2 * (Xn))) >> 32);*/
      multAcc_32x32_keep32_R(acc, b2, Xn);
      /* acc +=  a1 * y[n-1] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) a1 * (Yn1))) >> 32);*/
      multAcc_32x32_keep32_R(acc, a1, Yn1);
      /* acc +=  a2 * y[n-2] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) a2 * (Yn2))) >> 32);*/
      multAcc_32x32_keep32_R(acc, a2, Yn2);

      /* The result is converted to 1.31, Yn2 variable is reused  */
      Yn2 = acc << shift;

      /* Read the forth input */
      Xn = *(pIn + 3U);

      /* Store the output in the destination buffer. */
      *(pOut + 2U) = Yn2;
      pIn += 4U;

      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */
      /* acc =  b0 * x[n] */
      /* acc = (q31) (((q63) b0 * (Xn)) >> 32);*/
      mult_32x32_keep32_R(acc, b0, Xn);
      /* acc +=  b1 * x[n-1] */
      /*acc = (q31) ((((q63) acc << 32) + ((q63) b1 * (Xn1))) >> 32);*/
      multAcc_32x32_keep32_R(acc, b1, Xn1);
      /* acc +=  b[2] * x[n-2] */
      /*acc = (q31) ((((q63) acc << 32) + ((q63) b2 * (Xn2))) >> 32);*/
      multAcc_32x32_keep32_R(acc, b2, Xn2);
      /* acc +=  a1 * y[n-1] */
      /*acc = (q31) ((((q63) acc << 32) + ((q63) a1 * (Yn2))) >> 32);*/
      multAcc_32x32_keep32_R(acc, a1, Yn2);
      /* acc +=  a2 * y[n-2] */
      /*acc = (q31) ((((q63) acc << 32) + ((q63) a2 * (Yn1))) >> 32);*/
      multAcc_32x32_keep32_R(acc, a2, Yn1);

      /* Every time after the output is computed state should be updated. */
      /* The states should be updated as:  */
      /* Xn2 = Xn1 */
      Xn2 = Xn1;

      /* The result is converted to 1.31, Yn1 variable is reused  */
      Yn1 = acc << shift;

      /* Xn1 = Xn */
      Xn1 = Xn;

      /* Store the output in the destination buffer. */
      *(pOut + 3U) = Yn1;
      pOut += 4U;

      /* decrement loop counter */
      sample--;
    }

    /* Loop unrolling: Compute remaining outputs */
    sample = (blockSize & 0x3U);

#else

    /* Initialize blkCnt with number of samples */
    sample = blockSize;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

    while (sample > 0U)
    {
      /* Read the input */
      Xn = *pIn++;

      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */
      /* acc =  b0 * x[n] */
      /* acc = (q31) (((q63) b0 * (Xn)) >> 32);*/
      mult_32x32_keep32_R(acc, b0, Xn);
      /* acc +=  b1 * x[n-1] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) b1 * (Xn1))) >> 32);*/
      multAcc_32x32_keep32_R(acc, b1, Xn1);
      /* acc +=  b[2] * x[n-2] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) b2 * (Xn2))) >> 32);*/
      multAcc_32x32_keep32_R(acc, b2, Xn2);
      /* acc +=  a1 * y[n-1] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) a1 * (Yn1))) >> 32);*/
      multAcc_32x32_keep32_R(acc, a1, Yn1);
      /* acc +=  a2 * y[n-2] */
      /* acc = (q31) ((((q63) acc << 32) + ((q63) a2 * (Yn2))) >> 32);*/
      multAcc_32x32_keep32_R(acc, a2, Yn2);

      /* The result is converted to 1.31  */
      acc = acc << shift;

      /* Every time after the output is computed state should be updated. */
      /* The states should be updated as:  */
      /* Xn2 = Xn1 */
      /* Xn1 = Xn  */
      /* Yn2 = Yn1 */
      /* Yn1 = acc */
      Xn2 = Xn1;
      Xn1 = Xn;
      Yn2 = Yn1;
      Yn1 = acc;

      /* Store the output in the destination buffer. */
      *pOut++ = acc;

      /* decrement loop counter */
      sample--;
    }

    /* The first stage goes from the input buffer to the output buffer. */
    /* Subsequent stages occur in-place in the output buffer */
    pIn = pDst;

    /* Reset to destination pointer */
    pOut = pDst;

    /* Store the updated state variables back into the pState array */
    *pState++ = Xn1;
    *pState++ = Xn2;
    *pState++ = Yn1;
    *pState++ = Yn2;

  } while (--stage);
}

/**
  @} end of BiquadCascadeDF1 group
 */
