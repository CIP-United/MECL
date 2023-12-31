/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_linear_interp_q31.c
 * Description:  Q31 linear interpolation
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

#include "dsp/interpolation_functions.h"

/**
  @ingroup groupInterpolation
 */


/**
   * @addtogroup LinearInterpolate
   * @{
   */

  /**
   *
   * @brief  Process function for the Q31 Linear Interpolation Function.
   * @param[in] pYData   pointer to Q31 Linear Interpolation table
   * @param[in] x        input sample to process
   * @param[in] nValues  number of table values
   * @return y processed output sample.
   *
   * \par
   * Input sample <code>x</code> is in 12.20 format which contains 12 bits for table index and 20 bits for fractional part.
   * This function can support maximum of table size 2^12.
   *
   */
  q31 mips_linear_interp_q31(
  const q31 * pYData,
  q31 x,
  uint32_t nValues)
  {
    q31 y;                                     /* output */
    q31 y0, y1;                                /* Nearest output values */
    q31 fract;                                 /* fractional part */
    int32_t index;                               /* Index to read nearest output values */

    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    index = ((x & (q31)0xFFF00000) >> 20);

    if (index >= (int32_t)(nValues - 1))
    {
      return (pYData[nValues - 1]);
    }
    else if (index < 0)
    {
      return (pYData[0]);
    }
    else
    {
      /* 20 bits for the fractional part */
      /* shift left by 11 to keep fract in 1.31 format */
      fract = (x & 0x000FFFFF) << 11;

      /* Read two nearest output values from the index in 1.31(q31) format */
      y0 = pYData[index];
      y1 = pYData[index + 1];

      /* Calculation of y0 * (1-fract) and y is in 2.30 format */
      y = ((q31) ((q63) y0 * (0x7FFFFFFF - fract) >> 32));

      /* Calculation of y0 * (1-fract) + y1 *fract and y is in 2.30 format */
      y += ((q31) (((q63) y1 * fract) >> 32));

      /* Convert y to 1.31 format */
      return (y << 1U);
    }
  }



  /**
   * @} end of LinearInterpolate group
   */

