#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/matrix_functions.h"

#define SNR_THRESHOLD 20
#define SNR_LOW_THRESHOLD 11
#define ABS_ERROR_Q7 ((q7)2)
#define ABS_ERROR_Q63 ((q63)(1<<16))

#define ONEHALF 0x4000

#define MAXMATRIXDIM 47

static void checkInnerTail(q7 *b)
{
    ASSERT_TRUE(b[0] == 0);
    ASSERT_TRUE(b[1] == 0);
    ASSERT_TRUE(b[2] == 0);
    ASSERT_TRUE(b[3] == 0);
    ASSERT_TRUE(b[4] == 0);
    ASSERT_TRUE(b[5] == 0);
    ASSERT_TRUE(b[6] == 0);
    ASSERT_TRUE(b[7] == 0);

    ASSERT_TRUE(b[8] == 0);
    ASSERT_TRUE(b[9] == 0);
    ASSERT_TRUE(b[10] == 0);
    ASSERT_TRUE(b[11] == 0);
    ASSERT_TRUE(b[12] == 0);
    ASSERT_TRUE(b[13] == 0);
    ASSERT_TRUE(b[14] == 0);
    ASSERT_TRUE(b[15] == 0);
}



#define PREPAREDATA2()                                                   \
      mips_matrix_instance_q7 in1;\
      mips_matrix_instance_q7 in2;\
      mips_matrix_instance_q7 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=columns;                                               \
      memcpy((void*)ap,(const void*)inp1,sizeof(q7)*rows*columns);\
      in1.pData = ap;                                                    \
                                                                         \
      in2.numRows=rows;                                                  \
      in2.numCols=columns;                                               \
      memcpy((void*)bp,(const void*)inp2,sizeof(q7)*rows*columns);\
      in2.pData = bp;                                                    \
                                                                         \
      out.numRows=rows;                                                  \
      out.numCols=columns;                                               \
      out.pData = outp;

#define PREPAREDATA1(TRANSPOSED)                                         \
      mips_matrix_instance_q7 in1;\
      mips_matrix_instance_q7 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=columns;                                               \
      memcpy((void*)ap,(const void*)inp1,sizeof(q7)*rows*columns);\
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

#define PREPAREVECDATA2()                                            \
      mips_matrix_instance_q7 in1;\
      in1.numRows=rows;                                              \
      in1.numCols=internal;                                          \
      memcpy((void*)ap,(const void*)inp1,sizeof(q7)*rows*internal);\
      in1.pData = ap;                                                \
                                                                     \
      memcpy((void*)bp,(const void*)inp2,sizeof(q7)*internal);
      



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
    int paramCountdims = 0;

    q7 q7input1[MAX_SIZE] = {0};
    q7 q7input2[MAX_SIZE] = {0};
    q15 q7dims[MAX_SIZE] = {0};


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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, UnaryQ7, "InputA1_q7.txt");
#else
	inputFile1 = UnaryQ7_InputA1_q7;
	inputFile1Len = sizeof(UnaryQ7_InputA1_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, UnaryQ7, "InputVec1_q7.txt");
#else
	inputFile2 = UnaryQ7_InputVec1_q7;
	inputFile2Len = sizeof(UnaryQ7_InputVec1_q7);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(dimsFile, sizeof(dimsFile), "%s%s%s", Patterns_PATH, UnaryQ7, "DimsUnary1_s16.txt");
#else
	dimsFile = UnaryQ7_DimsUnary1_s16;
	dimsFileLen = sizeof(UnaryQ7_DimsUnary1_s16);
#endif


    // load input data
#if defined(NOT_EMBEDDED)
	load_data_q7(inputFile1, &paramCountInput1, q7input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q7(inputFile1, paramCountInput1, q7input1);
	paramCountInput1 = paramCountInput1/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q7(inputFile2, &paramCountInput2, q7input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q7(inputFile2, paramCountInput2, q7input2);
	paramCountInput2 = paramCountInput2/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile, &paramCountdims, q7dims);
#else
	paramCountdims = dimsFileLen;
	load_data_q15(dimsFile, paramCountdims, q7dims);
	paramCountdims = paramCountdims/sizeof(q15);
#endif


    q7 q7output[MAX_SIZE] = {0};
    
    q7 q7a[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    q7 q7b[MAXMATRIXDIM] = {0};

    const q7 *inp1;
    const q7 *inp2 ;    
    q7  *outp;    
    q7  *ap;
    q7  *bp;
                                                           
    int16_t *dimsp;           
                
    int nbMatrixes;
    int rows,internal,columns;
    int i;

// =====================

	printf("== mips_mat_trans_q7 test ==  \n"); 
    
    inp1 = q7input1;
    outp = q7output;
    dimsp = q7dims;
    ap = q7a;
    nbMatrixes = paramCountdims >> 1;
    mips_status status;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;
          PREPAREDATA1(true);

          status=mips_mat_trans_q7(&in1,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          checkInnerTail(outp);

      }
      

	printf("mips_mat_trans_q7 finish \n");

	printf("mips_mat_trans_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryQ7, "RefTranspose1_q7.txt");
#else
	referenceFile = UnaryQ7_RefTranspose1_q7;
	referenceFileLen = sizeof(UnaryQ7_RefTranspose1_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output, 0, (q7)SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output, referenceFileLen, (q7)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output, referenceFileLen, ABS_ERROR_Q7);
#endif


    memset(q7output, 0, sizeof(q7)*MAX_SIZE);

	printf("\n== mips_mat_trans_q7 check done  == \n\n");  

// =====================

	printf("== mips_mat_vec_mult_q7 test ==  \n"); 
    
    inp1 = q7input1;
    inp2 = q7input2;
    outp = q7output;
    dimsp = q7dims;
    ap = q7a;
    bp = q7b;
    nbMatrixes = paramCountdims / 2;
    

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          internal = *dimsp++;

          PREPAREVECDATA2();

          mips_mat_vec_mult_q7(&in1, bp, outp);

          outp += rows ;
          checkInnerTail(outp);

      }


	printf("mips_mat_vec_mult_q7 finish \n");

	printf("mips_mat_vec_mult_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryQ7, "RefVecMul1_q7.txt");
#else
	referenceFile = UnaryQ7_RefVecMul1_q7;
	referenceFileLen = sizeof(UnaryQ7_RefVecMul1_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output, 0, (q7)SNR_LOW_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output, referenceFileLen, (q7)SNR_LOW_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output, referenceFileLen, ABS_ERROR_Q7);
#endif


	printf("\n== mips_mat_vec_mult_q7 check done  == \n\n");  

// =====================

return 0;

}