#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/basic_math_functions.h"

#define SNR_THRESHOLD (float)120
#define REL_ERROR (float)(5.0e-5)

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
	float f32input1[MAX_SIZE] = {0};
	float f32input2[MAX_SIZE] = {0};

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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, BasicMathsF32, "Input1_f32.txt");
#else
	inputFile1 = BasicMathsF32_Input1_f32;
	inputFile1Len = sizeof(BasicMathsF32_Input1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, BasicMathsF32, "Input2_f32.txt");
#else
	inputFile2 = BasicMathsF32_Input2_f32;
	inputFile2Len = sizeof(BasicMathsF32_Input2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF32, "Reference1_f32.txt");
#else
	referenceFile = BasicMathsF32_Reference1_f32;
	referenceFileLen = sizeof(BasicMathsF32_Reference1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
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

	float f32output1[MAX_SIZE] = {0};

	printf("== mips_add_f32 test ==  \n");
	mips_add_f32(f32input1, f32input2, f32output1, paramCountInput1);
	printf("mips_add_f32 finish \n");

	printf("mips_add_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, paramCountInput1, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, paramCountInput1, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountInput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_add_f32 check done  == \n\n");

	// for (size_t i = 0; i < paramCountInput1; i++)
	// {
	// 	printf("mips_add_f32 output = %f \n", f32output1[i]);
	// }
	
// =====================

	printf("== mips_sub_f32 test ==  \n");
	mips_sub_f32(f32input1, f32input2, f32output1, paramCountInput1);
	printf("mips_sub_f32 finish \n");

	printf("mips_sub_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF32, "Reference2_f32.txt");
#else
	referenceFile = BasicMathsF32_Reference2_f32;
	referenceFileLen = sizeof(BasicMathsF32_Reference2_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
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


	printf("\n== mips_sub_f32 check done  == \n\n");

// =====================

	printf("== mips_mult_f32 test ==  \n");
	mips_mult_f32(f32input1, f32input2, f32output1, paramCountInput1);
	printf("mips_mult_f32 finish \n");

	printf("mips_mult_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF32, "Reference3_f32.txt");
#else
	referenceFile = BasicMathsF32_Reference3_f32;
	referenceFileLen = sizeof(BasicMathsF32_Reference3_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
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


	printf("\n== mips_mult_f32 check done  == \n\n");

// =====================

	printf("== mips_negate_f32 test ==  \n");
	mips_negate_f32(f32input1, f32output1, paramCountInput1);
	printf("mips_negate_f32 finish \n");

	printf("mips_negate_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF32, "Reference4_f32.txt");
#else
	referenceFile = BasicMathsF32_Reference4_f32;
	referenceFileLen = sizeof(BasicMathsF32_Reference4_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
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


	printf("\n== mips_negate_f32 check done  == \n\n");

// =====================

	printf("== mips_offset_f32 test ==  \n");
	mips_offset_f32(f32input1, 0.5f, f32output1, paramCountInput1);
	printf("mips_offset_f32 finish \n");

	printf("mips_offset_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF32, "Reference5_f32.txt");
#else
	referenceFile = BasicMathsF32_Reference5_f32;
	referenceFileLen = sizeof(BasicMathsF32_Reference5_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
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


	printf("\n== mips_offset_f32 check done  == \n\n");

// =====================
	
	printf("== mips_scale_f32 test ==  \n");
	mips_scale_f32(f32input1, 0.5f, f32output1, paramCountInput1);
	printf("mips_scale_f32 finish \n");

	printf("mips_scale_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF32, "Reference6_f32.txt");
#else
	referenceFile = BasicMathsF32_Reference6_f32;
	referenceFileLen = sizeof(BasicMathsF32_Reference6_f32);
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


	printf("\n== mips_scale_f32 check done  == \n\n");

// =====================

	float f32outputScalar = 0.f;

	printf("== mips_dot_prod_f32 3 test ==  \n");
	mips_dot_prod_f32(f32input1, f32input2, 3, &f32outputScalar);
	printf("mips_dot_prod_f32 3 finish \n");

	printf("mips_dot_prod_f32 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF32, "Reference7_f32.txt");
#else
	referenceFile = BasicMathsF32_Reference7_f32;
	referenceFileLen = sizeof(BasicMathsF32_Reference7_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, &f32outputScalar, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, &f32outputScalar, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, &f32outputScalar, 0, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, &f32outputScalar, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_dot_prod_f32 3 check done  == \n\n");

// =====================

	printf("== mips_dot_prod_f32 4N test ==  \n");
	mips_dot_prod_f32(f32input1, f32input2, 8, &f32outputScalar);
	printf("mips_dot_prod_f32 4N finish \n");

	printf("mips_dot_prod_f32 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF32, "Reference8_f32.txt");
#else
	referenceFile = BasicMathsF32_Reference8_f32;
	referenceFileLen = sizeof(BasicMathsF32_Reference8_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, &f32outputScalar, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, &f32outputScalar, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, &f32outputScalar, 0, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, &f32outputScalar, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_dot_prod_f32 4N check done  == \n\n");

// =====================

	printf("== mips_dot_prod_f32 4N+1 test ==  \n");
	mips_dot_prod_f32(f32input1, f32input2, 11, &f32outputScalar);
	printf("mips_dot_prod_f32 4N+1 finish \n");

	printf("mips_dot_prod_f32 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF32, "Reference9_f32.txt");
#else
	referenceFile = BasicMathsF32_Reference9_f32;
	referenceFileLen = sizeof(BasicMathsF32_Reference9_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, &f32outputScalar, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, &f32outputScalar, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, &f32outputScalar, 0, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, &f32outputScalar, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_dot_prod_f32 4N+1 check done  == \n\n");

// =====================

	printf("== mips_dot_prod_f32 long test ==  \n");
	mips_dot_prod_f32(f32input1, f32input2, paramCountInput1, &f32outputScalar);
	printf("mips_dot_prod_f32 4N+1 finish \n");

	printf("mips_dot_prod_f32 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF32, "Reference11_f32.txt");
#else
	referenceFile = BasicMathsF32_Reference11_f32;
	referenceFileLen = sizeof(BasicMathsF32_Reference11_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, &f32outputScalar, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, &f32outputScalar, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, &f32outputScalar, 0, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, &f32outputScalar, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_dot_prod_f32 4N+1 check done  == \n\n");

// =====================

	printf("== mips_abs_f32 test ==  \n");
	mips_abs_f32(f32input1, f32output1, paramCountInput1);
	printf("mips_abs_f32 finish \n");

	printf("mips_abs_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF32, "Reference10_f32.txt");
#else
	referenceFile = BasicMathsF32_Reference10_f32;
	referenceFileLen = sizeof(BasicMathsF32_Reference10_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
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


	printf("\n== mips_abs_f32 check done  == \n\n");

// =====================

 	int paramCountInput12 = 0;
	float f32input12[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	char inputFile12[255] = {0};
#else
	void *inputFile12;
	int inputFile12Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile12, sizeof(inputFile12), "%s%s%s", Patterns_PATH, BasicMathsF32, "Input12_f32.txt");
#else
	inputFile12 = BasicMathsF32_Input12_f32;
	inputFile12Len = sizeof(BasicMathsF32_Input12_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile12, &paramCountInput12, f32input12);
#else
	paramCountInput12 = inputFile12Len;
	load_data_f32(inputFile12, paramCountInput12, f32input12);
	paramCountInput12 = paramCountInput12/sizeof(f32);
#endif



	printf("== mips_clip_f32 test ==  \n");
	mips_clip_f32(f32input12, f32output1, -0.5f, -0.1f, paramCountInput12);
	printf("mips_clip_f32 finish \n");

	printf("mips_clip_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF32, "Reference12_f32.txt");
#else
	referenceFile = BasicMathsF32_Reference12_f32;
	referenceFileLen = sizeof(BasicMathsF32_Reference12_f32);
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


	printf("\n== mips_clip_f32 check done  == \n\n");

// =====================

	printf("== mips_clip_f32 test ==  \n");
	mips_clip_f32(f32input12, f32output1, -0.5f, 0.5f, paramCountInput12);
	printf("mips_clip_f32 finish \n");

	printf("mips_clip_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF32, "Reference13_f32.txt");
#else
	referenceFile = BasicMathsF32_Reference13_f32;
	referenceFileLen = sizeof(BasicMathsF32_Reference13_f32);
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


	printf("\n== mips_clip_f32 check done  == \n\n");

// =====================

	printf("== mips_clip_f32 test ==  \n");
	mips_clip_f32(f32input12, f32output1, 0.1f, 0.5f, paramCountInput12);
	printf("mips_clip_f32 finish \n");

	printf("mips_clip_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsF32, "Reference14_f32.txt");
#else
	referenceFile = BasicMathsF32_Reference14_f32;
	referenceFileLen = sizeof(BasicMathsF32_Reference14_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
    referenceFileLen =referenceFileLen/sizeof(f32);
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


	printf("\n== mips_clip_f32 check done  == \n\n");

// =====================
	return 0;

}