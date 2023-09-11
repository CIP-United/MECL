/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_atan2_q15.c
 * Description:  float32 Arc tangent of y/x
 *
 * $Date:        31 Augest 2023
 * $Revision:    V1.0.0
 *
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2022 ARM Limited or its affiliates. All rights reserved.
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

#include "dsp/fast_math_functions.h"        
#include "dsp/utils.h"        

/*

atan for argument between in [0, 1.0]

*/


/* Q2.13 */
#define ATANHALFQ13 0xed6
#define PIHALFQ13 0x3244
#define PIQ13 0x6488

#define ATAN2_NB_COEFS_Q15 10

static const q15 atan2_coefs_q15[ATAN2_NB_COEFS_Q15]={
     0, // 0x0000
 32767, // 0x7fff
    -1, // 0xffff
-10905, // 0xd567
  -144, // 0xff70
  7085, // 0x1bad
  -680, // 0xfd58
 -5719, // 0xe9a9
  4393, // 0x1129
 -1061  // 0xfbdb
};

__STATIC_FORCEINLINE q15 mips_atan_limited_q15(q15 x)
{
    q31 res=(q31)atan2_coefs_q15[ATAN2_NB_COEFS_Q15-1];
    int i=1;
    for(i=1;i<ATAN2_NB_COEFS_Q15;i++)
    {
        res = ((q31) x * res) >> 15U;
        res = res + ((q31) atan2_coefs_q15[ATAN2_NB_COEFS_Q15-1-i]) ;
    }

    res = __SSAT(res>>2,16);

    
    return(res);
}


__STATIC_FORCEINLINE q15 mips_atan_q15(q15 y,q15 x)
{
   int sign=0;
   q15 res=0;

   if (y<0)
   {
     /* Negate y */
     y = (y == (q15) 0x8000) ? (q15) 0x7fff : -y;

     sign=1-sign;
   }

   if (x < 0)
   {
      sign=1 - sign;
     
      /* Negate x */
     x = (x == (q15) 0x8000) ? (q15) 0x7fff : -x;
   }

   if (y > x)
   {
    q15 ratio;
    int16_t shift;

    mips_divide_q15(x,y,&ratio,&shift);

    /* Shift ratio by shift */
    if (shift >=0)
    {
       ratio = __SSAT(((q31) ratio << shift), 16);
    }
    else
    {
       ratio = (ratio >> -shift);
    }
   
    res = PIHALFQ13 - mips_atan_limited_q15(ratio);
      
   }
   else
   {
    q15 ratio;
    int16_t shift;

    mips_divide_q15(y,x,&ratio,&shift);

    /* Shift ratio by shift */
    if (shift >=0)
    {
       ratio = __SSAT(((q31) ratio << shift), 16);
    }
    else
    {
       ratio = (ratio >> -shift);
    }
   

    res = mips_atan_limited_q15(ratio);

   }


   if (sign)
   {
     /* Negate res */
     res = (res == (q15) 0x8000) ? (q15) 0x7fff : -res;
   }

   return(res);
}


/**
  @ingroup groupFastMath
 */


/**
  @addtogroup atan2
  @{
 */

/**
  @brief       Arc Tangent of y/x using sign of y and x to get right quadrant
  @param[in]   y  y coordinate
  @param[in]   x  x coordinate
  @param[out]  result  Result in Q2.13
  @return  error status.
 
  @par         Compute the Arc tangent of y/x:
                   The sign of y and x are used to determine the right quadrant
                   and compute the right angle.
*/


mips_status mips_atan2_q15(q15 y,q15 x,q15 *result)
{
    if (x > 0)
    {
        *result=mips_atan_q15(y,x);
        return(MIPS_MATH_SUCCESS);
    }
    if (x < 0)
    {
        if (y > 0)
        {
           *result=mips_atan_q15(y,x) + PIQ13;
        }
        else if (y < 0)
        {
           *result=mips_atan_q15(y,x) - PIQ13;
        }
        else
        {
            if (y<0)
            {
               *result= -PIQ13;
            }
            else
            {
               *result= PIQ13;
            }
        }
        return(MIPS_MATH_SUCCESS);
    }
    if (x == 0)
    {
        if (y > 0)
        {
            *result=PIHALFQ13;
            return(MIPS_MATH_SUCCESS);
        }
        if (y < 0)
        {
            *result=-PIHALFQ13;
            return(MIPS_MATH_SUCCESS);
        }
    }
    

    return(MIPS_MATH_NANINF);

}

/**
  @} end of atan2 group
 */
