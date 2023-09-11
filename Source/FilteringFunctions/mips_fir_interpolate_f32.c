/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_fir_interpolate_f32.c
 * Description:  Floating-point FIR interpolation sequences
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
  @defgroup FIR_Interpolate Finite Impulse Response (FIR) Interpolator

  These functions combine an upsampler (zero stuffer) and an FIR filter.
  They are used in multirate systems for increasing the sample rate of a signal without introducing high frequency images.
  Conceptually, the functions are equivalent to the block diagram below:
  \image html FIRInterpolator.gif "Components included in the FIR Interpolator functions"
  After upsampling by a factor of <code>L</code>, the signal should be filtered by a lowpass filter with a normalized
  cutoff frequency of <code>1/L</code> in order to eliminate high frequency copies of the spectrum.
  The user of the function is responsible for providing the filter coefficients.

  The FIR interpolator functions provided in the MIPS Embedded Compute Library combine the upsampler and FIR filter in an efficient manner.
  The upsampler inserts <code>L-1</code> zeros between each sample.
  Instead of multiplying by these zero values, the FIR filter is designed to skip them.
  This leads to an efficient implementation without any wasted effort.
  The functions operate on blocks of input and output data.
  <code>pSrc</code> points to an array of <code>blockSize</code> input values and
  <code>pDst</code> points to an array of <code>blockSize*L</code> output values.

  The library provides separate functions for Q15, Q31, and floating-point data types.

  @par           Algorithm
                   The functions use a polyphase filter structure:
  <pre>
      y[n] = b[0] * x[n] + b[L]   * x[n-1] + ... + b[L*(phaseLength-1)] * x[n-phaseLength+1]
      y[n+1] = b[1] * x[n] + b[L+1] * x[n-1] + ... + b[L*(phaseLength-1)+1] * x[n-phaseLength+1]
      ...
      y[n+(L-1)] = b[L-1] * x[n] + b[2*L-1] * x[n-1] + ....+ b[L*(phaseLength-1)+(L-1)] * x[n-phaseLength+1]
  </pre>
                   This approach is more efficient than straightforward upsample-then-filter algorithms.
                   With this method the computation is reduced by a factor of <code>1/L</code> when compared to using a standard FIR filter.
  @par
                   <code>pCoeffs</code> points to a coefficient array of size <code>numTaps</code>.
                   <code>numTaps</code> must be a multiple of the interpolation factor <code>L</code> and this is checked by the
                   initialization functions.
                   Internally, the function divides the FIR filter's impulse response into shorter filters of length
                   <code>phaseLength=numTaps/L</code>.
                   Coefficients are stored in time reversed order.
  <pre>
      {b[numTaps-1], b[numTaps-2], b[N-2], ..., b[1], b[0]}
  </pre>
  @par
                   <code>pState</code> points to a state array of size <code>blockSize + phaseLength - 1</code>.
                   Samples in the state buffer are stored in the order:
  <pre>
     {x[n-phaseLength+1], x[n-phaseLength], x[n-phaseLength-1], x[n-phaseLength-2]....x[0], x[1], ..., x[blockSize-1]}
  </pre>
  @par
                   The state variables are updated after each block of data is processed, the coefficients are untouched.

  @par           Instance Structure
                   The coefficients and state variables for a filter are stored together in an instance data structure.
                   A separate instance structure must be defined for each filter.
                   Coefficient arrays may be shared among several instances while state variable array should be allocated separately.
                   There are separate instance structure declarations for each of the 3 supported data types.

  @par           Initialization Functions
                   There is also an associated initialization function for each data type.
                   The initialization function performs the following operations:
                   - Sets the values of the internal structure fields.
                   - Zeros out the values in the state buffer.
                   - Checks to make sure that the length of the filter is a multiple of the interpolation factor.
                   To do this manually without calling the init function, assign the follow subfields of the instance structure:
                   L (interpolation factor), pCoeffs, phaseLength (numTaps / L), pState. Also set all of the values in pState to zero.
  @par
                   Use of the initialization function is optional.
                   However, if the initialization function is used, then the instance structure cannot be placed into a const data section.
                   To place an instance structure into a const data section, the instance structure must be manually initialized.
                   The code below statically initializes each of the 3 different data type filter instance structures
  <pre>
      mips_fir_interpolate_instance_f32 S = {L, phaseLength, pCoeffs, pState};
      mips_fir_interpolate_instance_q31 S = {L, phaseLength, pCoeffs, pState};
      mips_fir_interpolate_instance_q15 S = {L, phaseLength, pCoeffs, pState};
  </pre>
  @par
                   where <code>L</code> is the interpolation factor; <code>phaseLength=numTaps/L</code> is the
                   length of each of the shorter FIR filters used internally,
                   <code>pCoeffs</code> is the address of the coefficient buffer;
                   <code>pState</code> is the address of the state buffer.
                   Be sure to set the values in the state buffer to zeros when doing static initialization.

  @par           Fixed-Point Behavior
                   Care must be taken when using the fixed-point versions of the FIR interpolate filter functions.
                   In particular, the overflow and saturation behavior of the accumulator used in each function must be considered.
                   Refer to the function specific documentation below for usage guidelines.
 */

/**
  @addtogroup FIR_Interpolate
  @{
 */

/**
  @brief         Processing function for floating-point FIR interpolator.
  @param[in]     S          points to an instance of the floating-point FIR interpolator structure
  @param[in]     pSrc       points to the block of input data
  @param[out]    pDst       points to the block of output data
  @param[in]     blockSize  number of input samples to process
  @return        none
 */

void mips_fir_interpolate_f32(
  const mips_fir_interpolate_instance_f32 * S,
  const f32 * pSrc,
        f32 * pDst,
        uint32_t blockSize)
{
#if (1)
//#if !defined(MIPS_MATH_CM0_FAMILY)

        f32 *pState = S->pState;                 /* State pointer */
  const f32 *pCoeffs = S->pCoeffs;               /* Coefficient pointer */
        f32 *pStateCur;                          /* Points to the current sample of the state */
        f32 *ptr1;                               /* Temporary pointer for state buffer */
  const f32 *ptr2;                               /* Temporary pointer for coefficient buffer */
        f32 sum0;                                /* Accumulators */
        uint32_t i, blkCnt, tapCnt;                    /* Loop counters */
        uint32_t phaseLen = S->phaseLength;            /* Length of each polyphase filter component */
        uint32_t j;

#if defined (MIPS_MATH_LOOPUNROLL)
        f32 acc0, acc1, acc2, acc3;
        f32 x0, x1, x2, x3;
        f32 c0, c1, c2, c3;
#endif

  /* S->pState buffer contains previous frame (phaseLen - 1) samples */
  /* pStateCur points to the location where the new input data should be written */
  pStateCur = S->pState + (phaseLen - 1U);

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* Copy new input sample into the state buffer */
    *pStateCur++ = *pSrc++;
    *pStateCur++ = *pSrc++;
    *pStateCur++ = *pSrc++;
    *pStateCur++ = *pSrc++;

    /* Address modifier index of coefficient buffer */
    j = 1U;

    /* Loop over the Interpolation factor. */
    i = (S->L);

    while (i > 0U)
    {
      /* Set accumulator to zero */
      acc0 = 0.0f;
      acc1 = 0.0f;
      acc2 = 0.0f;
      acc3 = 0.0f;

      /* Initialize state pointer */
      ptr1 = pState;

      /* Initialize coefficient pointer */
      ptr2 = pCoeffs + (S->L - j);

      /* Loop over the polyPhase length. Unroll by a factor of 4.
         Repeat until we've computed numTaps-(4*S->L) coefficients. */
      tapCnt = phaseLen >> 2U;

      x0 = *(ptr1++);
      x1 = *(ptr1++);
      x2 = *(ptr1++);

      while (tapCnt > 0U)
      {
        /* Read the input sample */
        x3 = *(ptr1++);

        /* Read the coefficient */
        c0 = *(ptr2);

        /* Perform the multiply-accumulate */
        acc0 += x0 * c0;
        acc1 += x1 * c0;
        acc2 += x2 * c0;
        acc3 += x3 * c0;

        /* Read the coefficient */
        c1 = *(ptr2 + S->L);

        /* Read the input sample */
        x0 = *(ptr1++);

        /* Perform the multiply-accumulate */
        acc0 += x1 * c1;
        acc1 += x2 * c1;
        acc2 += x3 * c1;
        acc3 += x0 * c1;

        /* Read the coefficient */
        c2 = *(ptr2 + S->L * 2);

        /* Read the input sample */
        x1 = *(ptr1++);

        /* Perform the multiply-accumulate */
        acc0 += x2 * c2;
        acc1 += x3 * c2;
        acc2 += x0 * c2;
        acc3 += x1 * c2;

        /* Read the coefficient */
        c3 = *(ptr2 + S->L * 3);

        /* Read the input sample */
        x2 = *(ptr1++);

        /* Perform the multiply-accumulate */
        acc0 += x3 * c3;
        acc1 += x0 * c3;
        acc2 += x1 * c3;
        acc3 += x2 * c3;


        /* Upsampling is done by stuffing L-1 zeros between each sample.
         * So instead of multiplying zeros with coefficients,
         * Increment the coefficient pointer by interpolation factor times. */
        ptr2 += 4 * S->L;

        /* Decrement loop counter */
        tapCnt--;
      }

      /* If the polyPhase length is not a multiple of 4, compute the remaining filter taps */
      tapCnt = phaseLen % 0x4U;

      while (tapCnt > 0U)
      {
        /* Read the input sample */
        x3 = *(ptr1++);

        /* Read the coefficient */
        c0 = *(ptr2);

        /* Perform the multiply-accumulate */
        acc0 += x0 * c0;
        acc1 += x1 * c0;
        acc2 += x2 * c0;
        acc3 += x3 * c0;

        /* Increment the coefficient pointer by interpolation factor times. */
        ptr2 += S->L;

        /* update states for next sample processing */
        x0 = x1;
        x1 = x2;
        x2 = x3;

        /* Decrement loop counter */
        tapCnt--;
      }

      /* The result is in the accumulator, store in the destination buffer. */
      *(pDst           ) = acc0;
      *(pDst +     S->L) = acc1;
      *(pDst + 2 * S->L) = acc2;
      *(pDst + 3 * S->L) = acc3;

      pDst++;

      /* Increment the address modifier index of coefficient buffer */
      j++;

      /* Decrement loop counter */
      i--;
    }

    /* Advance the state pointer by 1
     * to process the next group of interpolation factor number samples */
    pState = pState + 4;

    pDst += S->L * 3;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = blockSize % 0x4U;

#else

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

  while (blkCnt > 0U)
  {
    /* Copy new input sample into the state buffer */
    *pStateCur++ = *pSrc++;

    /* Address modifier index of coefficient buffer */
    j = 1U;

    /* Loop over the Interpolation factor. */
    i = S->L;

    while (i > 0U)
    {
      /* Set accumulator to zero */
      sum0 = 0.0f;

      /* Initialize state pointer */
      ptr1 = pState;

      /* Initialize coefficient pointer */
      ptr2 = pCoeffs + (S->L - j);

      /* Loop over the polyPhase length.
         Repeat until we've computed numTaps-(4*S->L) coefficients. */

#if defined (MIPS_MATH_LOOPUNROLL)

     /* Loop unrolling: Compute 4 outputs at a time */
      tapCnt = phaseLen >> 2U;

      while (tapCnt > 0U)
      {
        /* Perform the multiply-accumulate */
        sum0 += *ptr1++ * *ptr2;

        /* Upsampling is done by stuffing L-1 zeros between each sample.
         * So instead of multiplying zeros with coefficients,
         * Increment the coefficient pointer by interpolation factor times. */
        ptr2 += S->L;

        sum0 += *ptr1++ * *ptr2;
        ptr2 += S->L;

        sum0 += *ptr1++ * *ptr2;
        ptr2 += S->L;

        sum0 += *ptr1++ * *ptr2;
        ptr2 += S->L;

        /* Decrement loop counter */
        tapCnt--;
      }

      /* Loop unrolling: Compute remaining outputs */
      tapCnt = phaseLen % 0x4U;

#else

      /* Initialize tapCnt with number of samples */
      tapCnt = phaseLen;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

      while (tapCnt > 0U)
      {
        /* Perform the multiply-accumulate */
        sum0 += *ptr1++ * *ptr2;

        /* Upsampling is done by stuffing L-1 zeros between each sample.
         * So instead of multiplying zeros with coefficients,
         * Increment the coefficient pointer by interpolation factor times. */
        ptr2 += S->L;

        /* Decrement loop counter */
        tapCnt--;
      }

      /* The result is in the accumulator, store in the destination buffer. */
      *pDst++ = sum0;

      /* Increment the address modifier index of coefficient buffer */
      j++;

      /* Decrement the loop counter */
      i--;
    }

    /* Advance the state pointer by 1
     * to process the next group of interpolation factor number samples */
    pState = pState + 1;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* Processing is complete.
     Now copy the last phaseLen - 1 samples to the satrt of the state buffer.
     This prepares the state buffer for the next function call. */

  /* Points to the start of the state buffer */
  pStateCur = S->pState;

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  tapCnt = (phaseLen - 1U) >> 2U;

  /* copy data */
  while (tapCnt > 0U)
  {
    *pStateCur++ = *pState++;
    *pStateCur++ = *pState++;
    *pStateCur++ = *pState++;
    *pStateCur++ = *pState++;

    /* Decrement loop counter */
    tapCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  tapCnt = (phaseLen - 1U) % 0x04U;

#else

    /* Initialize tapCnt with number of samples */
    tapCnt = (phaseLen - 1U);

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

  /* Copy data */
  while (tapCnt > 0U)
  {
    *pStateCur++ = *pState++;

    /* Decrement loop counter */
    tapCnt--;
  }

#else
/* alternate version for CM0_FAMILY */

        f32 *pState = S->pState;                 /* State pointer */
  const f32 *pCoeffs = S->pCoeffs;               /* Coefficient pointer */
        f32 *pStateCur;                        /* Points to the current sample of the state */
        f32 *ptr1;                               /* Temporary pointer for state buffer */
  const f32 *ptr2;                               /* Temporary pointer for coefficient buffer */
        f32 sum0;                                /* Accumulators */
        uint32_t i, blkCnt, tapCnt;                    /* Loop counters */
        uint32_t phaseLen = S->phaseLength;            /* Length of each polyphase filter component */

  /* S->pState buffer contains previous frame (phaseLen - 1) samples */
  /* pStateCur points to the location where the new input data should be written */
  pStateCur = S->pState + (phaseLen - 1U);

  /* Total number of intput samples */
  blkCnt = blockSize;

  /* Loop over the blockSize. */
  while (blkCnt > 0U)
  {
    /* Copy new input sample into the state buffer */
    *pStateCur++ = *pSrc++;

    /* Loop over the Interpolation factor. */
    i = S->L;

    while (i > 0U)
    {
      /* Set accumulator to zero */
      sum0 = 0.0f;

      /* Initialize state pointer */
      ptr1 = pState;

      /* Initialize coefficient pointer */
      ptr2 = pCoeffs + (i - 1U);

      /* Loop over the polyPhase length */
      tapCnt = phaseLen;

      while (tapCnt > 0U)
      {
        /* Perform the multiply-accumulate */
        sum0 += *ptr1++ * *ptr2;

        /* Increment the coefficient pointer by interpolation factor times. */
        ptr2 += S->L;

        /* Decrement the loop counter */
        tapCnt--;
      }

      /* The result is in the accumulator, store in the destination buffer. */
      *pDst++ = sum0;

      /* Decrement loop counter */
      i--;
    }

    /* Advance the state pointer by 1
     * to process the next group of interpolation factor number samples */
    pState = pState + 1;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Processing is complete.
   ** Now copy the last phaseLen - 1 samples to the start of the state buffer.
   ** This prepares the state buffer for the next function call. */

  /* Points to the start of the state buffer */
  pStateCur = S->pState;

  tapCnt = phaseLen - 1U;

  /* Copy data */
  while (tapCnt > 0U)
  {
    *pStateCur++ = *pState++;

    /* Decrement loop counter */
    tapCnt--;
  }

#endif /* #if !defined(MIPS_MATH_CM0_FAMILY) */

}

/**
  @} end of FIR_Interpolate group
 */