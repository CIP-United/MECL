#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/complex_math_functions.h"

#define SNR_THRESHOLD (f32)60
#define SNR_MAG_THRESHOLD 80
#define SNR_MAG_FAST_THRESHOLD 60

#define MAG_ERROR_Q15 ((q15)1)
#define MAG_FAST_ERROR_Q15 ((q15)50)

#define ABS_ERROR_Q15 ((q15)5)
#define ABS_ERROR_Q31 ((q31)550)

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
	q15 q15input1[MAX_SIZE] = {0};
	q15 q15input2[MAX_SIZE] = {0};
	q15 q15input3[MAX_SIZE] = {0};

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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Input1_q15.txt");
#else
	inputFile1 = ComplexMathsQ15_Input1_q15;
	inputFile1Len = sizeof(ComplexMathsQ15_Input1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Input2_q15.txt");
#else
	inputFile2 = ComplexMathsQ15_Input2_q15;
	inputFile2Len = sizeof(ComplexMathsQ15_Input2_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Input3_q15.txt");
#else
	inputFile3 = ComplexMathsQ15_Input3_q15;
	inputFile3Len = sizeof(ComplexMathsQ15_Input3_q15);
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


	q15 q15output1[MAX_SIZE] = {0};
	uint16_t u16output1[MAX_SIZE] = {0};

	printf("== mips_cmplx_conj_q15 test 3 ==  \n");
	mips_cmplx_conj_q15(q15input1, q15output1, 7);
	printf("mips_cmplx_conj_q15 finish \n");

	printf("mips_cmplx_conj_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference1_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference1_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 14, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 14, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 14, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 14, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_conj_q15 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_conj_q15 test 4N ==  \n");
	mips_cmplx_conj_q15(q15input1, q15output1, 16);
	printf("mips_cmplx_conj_q15 finish \n");

	printf("mips_cmplx_conj_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference1_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference1_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 32, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 32, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 32, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 32, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_conj_q15 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_conj_q15 test 4N+1 ==  \n");
	mips_cmplx_conj_q15(q15input1, q15output1, 23);
	printf("mips_cmplx_conj_q15 finish \n");

	printf("mips_cmplx_conj_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference1_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference1_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 46, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 46, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 46, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 46, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_conj_q15 4N+1 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_conj_q15 long ==  \n");
	mips_cmplx_conj_q15(q15input1, q15output1, paramCountInput1);
	printf("mips_cmplx_conj_q15 finish \n");

	printf("mips_cmplx_conj_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference1_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference1_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, paramCountInput1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, paramCountInput1, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, paramCountInput1, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_conj_q15 long check done  == \n\n");

	// =====================
	q31 re, im;
	q31 q31output1[MAX_SIZE] = {0};

	printf("== mips_cmplx_dot_prod_q15 3 test ==  \n");
	mips_cmplx_dot_prod_q15(q15input1, q15input2, 7, &re, &im);
	printf("mips_cmplx_dot_prod_q15 finish \n");

	printf("mips_cmplx_dot_prod_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference2_q31.txt");
#else
	referenceFile = ComplexMathsQ15_Reference2_q31;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference2_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif

	q31output1[0] = re;
	q31output1[1] = im;

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


	printf("\n== mips_cmplx_dot_prod_q15 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_dot_prod_q15 4N test ==  \n");
	mips_cmplx_dot_prod_q15(q15input1, q15input2, 16, &re, &im);
	printf("mips_cmplx_dot_prod_q15 finish \n");

	printf("mips_cmplx_dot_prod_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference3_q31.txt");
#else
	referenceFile = ComplexMathsQ15_Reference3_q31;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference3_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif

	q31output1[0] = re;
	q31output1[1] = im;

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


	printf("\n== mips_cmplx_dot_prod_q15 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_dot_prod_q15 4N+1 test ==  \n");
	mips_cmplx_dot_prod_q15(q15input1, q15input2, 23, &re, &im);
	printf("mips_cmplx_dot_prod_q15 finish \n");

	printf("mips_cmplx_dot_prod_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference4_q31.txt");
#else
	referenceFile = ComplexMathsQ15_Reference4_q31;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference4_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif

	q31output1[0] = re;
	q31output1[1] = im;

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


	printf("\n== mips_cmplx_dot_prod_q15 4N+1 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_q15 3 test ==  \n");
	mips_cmplx_mag_q15(q15input1, q15output1, 7);
	printf("mips_cmplx_mag_q15 finish \n");

	printf("mips_cmplx_mag_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference5_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference5_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference5_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 7, SNR_MAG_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 7, SNR_MAG_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 7, MAG_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 7, MAG_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mag_q15 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_q15 4N test ==  \n");
	mips_cmplx_mag_q15(q15input1, q15output1, 16);
	printf("mips_cmplx_mag_q15 finish \n");

	printf("mips_cmplx_mag_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference5_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference5_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference5_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 16, SNR_MAG_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 16, SNR_MAG_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 16, MAG_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 16, MAG_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mag_q15 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_q15 4N+1 test ==  \n");
	mips_cmplx_mag_q15(q15input1, q15output1, 23);
	printf("mips_cmplx_mag_q15 finish \n");

	printf("mips_cmplx_mag_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference5_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference5_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference5_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 23, SNR_MAG_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 23, SNR_MAG_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 23, MAG_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 23, MAG_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mag_q15 4N+1 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_q15 long test ==  \n");
	mips_cmplx_mag_q15(q15input1, q15output1, paramCountInput1);
	printf("mips_cmplx_mag_q15 finish \n");

	printf("mips_cmplx_mag_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference5_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference5_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference5_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = sizeof(ComplexMathsQ15_Reference5_q15)/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_MAG_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_MAG_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, MAG_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, MAG_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mag_q15 long check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_fast_q15 3 test ==  \n");
	mips_cmplx_mag_fast_q15(q15input1, q15output1, 7);
	printf("mips_cmplx_mag_fast_q15 finish \n");

	printf("mips_cmplx_mag_fast_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference5_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference5_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference5_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 7, SNR_MAG_FAST_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 7, SNR_MAG_FAST_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 7, MAG_FAST_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 7, MAG_FAST_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mag_fast_q15 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_fast_q15 4N test ==  \n");
	mips_cmplx_mag_fast_q15(q15input1, q15output1, 16);
	printf("mips_cmplx_mag_fast_q15 finish \n");

	printf("mips_cmplx_mag_fast_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference5_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference5_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference5_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 16, SNR_MAG_FAST_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 16, SNR_MAG_FAST_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 16, MAG_FAST_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 16, MAG_FAST_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mag_fast_q15 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_fast_q15 4N+1 test ==  \n");
	mips_cmplx_mag_fast_q15(q15input1, q15output1, 23);
	printf("mips_cmplx_mag_fast_q15 finish \n");

	printf("mips_cmplx_mag_fast_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference5_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference5_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference5_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 23, SNR_MAG_FAST_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 23, SNR_MAG_FAST_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 23, MAG_FAST_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 23, MAG_FAST_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mag_fast_q15 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_fast_q15 long test ==  \n");
	mips_cmplx_mag_fast_q15(q15input1, q15output1, paramCountInput1);
	printf("mips_cmplx_mag_fast_q15 finish \n");

	printf("mips_cmplx_mag_fast_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference5_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference5_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference5_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = sizeof(ComplexMathsQ15_Reference5_q15)/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_MAG_FAST_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_MAG_FAST_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, MAG_FAST_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, MAG_FAST_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mag_fast_q15 long check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_q15 3 test ==  \n");
	mips_cmplx_mag_squared_q15(q15input1, q15output1, 7);
	printf("mips_cmplx_mag_squared_q15 finish \n");

	printf("mips_cmplx_mag_squared_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference6_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference6_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference6_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 7, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 7, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 7, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 7, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mag_squared_q15 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_q15 4N test ==  \n");
	mips_cmplx_mag_squared_q15(q15input1, q15output1, 16);
	printf("mips_cmplx_mag_squared_q15 finish \n");

	printf("mips_cmplx_mag_squared_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference6_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference6_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference6_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 16, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 16, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 16, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 16, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mag_squared_q15 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_q15 4N+1 test ==  \n");
	mips_cmplx_mag_squared_q15(q15input1, q15output1, 23);
	printf("mips_cmplx_mag_squared_q15 finish \n");

	printf("mips_cmplx_mag_squared_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference6_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference6_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference6_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 23, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 23, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 23, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 23, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mag_squared_q15 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_q15 long test ==  \n");
	mips_cmplx_mag_squared_q15(q15input1, q15output1, paramCountInput1);
	printf("mips_cmplx_mag_squared_q15 finish \n");

	printf("mips_cmplx_mag_squared_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference6_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference6_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference6_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = sizeof(ComplexMathsQ15_Reference6_q15)/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mag_squared_q15 long check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_q15 3 test ==  \n");
	mips_cmplx_mult_cmplx_q15(q15input1, q15input2, q15output1, 7);
	printf("mips_cmplx_mult_cmplx_q15 finish \n");

	printf("mips_cmplx_mult_cmplx_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference7_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference7_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference7_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 14, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 14, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 14, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 14, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mult_cmplx_q15 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_q15 4N test ==  \n");
	mips_cmplx_mult_cmplx_q15(q15input1, q15input2, q15output1, 16);
	printf("mips_cmplx_mult_cmplx_q15 finish \n");

	printf("mips_cmplx_mult_cmplx_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference7_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference7_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference7_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 32, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 32, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 32, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 32, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mult_cmplx_q15 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_q15 4N+1 test ==  \n");
	mips_cmplx_mult_cmplx_q15(q15input1, q15input2, q15output1, 23);
	printf("mips_cmplx_mult_cmplx_q15 finish \n");

	printf("mips_cmplx_mult_cmplx_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference7_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference7_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference7_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 46, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 46, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 46, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 46, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mult_cmplx_q15 4N+1 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_q15 long test ==  \n");
	mips_cmplx_mult_cmplx_q15(q15input1, q15input2, q15output1, 256);
	printf("mips_cmplx_mult_cmplx_q15 finish \n");

	printf("mips_cmplx_mult_cmplx_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference7_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference7_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference7_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = referenceFileLen/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mult_cmplx_q15 long check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_real_q15 3 test ==  \n");
	mips_cmplx_mult_real_q15(q15input1, q15input3, q15output1, 7);
	printf("mips_cmplx_mult_real_q15 finish \n");

	printf("mips_cmplx_mult_real_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference8_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference8_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference8_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 7, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 7, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 7, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 7, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mult_real_q15 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_real_q15 4N test ==  \n");
	mips_cmplx_mult_real_q15(q15input1, q15input3, q15output1, 16);
	printf("mips_cmplx_mult_real_q15 finish \n");

	printf("mips_cmplx_mult_real_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference8_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference8_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference8_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 32, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 32, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 32, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 32, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mult_real_q15 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_real_q15 4N+1 test ==  \n");
	mips_cmplx_mult_real_q15(q15input1, q15input3, q15output1, 23);
	printf("mips_cmplx_mult_real_q15 finish \n");

	printf("mips_cmplx_mult_real_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference8_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference8_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference8_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 46, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 46, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 46, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, 46, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mult_real_q15 4N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_real_q15 long test ==  \n");
	mips_cmplx_mult_real_q15(q15input1, q15input3, q15output1, 256);
	printf("mips_cmplx_mult_real_q15 finish \n");

	printf("mips_cmplx_mult_real_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsQ15, "Reference8_q15.txt");
#else
	referenceFile = ComplexMathsQ15_Reference8_q15;
	referenceFileLen = sizeof(ComplexMathsQ15_Reference8_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = referenceFileLen/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, ABS_ERROR_Q15);
#endif


	printf("\n== mips_cmplx_mult_real_q15 long check done  == \n\n");

	// =====================

	return 0;
}