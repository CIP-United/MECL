#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/matrix_functions.h"

#define SNR_THRESHOLD 100
#define ABS_ERROR_Q31 ((q31)5)
#define ABS_ERROR_Q63 ((q63)(1<<16))
#define ONEHALF 0x40000000
#define MAXMATRIXDIM 40

static void checkInnerTail(q31 *b)
{
    ASSERT_TRUE(b[0] == 0);
    ASSERT_TRUE(b[1] == 0);
    ASSERT_TRUE(b[2] == 0);
    ASSERT_TRUE(b[3] == 0);
}


#define LOADDATA2()                          \
      q31 *inp1, *inp2;    \
      q31  *outp, *tmpPtr, *ap, *bp;    \
                                             \
      inp1 = q31input1;                 \
      inp2 = q31input2;                 \
      outp = q31output;                 \
      tmpPtr = tmp1;                 \
      ap = q31a1;                 \
      bp = q31b1;                 \
                                             \
      int16_t *dimsp;          \
      dimsp = q31dims;           \
      int nbMatrixes = paramCountdims / 3;\
      int rows,internal,columns;                      
                      

#define PREPAREDATA2()                                                   \
      mips_matrix_instance_q31 in1;\
      mips_matrix_instance_q31 in2;\
      mips_matrix_instance_q31 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=internal;                                               \
      memcpy((void*)ap,(const void*)inp1,2*sizeof(q31)*rows*internal);\
      in1.pData = ap;                                                    \
                                                                         \
      in2.numRows=internal;                                                  \
      in2.numCols=columns;                                               \
      memcpy((void*)bp,(const void*)inp2,2*sizeof(q31)*internal*columns);\
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

	q31 q31input1[MAX_SIZE] = {0};
    q31 q31input2[MAX_SIZE] = {0};
    q31 q31input3[MAX_SIZE] = {0};
    q31 q31input4[MAX_SIZE] = {0};
    q15 q31dims[MAX_SIZE] = {0};


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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, BinaryQ31, "InputA1_q31.txt");
#else
	inputFile1 = BinaryQ31_InputA1_q31;
	inputFile1Len = sizeof(BinaryQ31_InputA1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, BinaryQ31, "InputB1_q31.txt");
#else
	inputFile2 = BinaryQ31_InputB1_q31;
	inputFile2Len = sizeof(BinaryQ31_InputB1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, BinaryQ31, "InputAC1_q31.txt");
#else
	inputFile3 = BinaryQ31_InputAC1_q31;
	inputFile3Len = sizeof(BinaryQ31_InputAC1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile4, sizeof(inputFile4), "%s%s%s", Patterns_PATH, BinaryQ31, "InputBC1_q31.txt");
#else
	inputFile4 = BinaryQ31_InputBC1_q31;
	inputFile4Len = sizeof(BinaryQ31_InputBC1_q31);
#endif

   
#if defined(NOT_EMBEDDED)
	snprintf(dimsFile, sizeof(dimsFile), "%s%s%s", Patterns_PATH, BinaryQ31, "DimsBinary1_s16.txt");
#else
	dimsFile = BinaryQ31_DimsBinary1_s16;
	dimsFileLen = sizeof(BinaryQ31_DimsBinary1_s16);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile1, &paramCountInput1, q31input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q31(inputFile1, paramCountInput1, q31input1);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile2, &paramCountInput2, q31input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q31(inputFile2, paramCountInput2, q31input2);
	paramCountInput2 = paramCountInput2/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile3, &paramCountInput3, q31input3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_q31(inputFile3, paramCountInput3, q31input3);
	paramCountInput3 = paramCountInput3/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile4, &paramCountInput4, q31input4);
#else
	paramCountInput4 = inputFile4Len;
	load_data_q31(inputFile4, paramCountInput4, q31input4);
	paramCountInput4 = paramCountInput4/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile, &paramCountdims, q31dims);
#else
	paramCountdims = dimsFileLen;
	load_data_q15(dimsFile, paramCountdims, q31dims);
	paramCountdims = paramCountdims/sizeof(q15);
#endif

    
	q31 q31output[MAX_SIZE] = {0};

    q31 tmp[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    q31 q31a1[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    q31 q31b1[MAXMATRIXDIM*MAXMATRIXDIM] = {0};

    q31 q31a2[2*MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    q31 q31b2[2*MAXMATRIXDIM*MAXMATRIXDIM] = {0};

    const q31 *inp1, *inp2;
    q31  *outp, *tmpPtr, *ap, *bp;

    int16_t *dimsp;          
    dimsp = q31dims;           
    int nbMatrixes;
    int rows,internal,columns;
    int i;

// =====================
	
    printf("== mips_mat_mult_q31 test ==  \n");
 
    inp1 = q31input1;                 
    inp2 = q31input2;                 
    outp = q31output; 

    ap = q31a1;                 
    bp = q31b1;
    dimsp = q31dims; 

    nbMatrixes = paramCountdims / 3;

    mips_status status1;

      for(int i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          internal = *dimsp++;
          columns = *dimsp++;

          PREPAREDATA2();

          status1=mips_mat_mult_q31(&in1,&in2,&out);
          ASSERT_TRUE(status1==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          checkInnerTail(outp);

      }



	printf("mips_mat_mult_q31 finish \n");

	printf("mips_mat_mult_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BinaryQ31, "RefMul1_q31.txt");
#else
	referenceFile = BinaryQ31_RefMul1_q31;
	referenceFileLen = sizeof(BinaryQ31_RefMul1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output, 0, (q31)SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output, referenceFileLen, (q31)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output, 0, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output, referenceFileLen, ABS_ERROR_Q31);
#endif


    memset(q31output, 0, sizeof(q31)*MAX_SIZE);

	printf("\n== mips_mat_mult_q31 check done  == \n\n");  

// =====================
	
    printf("== mips_mat_cmplx_mult_q31 test ==  \n");
 
    inp1 = q31input3;                 
    inp2 = q31input4;
    outp = q31output;

    ap = q31a2;                 
    bp = q31b2; 
    dimsp = q31dims; 

    nbMatrixes = paramCountdims / 3;

    mips_status status2;

      for(int i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          internal = *dimsp++;
          columns = *dimsp++;


          PREPAREDATA2();

          status2=mips_mat_cmplx_mult_q31(&in1,&in2,&out);
          ASSERT_TRUE(status2==MIPS_MATH_SUCCESS);

          outp += (2*rows * columns);
          checkInnerTail(outp);

      }


	printf("mips_mat_cmplx_mult_q31 finish \n");

	printf("mips_mat_cmplx_mult_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BinaryQ31, "RefCmplxMul1_q31.txt");
#else
	referenceFile = BinaryQ31_RefCmplxMul1_q31;
	referenceFileLen = sizeof(BinaryQ31_RefCmplxMul1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output, 0, (q31)SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output, referenceFileLen, (q31)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output, 0, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output, referenceFileLen, ABS_ERROR_Q31);
#endif


    memset(q31output, 0, sizeof(q31)*MAX_SIZE);

	printf("\n== mips_mat_cmplx_mult_q31 check done  == \n\n"); 

// =====================
	
    printf("== mips_mat_mult_opt_q31 test ==  \n");
 
    inp1 = q31input1;                 
    inp2 = q31input2;
    outp = q31output;
    tmpPtr = tmp;

    ap = q31a1;                 
    bp = q31b1;
    dimsp = q31dims; 

    nbMatrixes = paramCountdims / 3;

    mips_status status3;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          internal = *dimsp++;
          columns = *dimsp++;

          PREPAREDATA2();
          memset(tmpPtr,0,sizeof(q31)*internal*columns + 16);
          status3=mips_mat_mult_opt_q31(&in1,&in2,&out,tmpPtr);
          ASSERT_TRUE(status3==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          checkInnerTail(outp);
          checkInnerTail(tmpPtr + internal*columns);

      }


	printf("mips_mat_mult_opt_q31 finish \n");

	printf("mips_mat_mult_opt_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BinaryQ31, "RefMul1_q31.txt");
#else
	referenceFile = BinaryQ31_RefMul1_q31;
	referenceFileLen = sizeof(BinaryQ31_RefMul1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
    referenceFileLen = referenceFileLen/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output, 0, (q31)SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output, referenceFileLen, (q31)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output, 0, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output, referenceFileLen, ABS_ERROR_Q31);
#endif


	printf("\n== mips_mat_mult_opt_q31 check done  == \n\n");  

// =====================


return 0;

}