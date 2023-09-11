#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/matrix_functions.h"

#define SNR_THRESHOLD 120
#define REL_ERROR (1.0e-6)
#define ABS_ERROR (1.0e-5)
#define MAXMATRIXDIM 40


#define LOADDATA2()                          \
      const double *inp1, *inp2;    \
      double  *outp, *ap, *bp;    \
                                             \
      inp1 = f64input1;                 \
      inp2 = f64input2;                 \
      outp = f64output;                 \
      ap = f64a1;                 \
      bp = f64b1;                 \
                                             \
      int16_t *dimsp;          \
      dimsp = f64dims;           \
      int nbMatrixes = paramCountdims / 3;\
      int rows,internal,columns;                      


#define PREPAREDATA2()                                                   \
      mips_matrix_instance_f64 in1;\
      mips_matrix_instance_f64 in2;\
      mips_matrix_instance_f64 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=internal;                                               \
      memcpy((void*)ap,(const void*)inp1,2*sizeof(f64)*rows*internal);\
      in1.pData = ap;                                                    \
                                                                         \
      in2.numRows=internal;                                                  \
      in2.numCols=columns;                                               \
      memcpy((void*)bp,(const void*)inp2,2*sizeof(f64)*internal*columns);\
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

	double f64input1[MAX_SIZE] = {0};
    double f64input2[MAX_SIZE] = {0};
    double f64input3[MAX_SIZE] = {0};
    double f64input4[MAX_SIZE] = {0};
    q15 f64dims[MAX_SIZE] = {0};


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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, BinaryF64, "InputA1_f64.txt");
#else
	inputFile1 = BinaryF64_InputA1_f64;
	inputFile1Len = sizeof(BinaryF64_InputA1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, BinaryF64, "InputB1_f64.txt");
#else
	inputFile2 = BinaryF64_InputB1_f64;
	inputFile2Len = sizeof(BinaryF64_InputB1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, BinaryF64, "InputAC1_f64.txt");
#else
	inputFile3 = BinaryF64_InputAC1_f64;
	inputFile3Len = sizeof(BinaryF64_InputAC1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile4, sizeof(inputFile4), "%s%s%s", Patterns_PATH, BinaryF64, "InputBC1_f64.txt");
#else
	inputFile4 = BinaryF64_InputBC1_f64;
	inputFile4Len = sizeof(BinaryF64_InputBC1_f64);
#endif

   
#if defined(NOT_EMBEDDED)
	snprintf(dimsFile, sizeof(dimsFile), "%s%s%s", Patterns_PATH, BinaryF64, "DimsBinary1_s16.txt");
#else
	dimsFile = BinaryF64_DimsBinary1_s16;
	dimsFileLen = sizeof(BinaryF64_DimsBinary1_s16);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile1, &paramCountInput1, f64input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f64(inputFile1, paramCountInput1, f64input1);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile2, &paramCountInput2, f64input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_f64(inputFile2, paramCountInput2, f64input2);
	paramCountInput2 = paramCountInput2/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile3, &paramCountInput3, f64input3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_f64(inputFile3, paramCountInput3, f64input3);
	paramCountInput3 = paramCountInput3/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile4, &paramCountInput4, f64input4);
#else
	paramCountInput4 = inputFile4Len;
	load_data_f64(inputFile4, paramCountInput4, f64input4);
	paramCountInput4 = paramCountInput4/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile, &paramCountdims, f64dims);
#else
	paramCountdims = dimsFileLen;
	load_data_q15(dimsFile, paramCountdims, f64dims);
	paramCountdims = paramCountdims/sizeof(q15);
#endif

    
	double f64output[MAX_SIZE] = {0};
    double f64a1[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    double f64b1[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    double f64a2[2*MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    double f64b2[2*MAXMATRIXDIM*MAXMATRIXDIM] = {0};

// =====================
	
    printf("== mips_mat_mult_f64 test ==  \n");
 
    LOADDATA2();
    mips_status status;

      for(int i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          internal = *dimsp++;
          columns = *dimsp++;


          PREPAREDATA2();

          status=mips_mat_mult_f64(&in1,&in2,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);

      }


	printf("mips_mat_mult_f64 finish \n");

	printf("mips_mat_mult_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BinaryF64, "RefMul1_f64.txt");
#else
	referenceFile = BinaryF64_RefMul1_f64;
	referenceFileLen = sizeof(BinaryF64_RefMul1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output, referenceFileLen, (f64)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


	printf("\n== mips_mat_mult_f64 check done  == \n\n");

// =====================

#if 0
    printf("== mips_mat_cmplx_mult_f64 test ==  \n");
 
     inp1 = f64input3;                 
     inp2 = f64input4;
     tmpPtr = tmp2;                 
     ap = f64a2;                 
     bp = f64b2;     

      for(int i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          internal = *dimsp++;
          columns = *dimsp++;


          PREPAREDATA2();

          mips_mat_cmplx_mult_f64(&in1,&in2,&out);

          outp += (2*rows * columns);

      }


	printf("mips_mat_cmplx_mult_f64 finish \n");

	printf("mips_mat_cmplx_mult_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BinaryF64, "RefCmplxMul1_f64.txt");
#else
	referenceFile = BinaryF64_RefCmplxMul1_f64;
	referenceFileLen = sizeof(BinaryF64_RefCmplxMul1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output, referenceFileLen, (f64)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


	printf("\n== mips_mat_cmplx_mult_f64 check done  == \n\n");
#endif 

// =====================

return 0;

}