/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cfft_init_q31.c
 * Description:  Initialization function for cfft q31 instance
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

#define FFTINIT(EXT,SIZE)                                           \
  S->bitRevLength = mips_cfft_sR_##EXT##_len##SIZE.bitRevLength;        \
  S->pBitRevTable = mips_cfft_sR_##EXT##_len##SIZE.pBitRevTable;         \
  S->pTwiddle = mips_cfft_sR_##EXT##_len##SIZE.pTwiddle;

/**
  @addtogroup ComplexFFT
  @{
 */

/**
  @brief         Initialization function for the cfft q31 function
  @param[in,out] S              points to an instance of the floating-point CFFT structure
  @param[in]     fftLen         fft length (number of complex samples)
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS        : Operation successful
                   - \ref MIPS_MATH_ARGUMENT_ERROR : an error is detected

  @par          Use of this function is mandatory only for the DSP version of the FFT.
                Other versions can still initialize directly the data structure using 
                variables declared in mips_const_structs.h
 */

#include "dsp/transform_functions.h"
#include "mips_common_tables.h"
#include "mips_const_structs.h"


mips_status mips_cfft_init_q31(
  mips_cfft_instance_q31 * S,
  uint16_t fftLen)
{
        /*  Initialise the default mips status */
        mips_status status = MIPS_MATH_SUCCESS;

        /*  Initialise the FFT length */
        S->fftLen = fftLen;

        /*  Initialise the Twiddle coefficient pointer */
        S->pTwiddle = NULL;


        /*  Initializations of Instance structure depending on the FFT length */
        switch (S->fftLen) {
#if !defined(MIPS_DSP_CONFIG_TABLES) || defined(MIPS_ALL_FFT_TABLES) || (defined(MIPS_TABLE_TWIDDLECOEF_Q31_4096) && defined(MIPS_TABLE_BITREVIDX_FXT_4096))
            /*  Initializations of structure parameters for 4096 point FFT */
        case 4096U:
            /*  Initialise the bit reversal table modifier */
            FFTINIT(q31,4096);
            break;
#endif

#if !defined(MIPS_DSP_CONFIG_TABLES) || defined(MIPS_ALL_FFT_TABLES) || (defined(MIPS_TABLE_TWIDDLECOEF_Q31_2048) && defined(MIPS_TABLE_BITREVIDX_FXT_2048))
            /*  Initializations of structure parameters for 2048 point FFT */
        case 2048U:
            /*  Initialise the bit reversal table modifier */
            FFTINIT(q31,2048);

            break;
#endif

#if !defined(MIPS_DSP_CONFIG_TABLES) || defined(MIPS_ALL_FFT_TABLES) || (defined(MIPS_TABLE_TWIDDLECOEF_Q31_1024) && defined(MIPS_TABLE_BITREVIDX_FXT_1024))
            /*  Initializations of structure parameters for 1024 point FFT */
        case 1024U:
            /*  Initialise the bit reversal table modifier */
            FFTINIT(q31,1024);

            break;
#endif

#if !defined(MIPS_DSP_CONFIG_TABLES) || defined(MIPS_ALL_FFT_TABLES) || (defined(MIPS_TABLE_TWIDDLECOEF_Q31_512) && defined(MIPS_TABLE_BITREVIDX_FXT_512))
            /*  Initializations of structure parameters for 512 point FFT */
        case 512U:
            /*  Initialise the bit reversal table modifier */
            FFTINIT(q31,512);
            break;
#endif

#if !defined(MIPS_DSP_CONFIG_TABLES) || defined(MIPS_ALL_FFT_TABLES) || (defined(MIPS_TABLE_TWIDDLECOEF_Q31_256) && defined(MIPS_TABLE_BITREVIDX_FXT_256))
        case 256U:
            FFTINIT(q31,256);
            break;
#endif

#if !defined(MIPS_DSP_CONFIG_TABLES) || defined(MIPS_ALL_FFT_TABLES) || (defined(MIPS_TABLE_TWIDDLECOEF_Q31_128) && defined(MIPS_TABLE_BITREVIDX_FXT_128))
        case 128U:
            FFTINIT(q31,128);
            break;
#endif 

#if !defined(MIPS_DSP_CONFIG_TABLES) || defined(MIPS_ALL_FFT_TABLES) || (defined(MIPS_TABLE_TWIDDLECOEF_Q31_64) && defined(MIPS_TABLE_BITREVIDX_FXT_64))
        case 64U:
            FFTINIT(q31,64);
            break;
#endif 

#if !defined(MIPS_DSP_CONFIG_TABLES) || defined(MIPS_ALL_FFT_TABLES) || (defined(MIPS_TABLE_TWIDDLECOEF_Q31_32) && defined(MIPS_TABLE_BITREVIDX_FXT_32))
        case 32U:
            FFTINIT(q31,32);
            break;
#endif 

#if !defined(MIPS_DSP_CONFIG_TABLES) || defined(MIPS_ALL_FFT_TABLES) || (defined(MIPS_TABLE_TWIDDLECOEF_Q31_16) && defined(MIPS_TABLE_BITREVIDX_FXT_16))
        case 16U:
            /*  Initializations of structure parameters for 16 point FFT */
            FFTINIT(q31,16);
            break;
#endif

        default:
            /*  Reporting argument error if fftSize is not valid value */
            status = MIPS_MATH_ARGUMENT_ERROR;
            break;
        }


        return (status);
}


/**
  @} end of ComplexFFT group
 */
