#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/complex_math_functions.h"

#define SNR_THRESHOLD 120

#define REL_ERROR (7.0e-6)

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
	f32 f32input1[MAX_SIZE] = {0};
	f32 f32input2[MAX_SIZE] = {0};
	f32 f32input3[MAX_SIZE] = {0};

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
	char referenceFile[255] = {0};
#else
	void *referenceFile;
	int referenceFileLen = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Input1_f32.txt");
#else
	inputFile1 = ComplexMathsF32_Input1_f32;
	inputFile1Len = sizeof(ComplexMathsF32_Input1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Input2_f32.txt");
#else
	inputFile2 = ComplexMathsF32_Input2_f32;
	inputFile2Len = sizeof(ComplexMathsF32_Input2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Input3_f32.txt");
#else
	inputFile3 = ComplexMathsF32_Input3_f32;
	inputFile3Len = sizeof(ComplexMathsF32_Input3_f32);
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


	f32 f32output1[MAX_SIZE] = {0};
	uint16_t u16output1[MAX_SIZE] = {0};

	printf("== mips_cmplx_conj_f32 test 3 ==  \n");
	mips_cmplx_conj_f32(f32input1, f32output1, 3);
	printf("mips_cmplx_conj_f32 finish \n");

	printf("mips_cmplx_conj_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference1_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference1_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 6, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 6, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 6, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, 6, REL_ERROR);
#endif


	printf("\n== mips_cmplx_conj_f32 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_conj_f32 test 4N ==  \n");
	mips_cmplx_conj_f32(f32input1, f32output1, 8);
	printf("mips_cmplx_conj_f32 finish \n");

	printf("mips_cmplx_conj_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference1_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference1_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 16, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 16, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 16, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, 16, REL_ERROR);
#endif


	printf("\n== mips_cmplx_conj_f32 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_conj_f32 test 4N+1 ==  \n");
	mips_cmplx_conj_f32(f32input1, f32output1, 11);
	printf("mips_cmplx_conj_f32 finish \n");

	printf("mips_cmplx_conj_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference1_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference1_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 22, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 22, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 22, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, 22, REL_ERROR);
#endif


	printf("\n== mips_cmplx_conj_f32 4N+1 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_conj_f32 long ==  \n");
	mips_cmplx_conj_f32(f32input1, f32output1, paramCountInput1);
	printf("mips_cmplx_conj_f32 finish \n");

	printf("mips_cmplx_conj_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference1_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference1_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountInput1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, paramCountInput1, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, paramCountInput1, REL_ERROR);
#endif


	printf("\n== mips_cmplx_conj_f32 long check done  == \n\n");

	// =====================
	f32 re, im;

	printf("== mips_cmplx_dot_prod_f32 3 test ==  \n");
	mips_cmplx_dot_prod_f32(f32input1, f32input2, 3, &re, &im);
	printf("mips_cmplx_dot_prod_f32 finish \n");

	printf("mips_cmplx_dot_prod_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference2_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference2_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference2_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif

	f32output1[0] = re;
	f32output1[1] = im;

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, REL_ERROR);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_cmplx_dot_prod_f32 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_dot_prod_f32 4N test ==  \n");
	mips_cmplx_dot_prod_f32(f32input1, f32input2, 8, &re, &im);
	printf("mips_cmplx_dot_prod_f32 finish \n");

	printf("mips_cmplx_dot_prod_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference3_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference3_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference3_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif

	f32output1[0] = re;
	f32output1[1] = im;

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, REL_ERROR);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_cmplx_dot_prod_f32 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_dot_prod_f32 4N+1 test ==  \n");
	mips_cmplx_dot_prod_f32(f32input1, f32input2, 11, &re, &im);
	printf("mips_cmplx_dot_prod_f32 finish \n");

	printf("mips_cmplx_dot_prod_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference4_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference4_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference4_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif

	f32output1[0] = re;
	f32output1[1] = im;

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, REL_ERROR);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_cmplx_dot_prod_f32 4N+1 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_dot_prod_f32 long test ==  \n");
	mips_cmplx_dot_prod_f32(f32input1, f32input2, paramCountInput1, &re, &im);
	printf("mips_cmplx_dot_prod_f32 finish \n");

	printf("mips_cmplx_dot_prod_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference9_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference9_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference9_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif

	f32output1[0] = re;
	f32output1[1] = im;

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, REL_ERROR);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_cmplx_dot_prod_f32 long check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_f32 3 test ==  \n");
	mips_cmplx_mag_f32(f32input1, f32output1, 3);
	printf("mips_cmplx_mag_f32 finish \n");

	printf("mips_cmplx_mag_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference5_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference5_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference5_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 3, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 3, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 3, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, 3, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_f32 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_f32 4N test ==  \n");
	mips_cmplx_mag_f32(f32input1, f32output1, 8);
	printf("mips_cmplx_mag_f32 finish \n");

	printf("mips_cmplx_mag_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference5_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference5_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference5_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 8, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 8, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 8, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, 8, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_f32 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_f32 4N+1 test ==  \n");
	mips_cmplx_mag_f32(f32input1, f32output1, 11);
	printf("mips_cmplx_mag_f32 finish \n");

	printf("mips_cmplx_mag_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference5_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference5_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference5_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 11, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 11, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 11, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, 11, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_f32 4N+1 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_f32 long test ==  \n");
	mips_cmplx_mag_f32(f32input1, f32output1, paramCountInput1);
	printf("mips_cmplx_mag_f32 finish \n");

	printf("mips_cmplx_mag_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference5_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference5_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference5_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 0, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_f32 long check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_f32 3 test ==  \n");
	mips_cmplx_mag_squared_f32(f32input1, f32output1, 6);
	printf("mips_cmplx_mag_squared_f32 finish \n");

	printf("mips_cmplx_mag_squared_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference6_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference6_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference6_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 3, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 3, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 3, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, 3, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_squared_f32 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_f32 4N test ==  \n");
	mips_cmplx_mag_squared_f32(f32input1, f32output1, 8);
	printf("mips_cmplx_mag_squared_f32 finish \n");

	printf("mips_cmplx_mag_squared_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference6_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference6_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference6_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 8, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 8, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 8, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, 8, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_squared_f32 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_f32 4N+1 test ==  \n");
	mips_cmplx_mag_squared_f32(f32input1, f32output1, 11);
	printf("mips_cmplx_mag_squared_f32 finish \n");

	printf("mips_cmplx_mag_squared_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference6_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference6_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference6_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 11, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 11, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 11, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, 11, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_squared_f32 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_f32 long test ==  \n");
	mips_cmplx_mag_squared_f32(f32input1, f32output1, paramCountInput1);
	printf("mips_cmplx_mag_squared_f32 finish \n");

	printf("mips_cmplx_mag_squared_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference6_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference6_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference6_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 0, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_squared_f32 long check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_f32 3 test ==  \n");
	mips_cmplx_mult_cmplx_f32(f32input1, f32input2, f32output1, 3);
	printf("mips_cmplx_mult_cmplx_f32 finish \n");

	printf("mips_cmplx_mult_cmplx_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference7_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference7_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference7_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 6, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 6, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 6, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, 6, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mult_cmplx_f32 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_f32 4N test ==  \n");
	mips_cmplx_mult_cmplx_f32(f32input1, f32input2, f32output1, 8);
	printf("mips_cmplx_mult_cmplx_f32 finish \n");

	printf("mips_cmplx_mult_cmplx_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference7_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference7_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference7_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 16, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 16, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 16, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, 16, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mult_cmplx_f32 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_f32 4N+1 test ==  \n");
	mips_cmplx_mult_cmplx_f32(f32input1, f32input2, f32output1, 11);
	printf("mips_cmplx_mult_cmplx_f32 finish \n");

	printf("mips_cmplx_mult_cmplx_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference7_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference7_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference7_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 22, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 22, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 22, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, 22, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mult_cmplx_f32 4N+1 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_f32 long test ==  \n");
	mips_cmplx_mult_cmplx_f32(f32input1, f32input2, f32output1, paramCountInput1);
	printf("mips_cmplx_mult_cmplx_f32 finish \n");

	printf("mips_cmplx_mult_cmplx_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference7_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference7_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference7_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 0, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mult_cmplx_f32 long check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_real_f32 3 test ==  \n");
	mips_cmplx_mult_real_f32(f32input1, f32input3, f32output1, 3);
	printf("mips_cmplx_mult_real_f32 finish \n");

	printf("mips_cmplx_mult_real_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference8_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference8_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference8_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 6, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 6, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 6, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, 6, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mult_real_f32 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_real_f32 4N test ==  \n");
	mips_cmplx_mult_real_f32(f32input1, f32input3, f32output1, 8);
	printf("mips_cmplx_mult_real_f32 finish \n");

	printf("mips_cmplx_mult_real_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference8_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference8_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference8_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1,16, SNR_THRESHOLD);
	rel_check_f32(referenceFile, f32output1, 16, REL_ERROR);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 16, SNR_THRESHOLD);
	rel_check_special_f32(referenceData_f32, f32output1, 16, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mult_real_f32 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_real_f32 4N+1 test ==  \n");
	mips_cmplx_mult_real_f32(f32input1, f32input3, f32output1, 11);
	printf("mips_cmplx_mult_real_f32 finish \n");

	printf("mips_cmplx_mult_real_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference8_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference8_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference8_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 22, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 22, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 22, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, 22, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mult_real_f32 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_real_f32 long test ==  \n");
	mips_cmplx_mult_real_f32(f32input1, f32input3, f32output1, paramCountInput1);
	printf("mips_cmplx_mult_real_f32 finish \n");

	printf("mips_cmplx_mult_real_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF32, "Reference8_f32.txt");
#else
	referenceFile = ComplexMathsF32_Reference8_f32;
	referenceFileLen = sizeof(ComplexMathsF32_Reference8_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 0, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mult_real_f32 long check done  == \n\n");

	// =====================

	return 0;
}