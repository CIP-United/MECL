#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/complex_math_functions.h"

#define SNR_THRESHOLD 100

#define ABS_ERROR_Q31 ((q31)100)
#define ABS_ERROR_Q63 ((q63)(1<<18))

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
	q31 q31input1[MAX_SIZE] = {0};
	q31 q31input2[MAX_SIZE] = {0};
	q31 q31input3[MAX_SIZE] = {0};

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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Input1_q31.txt");
#else
	inputFile1 = ComplexMathsQ31_Input1_q31;
	inputFile1Len = sizeof(ComplexMathsQ31_Input1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Input2_q31.txt");
#else
	inputFile2 = ComplexMathsQ31_Input2_q31;
	inputFile2Len = sizeof(ComplexMathsQ31_Input2_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Input3_q31.txt");
#else
	inputFile3 = ComplexMathsQ31_Input3_q31;
	inputFile3Len = sizeof(ComplexMathsQ31_Input3_q31);
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


	q31 q31output1[MAX_SIZE] = {0};
	uint16_t u16output1[MAX_SIZE] = {0};

	printf("== mips_cmplx_conj_q31 test 3 ==  \n");
	mips_cmplx_conj_q31(q31input1, q31output1, 3);
	printf("mips_cmplx_conj_q31 finish \n");

	printf("mips_cmplx_conj_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference1_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference1_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 6, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 6, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 6, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 6, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_conj_q31 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_conj_q31 test 4N ==  \n");
	mips_cmplx_conj_q31(q31input1, q31output1, 8);
	printf("mips_cmplx_conj_q31 finish \n");

	printf("mips_cmplx_conj_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference1_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference1_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 16, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 16, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 16, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 16, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_conj_q31 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_conj_q31 test 4N+1 ==  \n");
	mips_cmplx_conj_q31(q31input1, q31output1, 11);
	printf("mips_cmplx_conj_q31 finish \n");

	printf("mips_cmplx_conj_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference1_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference1_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 22, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 22, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 22, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 22, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_conj_q31 4N+1 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_conj_q31 long ==  \n");
	mips_cmplx_conj_q31(q31input1, q31output1, paramCountInput1);
	printf("mips_cmplx_conj_q31 finish \n");

	printf("mips_cmplx_conj_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference1_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference1_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, paramCountInput1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, paramCountInput1, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, paramCountInput1, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_conj_q31 long check done  == \n\n");

	// =====================
	q63 re, im;
	q63 q63output1[MAX_SIZE] = {0};

	printf("== mips_cmplx_dot_prod_q31 3 test ==  \n");
	mips_cmplx_dot_prod_q31(q31input1, q31input2, 3, &re, &im);
	printf("mips_cmplx_dot_prod_q31 finish \n");

	printf("mips_cmplx_dot_prod_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference2_q63.txt");
#else
	referenceFile = ComplexMathsQ31_Reference2_q63;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference2_q63);
	load_data_q63(referenceFile, referenceFileLen, referenceData_q63);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif

	q63output1[0] = re;
	q63output1[1] = im;

#if defined(NOT_EMBEDDED)
	snr_check_q63(referenceFile, q63output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q63(referenceData_q63, q63output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q63(referenceFile, q63output1, 0, ABS_ERROR_Q63);
#else
	near_check_special_q63(referenceData_q63, q63output1, referenceFileLen, ABS_ERROR_Q63);
#endif


	printf("\n== mips_cmplx_dot_prod_q31 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_dot_prod_q31 4N test ==  \n");
	mips_cmplx_dot_prod_q31(q31input1, q31input2, 8, &re, &im);
	printf("mips_cmplx_dot_prod_q31 finish \n");

	printf("mips_cmplx_dot_prod_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference3_q63.txt");
#else
	referenceFile = ComplexMathsQ31_Reference3_q63;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference3_q63);
	load_data_q63(referenceFile, referenceFileLen, referenceData_q63);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif

	q63output1[0] = re;
	q63output1[1] = im;

#if defined(NOT_EMBEDDED)
	snr_check_q63(referenceFile, q63output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q63(referenceData_q63, q63output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q63(referenceFile, q63output1, 0, ABS_ERROR_Q63);
#else
	near_check_special_q63(referenceData_q63, q63output1, referenceFileLen, ABS_ERROR_Q63);
#endif


	printf("\n== mips_cmplx_dot_prod_q31 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_dot_prod_q31 4N+1 test ==  \n");
	mips_cmplx_dot_prod_q31(q31input1, q31input2, 11, &re, &im);
	printf("mips_cmplx_dot_prod_q31 finish \n");

	printf("mips_cmplx_dot_prod_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference4_q63.txt");
#else
	referenceFile = ComplexMathsQ31_Reference4_q63;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference4_q63);
	load_data_q63(referenceFile, referenceFileLen, referenceData_q63);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif

	q63output1[0] = re;
	q63output1[1] = im;

#if defined(NOT_EMBEDDED)
	snr_check_q63(referenceFile, q63output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q63(referenceData_q63, q63output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q63(referenceFile, q63output1, 0, ABS_ERROR_Q63);
#else
	near_check_special_q63(referenceData_q63, q63output1, referenceFileLen, ABS_ERROR_Q63);
#endif


	printf("\n== mips_cmplx_dot_prod_q31 4N+1 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_q31 3 test ==  \n");
	mips_cmplx_mag_q31(q31input1, q31output1, 3);
	printf("mips_cmplx_mag_q31 finish \n");

	printf("mips_cmplx_mag_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference5_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference5_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference5_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 3, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 3, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 3, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 3, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mag_q31 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_q31 4N test ==  \n");
	mips_cmplx_mag_q31(q31input1, q31output1, 8);
	printf("mips_cmplx_mag_q31 finish \n");

	printf("mips_cmplx_mag_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference5_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference5_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference5_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 8, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 8, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 8, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 8, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mag_q31 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_q31 4N+1 test ==  \n");
	mips_cmplx_mag_q31(q31input1, q31output1, 11);
	printf("mips_cmplx_mag_q31 finish \n");

	printf("mips_cmplx_mag_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference5_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference5_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference5_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 11, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 11, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 11, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 11, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mag_q31 4N+1 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_q31 long test ==  \n");
	mips_cmplx_mag_q31(q31input1, q31output1, 256);
	printf("mips_cmplx_mag_q31 finish \n");

	printf("mips_cmplx_mag_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference5_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference5_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference5_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 0, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFileLen, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mag_q31 long check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_q31 3 test ==  \n");
	mips_cmplx_mag_squared_q31(q31input1, q31output1, 3);
	printf("mips_cmplx_mag_squared_q31 finish \n");

	printf("mips_cmplx_mag_squared_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference6_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference6_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference6_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 3, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 3, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 3, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 3, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mag_squared_q31 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_q31 4N test ==  \n");
	mips_cmplx_mag_squared_q31(q31input1, q31output1, 8);
	printf("mips_cmplx_mag_squared_q31 finish \n");

	printf("mips_cmplx_mag_squared_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference6_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference6_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference6_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 8, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 8, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 8, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 8, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mag_squared_q31 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_q31 4N+1 test ==  \n");
	mips_cmplx_mag_squared_q31(q31input1, q31output1, 11);
	printf("mips_cmplx_mag_squared_q31 finish \n");

	printf("mips_cmplx_mag_squared_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference6_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference6_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference6_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 11, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 11, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 11, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 11, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mag_squared_q31 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_q31 long test ==  \n");
	mips_cmplx_mag_squared_q31(q31input1, q31output1, paramCountInput1);
	printf("mips_cmplx_mag_squared_q31 finish \n");

	printf("mips_cmplx_mag_squared_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference6_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference6_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference6_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 0, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFileLen, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mag_squared_q31 long check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_q31 3 test ==  \n");
	mips_cmplx_mult_cmplx_q31(q31input1, q31input2, q31output1, 3);
	printf("mips_cmplx_mult_cmplx_q31 finish \n");

	printf("mips_cmplx_mult_cmplx_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference7_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference7_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference7_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 6, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 6, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 6, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 6, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mult_cmplx_q31 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_q31 4N test ==  \n");
	mips_cmplx_mult_cmplx_q31(q31input1, q31input2, q31output1, 8);
	printf("mips_cmplx_mult_cmplx_q31 finish \n");

	printf("mips_cmplx_mult_cmplx_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference7_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference7_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference7_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 16, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 16, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 16, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 16, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mult_cmplx_q31 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_q31 4N+1 test ==  \n");
	mips_cmplx_mult_cmplx_q31(q31input1, q31input2, q31output1, 11);
	printf("mips_cmplx_mult_cmplx_q31 finish \n");

	printf("mips_cmplx_mult_cmplx_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference7_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference7_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference7_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 22, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 22, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 22, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 22, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mult_cmplx_q31 4N+1 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_q31 long test ==  \n");
	mips_cmplx_mult_cmplx_q31(q31input1, q31input2, q31output1, 256);
	printf("mips_cmplx_mult_cmplx_q31 finish \n");

	printf("mips_cmplx_mult_cmplx_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference7_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference7_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference7_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 0, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFileLen, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mult_cmplx_q31 long check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_real_q31 3 test ==  \n");
	mips_cmplx_mult_real_q31(q31input1, q31input3, q31output1, 3);
	printf("mips_cmplx_mult_real_q31 finish \n");

	printf("mips_cmplx_mult_real_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference8_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference8_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference8_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 3, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 3, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 3, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 3, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mult_real_q31 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_real_q31 4N test ==  \n");
	mips_cmplx_mult_real_q31(q31input1, q31input3, q31output1, 8);
	printf("mips_cmplx_mult_real_q31 finish \n");

	printf("mips_cmplx_mult_real_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference8_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference8_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference8_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 16, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 16, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 16, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 16, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mult_real_q31 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_real_q31 4N+1 test ==  \n");
	mips_cmplx_mult_real_q31(q31input1, q31input3, q31output1, 11);
	printf("mips_cmplx_mult_real_q31 finish \n");

	printf("mips_cmplx_mult_real_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference8_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference8_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference8_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 22, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 22, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 22, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 22, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mult_real_q31 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_real_q31 long test ==  \n");
	mips_cmplx_mult_real_q31(q31input1, q31input3, q31output1, 256);
	printf("mips_cmplx_mult_real_q31 finish \n");

	printf("mips_cmplx_mult_real_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ31, "Reference8_q31.txt");
#else
	referenceFile = ComplexMathsQ31_Reference8_q31;
	referenceFileLen = sizeof(ComplexMathsQ31_Reference8_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 0, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFileLen, ABS_ERROR_Q31);
#endif


	printf("\n== mips_cmplx_mult_real_q31 long check done  == \n\n");

	// =====================

	return 0;
}