/******************************************************************************
 * @file     mips_math_memory.h
 * @brief    Public header file for MIPS Embedded Compute Library
 * @version  V1.0.0
 * @date     31 Augest 2023
 ******************************************************************************/
/*
 * Copyright (c) 2010-2021 Arm Limited or its affiliates. All rights reserved.
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

#ifndef _MIPS_MATH_MEMORY_H_

#define _MIPS_MATH_MEMORY_H_

#include "mips_math_types.h"


#ifdef   __cplusplus
extern "C"
{
#endif

/**
  @brief definition to read/write two 16 bit values.
  @deprecated
 */
#if defined ( __GNUC__ )
  #define __SIMD32_TYPE int32_t
#else
  #error Unknown compiler
#endif

#define __SIMD32(addr)        (*(__SIMD32_TYPE **) & (addr))
#define __SIMD32_CONST(addr)  ( (__SIMD32_TYPE * )   (addr))
#define _SIMD32_OFFSET(addr)  (*(__SIMD32_TYPE * )   (addr))
#define __SIMD64(addr)        (*(      int64_t **) & (addr))


/* SIMD replacement */


/**
  @brief         Read 2 Q15 from Q15 pointer.
  @param[in]     pQ15      points to input value
  @return        Q31 value
 */
__STATIC_FORCEINLINE q31 read_q15x2 (
  q15 const * pQ15)
{
  q31 val;

  val = (pQ15[1] << 16) | (pQ15[0] & 0x0FFFF) ;

  return (val);
}

/**
  @brief         Read 2 Q15 from Q15 pointer and increment pointer afterwards.
  @param[in]     pQ15      points to input value
  @return        Q31 value
 */
#define read_q15x2_ia(pQ15) read_q15x2((*(pQ15) += 2) - 2)

/**
  @brief         Read 2 Q15 from Q15 pointer and decrement pointer afterwards.
  @param[in]     pQ15      points to input value
  @return        Q31 value
 */
#define read_q15x2_da(pQ15) read_q15x2((*(pQ15) -= 2) + 2)

/**
  @brief         Write 2 Q15 to Q15 pointer and increment pointer afterwards.
  @param[in]     pQ15      points to input value
  @param[in]     value     Q31 value
  @return        none
 */
__STATIC_FORCEINLINE void write_q15x2_ia (
  q15 ** pQ15,
  q31    value)
{
  q31 val = value;

  (*pQ15)[0] = (q15)(val & 0x0FFFF);
  (*pQ15)[1] = (q15)((val >> 16) & 0x0FFFF);

 *pQ15 += 2;
}

/**
  @brief         Write 2 Q15 to Q15 pointer.
  @param[in]     pQ15      points to input value
  @param[in]     value     Q31 value
  @return        none
 */
__STATIC_FORCEINLINE void write_q15x2 (
  q15 * pQ15,
  q31   value)
{
  q31 val = value;

  pQ15[0] = (q15)(val & 0x0FFFF);
  pQ15[1] = (q15)(val >> 16);

}


/**
  @brief         Read 4 Q7 from Q7 pointer
  @param[in]     pQ7       points to input value
  @return        Q31 value
 */
__STATIC_FORCEINLINE q31 read_q7x4 (
  q7 const * pQ7)
{
  q31 val;

  val =((pQ7[3] & 0x0FF) << 24)  | ((pQ7[2] & 0x0FF) << 16)  | ((pQ7[1] & 0x0FF) << 8)  | (pQ7[0] & 0x0FF);

  return (val);
}

/**
  @brief         Read 4 Q7 from Q7 pointer and increment pointer afterwards.
  @param[in]     pQ7       points to input value
  @return        Q31 value
 */
#define read_q7x4_ia(pQ7) read_q7x4((*(pQ7) += 4) - 4)

/**
  @brief         Read 4 Q7 from Q7 pointer and decrement pointer afterwards.
  @param[in]     pQ7       points to input value
  @return        Q31 value
 */
#define read_q7x4_da(pQ7) read_q7x4((*(pQ7) -= 4) + 4)

/**
  @brief         Write 4 Q7 to Q7 pointer and increment pointer afterwards.
  @param[in]     pQ7       points to input value
  @param[in]     value     Q31 value
  @return        none
 */
__STATIC_FORCEINLINE void write_q7x4_ia (
  q7 ** pQ7,
  q31   value)
{
  q31 val = value;

  (*pQ7)[0] = (q7)(val & 0x0FF);
  (*pQ7)[1] = (q7)((val >> 8) & 0x0FF);
  (*pQ7)[2] = (q7)((val >> 16) & 0x0FF);
  (*pQ7)[3] = (q7)((val >> 24) & 0x0FF);

  *pQ7 += 4;
}


#ifdef   __cplusplus
}
#endif

#endif /*ifndef _MIPS_MATH_MEMORY_H_ */
