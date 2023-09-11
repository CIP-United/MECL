#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/matrix_functions.h"

#define SNR_THRESHOLD 70
#define SNR_LOW_THRESHOLD 30
#define ABS_HIGH_ERROR_Q15 ((q15)2000)
#define ABS_ERROR_Q15 ((q15)1000)

#define ABS_ERROR_Q63 ((q63)(1<<16))

#define MULT_SNR_THRESHOLD 60

#define ONEHALF 0x4000
#define MAXMATRIXDIM 40

static void checkInnerTail(q15 *b)
{
    ASSERT_TRUE(b[0] == 0);
    ASSERT_TRUE(b[1] == 0);
    ASSERT_TRUE(b[2] == 0);
    ASSERT_TRUE(b[3] == 0);
    ASSERT_TRUE(b[4] == 0);
    ASSERT_TRUE(b[5] == 0);
    ASSERT_TRUE(b[6] == 0);
    ASSERT_TRUE(b[7] == 0);
}


                                      

#define PREPAREDATA2C()                                                   \
      mips_matrix_instance_q15 in1;\
      mips_matrix_instance_q15 in2;\
      mips_matrix_instance_q15 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=internal;                                               \
      memcpy((void*)ap,(const void*)inp1,2*sizeof(q15)*rows*internal);\
      in1.pData = ap;                                                    \
                                                                         \
      in2.numRows=internal;                                                  \
      in2.numCols=columns;                                               \
      memcpy((void*)bp,(const void*)inp2,2*sizeof(q15)*internal*columns);\
      in2.pData = bp;                                                    \
                                                                         \
      out.numRows=rows;                                                  \
      out.numCols=columns;                                               \
      out.pData = outp;

#define PREPAREDATA2R()                                                   \
      mips_matrix_instance_q15 in1;\
      mips_matrix_instance_q15 in2;\
      mips_matrix_instance_q15 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=internal;                                               \
      memcpy((void*)ap,(const void*)inp1,sizeof(q15)*rows*internal);\
      in1.pData = ap;                                                    \
                                                                         \
      in2.numRows=internal;                                                  \
      in2.numCols=columns;                                               \
      memcpy((void*)bp,(const void*)inp2,sizeof(q15)*internal*columns);\
      in2.pData = bp;                                                    \
                                                                         \
      out.numRows=rows;                                                  \
      out.numCols=columns;                                               \
      out.pData = outp;

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
    int paramCountdims = 0;

	q15 q15input1[MAX_SIZE] = {0};
    q15 q15input2[MAX_SIZE] = {0};
    q15 q15input3[MAX_SIZE] = {0};
    q15 q15input4[MAX_SIZE] = {0};
    q15 q15dims[MAX_SIZE] = {0};


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
	char referenceFile[255] = {0};
#else
	void *referenceFile;
	int referenceFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char dimsFile[255] = {0};
#else
	void *dimsFile;
	int dimsFileLen = 0;
#endif



	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, BinaryQ15, "InputA1_q15.txt");
#else
	inputFile1 = BinaryQ15_InputA1_q15;
	inputFile1Len = sizeof(BinaryQ15_InputA1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, BinaryQ15, "InputB1_q15.txt");
#else
	inputFile2 = BinaryQ15_InputB1_q15;
	inputFile2Len = sizeof(BinaryQ15_InputB1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, BinaryQ15, "InputAC1_q15.txt");
#else
	inputFile3 = BinaryQ15_InputAC1_q15;
	inputFile3Len = sizeof(BinaryQ15_InputAC1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile4, sizeof(inputFile4), "%s%s%s", Patterns_PATH, BinaryQ15, "InputBC1_q15.txt");
#else
	inputFile4 = BinaryQ15_InputBC1_q15;
	inputFile4Len = sizeof(BinaryQ15_InputBC1_q15);
#endif

   
#if defined(NOT_EMBEDDED)
	snprintf(dimsFile, sizeof(dimsFile), "%s%s%s", Patterns_PATH, BinaryQ15, "DimsBinary1_s16.txt");
#else
	dimsFile = BinaryQ15_DimsBinary1_s16;
	dimsFileLen = sizeof(BinaryQ15_DimsBinary1_s16);
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
	load_data_q15(dimsFile, &paramCountdims, q15dims);
#else
	paramCountdims = dimsFileLen;
	load_data_q15(dimsFile, paramCountdims, q15dims);
	paramCountdims = paramCountdims/sizeof(q15);
#endif

    
	q15 q15output[MAX_SIZE] = {0};
    q15 tmp1[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    q15 q15a1[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    q15 q15b1[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    q15 tmp2[2*MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    q15 q15a2[2*MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    q15 q15b2[2*MAXMATRIXDIM*MAXMATRIXDIM] = {0};

    const q15 *inp1, *inp2;
    q15  *outp, *tmpPtr, *ap, *bp;

    int16_t *dimsp;          
    dimsp = q15dims;           
    int nbMatrixes;
    int rows,internal,columns;
    int i;

// =====================
	
    printf("== mips_mat_mult_q15 test ==  \n");
 
    inp1 = q15input1;                 
    inp2 = q15input2;                 
    outp = q15output;                 
    tmpPtr = tmp1;                 
    ap = q15a1;                 
    bp = q15b1;
    dimsp = q15dims; 

    nbMatrixes = paramCountdims / 3;

    mips_status status1;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          internal = *dimsp++;
          columns = *dimsp++;


          PREPAREDATA2R();
          memset(tmpPtr,0,sizeof(q15)*internal*columns + 16);
          status1=mips_mat_mult_q15(&in1,&in2,&out,tmpPtr);
          ASSERT_TRUE(status1==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          checkInnerTail(outp);
          checkInnerTail(tmpPtr + internal * columns);

      }



	printf("mips_mat_mult_q15 finish \n");

	printf("mips_mat_mult_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BinaryQ15, "RefMul1_q15.txt");
#else
	referenceFile = BinaryQ15_RefMul1_q15;
	referenceFileLen = sizeof(BinaryQ15_RefMul1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output, 0, (q15)SNR_LOW_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output, referenceFileLen, (q15)SNR_LOW_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output, 0, ABS_HIGH_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output, referenceFileLen, ABS_HIGH_ERROR_Q15);
#endif


    memset(q15output, 0, sizeof(q15)*MAX_SIZE);

	printf("\n== mips_mat_mult_q15 check done  == \n\n");  

// =====================
	
    printf("== mips_mat_cmplx_mult_q15 test ==  \n");
 
    inp1 = q15input3;                 
    inp2 = q15input4;
    outp = q15output;
    tmpPtr = tmp2;                 
    ap = q15a2;                 
    bp = q15b2;
    dimsp = q15dims; 

    nbMatrixes = paramCountdims / 3; 
    
    mips_status status2;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          internal = *dimsp++;
          columns = *dimsp++;


          PREPAREDATA2C();

          status2=mips_mat_cmplx_mult_q15(&in1,&in2,&out,tmpPtr);
          ASSERT_TRUE(status2==MIPS_MATH_SUCCESS);

          outp += (2*rows * columns);
          checkInnerTail(outp);

      }


	printf("mips_mat_cmplx_mult_q15 finish \n");

	printf("mips_mat_cmplx_mult_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BinaryQ15, "RefCmplxMul1_q15.txt");
#else
	referenceFile = BinaryQ15_RefCmplxMul1_q15;
	referenceFileLen = sizeof(BinaryQ15_RefCmplxMul1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
    referenceFileLen = referenceFileLen/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output, 0, (q15)MULT_SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output, referenceFileLen, (q15)MULT_SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output, referenceFileLen, ABS_ERROR_Q15);
#endif


	printf("\n== mips_mat_cmplx_mult_q15 check done  == \n\n"); 

// =====================


return 0;

}