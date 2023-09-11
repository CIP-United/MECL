#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/basic_math_functions.h"
#define SNR_THRESHOLD 20

#define ABS_ERROR_Q7 ((q7)2)
#define ABS_ERROR_Q31 ((q31)(1<<15))

#define ONEHALF 0x40

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
	q7 q7input1[MAX_SIZE] = {0};
	q7 q7input2[MAX_SIZE] = {0};
    q7 q7input3[MAX_SIZE] = {0};

	int paramCountInput4 = 0;
	int paramCountInput5 = 0;
    int paramCountInput6 = 0;
	q7 q7input4[MAX_SIZE] = {0};
	q7 q7input5[MAX_SIZE] = {0};
    q7 q7input6[MAX_SIZE] = {0};

    int paramCountInputa = 0;
	int paramCountInputb = 0;
	uint8_t u8inputa[MAX_SIZE] = {0};
	uint8_t u8inputb[MAX_SIZE] = {0};

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
	char inputFile5[255] = {0};
#else
	void *inputFile5;
	int inputFile5Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile6[255] = {0};
#else
	void *inputFile6;
	int inputFile6Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char referenceFile[255] = {0};
#else
	void *referenceFile;
	int referenceFileLen = 0;
#endif


#if defined(NOT_EMBEDDED)
	char inputFilea[255] = {0};
#else
	void *inputFilea;
	int inputFileaLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileb[255] = {0};
#else
	void *inputFileb;
	int inputFilebLen = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Input1_q7.txt");
#else
	inputFile1 = BasicMathsQ7_Input1_q7;
	inputFile1Len = sizeof(BasicMathsQ7_Input1_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Input2_q7.txt");
#else
	inputFile2 = BasicMathsQ7_Input2_q7;
	inputFile2Len = sizeof(BasicMathsQ7_Input2_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Input28_q7.txt");
#else
	inputFile3 = BasicMathsQ7_Input28_q7;
	inputFile3Len = sizeof(BasicMathsQ7_Input28_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile4, sizeof(inputFile4), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Input12_q7.txt");
#else
	inputFile4 = BasicMathsQ7_Input12_q7;
	inputFile4Len = sizeof(BasicMathsQ7_Input12_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile5, sizeof(inputFile5), "%s%s%s", Patterns_PATH, BasicMathsQ7, "MaxPosInput12_s8.txt");
#else
	inputFile5 = BasicMathsQ7_MaxPosInput12_s8;
	inputFile5Len = sizeof(BasicMathsQ7_MaxPosInput12_s8);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile6, sizeof(inputFile6), "%s%s%s", Patterns_PATH, BasicMathsQ7, "MaxNegInput12_s8.txt");
#else
	inputFile6 = BasicMathsQ7_MaxNegInput12_s8;
	inputFile6Len = sizeof(BasicMathsQ7_MaxNegInput12_s8);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Reference1_q7.txt");
#else
	referenceFile = BasicMathsQ7_Reference1_q7;
	referenceFileLen = sizeof(BasicMathsQ7_Reference1_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFilea, sizeof(inputFilea), "%s%s%s", Patterns_PATH, BasicMathsQ7, "BitwiseInput24_s8.txt");
#else
	inputFilea = BasicMathsQ7_BitwiseInput24_s8;
	inputFileaLen = sizeof(BasicMathsQ7_BitwiseInput24_s8);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb, sizeof(inputFileb), "%s%s%s", Patterns_PATH, BasicMathsQ7, "BitwiseInput25_s8.txt");
#else
	inputFileb = BasicMathsQ7_BitwiseInput25_s8;
	inputFilebLen = sizeof(BasicMathsQ7_BitwiseInput25_s8);
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
	load_data_q7(inputFile3, &paramCountInput3, q7input3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_q7(inputFile3, paramCountInput3, q7input3);
	paramCountInput3 = paramCountInput3/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q7(inputFile4, &paramCountInput4, q7input4);
#else
	paramCountInput4 = inputFile4Len;
	load_data_q7(inputFile4, paramCountInput4, q7input4);
	paramCountInput4 = paramCountInput4/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q7(inputFile5, &paramCountInput5, q7input5);
#else
	paramCountInput5 = inputFile5Len;
	load_data_q7(inputFile5, paramCountInput5, q7input5);
	paramCountInput5 = paramCountInput5/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q7(inputFile6, &paramCountInput6, q7input6);
#else
	paramCountInput6 = inputFile6Len;
	load_data_q7(inputFile6, paramCountInput6, q7input6);
	paramCountInput6 = paramCountInput6/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	load_data_u8(inputFilea, &paramCountInputa, u8inputa);
#else
	paramCountInputa = inputFileaLen;
	load_data_u8(inputFilea, paramCountInputa, u8inputa);
	paramCountInputa = paramCountInputa/sizeof(uint8_t);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u8(inputFileb, &paramCountInputb, u8inputb);
#else
	paramCountInputb = inputFilebLen;
	load_data_u8(inputFileb, paramCountInputb, u8inputb);
	paramCountInputb = paramCountInputb/sizeof(uint8_t);
#endif

	
    q7 q7output1[MAX_SIZE] = {0};

	printf("== mips_add_q7 test ==  \n");

	mips_add_q7(q7input1, q7input2, q7output1, paramCountInput1);
	printf("mips_add_q7 finish \n");

	printf("mips_add_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, paramCountInput1, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, paramCountInput1, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, paramCountInput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_add_q7 check done  == \n\n");


// =====================

	printf("== mips_sub_q7 test ==  \n");
	mips_sub_q7(q7input1, q7input2, q7output1, paramCountInput1);
	printf("mips_sub_q7 finish \n");

	printf("mips_sub_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Reference2_q7.txt");
#else
	referenceFile = BasicMathsQ7_Reference2_q7;
	referenceFileLen = sizeof(BasicMathsQ7_Reference2_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, paramCountInput1, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, paramCountInput1, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, paramCountInput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_sub_q7 check done  == \n\n");

// =====================

	printf("== mips_mult_q7 test ==  \n");
	mips_mult_q7(q7input1, q7input2, q7output1, paramCountInput1);
	printf("mips_mult_q7 finish \n");

	printf("mips_mult_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Reference3_q7.txt");
#else
	referenceFile = BasicMathsQ7_Reference3_q7;
	referenceFileLen = sizeof(BasicMathsQ7_Reference3_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, paramCountInput1, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, paramCountInput1, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, paramCountInput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_mult_q7 check done  == \n\n");

// =====================

	printf("== mips_negate_q7 test ==  \n");
	mips_negate_q7(q7input1, q7output1, paramCountInput1);
	printf("mips_negate_q7 finish \n");

	printf("mips_negate_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Reference4_q7.txt");
#else
	referenceFile = BasicMathsQ7_Reference4_q7;
	referenceFileLen = sizeof(BasicMathsQ7_Reference4_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, paramCountInput1, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, paramCountInput1, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, paramCountInput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_negate_q7 check done  == \n\n");

// =====================

	printf("== mips_offset_q7 test ==  \n");
	mips_offset_q7(q7input6, 0x8d, q7output1, paramCountInput6);
	printf("mips_offset_q7 finish \n");

	printf("mips_offset_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "NegSat19_q7.txt");
#else
	referenceFile = BasicMathsQ7_NegSat19_q7;
	referenceFileLen = sizeof(BasicMathsQ7_NegSat19_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
	referenceFileLen = referenceFileLen/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, referenceFileLen, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_offset_q7 check done  == \n\n");

// =====================

	printf("== mips_offset_q7 test ==  \n");
	mips_offset_q7(q7input5, 0x73, q7output1, paramCountInput5);
	printf("mips_offset_q7 finish \n");

	printf("mips_offset_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "PosSat18_q7.txt");
#else
	referenceFile = BasicMathsQ7_PosSat18_q7;
	referenceFileLen = sizeof(BasicMathsQ7_PosSat18_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
	referenceFileLen = referenceFileLen/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, referenceFileLen, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_offset_q7 check done  == \n\n");

// =====================

	printf("== mips_offset_q7 test ==  \n");
	mips_offset_q7(q7input1, ONEHALF, q7output1, paramCountInput1);
	printf("mips_offset_q7 finish \n");

	printf("mips_offset_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Reference5_q7.txt");
#else
	referenceFile = BasicMathsQ7_Reference5_q7;
	referenceFileLen = sizeof(BasicMathsQ7_Reference5_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
	referenceFileLen = referenceFileLen/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, referenceFileLen, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_offset_q7 check done  == \n\n");

// =====================

	printf("== mips_scale_q7 test ==  \n");
	mips_scale_q7(q7input1, ONEHALF, 0, q7output1, paramCountInput1);
	printf("mips_scale_q7 finish \n");

	printf("mips_scale_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Reference6_q7.txt");
#else
	referenceFile = BasicMathsQ7_Reference6_q7;
	referenceFileLen = sizeof(BasicMathsQ7_Reference6_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
	referenceFileLen = referenceFileLen/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, referenceFileLen, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_scale_q7 check done  == \n\n");


// =====================

	printf("== mips_scale_q7 test ==  \n");
	mips_scale_q7(q7input6, 0x80, 0, q7output1, paramCountInput6);
	printf("mips_scale_q7 finish \n");

	printf("mips_scale_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "PosSat20_q7.txt");
#else
	referenceFile = BasicMathsQ7_PosSat20_q7;
	referenceFileLen = sizeof(BasicMathsQ7_PosSat20_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
	referenceFileLen = referenceFileLen/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, referenceFileLen, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_scale_q7 check done  == \n\n");

// =====================

    q31 q31output1[MAX_SIZE] = {0};
	printf("== mips_dot_prod_q7 15 test ==  \n");
	mips_dot_prod_q7(q7input1, q7input2, 15, q31output1);
	printf("mips_dot_prod_q7 15 finish \n");

	printf("mips_dot_prod_q7 15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Reference7_q31.txt");
#else
	referenceFile = BasicMathsQ7_Reference7_q31;
	referenceFileLen = sizeof(BasicMathsQ7_Reference7_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 1, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 1, ABS_ERROR_Q31);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 1, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 1, SNR_THRESHOLD);
#endif


	printf("\n== mips_dot_prod_q7 15 check done  == \n\n");

// =====================

	printf("== mips_dot_prod_q7 4N test ==  \n");
	mips_dot_prod_q7(q7input1, q7input2, 32, q31output1);
	printf("mips_dot_prod_q7 4N finish \n");

	printf("mips_dot_prod_q7 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Reference8_q31.txt");
#else
	referenceFile = BasicMathsQ7_Reference8_q31;
	referenceFileLen = sizeof(BasicMathsQ7_Reference8_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 1, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 1, ABS_ERROR_Q31);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 1, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 1, SNR_THRESHOLD);
#endif


	printf("\n== mips_dot_prod_q7 4N check done  == \n\n");

// =====================

	printf("== mips_dot_prod_q7 4N+1 test ==  \n");
	mips_dot_prod_q7(q7input1, q7input2, 47, q31output1);
	printf("mips_dot_prod_q7 4N+1 finish \n");

	printf("mips_dot_prod_q7 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Reference9_q31.txt");
#else
	referenceFile = BasicMathsQ7_Reference9_q31;
	referenceFileLen = sizeof(BasicMathsQ7_Reference9_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 1, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, 1, ABS_ERROR_Q31);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 1, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 1, SNR_THRESHOLD);
#endif


	printf("\n== mips_dot_prod_q7 4N+1 check done  == \n\n");

// =====================

	printf("== mips_dot_prod_q7 long test ==  \n");
	mips_dot_prod_q7(q7input1, q7input2, paramCountInput1, q31output1);
	printf("mips_dot_prod_q7 long finish \n");

	printf("mips_dot_prod_q7 long checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Reference11_q31.txt");
#else
	referenceFile = BasicMathsQ7_Reference11_q31;
	referenceFileLen = sizeof(BasicMathsQ7_Reference11_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 0, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFileLen, ABS_ERROR_Q31);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_dot_prod_q7 long check done  == \n\n");

// =====================

	printf("== mips_abs_q7 test ==  \n");
	mips_abs_q7(q7input1, q7output1, paramCountInput1);
	printf("mips_abs_q7 finish \n");

	printf("mips_abs_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Reference10_q7.txt");
#else
	referenceFile = BasicMathsQ7_Reference10_q7;
	referenceFileLen = sizeof(BasicMathsQ7_Reference10_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
	referenceFileLen = referenceFileLen/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, referenceFileLen, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_abs_q7 check done  == \n\n");

// =====================


	printf("== mips_shift_q7 test ==  \n");
	mips_shift_q7(q7input4, 1, q7output1, paramCountInput4);
	printf("mips_shift_q7 finish \n");

	printf("mips_shift_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Shift21_q7.txt");
#else
	referenceFile = BasicMathsQ7_Shift21_q7;
	referenceFileLen = sizeof(BasicMathsQ7_Shift21_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
	referenceFileLen = referenceFileLen/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, referenceFileLen, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_shift_q7 check done  == \n\n");

// =====================


	printf("== mips_shift_q7 test ==  \n");
	mips_shift_q7(q7input5, 1, q7output1, paramCountInput5);
	printf("mips_shift_q7 finish \n");

	printf("mips_shift_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Shift22_q7.txt");
#else
	referenceFile = BasicMathsQ7_Shift22_q7;
	referenceFileLen = sizeof(BasicMathsQ7_Shift22_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
	referenceFileLen = referenceFileLen/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, referenceFileLen, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_shift_q7 check done  == \n\n");

// =====================


	printf("== mips_shift_q7 test ==  \n");
	mips_shift_q7(q7input6, 1, q7output1, paramCountInput6);
	printf("mips_shift_q7 finish \n");

	printf("mips_shift_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Shift23_q7.txt");
#else
	referenceFile = BasicMathsQ7_Shift23_q7;
	referenceFileLen = sizeof(BasicMathsQ7_Shift23_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
	referenceFileLen = referenceFileLen/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, referenceFileLen, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_shift_q7 check done  == \n\n");

// =====================

	printf("== mips_clip_q7 test ==  \n");
	mips_clip_q7(q7input3, q7output1, 0xC0, 0xF3, paramCountInput3);
	printf("mips_clip_q7 finish \n");

	printf("mips_clip_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Reference28_q7.txt");
#else
	referenceFile = BasicMathsQ7_Reference28_q7;
	referenceFileLen = sizeof(BasicMathsQ7_Reference28_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
	referenceFileLen = referenceFileLen/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, referenceFileLen, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_clip_q7 check done  == \n\n");


// =====================

	printf("== mips_clip_q7 test ==  \n");
	mips_clip_q7(q7input3, q7output1, 0xC0, 0x40, paramCountInput3);
	printf("mips_clip_q7 finish \n");

	printf("mips_clip_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Reference29_q7.txt");
#else
	referenceFile = BasicMathsQ7_Reference29_q7;
	referenceFileLen = sizeof(BasicMathsQ7_Reference29_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
	referenceFileLen = referenceFileLen/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, referenceFileLen, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_clip_q7 check done  == \n\n");


// =====================

 	printf("== mips_clip_q7 test ==  \n");
	mips_clip_q7(q7input3, q7output1, 0x0D, 0x40, paramCountInput3);
	printf("mips_clip_q7 finish \n");

	printf("mips_clip_q7 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Reference30_q7.txt");
#else
	referenceFile = BasicMathsQ7_Reference30_q7;
	referenceFileLen = sizeof(BasicMathsQ7_Reference30_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
	referenceFileLen = referenceFileLen/sizeof(q7);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile, q7output1, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, referenceFileLen, ABS_ERROR_Q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile, q7output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_clip_q7 check done  == \n\n");



// =====================

    uint8_t u8output1[MAX_SIZE] = {0};
	printf("== mips_and_u8 3 test ==  \n");
	mips_and_u8(u8inputa, u8inputb, u8output1, 15);
	printf("mips_and_u8 3 finish \n");

	printf("mips_and_u8 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "And24_s8.txt");
#else
	referenceFile = BasicMathsQ7_And24_s8;
	referenceFileLen = sizeof(BasicMathsQ7_And24_s8);
	load_data_u8(referenceFile, referenceFileLen, referenceData_u8);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u8(referenceFile, u8output1, 15);
#else
	eq_check_special_u8(referenceData_u8, u8output1, 15);
#endif


	printf("\n== mips_and_u8 3 check done  == \n\n");


// =====================

	printf("== mips_and_u8 4N test ==  \n");
	mips_and_u8(u8inputa, u8inputb, u8output1, 32);
	printf("mips_and_u8 4N finish \n");

	printf("mips_and_u8 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "And24_s8.txt");
#else
	referenceFile = BasicMathsQ7_And24_s8;
	referenceFileLen = sizeof(BasicMathsQ7_And24_s8);
	load_data_u8(referenceFile, referenceFileLen, referenceData_u8);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u8(referenceFile, u8output1, 32);
#else
	eq_check_special_u8(referenceData_u8, u8output1, 32);
#endif


	printf("\n== mips_and_u8 4N check done  == \n\n");

// =====================

	printf("== mips_and_u8 4N+1 test ==  \n");
	mips_and_u8(u8inputa, u8inputb, u8output1, 47);
	printf("mips_and_u8 4N+1 finish \n");

	printf("mips_and_u8 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "And24_s8.txt");
#else
	referenceFile = BasicMathsQ7_And24_s8;
	referenceFileLen = sizeof(BasicMathsQ7_And24_s8);
	load_data_u8(referenceFile, referenceFileLen, referenceData_u8);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u8(referenceFile, u8output1, 47);
#else
	eq_check_special_u8(referenceData_u8, u8output1, 47);
#endif


	printf("\n== mips_and_u8 4N+1 check done  == \n\n");

// =====================

	printf("== mips_or_u8 3 test ==  \n");
	mips_or_u8(u8inputa, u8inputb, u8output1, 15);
	printf("mips_or_u8 3 finish \n");

	printf("mips_or_u8 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Or25_s8.txt");
#else
	referenceFile = BasicMathsQ7_Or25_s8;
	referenceFileLen = sizeof(BasicMathsQ7_Or25_s8);
	load_data_u8(referenceFile, referenceFileLen, referenceData_u8);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u8(referenceFile, u8output1, 15);
#else
	eq_check_special_u8(referenceData_u8, u8output1, 15);
#endif


	printf("\n== mips_or_u8 3 check done  == \n\n");

// =====================

	printf("== mips_or_u8 4N test ==  \n");
	mips_or_u8(u8inputa, u8inputb, u8output1, 32);
	printf("mips_or_u8 4N finish \n");

	printf("mips_or_u8 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Or25_s8.txt");
#else
	referenceFile = BasicMathsQ7_Or25_s8;
	referenceFileLen = sizeof(BasicMathsQ7_Or25_s8);
	load_data_u8(referenceFile, referenceFileLen, referenceData_u8);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u8(referenceFile, u8output1, 32);
#else
	eq_check_special_u8(referenceData_u8, u8output1, 32);
#endif


	printf("\n== mips_or_u8 4N check done  == \n\n");


// =====================

	printf("== mips_or_u8 4N+1 test ==  \n");
	mips_or_u8(u8inputa, u8inputb, u8output1, 47);
	printf("mips_or_u8 4N+1 finish \n");

	printf("mips_or_u8 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Or25_s8.txt");
#else
	referenceFile = BasicMathsQ7_Or25_s8;
	referenceFileLen = sizeof(BasicMathsQ7_Or25_s8);
	load_data_u8(referenceFile, referenceFileLen, referenceData_u8);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u8(referenceFile, u8output1, 47);
#else
	eq_check_special_u8(referenceData_u8, u8output1, 47);
#endif


	printf("\n== mips_or_u8 4N+1 check done  == \n\n");

// =====================

	printf("== mips_not_u8 3 test ==  \n");
	mips_not_u8(u8inputa, u8output1, 15);
	printf("mips_not_u8 3 finish \n");

	printf("mips_not_u8 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Not26_s8.txt");
#else
	referenceFile = BasicMathsQ7_Not26_s8;
	referenceFileLen = sizeof(BasicMathsQ7_Not26_s8);
	load_data_u8(referenceFile, referenceFileLen, referenceData_u8);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u8(referenceFile, u8output1, 15);
#else
	eq_check_special_u8(referenceData_u8, u8output1, 15);
#endif


	printf("\n== mips_not_u8 3 check done  == \n\n");

// =====================

	printf("== mips_not_u8 4N test ==  \n");
	mips_not_u8(u8inputa, u8output1, 32);
	printf("mips_not_u8 4N finish \n");

	printf("mips_not_u8 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Not26_s8.txt");
#else
	referenceFile = BasicMathsQ7_Not26_s8;
	referenceFileLen = sizeof(BasicMathsQ7_Not26_s8);
	load_data_u8(referenceFile, referenceFileLen, referenceData_u8);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u8(referenceFile, u8output1, 32);
#else
	eq_check_special_u8(referenceData_u8, u8output1, 32);
#endif


	printf("\n== mips_not_u8 4N check done  == \n\n");

// =====================

	printf("== mips_not_u8 4N+1 test ==  \n");
	mips_not_u8(u8inputa, u8output1, 47);
	printf("mips_not_u8 4N+1 finish \n");

	printf("mips_not_u8 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Not26_s8.txt");
#else
	referenceFile = BasicMathsQ7_Not26_s8;
	referenceFileLen = sizeof(BasicMathsQ7_Not26_s8);
	load_data_u8(referenceFile, referenceFileLen, referenceData_u8);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u8(referenceFile, u8output1, 47);
#else
	eq_check_special_u8(referenceData_u8, u8output1, 47);
#endif


	printf("\n== mips_not_u8 4N+1 check done  == \n\n");

// =====================

 	printf("== mips_xor_u8 3 test ==  \n");
	mips_xor_u8(u8inputa, u8inputb, u8output1, 15);
	printf("mips_xor_u8 3 finish \n");

	printf("mips_xor_u8 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Xor27_s8.txt");
#else
	referenceFile = BasicMathsQ7_Xor27_s8;
	referenceFileLen = sizeof(BasicMathsQ7_Xor27_s8);
	load_data_u8(referenceFile, referenceFileLen, referenceData_u8);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u8(referenceFile, u8output1, 15);
#else
	eq_check_special_u8(referenceData_u8, u8output1, 15);
#endif


	printf("\n== mips_xor_u8 3 check done  == \n\n"); 

// =====================

 	printf("== mips_xor_u8 4N test ==  \n");
	mips_xor_u8(u8inputa, u8inputb, u8output1, 32);
	printf("mips_xor_u8 4N finish \n");

	printf("mips_xor_u8 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Xor27_s8.txt");
#else
	referenceFile = BasicMathsQ7_Xor27_s8;
	referenceFileLen = sizeof(BasicMathsQ7_Xor27_s8);
	load_data_u8(referenceFile, referenceFileLen, referenceData_u8);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u8(referenceFile, u8output1, 32);
#else
	eq_check_special_u8(referenceData_u8, u8output1, 32);
#endif


	printf("\n== mips_xor_u8 4N check done  == \n\n"); 

// =====================

 	printf("== mips_xor_u8 4N+1 test ==  \n");
	mips_xor_u8(u8inputa, u8inputb, u8output1, 47);
	printf("mips_xor_u8 4N+1 finish \n");

	printf("mips_xor_u8 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ7, "Xor27_s8.txt");
#else
	referenceFile = BasicMathsQ7_Xor27_s8;
	referenceFileLen = sizeof(BasicMathsQ7_Xor27_s8);
	load_data_u8(referenceFile, referenceFileLen, referenceData_u8);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u8(referenceFile, u8output1, 47);
#else
	eq_check_special_u8(referenceData_u8, u8output1, 47);
#endif


	printf("\n== mips_xor_u8 4N+1 check done  == \n\n"); 

// =====================

	return 0;
}