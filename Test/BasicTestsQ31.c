#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/basic_math_functions.h"

#define SNR_THRESHOLD 100
#define ABS_ERROR_Q31 ((q31)4)
#define ABS_ERROR_Q63 ((q63)(1<<17))

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
    int paramCountInput5 = 0;
    int paramCountInput6 = 0;

    int paramCountInputa = 0;
    int paramCountInputb = 0;

	q31 q31input1[MAX_SIZE] = {0};
	q31 q31input2[MAX_SIZE] = {0};
    q31 q31input3[MAX_SIZE] = {0};
    q31 q31input4[MAX_SIZE] = {0};
    q31 q31input5[MAX_SIZE] = {0};
    q31 q31input6[MAX_SIZE] = {0};

    q31 q31inputa[MAX_SIZE] = {0};
	q31 q31inputb[MAX_SIZE] = {0};

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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Input1_q31.txt");
#else
	inputFile1 = BasicMathsQ31_Input1_q31;
	inputFile1Len = sizeof(BasicMathsQ31_Input1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Input2_q31.txt");
#else
	inputFile2 = BasicMathsQ31_Input2_q31;
	inputFile2Len = sizeof(BasicMathsQ31_Input2_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Input28_q31.txt");
#else
	inputFile3 = BasicMathsQ31_Input28_q31;
	inputFile3Len = sizeof(BasicMathsQ31_Input28_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile4, sizeof(inputFile4), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Input12_q31.txt");
#else
	inputFile4 = BasicMathsQ31_Input12_q31;
	inputFile4Len = sizeof(BasicMathsQ31_Input12_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile5, sizeof(inputFile5), "%s%s%s", Patterns_PATH, BasicMathsQ31, "MaxPosInput12_s32.txt");
#else
	inputFile5 = BasicMathsQ31_MaxPosInput12_s32;
	inputFile5Len = sizeof(BasicMathsQ31_MaxPosInput12_s32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile6, sizeof(inputFile6), "%s%s%s", Patterns_PATH, BasicMathsQ31, "MaxNegInput12_s32.txt");
#else
	inputFile6 = BasicMathsQ31_MaxNegInput12_s32;
	inputFile6Len = sizeof(BasicMathsQ31_MaxNegInput12_s32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Reference1_q31.txt");
#else
	referenceFile = BasicMathsQ31_Reference1_q31;
	referenceFileLen = sizeof(BasicMathsQ31_Reference1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif

    
#if defined(NOT_EMBEDDED)
	snprintf(inputFilea, sizeof(inputFilea), "%s%s%s", Patterns_PATH, BasicMathsQ31, "BitwiseInput24_s32.txt");
#else
	inputFilea = BasicMathsQ31_BitwiseInput24_s32;
	inputFileaLen = sizeof(BasicMathsQ31_BitwiseInput24_s32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb, sizeof(inputFileb), "%s%s%s", Patterns_PATH, BasicMathsQ31, "BitwiseInput25_s32.txt");
#else
	inputFileb = BasicMathsQ31_BitwiseInput25_s32;
	inputFilebLen = sizeof(BasicMathsQ31_BitwiseInput25_s32);
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

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile4, &paramCountInput4, q31input4);
#else
	paramCountInput4 = inputFile4Len;
	load_data_q31(inputFile4, paramCountInput4, q31input4);
	paramCountInput4 = paramCountInput4/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile5, &paramCountInput5, q31input5);
#else
	paramCountInput5 = inputFile5Len;
	load_data_q31(inputFile5, paramCountInput5, q31input5);
	paramCountInput5 = paramCountInput5/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile6, &paramCountInput6, q31input6);
#else
	paramCountInput6 = inputFile6Len;
	load_data_q31(inputFile6, paramCountInput6, q31input6);
	paramCountInput6 = paramCountInput6/sizeof(q31);
#endif

	uint32_t u32inputa[MAX_SIZE] = {0};
	uint32_t u32inputb[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	load_data_u32(inputFilea, &paramCountInputa, u32inputa);
#else
	paramCountInputa = inputFileaLen;
	load_data_u32(inputFilea, paramCountInputa, u32inputa);
	paramCountInputa = paramCountInputa/sizeof(uint32_t);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u32(inputFileb, &paramCountInputb, u32inputb);
#else
	paramCountInputb = inputFilebLen;
	load_data_u32(inputFileb, paramCountInputb, u32inputb);
	paramCountInputb = paramCountInputb/sizeof(uint32_t);
#endif



	q31 q31output1[MAX_SIZE] = {0};

	printf("== mips_add_q31 test ==  \n");
	mips_add_q31(q31input1, q31input2, q31output1, paramCountInput1);
	printf("mips_add_q31 finish \n");

	printf("mips_add_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Reference1_q31.txt");
#else
	referenceFile = BasicMathsQ31_Reference1_q31;
	referenceFileLen = sizeof(BasicMathsQ31_Reference1_q31);
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

	printf("\n== mips_add_q31 check done  == \n\n");

	// for (size_t i = 0; i < 10; i++)
	// {
	// 	printf("input = %x \n", q31input1[i]);
    //     printf("mips_add_q31 output = %x \n", q31output1[i]);
	// }

// =====================

	printf("== mips_sub_q31 test ==  \n");
	mips_sub_q31(q31input1, q31input2, q31output1, paramCountInput1);
	printf("mips_sub_q31 finish \n");

	printf("mips_sub_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Reference2_q31.txt");
#else
	referenceFile = BasicMathsQ31_Reference2_q31;
	referenceFileLen = sizeof(BasicMathsQ31_Reference2_q31);
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


	printf("\n== mips_sub_q31 check done  == \n\n");

// =====================

	printf("== mips_mult_q31 test ==  \n");
	mips_mult_q31(q31input1, q31input2, q31output1, paramCountInput1);
	printf("mips_mult_q31 finish \n");

	printf("mips_mult_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Reference3_q31.txt");
#else
	referenceFile = BasicMathsQ31_Reference3_q31;
	referenceFileLen = sizeof(BasicMathsQ31_Reference3_q31);
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


	printf("\n== mips_mult_q31 check done  == \n\n");



// =====================

	printf("== mips_negate_q31 test ==  \n");
	mips_negate_q31(q31input1, q31output1, paramCountInput1);
	printf("mips_negate_q31 finish \n");

	printf("mips_negate_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Reference4_q31.txt");
#else
	referenceFile = BasicMathsQ31_Reference4_q31;
	referenceFileLen = sizeof(BasicMathsQ31_Reference4_q31);
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


	printf("\n== mips_negate_q31 check done  == \n\n");

// =====================

	printf("== mips_offset_q31 test ==  \n");
	mips_offset_q31(q31input1, 0x40000000, q31output1, paramCountInput1);
	printf("mips_offset_q31 finish \n");

	printf("mips_offset_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Reference5_q31.txt");
#else
	referenceFile = BasicMathsQ31_Reference5_q31;
	referenceFileLen = sizeof(BasicMathsQ31_Reference5_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
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


	printf("\n== mips_offset_q31 check done  == \n\n");

// =====================

	printf("== mips_offset_q31 test ==  \n");
	mips_offset_q31(q31input5, 0x73333333, q31output1, paramCountInput5);
	printf("mips_offset_q31 finish \n");

	printf("mips_offset_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "PosSat18_q31.txt");
#else
	referenceFile = BasicMathsQ31_PosSat18_q31;
	referenceFileLen = sizeof(BasicMathsQ31_PosSat18_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
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


	printf("\n== mips_offset_q31 check done  == \n\n");
// =====================

	printf("== mips_offset_q31 test ==  \n");
	mips_offset_q31(q31input6, 0x8ccccccd, q31output1, paramCountInput6);
	printf("mips_offset_q31 finish \n");

	printf("mips_offset_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "NegSat19_q31.txt");
#else
	referenceFile = BasicMathsQ31_NegSat19_q31;
	referenceFileLen = sizeof(BasicMathsQ31_NegSat19_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
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


	printf("\n== mips_offset_q31 check done  == \n\n");


// =====================

	printf("== mips_scale_q31 test ==  \n");
	mips_scale_q31(q31input1, 0x40000000, 0, q31output1, paramCountInput1);
	printf("mips_scale_q31 finish \n");

	printf("mips_scale_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Reference6_q31.txt");
#else
	referenceFile = BasicMathsQ31_Reference6_q31;
	referenceFileLen = sizeof(BasicMathsQ31_Reference6_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
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


	printf("\n== mips_scale_q31 check done  == \n\n");

// =====================

	printf("== mips_scale_q31 test ==  \n");
	mips_scale_q31(q31input6, 0x80000000, 0, q31output1, paramCountInput6);
	printf("mips_scale_q31 finish \n");

	printf("mips_scale_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "PosSat20_q31.txt");
#else
	referenceFile = BasicMathsQ31_PosSat20_q31;
	referenceFileLen = sizeof(BasicMathsQ31_PosSat20_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
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


	printf("\n== mips_scale_q31 check done  == \n\n");

// =====================dot

    q63 q63output1[MAX_SIZE] = {0};
	printf("== mips_dot_prod_q31 3 test ==  \n");
	mips_dot_prod_q31(q31input1, q31input2, 3, q63output1);
	printf("mips_dot_prod_q31 3 finish \n");

	printf("mips_dot_prod_q31 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Reference7_q63.txt");
#else
	referenceFile = BasicMathsQ31_Reference7_q63;
	referenceFileLen = sizeof(BasicMathsQ31_Reference7_q63);
	load_data_q63(referenceFile, referenceFileLen, referenceData_q63);
#endif



	// for (size_t i = 0; i < 10; i++)
	// {
	// 	printf("input1 = %x \n", q31input1[i]);
    //     printf("input2 = %x \n", q31input2[i]);
    //     printf("mips_add_q31 output = %x \n", q63output1[i]);
	// }
#if defined(NOT_EMBEDDED)
	near_check_q63(referenceFile, q63output1, 1, ABS_ERROR_Q63);
#else
	near_check_special_q63(referenceData_q63, q63output1, 1, ABS_ERROR_Q63);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q63(referenceFile, q63output1, 1, SNR_THRESHOLD);
#else
	snr_check_special_q63(referenceData_q63, q63output1, 1, SNR_THRESHOLD);
#endif


	printf("\n== mips_dot_prod_q31 3 check done  == \n\n");

// =====================

	printf("== mips_dot_prod_q31 4N test ==  \n");
	mips_dot_prod_q31(q31input1, q31input2, 8, q63output1);
	printf("mips_dot_prod_q31 4N finish \n");

	printf("mips_dot_prod_q31 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Reference8_q63.txt");
#else
	referenceFile = BasicMathsQ31_Reference8_q63;
	referenceFileLen = sizeof(BasicMathsQ31_Reference8_q63);
	load_data_q63(referenceFile, referenceFileLen, referenceData_q63);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q63(referenceFile, q63output1, 1, ABS_ERROR_Q63);
#else
	near_check_special_q63(referenceData_q63, q63output1, 1, ABS_ERROR_Q63);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q63(referenceFile, q63output1, 1, SNR_THRESHOLD);
#else
	snr_check_special_q63(referenceData_q63, q63output1, 1, SNR_THRESHOLD);
#endif


	printf("\n== mips_dot_prod_q31 4N check done  == \n\n");

// =====================

	printf("== mips_dot_prod_q31 4N+1 test ==  \n");
	mips_dot_prod_q31(q31input1, q31input2, 11, q63output1);
	printf("mips_dot_prod_q31 4N+1 finish \n");

	printf("mips_dot_prod_q31 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Reference9_q63.txt");
#else
	referenceFile = BasicMathsQ31_Reference9_q63;
	referenceFileLen = sizeof(BasicMathsQ31_Reference9_q63);
	load_data_q63(referenceFile, referenceFileLen, referenceData_q63);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q63(referenceFile, q63output1, 1, ABS_ERROR_Q63);
#else
	near_check_special_q63(referenceData_q63, q63output1, 1, ABS_ERROR_Q63);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q63(referenceFile, q63output1, 1, SNR_THRESHOLD);
#else
	snr_check_special_q63(referenceData_q63, q63output1, 1, SNR_THRESHOLD);
#endif


	printf("\n== mips_dot_prod_q31 4N+1 check done  == \n\n");

// =====================

	printf("== mips_dot_prod_q31 long test ==  \n");
	mips_dot_prod_q31(q31input1, q31input2, paramCountInput1, q63output1);
	printf("mips_dot_prod_q31 long finish \n");

	printf("mips_dot_prod_q31 long checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Reference11_q63.txt");
#else
	referenceFile = BasicMathsQ31_Reference11_q63;
	referenceFileLen = sizeof(BasicMathsQ31_Reference11_q63);
	load_data_q63(referenceFile, referenceFileLen, referenceData_q63);
#endif


#if defined(NOT_EMBEDDED)
	near_check_q63(referenceFile, q63output1, 0, ABS_ERROR_Q63);
#else
	near_check_special_q63(referenceData_q63, q63output1, referenceFileLen, ABS_ERROR_Q63);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q63(referenceFile, q63output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q63(referenceData_q63, q63output1, referenceFileLen, SNR_THRESHOLD);
#endif


	printf("\n== mips_dot_prod_q31 long check done  == \n\n");


// =====================clip

	printf("== mips_clip_q31 test ==  \n");
	mips_clip_q31(q31input3, q31output1, 0xC0000000, 0xF3333333, paramCountInput3);
	printf("mips_clip_q31 finish \n");

	printf("mips_clip_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Reference28_q31.txt");
#else
	referenceFile = BasicMathsQ31_Reference28_q31;
	referenceFileLen = sizeof(BasicMathsQ31_Reference28_q31);
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


	printf("\n== mips_clip_q31 check done  == \n\n");

// =====================clip

	printf("== mips_clip_q31 test ==  \n");
	mips_clip_q31(q31input3, q31output1, 0xC0000000, 0x40000000, paramCountInput3);
	printf("mips_clip_q31 finish \n");

	printf("mips_clip_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Reference29_q31.txt");
#else
	referenceFile = BasicMathsQ31_Reference29_q31;
	referenceFileLen = sizeof(BasicMathsQ31_Reference29_q31);
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


	printf("\n== mips_clip_q31 check done  == \n\n");

// =====================clip

	printf("== mips_clip_q31 test ==  \n");
	mips_clip_q31(q31input3, q31output1, 0x0CCCCCCD, 0x40000000, paramCountInput3);
	printf("mips_clip_q31 finish \n");

	printf("mips_clip_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Reference30_q31.txt");
#else
	referenceFile = BasicMathsQ31_Reference30_q31;
	referenceFileLen = sizeof(BasicMathsQ31_Reference30_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
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


	printf("\n== mips_clip_q31 check done  == \n\n");

// =====================

	printf("== mips_shift_q31 test ==  \n");
	mips_shift_q31(q31input4, 1, q31output1, paramCountInput4);
	printf("mips_shift_q31 finish \n");

	printf("mips_shift_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Shift21_q31.txt");
#else
	referenceFile = BasicMathsQ31_Shift21_q31;
	referenceFileLen = sizeof(BasicMathsQ31_Shift21_q31);
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


	printf("\n== mips_shift_q31 check done  == \n\n");

// =====================

	printf("== mips_shift_q31 test ==  \n");
	mips_shift_q31(q31input5, 1, q31output1, paramCountInput5);
	printf("mips_shift_q31 finish \n");

	printf("mips_shift_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Shift22_q31.txt");
#else
	referenceFile = BasicMathsQ31_Shift22_q31;
	referenceFileLen = sizeof(BasicMathsQ31_Shift22_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);		referenceFileLen = referenceFileLen/sizeof(q31);
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


	printf("\n== mips_shift_q31 check done  == \n\n");

// =====================

	printf("== mips_shift_q31 test ==  \n");
	mips_shift_q31(q31input6, 1, q31output1, paramCountInput6);
	printf("mips_shift_q31 finish \n");

	printf("mips_shift_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Shift23_q31.txt");
#else
	referenceFile = BasicMathsQ31_Shift23_q31;
	referenceFileLen = sizeof(BasicMathsQ31_Shift23_q31);
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


	printf("\n== mips_shift_q31 check done  == \n\n");

// =====================
uint32_t u32output1[MAX_SIZE] = {0};
	printf("== mips_and_u32 3test ==  \n");
	mips_and_u32(u32inputa, u32inputb, u32output1, 3);
	printf("mips_and_u32 3finish \n");

	printf("mips_and_u32 3checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "And24_s32.txt");
#else
	referenceFile = BasicMathsQ31_And24_s32;
	referenceFileLen = sizeof(BasicMathsQ31_And24_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif

    // for (size_t i = 0; i < 10; i++)
	// {
	// 	printf("input = %x \n", u32inputa[i]);
    //     printf("input = %x \n", u32inputb[i]);
    //     printf("mips_and_u32 output = %x \n", u32output1[i]);
	// }


#if defined(NOT_EMBEDDED)
	eq_check_u32(referenceFile, u32output1, 3);
#else
	eq_check_special_u32(referenceData_u32, u32output1, 3);
#endif


	printf("\n== mips_and_u32 3check done  == \n\n");

// =====================

	printf("== mips_and_u32 8test ==  \n");
	mips_and_u32(u32inputa, u32inputb, u32output1, 8);
	printf("mips_and_u32 8finish \n");

	printf("mips_and_u32 8checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "And24_s32.txt");
#else
	referenceFile = BasicMathsQ31_And24_s32;
	referenceFileLen = sizeof(BasicMathsQ31_And24_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif

 
#if defined(NOT_EMBEDDED)
	eq_check_u32(referenceFile, u32output1, 8);
#else
	eq_check_special_u32(referenceData_u32, u32output1, 8);
#endif


	printf("\n== mips_and_u32 8check done  == \n\n");

// =====================

	printf("== mips_and_u32 11test ==  \n");
	mips_and_u32(u32inputa, u32inputb, u32output1, 11);
	printf("mips_and_u32 11finish \n");

	printf("mips_and_u32 11checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "And24_s32.txt");
#else
	referenceFile = BasicMathsQ31_And24_s32;
	referenceFileLen = sizeof(BasicMathsQ31_And24_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif

 
#if defined(NOT_EMBEDDED)
	eq_check_u32(referenceFile, u32output1, 11);
#else
	eq_check_special_u32(referenceData_u32, u32output1, 11);
#endif


	printf("\n== mips_and_u32 11check done  == \n\n");

// =====================

	printf("== mips_or_u32 3test ==  \n");
	mips_or_u32(u32inputa, u32inputb, u32output1, 3);
	printf("mips_or_u32 3finish \n");

	printf("mips_or_u32 3checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Or25_s32.txt");
#else
	referenceFile = BasicMathsQ31_Or25_s32;
	referenceFileLen = sizeof(BasicMathsQ31_Or25_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u32(referenceFile, u32output1, 3);
#else
	eq_check_special_u32(referenceData_u32, u32output1, 3);
#endif

	printf("\n== mips_or_u32 3check done  == \n\n");

// =====================

	printf("== mips_or_u32 8test ==  \n");
	mips_or_u32(u32inputa, u32inputb, u32output1, 8);
	printf("mips_or_u32 8finish \n");

	printf("mips_or_u32 8checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Or25_s32.txt");
#else
	referenceFile = BasicMathsQ31_Or25_s32;
	referenceFileLen = sizeof(BasicMathsQ31_Or25_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u32(referenceFile, u32output1, 8);
#else
	eq_check_special_u32(referenceData_u32, u32output1, 8);
#endif

	printf("\n== mips_or_u32 8check done  == \n\n");

// =====================

	printf("== mips_or_u32 11test ==  \n");
	mips_or_u32(u32inputa, u32inputb, u32output1, 11);
	printf("mips_or_u32 11finish \n");

	printf("mips_or_u32 11checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Or25_s32.txt");
#else
	referenceFile = BasicMathsQ31_Or25_s32;
	referenceFileLen = sizeof(BasicMathsQ31_Or25_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u32(referenceFile, u32output1, 11);
#else
	eq_check_special_u32(referenceData_u32, u32output1, 11);
#endif

	printf("\n== mips_or_u32 11check done  == \n\n");

// =====================

	printf("== mips_not_u32 3test ==  \n");
	mips_not_u32(u32inputa, u32output1, 3);
	printf("mips_not_u32 3finish \n");

	printf("mips_not_u32 3checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Not26_s32.txt");
#else
	referenceFile = BasicMathsQ31_Not26_s32;
	referenceFileLen = sizeof(BasicMathsQ31_Not26_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u32(referenceFile, u32output1, 3);
#else
	eq_check_special_u32(referenceData_u32, u32output1, 3);
#endif

	printf("\n== mips_not_u32 3check done  == \n\n");

// =====================

	printf("== mips_not_u32 8test ==  \n");
	mips_not_u32(u32inputa, u32output1, 8);
	printf("mips_not_u32 8finish \n");

	printf("mips_not_u32 8checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Not26_s32.txt");
#else
	referenceFile = BasicMathsQ31_Not26_s32;
	referenceFileLen = sizeof(BasicMathsQ31_Not26_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u32(referenceFile, u32output1, 8);
#else
	eq_check_special_u32(referenceData_u32, u32output1, 8);
#endif

	printf("\n== mips_not_u32 8check done  == \n\n");

// =====================

	printf("== mips_not_u32 11test ==  \n");
	mips_not_u32(u32inputa, u32output1, 11);
	printf("mips_not_u32 11finish \n");

	printf("mips_not_u32 11checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Not26_s32.txt");
#else
	referenceFile = BasicMathsQ31_Not26_s32;
	referenceFileLen = sizeof(BasicMathsQ31_Not26_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u32(referenceFile, u32output1, 11);
#else
	eq_check_special_u32(referenceData_u32, u32output1, 11);
#endif

	printf("\n== mips_not_u32 11check done  == \n\n");

// =====================

	printf("== mips_xor_u32 3test ==  \n");
	mips_xor_u32(u32inputa, u32inputb, u32output1, 3);
	printf("mips_xor_u32 3finish \n");

	printf("mips_xor_u32 3checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Xor27_s32.txt");
#else
	referenceFile = BasicMathsQ31_Xor27_s32;
	referenceFileLen = sizeof(BasicMathsQ31_Xor27_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u32(referenceFile, u32output1, 3);
#else
	eq_check_special_u32(referenceData_u32, u32output1, 3);
#endif

	printf("\n== mips_xor_u32 3check done  == \n\n");

// =====================

	printf("== mips_xor_u32 8test ==  \n");
	mips_xor_u32(u32inputa, u32inputb, u32output1, 8);
	printf("mips_xor_u32 8finish \n");

	printf("mips_xor_u32 8checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Xor27_s32.txt");
#else
	referenceFile = BasicMathsQ31_Xor27_s32;
	referenceFileLen = sizeof(BasicMathsQ31_Xor27_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u32(referenceFile, u32output1, 8);
#else
	eq_check_special_u32(referenceData_u32, u32output1, 8);
#endif

	printf("\n== mips_xor_u32 8check done  == \n\n");

// =====================

	printf("== mips_xor_u32 11test ==  \n");
	mips_xor_u32(u32inputa, u32inputb, u32output1, 11);
	printf("mips_xor_u32 11finish \n");

	printf("mips_xor_u32 11checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, BasicMathsQ31, "Xor27_s32.txt");
#else
	referenceFile = BasicMathsQ31_Xor27_s32;
	referenceFileLen = sizeof(BasicMathsQ31_Xor27_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u32(referenceFile, u32output1, 11);
#else
	eq_check_special_u32(referenceData_u32, u32output1, 11);
#endif

	printf("\n== mips_xor_u32 11check done  == \n\n");


    return 0;
}
	
