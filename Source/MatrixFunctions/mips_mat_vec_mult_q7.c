/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mat_vec_mult_q7.c
 * Description:  Q7 matrix and vector multiplication
 *
 * $Date:        31 Augest 2023
 *
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
 * @ingroup groupMatrix
 */



/**
 * @addtogroup MatrixVectMult
 * @{
 */

/**
 * @brief Q7 matrix and vector multiplication.
 * @param[in]       *pSrcMat points to the input matrix structure
 * @param[in]       *pVec points to the input vector
 * @param[out]      *pDst points to the output vector
 */
void mips_mat_vec_mult_q7(const mips_matrix_instance_q7 *pSrcMat, const q7 *pVec, q7 *pDst)
{
    uint32_t numRows = pSrcMat->numRows;
    uint32_t numCols = pSrcMat->numCols;
    const q7 *pSrcA = pSrcMat->pData;
    const q7 *pInA1;       /* input data matrix pointer of Q7 type */
    const q7 *pInA2;       /* input data matrix pointer of Q7 type */
    const q7 *pInA3;       /* input data matrix pointer of Q7 type */
    const q7 *pInA4;       /* input data matrix pointer of Q7 type */
    const q7 *pInVec;      /* input data vector pointer of Q7 type */
    q7 *px;                /* output data pointer */
    uint32_t i, row, colCnt; /* loop counters */

    q31 matData, matData2, vecData, vecData2;


    /* Process 4 rows at a time */
    row = numRows >> 2;
    i = 0u;
    px = pDst;



    /* The following loop performs the dot-product of each row in pSrcA with the vector */
    while (row > 0) {
        /* Initialize accumulators */
        q31 sum1 = 0;
        q31 sum2 = 0;
        q31 sum3 = 0;
        q31 sum4 = 0;

        /* For every row wise process, the pInVec pointer is set
         ** to the starting address of the vector */
        pInVec = pVec;

        /* Loop unrolling: process 4 columns per iteration */
        colCnt = numCols >> 2;

        /* Initialize row pointers so we can track 4 rows at once */
        pInA1 = pSrcA + i;
        pInA2 = pInA1 + numCols;
        pInA3 = pInA2 + numCols;
        pInA4 = pInA3 + numCols;


        // Inner loop: matrix-vector multiplication

        while (colCnt > 0u) {
            // Read 4 values from vector
            vecData = read_q7x4_ia (&pInVec);
            vecData2 = __SXTB16(__ROR(vecData, 8));
            vecData = __SXTB16(vecData);
            // Read 16 values from the matrix - 4 values from each of 4 rows, and do multiply accumulate
            matData = read_q7x4_ia (&pInA1);
            matData2 = __SXTB16(__ROR(matData, 8));
            matData = __SXTB16(matData);
            sum1 = __SMLAD(matData, vecData, sum1);
            sum1 = __SMLAD(matData2, vecData2, sum1);
            matData = read_q7x4_ia (&pInA2);
            matData2 = __SXTB16(__ROR(matData, 8));
            matData = __SXTB16(matData);
            sum2 = __SMLAD(matData, vecData, sum2);
            sum2 = __SMLAD(matData2, vecData2, sum2);
            matData = read_q7x4_ia (&pInA3);
            matData2 = __SXTB16(__ROR(matData, 8));
            matData = __SXTB16(matData);
            sum3 = __SMLAD(matData, vecData, sum3);
            sum3 = __SMLAD(matData2, vecData2, sum3);
            matData = read_q7x4_ia (&pInA4);
            matData2 = __SXTB16(__ROR(matData, 8));
            matData = __SXTB16(matData);
            sum4 = __SMLAD(matData, vecData, sum4);
            sum4 = __SMLAD(matData2, vecData2, sum4);

            // Decrement the loop counter
            colCnt--;
        }

        /* process any remaining columns */

        colCnt = numCols & 3u;

        while (colCnt > 0) {
            vecData = *pInVec++;
            sum1 += *pInA1++ * vecData;
            sum2 += *pInA2++ * vecData;
            sum3 += *pInA3++ * vecData;
            sum4 += *pInA4++ * vecData;
            colCnt--;
        }

        /* Saturate and store the result in the destination buffer */
        *px++ = (q7)(__SSAT((sum1 >> 7), 8));
        *px++ = (q7)(__SSAT((sum2 >> 7), 8));
        *px++ = (q7)(__SSAT((sum3 >> 7), 8));
        *px++ = (q7)(__SSAT((sum4 >> 7), 8));

        i = i + numCols * 4;

        /* Decrement the row loop counter */
        row--;
    }

    /* process any remaining rows */
    row = numRows & 3u;
    while (row > 0) {

        q31 sum = 0;
        pInVec = pVec;
        pInA1 = pSrcA + i;

        // loop unrolling - process 4 elements at a time
        colCnt = numCols >> 2;

        while (colCnt > 0) {
            vecData = read_q7x4_ia (&pInVec);
            vecData2 = __SXTB16(__ROR(vecData, 8));
            vecData = __SXTB16(vecData);
            matData = read_q7x4_ia (&pInA1);
            matData2 = __SXTB16(__ROR(matData, 8));
            matData = __SXTB16(matData);
            sum = __SMLAD(matData, vecData, sum);
            sum = __SMLAD(matData2, vecData2, sum);
            colCnt--;
        }

        // process remainder of row
        colCnt = numCols & 3u;
        while (colCnt > 0) {
            sum += *pInA1++ * *pInVec++;
            colCnt--;
        }
        *px++ = (q7)(__SSAT((sum >> 7), 8));
        i = i + numCols;
        row--;
    }
}

/**
 * @} end of MatrixMult group
 */
