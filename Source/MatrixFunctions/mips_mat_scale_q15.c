/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mat_scale_q15.c
 * Description:  Multiplies a Q15 matrix by a scalar
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

#include "dsp/matrix_functions.h"

/**
  @ingroup groupMatrix
 */

/**
  @addtogroup MatrixScale
  @{
 */

/**
  @brief         Q15 matrix scaling.
  @param[in]     pSrc        points to input matrix
  @param[in]     scaleFract  fractional portion of the scale factor
  @param[in]     shift       number of bits to shift the result by
  @param[out]    pDst        points to output matrix structure
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS       : Operation successful
                   - \ref MIPS_MATH_SIZE_MISMATCH : Matrix size check failed

  @par           Scaling and Overflow Behavior
                   The input data <code>*pSrc</code> and <code>scaleFract</code> are in 1.15 format.
                   These are multiplied to yield a 2.30 intermediate result and this is shifted with saturation to 1.15 format.
 */
#if defined(MIPS_MATH_DSP)
mips_status mips_mat_scale_q15(
  const mips_matrix_instance_q15 * pSrc,
        q15                     scaleFract,
        int32_t                   shift,
        mips_matrix_instance_q15 * pDst)
{
  mips_status status;                             /* Status of matrix scaling */
  q15 *pIn = pSrc->pData;       /* input data matrix pointer */
  q15 *pOut = pDst->pData;      /* output data matrix pointer */
  uint32_t  numSamples;           /* total number of elements in the matrix */
  uint32_t  blkCnt;               /* loop counters */
  v2q15 vecIn, vecOut;
  q15 const *pInVec;
  int32_t kShift = 15 - shift;                   /* Total shift to apply after scaling */

  pInVec = (q15 const *) pIn;

  #ifdef MIPS_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pDst->numRows) ||
      (pSrc->numCols != pDst->numCols)   )
  {
    /* Set status as MIPS_MATH_SIZE_MISMATCH */
    status = MIPS_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef MIPS_MATH_MATRIX_CHECK */

  {
    /*
     * Total number of samples in the input matrix
     */
    numSamples = (uint32_t) pSrc->numRows * pSrc->numCols;
    blkCnt = numSamples >> 1;
    while (blkCnt > 0U)
    {
        /*
         * C(m,n) = A(m,n) * scale
         * Scaling and results are stored in the destination buffer.
         */
        vecIn = mips_dsp_load_v2q15(pInVec); pInVec += 2;

        /* multiply input with scaler value */
        vecOut = __builtin_mips_mulq_s_ph(vecIn, _mips_replv_ph(scaleFract));
         /* apply shifting */
        vecOut = _mips_shll_s_ph(vecOut, shift);

        mips_dsp_store_v2q15(pOut, vecOut); pOut += 2;

        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
    }
    /*
     * tail
     * (will be merged thru tail predication)
     */
    blkCnt = numSamples & 1;
    while (blkCnt > 0U)
    {
      /* C(m,n) = A(m,n) * k */

      /* Scale, saturate and store result in destination buffer. */
      *pOut++ = (q15) (__SSAT(((q31) (*pInVec++) * scaleFract) >> kShift, 16));

      /* Decrement loop counter */
      blkCnt--;
    }
     /* Set status as MIPS_MATH_SUCCESS */
    status = MIPS_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}

#else
mips_status mips_mat_scale_q15(
  const mips_matrix_instance_q15 * pSrc,
        q15                     scaleFract,
        int32_t                   shift,
        mips_matrix_instance_q15 * pDst)
{
        q15 *pIn = pSrc->pData;                      /* Input data matrix pointer */
        q15 *pOut = pDst->pData;                     /* Output data matrix pointer */
        uint32_t numSamples;                           /* Total number of elements in the matrix */
        uint32_t blkCnt;                               /* Loop counter */
        mips_status status;                             /* Status of matrix scaling */
        int32_t kShift = 15 - shift;                   /* Total shift to apply after scaling */

#if defined (MIPS_MATH_LOOPUNROLL) && defined (MIPS_MATH_DSP)
        q31 inA1, inA2;
        q31 out1, out2, out3, out4;                  /* Temporary output variables */
        q15 in1, in2, in3, in4;                      /* Temporary input variables */
#endif

#ifdef MIPS_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pDst->numRows) ||
      (pSrc->numCols != pDst->numCols)   )
  {
    /* Set status as MIPS_MATH_SIZE_MISMATCH */
    status = MIPS_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef MIPS_MATH_MATRIX_CHECK */

  {
    /* Total number of samples in input matrix */
    numSamples = (uint32_t) pSrc->numRows * pSrc->numCols;

#if defined (MIPS_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 outputs at a time */
    blkCnt = numSamples >> 2U;

    while (blkCnt > 0U)
    {
      /* C(m,n) = A(m,n) * k */

#if defined (MIPS_MATH_DSP)
      /* read 2 times 2 samples at a time from source */
      inA1 = read_q15x2_ia (&pIn);
      inA2 = read_q15x2_ia (&pIn);

      /* Scale inputs and store result in temporary variables
       * in single cycle by packing the outputs */
      out1 = (q31) ((q15) (inA1 >> 16) * scaleFract);
      out2 = (q31) ((q15) (inA1      ) * scaleFract);
      out3 = (q31) ((q15) (inA2 >> 16) * scaleFract);
      out4 = (q31) ((q15) (inA2      ) * scaleFract);

      /* apply shifting */
      out1 = out1 >> kShift;
      out2 = out2 >> kShift;
      out3 = out3 >> kShift;
      out4 = out4 >> kShift;

      /* saturate the output */
      in1 = (q15) (__SSAT(out1, 16));
      in2 = (q15) (__SSAT(out2, 16));
      in3 = (q15) (__SSAT(out3, 16));
      in4 = (q15) (__SSAT(out4, 16));

      /* store result to destination */
      write_q15x2_ia (&pOut, __PKHBT(in2, in1, 16));
      write_q15x2_ia (&pOut, __PKHBT(in4, in3, 16));

#else
      *pOut++ = (q15) (__SSAT(((q31) (*pIn++) * scaleFract) >> kShift, 16));
      *pOut++ = (q15) (__SSAT(((q31) (*pIn++) * scaleFract) >> kShift, 16));
      *pOut++ = (q15) (__SSAT(((q31) (*pIn++) * scaleFract) >> kShift, 16));
      *pOut++ = (q15) (__SSAT(((q31) (*pIn++) * scaleFract) >> kShift, 16));
#endif

      /* Decrement loop counter */
      blkCnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    blkCnt = numSamples % 0x4U;

#else

    /* Initialize blkCnt with number of samples */
    blkCnt = numSamples;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

    while (blkCnt > 0U)
    {
      /* C(m,n) = A(m,n) * k */

      /* Scale, saturate and store result in destination buffer. */
      *pOut++ = (q15) (__SSAT(((q31) (*pIn++) * scaleFract) >> kShift, 16));

      /* Decrement loop counter */
      blkCnt--;
    }

    /* Set status as MIPS_MATH_SUCCESS */
    status = MIPS_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of MatrixScale group
 */
