/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_iir_lattice_q31.c
 * Description:  Q31 IIR Lattice filter processing function
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
  @addtogroup IIR_Lattice
  @{
 */

/**
  @brief         Processing function for the Q31 IIR lattice filter.
  @param[in]     S          points to an instance of the Q31 IIR lattice structure
  @param[in]     pSrc       points to the block of input data
  @param[out]    pDst       points to the block of output data
  @param[in]     blockSize  number of samples to process
  @return        none

  @par           Scaling and Overflow Behavior
                   The function is implemented using an internal 64-bit accumulator.
                   The accumulator has a 2.62 format and maintains full precision of the intermediate multiplication results but provides only a single guard bit.
                   Thus, if the accumulator result overflows it wraps around rather than clip.
                   In order to avoid overflows completely the input signal must be scaled down by 2*log2(numStages) bits.
                   After all multiply-accumulates are performed, the 2.62 accumulator is saturated to 1.32 format and then truncated to 1.31 format.
 */

void mips_iir_lattice_q31(
  const mips_iir_lattice_instance_q31 * S,
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize)
{       
        q31 *pState = S->pState;                       /* State pointer */
        q31 *pStateCur;                                /* State current pointer */
        q31 fcurr, fnext = 0, gcurr = 0, gnext;        /* Temporary variables for lattice stages */
        q63 acc;                                       /* Accumlator */
        q31 *px1, *px2, *pk, *pv;                      /* Temporary pointers for state and coef */
        uint32_t numStages = S->numStages;               /* Number of stages */
        uint32_t blkCnt, tapCnt;                         /* Temporary variables for counts */


  /* initialise loop count */
  blkCnt = blockSize;

#if defined (MIPS_MATH_DSP)

  /* Sample processing */
  while (blkCnt > 0U)
  {
    /* Read Sample from input buffer */
    /* fN(n) = x(n) */
    fcurr = *pSrc++;

    /* Initialize Ladder coeff pointer */
    pv = &S->pvCoeffs[0];

    /* Initialize Reflection coeff pointer */
    pk = &S->pkCoeffs[0];

    /* Initialize state read pointer */
    px1 = pState;

    /* Initialize state write pointer */
    px2 = pState;

    /* Set accumulator to zero */
    acc = 0;

    /* Process sample for first tap */
    gcurr = *px1++;
    /* fN-1(n) = fN(n) - kN * gN-1(n-1) */
    fnext = __QSUB(fcurr, (q31) (((q63) gcurr * (*pk  )) >> 31));

    /* gN(n) = kN * fN-1(n) + gN-1(n-1) */
    gnext = __QADD(gcurr, (q31) (((q63) fnext * (*pk++)) >> 31));

    /* write gN-1(n-1) into state for next sample processing */
    *px2++ = gnext;

    /* y(n) += gN(n) * vN */
    acc += ((q63) gnext * *pv++);

    /* Update f values for next coefficient processing */
    fcurr = fnext;


#if defined (MIPS_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 taps at a time. */
    tapCnt = (numStages - 1U) >> 2U;

    while (tapCnt > 0U)
    {
      /* Process sample for 2nd, 6th ...taps */
      /* Read gN-2(n-1) from state buffer */
      gcurr = *px1++;
      /* fN-2(n) = fN-1(n) - kN-1 * gN-2(n-1) */
      fnext = __QSUB(fcurr, (q31) (((q63) gcurr * (*pk  )) >> 31));
      /* gN-1(n) = kN-1 * fN-2(n) + gN-2(n-1) */
      gnext = __QADD(gcurr, (q31) (((q63) fnext * (*pk++)) >> 31));
      /* y(n) += gN-1(n) * vN-1  */
      /* process for gN-5(n) * vN-5, gN-9(n) * vN-9 ... */
      acc += ((q63) gnext * *pv++);
      /* write gN-1(n) into state for next sample processing */
      *px2++ = gnext;

      /* Process sample for 3nd, 7th ...taps */
      /* Read gN-3(n-1) from state buffer */
      gcurr = *px1++;
      /* Process sample for 3rd, 7th .. taps */
      /* fN-3(n) = fN-2(n) - kN-2 * gN-3(n-1) */
      fcurr = __QSUB(fnext, (q31) (((q63) gcurr * (*pk  )) >> 31));
      /* gN-2(n) = kN-2 * fN-3(n) + gN-3(n-1) */
      gnext = __QADD(gcurr, (q31) (((q63) fcurr * (*pk++)) >> 31));
      /* y(n) += gN-2(n) * vN-2  */
      /* process for gN-6(n) * vN-6, gN-10(n) * vN-10 ... */
      acc += ((q63) gnext * *pv++);
      /* write gN-2(n) into state for next sample processing */
      *px2++ = gnext;

      /* Process sample for 4th, 8th ...taps */
      /* Read gN-4(n-1) from state buffer */
      gcurr = *px1++;
      /* Process sample for 4th, 8th .. taps */
      /* fN-4(n) = fN-3(n) - kN-3 * gN-4(n-1) */
      fnext = __QSUB(fcurr, (q31) (((q63) gcurr * (*pk  )) >> 31));
      /* gN-3(n) = kN-3 * fN-4(n) + gN-4(n-1) */
      gnext = __QADD(gcurr, (q31) (((q63) fnext * (*pk++)) >> 31));
      /* y(n) += gN-3(n) * vN-3  */
      /* process for gN-7(n) * vN-7, gN-11(n) * vN-11 ... */
      acc += ((q63) gnext * *pv++);
      /* write gN-3(n) into state for next sample processing */
      *px2++ = gnext;

      /* Process sample for 5th, 9th ...taps */
      /* Read gN-5(n-1) from state buffer */
      gcurr = *px1++;
      /* Process sample for 5th, 9th .. taps */
      /* fN-5(n) = fN-4(n) - kN-4 * gN-1(n-1) */
      fcurr = __QSUB(fnext, (q31) (((q63) gcurr * (*pk  )) >> 31));
      /* gN-4(n) = kN-4 * fN-5(n) + gN-5(n-1) */
      gnext = __QADD(gcurr, (q31) (((q63) fcurr * (*pk++)) >> 31));
      /* y(n) += gN-4(n) * vN-4  */
      /* process for gN-8(n) * vN-8, gN-12(n) * vN-12 ... */
      acc += ((q63) gnext * *pv++);

      /* write gN-4(n) into state for next sample processing */
      *px2++ = gnext;

      /* Decrement loop counter */
      tapCnt--;
    }

    fnext = fcurr;

    /* Loop unrolling: Compute remaining taps */
    tapCnt = (numStages - 1U) % 0x4U;

#else

    /* Initialize blkCnt with number of samples */
    tapCnt = (numStages - 1U);

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

    while (tapCnt > 0U)
    {
      gcurr = *px1++;
      /* Process sample for last taps */
      fnext = __QSUB(fcurr, (q31) (((q63) gcurr * (*pk  )) >> 31));
      gnext = __QADD(gcurr, (q31) (((q63) fnext * (*pk++)) >> 31));

      /* Output samples for last taps */
      acc += ((q63) gnext * *pv++);
      *px2++ = gnext;
      fcurr = fnext;

      /* Decrement loop counter */
      tapCnt--;
    }

    /* y(n) += g0(n) * v0 */
    acc += ((q63) fnext * *pv++);

    *px2++ = fnext;

    /* write out into pDst */
    *pDst++ = (q31) (acc >> 31U);

    /* Advance the state pointer by 4 to process the next group of 4 samples */
    pState = pState + 1U;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Processing is complete. Now copy last S->numStages samples to start of the buffer
     for the preperation of next frame process */

  /* Points to the start of the state buffer */
  pStateCur = &S->pState[0];
  pState = &S->pState[blockSize];

  /* Copy data */
#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 taps at a time. */
  tapCnt = numStages >> 2U;

  while (tapCnt > 0U)
  {
    *pStateCur++ = *pState++;
    *pStateCur++ = *pState++;
    *pStateCur++ = *pState++;
    *pStateCur++ = *pState++;

    /* Decrement loop counter */
    tapCnt--;
  }

  /* Loop unrolling: Compute remaining taps */
  tapCnt = numStages % 0x4U;

#else

  /* Initialize blkCnt with number of samples */
  tapCnt = (numStages - 1U);

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

  while (tapCnt > 0U)
  {
    *pStateCur++ = *pState++;

    /* Decrement loop counter */
    tapCnt--;
  }

#else /* #if defined (MIPS_MATH_DSP) */

  /* Sample processing */
  while (blkCnt > 0U)
  {
    /* Read Sample from input buffer */
    /* fN(n) = x(n) */
    fcurr = *pSrc++;

    /* Initialize Ladder coeff pointer */
    pv = &S->pvCoeffs[0];

    /* Initialize Reflection coeff pointer */
    pk = &S->pkCoeffs[0];

    /* Initialize state read pointer */
    px1 = pState;

    /* Initialize state write pointer */
    px2 = pState;

    /* Set accumulator to zero */
    acc = 0;

    tapCnt = numStages;

    while (tapCnt > 0U)
    {
      gcurr = *px1++;
      /* Process sample */
      /* fN-1(n) = fN(n) - kN * gN-1(n-1) */
      fnext = clip_q63_to_q31(((q63) fcurr - ((q31) (((q63) gcurr * (*pk  )) >> 31))));

      /* gN(n) = kN * fN-1(n) + gN-1(n-1) */
      gnext = clip_q63_to_q31(((q63) gcurr + ((q31) (((q63) fnext * (*pk++)) >> 31))));

      /* Output samples */
      /* y(n) += gN(n) * vN */
      acc += ((q63) gnext * *pv++);

      /* write gN-1(n-1) into state for next sample processing */
      *px2++ = gnext;

      /* Update f values for next coefficient processing */
      fcurr = fnext;

      tapCnt--;
    }

    /* y(n) += g0(n) * v0 */
    acc += ((q63) fnext * *pv++);

    *px2++ = fnext;

    /* write out into pDst */
    *pDst++ = (q31) (acc >> 31U);

    /* Advance the state pointer by 1 to process the next group of samples */
    pState = pState + 1U;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Processing is complete. Now copy last S->numStages samples to start of the buffer
     for the preperation of next frame process */

  /* Points to the start of the state buffer */
  pStateCur = &S->pState[0];
  pState = &S->pState[blockSize];

  tapCnt = numStages;

  /* Copy data */
  while (tapCnt > 0U)
  {
    *pStateCur++ = *pState++;

    /* Decrement loop counter */
    tapCnt--;
  }

#endif /* #if defined (MIPS_MATH_DSP) */

}

/**
  @} end of IIR_Lattice group
 */
