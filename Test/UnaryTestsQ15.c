#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/matrix_functions.h"

#define SNR_THRESHOLD 70

#define ABS_ERROR_Q15 ((q15)4)
#define ABS_ERROR_Q63 ((q63)(1<<16))

#define ONEHALF 0x4000

/* Upper bound of maximum matrix dimension used by Python */
#define MAXMATRIXDIM 40


static void refInnerTail(q15 *b)
{
    b[0] = 1;
    b[1] = -1;
    b[2] = 2;
    b[3] = -2;
    b[4] = 3;
    b[5] = -3;
    b[6] = 4;
    b[7] = -4;
}


static void checkInnerTail(q15 *b)
{
    ASSERT_TRUE(b[0] == 1);
    ASSERT_TRUE(b[1] == -1);
    ASSERT_TRUE(b[2] == 2);
    ASSERT_TRUE(b[3] == -2);
    ASSERT_TRUE(b[4] == 3);
    ASSERT_TRUE(b[5] == -3);
    ASSERT_TRUE(b[6] == 4);
    ASSERT_TRUE(b[7] == -4);
}



#define PREPAREDATA2()                                                   \
      mips_matrix_instance_q15 in1;\
      mips_matrix_instance_q15 in2;\
      mips_matrix_instance_q15 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=columns;                                               \
      memcpy((void*)ap,(const void*)inp1,sizeof(q15)*rows*columns);\
      in1.pData = ap;                                                    \
                                                                         \
      in2.numRows=rows;                                                  \
      in2.numCols=columns;                                               \
      memcpy((void*)bp,(const void*)inp2,sizeof(q15)*rows*columns);\
      in2.pData = bp;                                                    \
                                                                         \
      out.numRows=rows;                                                  \
      out.numCols=columns;                                               \
      out.pData = outp;


#define PREPAREDATA1(TRANSPOSED)                                         \
      mips_matrix_instance_q15 in1;\
      mips_matrix_instance_q15 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=columns;                                               \
      memcpy((void*)ap,(const void*)inp1,sizeof(q15)*rows*columns);\
      in1.pData = ap;                                                    \
                                                                         \
      if (TRANSPOSED)                                                    \
      {                                                                  \
         out.numRows=columns;                                            \
         out.numCols=rows;                                               \
      }                                                                  \
      else                                                               \
      {                                                                  \
      out.numRows=rows;                                                  \
      out.numCols=columns;                                               \
      }                                                                  \
      out.pData = outp;


#define PREPAREDATA1C(TRANSPOSED)                                         \
      mips_matrix_instance_q15 in1;\
      mips_matrix_instance_q15 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=columns;                                               \
      memcpy((void*)ap,(const void*)inp1,2*sizeof(q15)*rows*columns);\
      in1.pData = ap;                                                    \
                                                                         \
      if (TRANSPOSED)                                                    \
      {                                                                  \
         out.numRows=columns;                                            \
         out.numCols=rows;                                               \
      }                                                                  \
      else                                                               \
      {                                                                  \
      out.numRows=rows;                                                  \
      out.numCols=columns;                                               \
      }                                                                  \
      out.pData = outp;


#define PREPAREVECDATA2()                                             \
      mips_matrix_instance_q15 in1;\
      in1.numRows=rows;                                               \
      in1.numCols=internal;                                           \
      memcpy((void*)ap,(const void*)inp1,sizeof(q15)*rows*internal);\
      in1.pData = ap;                                                 \
                                                                      \
      memcpy((void*)bp,(const void*)inp2,sizeof(q15)*internal);


int main()
{

#if !defined(NOT_EMBEDDED)
	uint8_t referenceData_u8[MAX_SIZE] = {0};
	uint16_t referenceData_u16[MAX_SIZE] = {0};
	uint32_t referenceData_u32[MAX_SIZE] = {0};
	uint64_t referenceData_u64[MAX_SIZE] = {0};
	q7 referenceData_q7[MAX_SIZE] = {0};
	q15 referenceData_q15[MAX_SIZE] = {0};
	q31 referenceData_q31[MAX_SIZE] = {0};
	q63 referenceData_q63[MAX_SIZE] = {0};
	f32 referenceData_f32[MAX_SIZE] = {0};
	f64 referenceData_f64[MAX_SIZE] = {0};
#endif

    // declare input value
	int paramCountInput1 = 0;
    int paramCountInput2 = 0;
    int paramCountInput3 = 0;
    int paramCountInput4 = 0;
  
    int paramCountdims1 = 0;
    int paramCountdims2 = 0;


	q15 q15input1[MAX_SIZE] = {0};
    q15 q15input2[MAX_SIZE] = {0};
    q15 q15input3[MAX_SIZE] = {0};
    q15 q15input4[MAX_SIZE] = {0};


    q15 q15dims1[MAX_SIZE] = {0};
    q15 q15dims2[MAX_SIZE] = {0};


	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFile1[255] = {0};
#else
	void *inputFile1;
	int inputFile1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile2[255] = {0};
#else
	void *inputFile2;
	int inputFile2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile3[255] = {0};
#else
	void *inputFile3;
	int inputFile3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile4[255] = {0};
#else
	void *inputFile4;
	int inputFile4Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile5[255] = {0};
#else
	void *inputFile5;
	int inputFile5Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile6[255] = {0};
#else
	void *inputFile6;
	int inputFile6Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile7[255] = {0};
#else
	void *inputFile7;
	int inputFile7Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile8[255] = {0};
#else
	void *inputFile8;
	int inputFile8Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile9[255] = {0};
#else
	void *inputFile9;
	int inputFile9Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile10[255] = {0};
#else
	void *inputFile10;
	int inputFile10Len = 0;
#endif



#if defined(NOT_EMBEDDED)
	char dimsFile1[255] = {0};
#else
	void *dimsFile1;
	int dimsFile1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char dimsFile2[255] = {0};
#else
	void *dimsFile2;
	int dimsFile2Len = 0;
#endif



#if defined(NOT_EMBEDDED)
	char referenceFile[255] = {0};
#else
	void *referenceFile;
	int referenceFileLen = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename

    //input
#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, UnaryQ15, "InputA1_q15.txt");
#else
	inputFile1 = UnaryQ15_InputA1_q15;
	inputFile1Len = sizeof(UnaryQ15_InputA1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, UnaryQ15, "InputB1_q15.txt");
#else
	inputFile2 = UnaryQ15_InputB1_q15;
	inputFile2Len = sizeof(UnaryQ15_InputB1_q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, UnaryQ15, "InputAC1_q15.txt");
#else
	inputFile3 = UnaryQ15_InputAC1_q15;
	inputFile3Len = sizeof(UnaryQ15_InputAC1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile4, sizeof(inputFile4), "%s%s%s", Patterns_PATH, UnaryQ15, "InputVec1_q15.txt");
#else
	inputFile4 = UnaryQ15_InputVec1_q15;
	inputFile4Len = sizeof(UnaryQ15_InputVec1_q15);
#endif


    
	//dim
#if defined(NOT_EMBEDDED)
	snprintf(dimsFile1, sizeof(dimsFile1), "%s%s%s", Patterns_PATH, UnaryQ15, "DimsUnary1_s16.txt");
#else
	dimsFile1 = UnaryQ15_DimsUnary1_s16;
	dimsFile1Len = sizeof(UnaryQ15_DimsUnary1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile2, sizeof(dimsFile2), "%s%s%s", Patterns_PATH, UnaryQ15, "DimsInvert1_s16.txt");
#else
	dimsFile2 = UnaryQ15_DimsInvert1_s16;
	dimsFile2Len = sizeof(UnaryQ15_DimsInvert1_s16);
#endif

    

	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile1, &paramCountInput1, q15input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q15(inputFile1, paramCountInput1, q15input1);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile2, &paramCountInput2, q15input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q15(inputFile2, paramCountInput2, q15input2);
	paramCountInput2 = paramCountInput2/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile3, &paramCountInput3, q15input3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_q15(inputFile3, paramCountInput3, q15input3);
	paramCountInput3 = paramCountInput3/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile4, &paramCountInput4, q15input4);
#else
	paramCountInput4 = inputFile4Len;
	load_data_q15(inputFile4, paramCountInput4, q15input4);
	paramCountInput4 = paramCountInput4/sizeof(q15);
#endif


    
#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile1, &paramCountdims1, q15dims1);
#else
	paramCountdims1 = dimsFile1Len;
	load_data_q15(dimsFile1, paramCountdims1, q15dims1);
	paramCountdims1 = paramCountdims1/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile2, &paramCountdims2, q15dims2);
#else
	paramCountdims2 = dimsFile2Len;
	load_data_q15(dimsFile2, paramCountdims2, q15dims2);
	paramCountdims2 = paramCountdims2/sizeof(q15);
#endif



	q15 q15output[MAX_SIZE] = {0};
    q15 q15a[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    q15 q15b[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    q15 q15b2[MAXMATRIXDIM] = {0};

    

    mips_status status;

    const q15 *inp1;
    const q15 *inp2 ;    
    q15  *outp;    
    q15  *ap;
    q15  *bp;
                                                           
    int16_t *dimsp;           
                
    int nbMatrixes;
    int rows,internal,columns;
    int i;
// =====================

	printf("== mips_mat_add_q15 test ==  \n"); 
    
    inp1 = q15input1;
    inp2 = q15input2;
    outp = q15output;
    dimsp = q15dims1;
    ap = q15a;
    bp = q15b;
    nbMatrixes = paramCountdims1 >> 1;


      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATA2();
          refInnerTail(outp + rows * columns);
          status=mips_mat_add_q15(&in1,&in2,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          checkInnerTail(outp);

      }


	printf("mips_mat_add_q15 finish \n");

	printf("mips_mat_add_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryQ15, "RefAdd1_q15.txt");
#else
	referenceFile = UnaryQ15_RefAdd1_q15;
	referenceFileLen = sizeof(UnaryQ15_RefAdd1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output, referenceFileLen, (q15)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output, referenceFileLen, ABS_ERROR_Q15);
#endif


    memset(q15output, 0, sizeof(q15)*MAX_SIZE);

	printf("\n== mips_mat_add_q15 check done  == \n\n");  

// =====================

	printf("== mips_mat_sub_q15 test ==  \n"); 
    
    inp1 = q15input1;
    inp2 = q15input2;
    outp = q15output;
    dimsp = q15dims1;
    ap = q15a;
    bp = q15b;
    nbMatrixes = paramCountdims1 >> 1;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATA2();
          refInnerTail(outp + rows * columns);
          status=mips_mat_sub_q15(&in1,&in2,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          checkInnerTail(outp);

      }


	printf("mips_mat_sub_q15 finish \n");

	printf("mips_mat_sub_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryQ15, "RefSub1_q15.txt");
#else
	referenceFile = UnaryQ15_RefSub1_q15;
	referenceFileLen = sizeof(UnaryQ15_RefSub1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output, referenceFileLen, (q15)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output, referenceFileLen, ABS_ERROR_Q15);
#endif


    memset(q15output, 0, sizeof(q15)*MAX_SIZE);

	printf("\n== mips_mat_sub_q15 check done  == \n\n");  

// =====================

	printf("== mips_mat_scale_q15 test ==  \n"); 
    
    inp1 = q15input1;
    outp = q15output;
    dimsp = q15dims1;
    ap = q15a;
    nbMatrixes = paramCountdims1 >> 1;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATA1(false);
          refInnerTail(outp + rows * columns);
          status=mips_mat_scale_q15(&in1,ONEHALF,0,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          checkInnerTail(outp);

      }


	printf("mips_mat_scale_q15 finish \n");

	printf("mips_mat_scale_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryQ15, "RefScale1_q15.txt");
#else
	referenceFile = UnaryQ15_RefScale1_q15;
	referenceFileLen = sizeof(UnaryQ15_RefScale1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output, referenceFileLen, (q15)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output, referenceFileLen, ABS_ERROR_Q15);
#endif


    memset(q15output, 0, sizeof(q15)*MAX_SIZE);

	printf("\n== mips_mat_scale_q15 check done  == \n\n");  

// =====================

	printf("== mips_mat_trans_q15 test ==  \n"); 
    
    inp1 = q15input1;
    outp = q15output;
    dimsp = q15dims1;
    ap = q15a;
    nbMatrixes = paramCountdims1 >> 1;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATA1(true);
          refInnerTail(outp + rows * columns);
          status=mips_mat_trans_q15(&in1,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          checkInnerTail(outp);

      }


	printf("mips_mat_trans_q15 finish \n");

	printf("mips_mat_trans_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryQ15, "RefTranspose1_q15.txt");
#else
	referenceFile = UnaryQ15_RefTranspose1_q15;
	referenceFileLen = sizeof(UnaryQ15_RefTranspose1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output, referenceFileLen, (q15)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output, referenceFileLen, ABS_ERROR_Q15);
#endif


    memset(q15output, 0, sizeof(q15)*MAX_SIZE);

	printf("\n== mips_mat_trans_q15 check done  == \n\n");  

// =====================

	printf("== mips_mat_vec_mult_q15 test ==  \n"); 
    
    inp1 = q15input1;
    inp2 = q15input4;
    outp = q15output;
    dimsp = q15dims1;
    ap = q15a;
    bp = q15b2;
    nbMatrixes = paramCountdims1 / 2;
    

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          internal = *dimsp++;

          PREPAREVECDATA2();
          refInnerTail(outp + rows);
          mips_mat_vec_mult_q15(&in1, bp, outp);

          outp += rows ;
          checkInnerTail(outp);

      }


	printf("mips_mat_vec_mult_q15 finish \n");

	printf("mips_mat_vec_mult_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryQ15, "RefVecMul1_q15.txt");
#else
	referenceFile = UnaryQ15_RefVecMul1_q15;
	referenceFileLen = sizeof(UnaryQ15_RefVecMul1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = referenceFileLen/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output, referenceFileLen, (q15)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output, referenceFileLen, ABS_ERROR_Q15);
#endif


    memset(q15output, 0, sizeof(q15)*MAX_SIZE);

	printf("\n== mips_mat_vec_mult_q15 check done  == \n\n");  

// =====================

	printf("== mips_mat_cmplx_trans_q15 test ==  \n"); 
    
    inp1 = q15input3;
    outp = q15output;
    dimsp = q15dims1;
    ap = q15a;
    nbMatrixes = paramCountdims1 >> 1;


      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATA1C(true);
          refInnerTail(outp + 2*rows * columns);
          status=mips_mat_cmplx_trans_q15(&in1,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += 2*(rows * columns);
          checkInnerTail(outp);

      }


	printf("mips_mat_cmplx_trans_q15 finish \n");

	printf("mips_mat_cmplx_trans_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryQ15, "RefTransposeC1_q15.txt");
#else
	referenceFile = UnaryQ15_RefTransposeC1_q15;
	referenceFileLen = sizeof(UnaryQ15_RefTransposeC1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output, referenceFileLen, (q15)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output, referenceFileLen, ABS_ERROR_Q15);
#endif


	printf("\n== mips_mat_cmplx_trans_q15 check done  == \n\n"); 

// =====================

return 0;

}