#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/matrix_functions.h"

#define SNR_THRESHOLD 120
#define REL_ERROR (1.0e-6)
#define ABS_ERROR (1.0e-5)
#define MAXMATRIXDIM 40


static void checkInnerTail(f32 *b)
{
    ASSERT_TRUE(b[0] == 0.0f);
    ASSERT_TRUE(b[1] == 0.0f);
    ASSERT_TRUE(b[2] == 0.0f);
    ASSERT_TRUE(b[3] == 0.0f);
}

#define LOADDATA2a()                          \
      const float *inp1, *inp2;    \
      float  *outp1, *ap1, *bp1;    \
                                             \
      inp1 = &f32input1;                 \
      inp2 = &f32input2;                 \
      outp1 = &f32output1;                 \
      ap1 = &f32a1;                 \
      bp1 = &f32b1;                 \
                                             \
      int16_t *dimsp1;          \
      dimsp1 = &f32dims;           \
      int nbMatrixes1= paramCountdims / 3;\
      int rows1,internal1,columns1;                      

#define LOADDATA2b()                          \
      const float *inp3, *inp4;    \
      float  *outp2, *ap2, *bp2;    \
                                             \
      inp3 = &f32input3;                 \
      inp4 = &f32input4;                 \
      outp2 = &f32output2;                 \
      ap2 = &f32a2;                 \
      bp2 = &f32b2;                 \
                                             \
      int16_t *dimsp2;          \
      dimsp2 = &f32dims;           \
      int nbMatrixes2 = paramCountdims / 3;\
      int rows2,internal2,columns2;                    


#define PREPAREDATA2a()  \
      mips_matrix_instance_f32 in1;\
      mips_matrix_instance_f32 in2;\
      mips_matrix_instance_f32 out1;\
      in1.numRows=rows1;                                                  \
      in1.numCols=internal1;                                               \
      memcpy((void*)ap1,(const void*)inp1,2*sizeof(f32)*rows1*internal1);\
      in1.pData = ap1;                                                    \
                                                                         \
      in2.numRows=internal1;                                                  \
      in2.numCols=columns1;                                               \
      memcpy((void*)bp1,(const void*)inp2,2*sizeof(f32)*internal1*columns1);\
      in2.pData = bp1;                                                    \
                                                                         \
      out1.numRows=rows1;                                                  \
      out1.numCols=columns1;                                               \
      out1.pData = outp1;

#define PREPAREDATA2b()                                                   \
      mips_matrix_instance_f32 in3;\
      mips_matrix_instance_f32 in4;\
      mips_matrix_instance_f32 out2;\
      in3.numRows=rows2;                                                  \
      in3.numCols=internal2;                                               \
      memcpy((void*)ap2,(const void*)inp3,2*sizeof(f32)*rows2*internal2);\
      in3.pData = ap2;                                                    \
                                                                         \
      in4.numRows=internal2;                                                  \
      in4.numCols=columns2;                                               \
      memcpy((void*)bp2,(const void*)inp4,2*sizeof(f32)*internal2*columns2);\
      in4.pData = bp2;                                                    \
                                                                         \
      out2.numRows=rows2;                                                  \
      out2.numCols=columns2;                                               \
      out2.pData = outp2;

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

	float f32input1[MAX_SIZE] = {0};
    float f32input2[MAX_SIZE] = {0};
    float f32input3[MAX_SIZE] = {0};
    float f32input4[MAX_SIZE] = {0};
    q15 f32dims[MAX_SIZE] = {0};


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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, BinaryF32, "InputA1_f32.txt");
#else
	inputFile1 = BinaryF32_InputA1_f32;
	inputFile1Len = sizeof(BinaryF32_InputA1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, BinaryF32, "InputB1_f32.txt");
#else
	inputFile2 = BinaryF32_InputB1_f32;
	inputFile2Len = sizeof(BinaryF32_InputB1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, BinaryF32, "InputAC1_f32.txt");
#else
	inputFile3 = BinaryF32_InputAC1_f32;
	inputFile3Len = sizeof(BinaryF32_InputAC1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile4, sizeof(inputFile4), "%s%s%s", Patterns_PATH, BinaryF32, "InputBC1_f32.txt");
#else
	inputFile4 = BinaryF32_InputBC1_f32;
	inputFile4Len = sizeof(BinaryF32_InputBC1_f32);
#endif

   
#if defined(NOT_EMBEDDED)
	snprintf(dimsFile, sizeof(dimsFile), "%s%s%s", Patterns_PATH, BinaryF32, "DimsBinary1_s16.txt");
#else
	dimsFile = BinaryF32_DimsBinary1_s16;
	dimsFileLen = sizeof(BinaryF32_DimsBinary1_s16);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile1, &paramCountInput1, f32input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f32(inputFile1, paramCountInput1, f32input1);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile2, &paramCountInput2, f32input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_f32(inputFile2, paramCountInput2, f32input2);
	paramCountInput2 = paramCountInput2/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile3, &paramCountInput3, f32input3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_f32(inputFile3, paramCountInput3, f32input3);
	paramCountInput3 = paramCountInput3/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile4, &paramCountInput4, f32input4);
#else
	paramCountInput4 = inputFile4Len;
	load_data_f32(inputFile4, paramCountInput4, f32input4);
	paramCountInput4 = paramCountInput4/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile, &paramCountdims, f32dims);
#else
	paramCountdims = dimsFileLen;
	load_data_q15(dimsFile, paramCountdims, f32dims);
	paramCountdims = paramCountdims/sizeof(q15);
#endif

    
	float f32output1[MAX_SIZE] = {0};
    float f32output2[MAX_SIZE] = {0};
    float f32a1[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    float f32b1[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    float f32a2[2*MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    float f32b2[2*MAXMATRIXDIM*MAXMATRIXDIM] = {0};   

// =====================
	
    printf("== mips_mat_mult_f32 test ==  \n");

    LOADDATA2a();
    mips_status status1;

      for(int i=0;i < nbMatrixes1 ; i ++)
      {
          rows1 = *dimsp1++;
          internal1 = *dimsp1++;
          columns1 = *dimsp1++;


          PREPAREDATA2a();

          status1=mips_mat_mult_f32(&in1,&in2,&out1);
          ASSERT_TRUE(status1==MIPS_MATH_SUCCESS);

          outp1 += (rows1 * columns1);
          checkInnerTail(outp1);

      }


	printf("mips_mat_mult_f32 finish \n");

	printf("mips_mat_mult_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BinaryF32, "RefMul1_f32.txt");
#else
	referenceFile = BinaryF32_RefMul1_f32;
	referenceFileLen = sizeof(BinaryF32_RefMul1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


	printf("\n== mips_mat_mult_f32 check done  == \n\n");   

// =====================
	
    printf("== mips_mat_cmplx_mult_f32 test ==  \n");
 
    LOADDATA2b();
    mips_status status2;

      for(int i=0;i < nbMatrixes2 ; i ++)
      {
          rows2 = *dimsp2++;
          internal2 = *dimsp2++;
          columns2 = *dimsp2++;


          PREPAREDATA2b();

          status2=mips_mat_cmplx_mult_f32(&in3,&in4,&out2);
          ASSERT_TRUE(status2==MIPS_MATH_SUCCESS);

          outp2 += (2*rows2 * columns2);
          checkInnerTail(outp2);

      }


	printf("mips_mat_cmplx_mult_f32 finish \n");

	printf("mips_mat_cmplx_mult_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BinaryF32, "RefCmplxMul1_f32.txt");
#else
	referenceFile = BinaryF32_RefCmplxMul1_f32;
	referenceFileLen = sizeof(BinaryF32_RefCmplxMul1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output2, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output2, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output2, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output2, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


	printf("\n== mips_mat_cmplx_mult_f32 check done  == \n\n");  

// =====================

return 0;

}