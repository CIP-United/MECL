#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/basic_math_functions.h"

#define SNR_THRESHOLD 70
#define ABS_ERROR_Q15 ((q15)2)
#define ABS_ERROR_Q63 ((q63)(1<<17))
#define MULT_SNR_THRESHOLD 60
#define ONEHALF 0x4000

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
    int paramCountInput28 = 0;
	q15 q15input1[MAX_SIZE] = {0};
	q15 q15input2[MAX_SIZE] = {0};
    q15 q15input3[MAX_SIZE] = {0};
    q15 q15input28[MAX_SIZE] = {0};

	int paramCountInput4 = 0;
	int paramCountInput5 = 0;
	int paramCountInput6 = 0;
	q15 q15input4[MAX_SIZE] = {0};
	q15 q15input5[MAX_SIZE] = {0};
	q15 q15input6[MAX_SIZE] = {0};

    int paramCountInputa = 0;
	int paramCountInputb = 0;
	uint16_t u16inputa[MAX_SIZE] = {0};
	uint16_t u16inputb[MAX_SIZE] = {0};

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
	char inputFile28[255] = {0};
#else
	void *inputFile28;
	int inputFile28Len = 0;
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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Input1_q15.txt");
#else
	inputFile1 = BasicMathsQ15_Input1_q15;
	inputFile1Len = sizeof(BasicMathsQ15_Input1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Input2_q15.txt");
#else
	inputFile2 = BasicMathsQ15_Input2_q15;
	inputFile2Len = sizeof(BasicMathsQ15_Input2_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Input12_q15.txt");
#else
	inputFile3 = BasicMathsQ15_Input12_q15;
	inputFile3Len = sizeof(BasicMathsQ15_Input12_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile28, sizeof(inputFile28), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Input28_q15.txt");
#else
	inputFile28 = BasicMathsQ15_Input28_q15;
	inputFile28Len = sizeof(BasicMathsQ15_Input28_q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile4, sizeof(inputFile4), "%s%s%s", Patterns_PATH, BasicMathsQ15, "MaxPosInput12_s16.txt");
#else
	inputFile4 = BasicMathsQ15_MaxPosInput12_s16;
	inputFile4Len = sizeof(BasicMathsQ15_MaxPosInput12_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile5, sizeof(inputFile5), "%s%s%s", Patterns_PATH, BasicMathsQ15, "MaxNegInput12_s16.txt");
#else
	inputFile5 = BasicMathsQ15_MaxNegInput12_s16;
	inputFile5Len = sizeof(BasicMathsQ15_MaxNegInput12_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile6, sizeof(inputFile6), "%s%s%s", Patterns_PATH, BasicMathsQ15, "MaxNeg2Input12_s16.txt");
#else
	inputFile6 = BasicMathsQ15_MaxNeg2Input12_s16;
	inputFile6Len = sizeof(BasicMathsQ15_MaxNeg2Input12_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea, sizeof(inputFilea), "%s%s%s", Patterns_PATH, BasicMathsQ15, "BitwiseInput24_s16.txt");
#else
	inputFilea = BasicMathsQ15_BitwiseInput24_s16;
	inputFileaLen = sizeof(BasicMathsQ15_BitwiseInput24_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb, sizeof(inputFileb), "%s%s%s", Patterns_PATH, BasicMathsQ15, "BitwiseInput25_s16.txt");
#else
	inputFileb = BasicMathsQ15_BitwiseInput25_s16;
	inputFilebLen = sizeof(BasicMathsQ15_BitwiseInput25_s16);
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

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile28, &paramCountInput28, q15input28);
#else
	paramCountInput28 = inputFile28Len;
	load_data_q15(inputFile28, paramCountInput28, q15input28);
	paramCountInput28 = paramCountInput28/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile4, &paramCountInput4, q15input4);
#else
	paramCountInput4 = inputFile4Len;
	load_data_q15(inputFile4, paramCountInput4, q15input4);
	paramCountInput4 = paramCountInput4/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile5, &paramCountInput5, q15input5);
#else
	paramCountInput5 = inputFile5Len;
	load_data_q15(inputFile5, paramCountInput5, q15input5);
	paramCountInput5 = paramCountInput5/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile6, &paramCountInput6, q15input6);
#else
	paramCountInput6 = inputFile6Len;
	load_data_q15(inputFile6, paramCountInput6, q15input6);
	paramCountInput6 = paramCountInput6/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(inputFilea, &paramCountInputa, u16inputa);
#else
	paramCountInputa = inputFileaLen;
	load_data_u16(inputFilea, paramCountInputa, u16inputa);
	paramCountInputa = paramCountInputa/sizeof(uint16_t);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(inputFileb, &paramCountInputb, u16inputb);
#else
	paramCountInputb = inputFilebLen;
	load_data_u16(inputFileb, paramCountInputb, u16inputb);
	paramCountInputb = paramCountInputb/sizeof(uint16_t);
#endif

	q15 q15output1[MAX_SIZE] = {0};
	uint16_t u16output1[MAX_SIZE] = {0};

	printf("== mips_add_q15 test ==  \n");
	mips_add_q15(q15input1, q15input2, q15output1, paramCountInput1);
	printf("mips_add_q15 finish \n");

	printf("mips_add_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Reference1_q15.txt");
#else
	referenceFile = BasicMathsQ15_Reference1_q15;
	referenceFileLen = sizeof(BasicMathsQ15_Reference1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, paramCountInput1, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, paramCountInput1, ABS_ERROR_Q15);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, paramCountInput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_add_q15 check done  == \n\n");

	// for (size_t i = 0; i < paramCountInput1; i++)
	// {
	// 	printf("mips_add_q15 output = %f \n", q15output1[i]);
	// }
	
// =====================

	printf("== mips_sub_q15 test ==  \n");
	mips_sub_q15(q15input1, q15input2, q15output1, paramCountInput1);
	printf("mips_sub_q15 finish \n");

	printf("mips_sub_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Reference2_q15.txt");
#else
	referenceFile = BasicMathsQ15_Reference2_q15;
	referenceFileLen = sizeof(BasicMathsQ15_Reference2_q15);
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


	printf("\n== mips_sub_q15 check done  == \n\n");

// =====================

	printf("== mips_mult_q15 test ==  \n");
	mips_mult_q15(q15input1, q15input2, q15output1, paramCountInput1);
	printf("mips_mult_q15 finish \n");

	printf("mips_mult_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Reference3_q15.txt");
#else
	referenceFile = BasicMathsQ15_Reference3_q15;
	referenceFileLen = sizeof(BasicMathsQ15_Reference3_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, paramCountInput1, MULT_SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, paramCountInput1, MULT_SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, paramCountInput1, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, paramCountInput1, ABS_ERROR_Q15);
#endif


	printf("\n== mips_mult_q15 check done  == \n\n");

// =====================

	printf("== mips_negate_q15 test ==  \n");
	mips_negate_q15(q15input1, q15output1, paramCountInput1);
	printf("mips_negate_q15 finish \n");

	printf("mips_negate_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Reference4_q15.txt");
#else
	referenceFile = BasicMathsQ15_Reference4_q15;
	referenceFileLen = sizeof(BasicMathsQ15_Reference4_q15);
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


	printf("\n== mips_negate_q15 check done  == \n\n");

// =====================

	printf("== mips_offset_q15 test ==  \n");
	mips_offset_q15(q15input1, 0x4000, q15output1, paramCountInput1);
	printf("mips_offset_q15 finish \n");

	printf("mips_offset_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Reference5_q15.txt");
#else
	referenceFile = BasicMathsQ15_Reference5_q15;
	referenceFileLen = sizeof(BasicMathsQ15_Reference5_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
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


	printf("\n== mips_offset_q15 check done  == \n\n");

// =====================

 	printf("== mips_offset_q15 test ==  \n");
	mips_offset_q15(q15input5, 0x8ccd, q15output1, paramCountInput5);
	printf("mips_offset_q15 finish \n");

	printf("mips_offset_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "NegSat19_q15.txt");
#else
	referenceFile = BasicMathsQ15_NegSat19_q15;
	referenceFileLen = sizeof(BasicMathsQ15_NegSat19_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, ABS_ERROR_Q15);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_offset_q15 check done  == \n\n"); 

// =====================

 	printf("== mips_offset_q15 test ==  \n");
	mips_offset_q15(q15input4, 0x7333, q15output1, paramCountInput4);
	printf("mips_offset_q15 finish \n");

	printf("mips_offset_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "PosSat18_q15.txt");
#else
	referenceFile = BasicMathsQ15_PosSat18_q15;
	referenceFileLen = sizeof(BasicMathsQ15_PosSat18_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, ABS_ERROR_Q15);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_offset_q15 check done  == \n\n"); 

// =====================

	printf("== mips_scale_q15 test ==  \n");
	mips_scale_q15(q15input1, 0x4000, 0, q15output1, paramCountInput1);
	printf("mips_scale_q15 finish \n");

	printf("mips_scale_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Reference6_q15.txt");
#else
	referenceFile = BasicMathsQ15_Reference6_q15;
	referenceFileLen = sizeof(BasicMathsQ15_Reference6_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
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


	printf("\n== mips_scale_q15 check done  == \n\n");

// =====================

 	printf("== mips_scale_q15 test ==  \n");
	mips_scale_q15(q15input6, 0x8000, 0, q15output1, paramCountInput6);
	printf("mips_scale_q15 finish \n");

	printf("mips_scale_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "PosSat20_q15.txt");
#else
	referenceFile = BasicMathsQ15_PosSat20_q15;
	referenceFileLen = sizeof(BasicMathsQ15_PosSat20_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, ABS_ERROR_Q15);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_scale_q15 check done  == \n\n"); 

// =====================


    q63 q63output1[MAX_SIZE] = {0}; 

	printf("== mips_dot_prod_q15 3 test ==  \n");
	mips_dot_prod_q15(q15input1, q15input2, 7, q63output1);
    printf("mips_dot_prod_q15 3 finish \n");

	printf("mips_dot_prod_q15 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Reference7_q63.txt");
#else
	referenceFile = BasicMathsQ15_Reference7_q63;
	referenceFileLen = sizeof(BasicMathsQ15_Reference7_q63);
	load_data_q63(referenceFile, referenceFileLen, referenceData_q63);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q63(referenceFile, q63output1, 1, MULT_SNR_THRESHOLD);
#else
	snr_check_special_q63(referenceData_q63, q63output1, 1, MULT_SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q63(referenceFile, q63output1, 1, ABS_ERROR_Q63);
#else
	near_check_special_q63(referenceData_q63, q63output1, 1, ABS_ERROR_Q63);
#endif


	printf("\n== mips_dot_prod_q15 3 check done  == \n\n");

// =====================

	printf("== mips_dot_prod_q15 4N test ==  \n");
	mips_dot_prod_q15(q15input1, q15input2, 16, q63output1);
	printf("mips_dot_prod_q15 4N finish \n");

	printf("mips_dot_prod_q15 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Reference8_q63.txt");
#else
	referenceFile = BasicMathsQ15_Reference8_q63;
	referenceFileLen = sizeof(BasicMathsQ15_Reference8_q63);
	load_data_q63(referenceFile, referenceFileLen, referenceData_q63);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q63(referenceFile, q63output1, 1, MULT_SNR_THRESHOLD);
#else
	snr_check_special_q63(referenceData_q63, q63output1, 1, MULT_SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q63(referenceFile, q63output1, 1, ABS_ERROR_Q63);
#else
	near_check_special_q63(referenceData_q63, q63output1, 1, ABS_ERROR_Q63);
#endif


	printf("\n== mips_dot_prod_q15 4N check done  == \n\n");

// =====================

	printf("== mips_dot_prod_q15 4N+1 test ==  \n");
	mips_dot_prod_q15(q15input1, q15input2, 23, q63output1);
	printf("mips_dot_prod_q15 4N+1 finish \n");

	printf("mips_dot_prod_q15 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Reference9_q63.txt");
#else
	referenceFile = BasicMathsQ15_Reference9_q63;
	referenceFileLen = sizeof(BasicMathsQ15_Reference9_q63);
	load_data_q63(referenceFile, referenceFileLen, referenceData_q63);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q63(referenceFile, q63output1, 1, MULT_SNR_THRESHOLD);
#else
	snr_check_special_q63(referenceData_q63, q63output1, 1, MULT_SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q63(referenceFile, q63output1, 1, ABS_ERROR_Q63);
#else
	near_check_special_q63(referenceData_q63, q63output1, 1, ABS_ERROR_Q63);
#endif


	printf("\n== mips_dot_prod_q15 4N+1 check done  == \n\n");

// =====================

	printf("== mips_dot_prod_q15 long test ==  \n");
	mips_dot_prod_q15(q15input1, q15input2, paramCountInput1, q63output1);
	printf("mips_dot_prod_q15 4N+1 finish \n");

	printf("mips_dot_prod_q15 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Reference11_q63.txt");
#else
	referenceFile = BasicMathsQ15_Reference11_q63;
	referenceFileLen = sizeof(BasicMathsQ15_Reference11_q63);
	load_data_q63(referenceFile, referenceFileLen, referenceData_q63);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q63(referenceFile, q63output1, 0, MULT_SNR_THRESHOLD);
#else
	snr_check_special_q63(referenceData_q63, q63output1, referenceFileLen, MULT_SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q63(referenceFile, q63output1, 0, ABS_ERROR_Q63);
#else
	near_check_special_q63(referenceData_q63, q63output1, referenceFileLen, ABS_ERROR_Q63);
#endif


	printf("\n== mips_dot_prod_q15 4N+1 check done  == \n\n");

// =====================

	printf("== mips_abs_q15 test ==  \n");
	mips_abs_q15(q15input1, q15output1, paramCountInput1);
	printf("mips_abs_q15 finish \n");

	printf("mips_abs_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Reference10_q15.txt");
#else
	referenceFile = BasicMathsQ15_Reference10_q15;
	referenceFileLen = sizeof(BasicMathsQ15_Reference10_q15);
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


	printf("\n== mips_abs_q15 check done  == \n\n");

// =====================
	printf("== mips_shift_q15 test ==  \n");
	mips_shift_q15(q15input3, 1, q15output1, paramCountInput3);
	printf("mips_shift_q15 finish \n");

	printf("mips_shift_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Shift21_q15.txt");
#else
	referenceFile = BasicMathsQ15_Shift21_q15;
	referenceFileLen = sizeof(BasicMathsQ15_Shift21_q15);
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


	printf("\n== mips_shift_q15 check done  == \n\n");

// =====================


	printf("== mips_shift_q15 test ==  \n");
	mips_shift_q15(q15input4, 1, q15output1, paramCountInput4);
	printf("mips_shift_q15 finish \n");

	printf("mips_shift_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Shift22_q15.txt");
#else
	referenceFile = BasicMathsQ15_Shift22_q15;
	referenceFileLen = sizeof(BasicMathsQ15_Shift22_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = referenceFileLen/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, ABS_ERROR_Q15);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_shift_q15 check done  == \n\n");

// =====================


	printf("== mips_shift_q15 test ==  \n");
	mips_shift_q15(q15input5, 1, q15output1, paramCountInput5);
	printf("mips_shift_q15 finish \n");

	printf("mips_shift_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Shift23_q15.txt");
#else
	referenceFile = BasicMathsQ15_Shift23_q15;
	referenceFileLen = sizeof(BasicMathsQ15_Shift23_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = referenceFileLen/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, ABS_ERROR_Q15);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_shift_q15 check done  == \n\n");

// =====================
	
	printf("== mips_and_u16 3 test ==  \n");
	mips_and_u16(u16inputa, u16inputb, u16output1, 7);
	printf("mips_and_u16 3 finish \n");

	printf("mips_and_u16 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "And24_s16.txt");
#else
	referenceFile = BasicMathsQ15_And24_s16;
	referenceFileLen = sizeof(BasicMathsQ15_And24_s16);
	load_data_u16(referenceFile, referenceFileLen, referenceData_u16);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u16(referenceFile, u16output1, 7);
#else
	eq_check_special_u16(referenceData_u16, u16output1, 7);
#endif


	printf("\n== mips_and_u16 3 check done  == \n\n");


// =====================

	printf("== mips_and_u16 4N test ==  \n");
	mips_and_u16(u16inputa, u16inputb, u16output1, 16);
	printf("mips_and_u16 4N finish \n");

	printf("mips_and_u16 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "And24_s16.txt");
#else
	referenceFile = BasicMathsQ15_And24_s16;
	referenceFileLen = sizeof(BasicMathsQ15_And24_s16);
	load_data_u16(referenceFile, referenceFileLen, referenceData_u16);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u16(referenceFile, u16output1, 16);
#else
	eq_check_special_u16(referenceData_u16, u16output1, 16);
#endif


	printf("\n== mips_and_u16 4N check done  == \n\n");

// =====================

	printf("== mips_and_u16 4N+1 test ==  \n");
	mips_and_u16(u16inputa, u16inputb, u16output1, 23);
	printf("mips_and_u16 4N+1 finish \n");

	printf("mips_and_u16 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "And24_s16.txt");
#else
	referenceFile = BasicMathsQ15_And24_s16;
	referenceFileLen = sizeof(BasicMathsQ15_And24_s16);
	load_data_u16(referenceFile, referenceFileLen, referenceData_u16);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u16(referenceFile, u16output1, 23);
#else
	eq_check_special_u16(referenceData_u16, u16output1, 23);
#endif


	printf("\n== mips_and_u16 4N+1 check done  == \n\n");

// =====================

	printf("== mips_or_u16 3 test ==  \n");
	mips_or_u16(u16inputa, u16inputb, u16output1, 7);
	printf("mips_or_u16 3 finish \n");

	printf("mips_or_u16 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Or25_s16.txt");
#else
	referenceFile = BasicMathsQ15_Or25_s16;
	referenceFileLen = sizeof(BasicMathsQ15_Or25_s16);
	load_data_u16(referenceFile, referenceFileLen, referenceData_u16);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u16(referenceFile, u16output1, 7);
#else
	eq_check_special_u16(referenceData_u16, u16output1, 7);
#endif


	printf("\n== mips_or_u16 3 check done  == \n\n");

// =====================

	printf("== mips_or_u16 4N test ==  \n");
	mips_or_u16(u16inputa, u16inputb, u16output1, 16);
	printf("mips_or_u16 4N finish \n");

	printf("mips_or_u16 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Or25_s16.txt");
#else
	referenceFile = BasicMathsQ15_Or25_s16;
	referenceFileLen = sizeof(BasicMathsQ15_Or25_s16);
	load_data_u16(referenceFile, referenceFileLen, referenceData_u16);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u16(referenceFile, u16output1, 16);
#else
	eq_check_special_u16(referenceData_u16, u16output1, 16);
#endif


	printf("\n== mips_or_u16 4N check done  == \n\n");


// =====================

	printf("== mips_or_u16 4N+1 test ==  \n");
	mips_or_u16(u16inputa, u16inputb, u16output1, 23);
	printf("mips_or_u16 4N+1 finish \n");

	printf("mips_or_u16 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Or25_s16.txt");
#else
	referenceFile = BasicMathsQ15_Or25_s16;
	referenceFileLen = sizeof(BasicMathsQ15_Or25_s16);
	load_data_u16(referenceFile, referenceFileLen, referenceData_u16);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u16(referenceFile, u16output1, 23);
#else
	eq_check_special_u16(referenceData_u16, u16output1, 23);
#endif


	printf("\n== mips_or_u16 4N+1 check done  == \n\n");

// =====================

	printf("== mips_not_u16 3 test ==  \n");
	mips_not_u16(u16inputa, u16output1, 7);
	printf("v finish \n");

	printf("mips_not_u16 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Not26_s16.txt");
#else
	referenceFile = BasicMathsQ15_Not26_s16;
	referenceFileLen = sizeof(BasicMathsQ15_Not26_s16);
	load_data_u16(referenceFile, referenceFileLen, referenceData_u16);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u16(referenceFile, u16output1, 7);
#else
	eq_check_special_u16(referenceData_u16, u16output1, 7);
#endif


	printf("\n== mips_not_u16 3 check done  == \n\n"); 

// =====================

	printf("== mips_not_u16 4N test ==  \n");
	mips_not_u16(u16inputa, u16output1, 16);
	printf("v finish \n");

	printf("mips_not_u16 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Not26_s16.txt");
#else
	referenceFile = BasicMathsQ15_Not26_s16;
	referenceFileLen = sizeof(BasicMathsQ15_Not26_s16);
	load_data_u16(referenceFile, referenceFileLen, referenceData_u16);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u16(referenceFile, u16output1, 16);
#else
	eq_check_special_u16(referenceData_u16, u16output1, 16);
#endif


	printf("\n== mips_not_u16 4N check done  == \n\n"); 

// =====================

	printf("== mips_not_u16 4N+1 test ==  \n");
	mips_not_u16(u16inputa, u16output1, 23);
	printf("v finish \n");

	printf("mips_not_u16 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Not26_s16.txt");
#else
	referenceFile = BasicMathsQ15_Not26_s16;
	referenceFileLen = sizeof(BasicMathsQ15_Not26_s16);
	load_data_u16(referenceFile, referenceFileLen, referenceData_u16);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u16(referenceFile, u16output1, 23);
#else
	eq_check_special_u16(referenceData_u16, u16output1, 23);
#endif


	printf("\n== mips_not_u16 4N+1 check done  == \n\n"); 

// =====================

	printf("== mips_xor_u16 3 test ==  \n");
	mips_xor_u16(u16inputa, u16inputb, u16output1, 7);
	printf("mips_xor_u16 3 finish \n");

	printf("mips_xor_u16 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Xor27_s16.txt");
#else
	referenceFile = BasicMathsQ15_Xor27_s16;
	referenceFileLen = sizeof(BasicMathsQ15_Xor27_s16);
	load_data_u16(referenceFile, referenceFileLen, referenceData_u16);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u16(referenceFile, u16output1, 7);
#else
	eq_check_special_u16(referenceData_u16, u16output1, 7);
#endif


	printf("\n== mips_xor_u16 3 check done  == \n\n");  

// =====================

	printf("== mips_xor_u16 4N test ==  \n");
	mips_xor_u16(u16inputa, u16inputb, u16output1, 16);
	printf("mips_xor_u16 4N finish \n");

	printf("mips_xor_u16 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Xor27_s16.txt");
#else
	referenceFile = BasicMathsQ15_Xor27_s16;
	referenceFileLen = sizeof(BasicMathsQ15_Xor27_s16);
	load_data_u16(referenceFile, referenceFileLen, referenceData_u16);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u16(referenceFile, u16output1, 16);
#else
	eq_check_special_u16(referenceData_u16, u16output1, 16);
#endif


	printf("\n== mips_xor_u16 4N check done  == \n\n");  

// =====================

	printf("== mips_xor_u16 4N+1 test ==  \n");
	mips_xor_u16(u16inputa, u16inputb, u16output1, 23);
	printf("mips_xor_u16 4N+1 finish \n");

	printf("mips_xor_u16 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Xor27_s16.txt");
#else
	referenceFile = BasicMathsQ15_Xor27_s16;
	referenceFileLen = sizeof(BasicMathsQ15_Xor27_s16);
	load_data_u16(referenceFile, referenceFileLen, referenceData_u16);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u16(referenceFile, u16output1, 23);
#else
	eq_check_special_u16(referenceData_u16, u16output1, 23);
#endif


	printf("\n== mips_xor_u16 4N+1 check done  == \n\n");  

// =====================

	printf("== mips_clip_q15 test ==  \n");
	mips_clip_q15(q15input28, q15output1, 0xC000, 0xF333, paramCountInput28);
	printf("mips_clip_q15 finish \n");

	printf("mips_clip_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Reference28_q15.txt");
#else
	referenceFile = BasicMathsQ15_Reference28_q15;
	referenceFileLen = sizeof(BasicMathsQ15_Reference28_q15);
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


	printf("\n== mips_clip_q15 check done  == \n\n");

// =====================

	printf("== mips_clip_q15 test ==  \n");
	mips_clip_q15(q15input28, q15output1, 0xC000, 0x4000, paramCountInput28);
	printf("mips_clip_q15 finish \n");

	printf("mips_clip_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Reference29_q15.txt");
#else
	referenceFile = BasicMathsQ15_Reference29_q15;
	referenceFileLen = sizeof(BasicMathsQ15_Reference29_q15);
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


	printf("\n== mips_clip_q15 check done  == \n\n");

// =====================

	printf("== mips_clip_q15 test ==  \n");
	mips_clip_q15(q15input28, q15output1, 0x0CCD, 0x4000, paramCountInput28);
	printf("mips_clip_q15 finish \n");

	printf("mips_clip_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ15, "Reference30_q15.txt");
#else
	referenceFile = BasicMathsQ15_Reference30_q15;
	referenceFileLen = sizeof(BasicMathsQ15_Reference30_q15);
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


	printf("\n== mips_clip_q15 check done  == \n\n");

// =====================
	
	return 0;

}