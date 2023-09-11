#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/basic_math_functions.h"

#define SNR_THRESHOLD 250
#define REL_ERROR (2.0e-13)

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
	double f64input1[MAX_SIZE] = {0};
	double f64input2[MAX_SIZE] = {0};

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


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, BasicMathsF64, "Input1_f64.txt");
#else
	inputFile1 = BasicMathsF64_Input1_f64;
	inputFile1Len = sizeof(BasicMathsF64_Input1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, BasicMathsF64, "Input2_f64.txt");
#else
	inputFile2 = BasicMathsF64_Input2_f64;
	inputFile2Len = sizeof(BasicMathsF64_Input2_f64);
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

	double f64output1[MAX_SIZE] = {0};

// ===========mips_add_f64==========

	printf("== mips_add_f64 test ==  \n");
	mips_add_f64(f64input1, f64input2, f64output1, paramCountInput1);
	printf("mips_add_f64 finish \n");

	printf("mips_add_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF64, "Reference1_f64.txt");
#else
	referenceFile = BasicMathsF64_Reference1_f64;
	referenceFileLen = sizeof(BasicMathsF64_Reference1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, paramCountInput1, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, paramCountInput1, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountInput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_add_f64 check done  == \n\n");

	// for (size_t i = 0; i < paramCountInput1; i++)
	// {
	// 	printf("mips_add_f64 output = %f \n", f64output1[i]);
	// }
	
// ==========mips_sub_f64===========

	printf("== mips_sub_f64 test ==  \n");
	mips_sub_f64(f64input1, f64input2, f64output1, paramCountInput1);
	printf("mips_sub_f64 finish \n");

	printf("mips_sub_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF64, "Reference2_f64.txt");
#else
	referenceFile = BasicMathsF64_Reference2_f64;
	referenceFileLen = sizeof(BasicMathsF64_Reference2_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountInput1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, paramCountInput1, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, paramCountInput1, REL_ERROR);
#endif


	printf("\n== mips_sub_f64 check done  == \n\n");

// ===========mips_mult_f64==========

	printf("== mips_mult_f64 test ==  \n");
	mips_mult_f64(f64input1, f64input2, f64output1, paramCountInput1);
	printf("mips_mult_f64 finish \n");

	printf("mips_mult_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF64, "Reference3_f64.txt");
#else
	referenceFile = BasicMathsF64_Reference3_f64;
	referenceFileLen = sizeof(BasicMathsF64_Reference3_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountInput1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, paramCountInput1, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, paramCountInput1, REL_ERROR);
#endif


	printf("\n== mips_mult_f64 check done  == \n\n");

// ==========mips_negate_f64===========

	printf("== mips_negate_f64 test ==  \n");
	mips_negate_f64(f64input1, f64output1, paramCountInput1);
	printf("mips_negate_f64 finish \n");

	printf("mips_negate_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF64, "Reference4_f64.txt");
#else
	referenceFile = BasicMathsF64_Reference4_f64;
	referenceFileLen = sizeof(BasicMathsF64_Reference4_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountInput1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, paramCountInput1, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, paramCountInput1, REL_ERROR);
#endif


	printf("\n== mips_negate_f64 check done  == \n\n");

// ============mips_offset_f64=========

	printf("== mips_offset_f64 test ==  \n");
	mips_offset_f64(f64input1, 0.5L, f64output1, paramCountInput1);
	printf("mips_offset_f64 finish \n");

	printf("mips_offset_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF64, "Reference5_f64.txt");
#else
	referenceFile = BasicMathsF64_Reference5_f64;
	referenceFileLen = sizeof(BasicMathsF64_Reference5_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountInput1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, paramCountInput1, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, paramCountInput1, REL_ERROR);
#endif


	printf("\n== mips_offset_f64 check done  == \n\n");

// ===========mips_scale_f64==========
	
	printf("== mips_scale_f64 test ==  \n");
	mips_scale_f64(f64input1, 0.5L, f64output1, paramCountInput1);
	printf("mips_scale_f64 finish \n");

	printf("mips_scale_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF64, "Reference6_f64.txt");
#else
	referenceFile = BasicMathsF64_Reference6_f64;
	referenceFileLen = sizeof(BasicMathsF64_Reference6_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, 0, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_scale_f64 check done  == \n\n");

// ========mips_dot_prod_f64 2=============

	double f64outputScalar = 0.0;

	printf("== mips_dot_prod_f64 2 test ==  \n");
	mips_dot_prod_f64(f64input1, f64input2, 2, &f64outputScalar);
	printf("mips_dot_prod_f64 2 finish \n");

	printf("mips_dot_prod_f64 2 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF64, "Reference7_f64.txt");
#else
	referenceFile = BasicMathsF64_Reference7_f64;
	referenceFileLen = sizeof(BasicMathsF64_Reference7_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, &f64outputScalar, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, &f64outputScalar, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, &f64outputScalar, 0, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, &f64outputScalar, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_dot_prod_f64 2 check done  == \n\n");

// ==========mips_dot_prod_f64 4N===========

	printf("== mips_dot_prod_f64 4N test ==  \n");
	mips_dot_prod_f64(f64input1, f64input2, 4, &f64outputScalar);
	printf("mips_dot_prod_f64 4N finish \n");

	printf("mips_dot_prod_f64 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF64, "Reference8_f64.txt");
#else
	referenceFile = BasicMathsF64_Reference8_f64;
	referenceFileLen = sizeof(BasicMathsF64_Reference8_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, &f64outputScalar, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, &f64outputScalar, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, &f64outputScalar, 0, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, &f64outputScalar, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_dot_prod_f64 4N check done  == \n\n");

// ========mips_dot_prod_f64 4N+1=============

	printf("== mips_dot_prod_f64 4N+1 test ==  \n");
	mips_dot_prod_f64(f64input1, f64input2, 5, &f64outputScalar);
	printf("mips_dot_prod_f64 4N+1 finish \n");

	printf("mips_dot_prod_f64 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF64, "Reference9_f64.txt");
#else
	referenceFile = BasicMathsF64_Reference9_f64;
	referenceFileLen = sizeof(BasicMathsF64_Reference9_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, &f64outputScalar, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, &f64outputScalar, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, &f64outputScalar, 0, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, &f64outputScalar, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_dot_prod_f64 4N+1 check done  == \n\n");

// ============mips_dot_prod_f64 long=========

	printf("== mips_dot_prod_f64 long test ==  \n");
	mips_dot_prod_f64(f64input1, f64input2, paramCountInput1, &f64outputScalar);
	printf("mips_dot_prod_f64 4N+1 finish \n");

	printf("mips_dot_prod_f64 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF64, "Reference11_f64.txt");
#else
	referenceFile = BasicMathsF64_Reference11_f64;
	referenceFileLen = sizeof(BasicMathsF64_Reference11_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, &f64outputScalar, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, &f64outputScalar, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, &f64outputScalar, 0, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, &f64outputScalar, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_dot_prod_f64 4N+1 check done  == \n\n");

// =========mips_abs_f64============

	printf("== mips_abs_f64 test ==  \n");
	mips_abs_f64(f64input1, f64output1, paramCountInput1);
	printf("mips_abs_f64 finish \n");

	printf("mips_abs_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF64, "Reference10_f64.txt");
#else
	referenceFile = BasicMathsF64_Reference10_f64;
	referenceFileLen = sizeof(BasicMathsF64_Reference10_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountInput1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, paramCountInput1, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, paramCountInput1, REL_ERROR);
#endif


	printf("\n== mips_abs_f64 check done  == \n\n");

// =====================

	return 0;

}