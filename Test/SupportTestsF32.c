#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/support_functions.h"
#define SNR_THRESHOLD 120
#define REL_ERROR (1.0e-5)
#define ABS_Q15_ERROR ((q15)10)
#define ABS_Q31_ERROR ((q31)80)
#define ABS_Q7_ERROR ((q7)10)

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
	int paramCountInput = 0;
	int paramCountInputsort = 0;
	int paramCountInputbitonic16 = 0;
	int paramCountInputbitonic32 = 0;
	int paramCountInputconst = 0;
	int paramCountInputweights = 0;

	float f32input[MAX_SIZE] = {0};
	float f32inputsort[MAX_SIZE] = {0};
	float f32inputbitonic16[MAX_SIZE] = {0};
	float f32inputbitonic32[MAX_SIZE] = {0};
	float f32inputcost[MAX_SIZE] = {0};
	float f32inputweights[MAX_SIZE] = {0};

	int paramCountSamplesf32 = 0;
	int paramCountSamplesq15 = 0;
	int paramCountSamplesq31 = 0;
	int paramCountSamplesq7 = 0;
	int paramCountSamplesf64 = 0;

	float f32samples[MAX_SIZE] = {0};
	q15 q15samples[MAX_SIZE] = {0};
	q31 q31samples[MAX_SIZE] = {0};
	q7 q7samples[MAX_SIZE] = {0};
	double f64samples[MAX_SIZE] = {0};

	int paramCountReff32 = 0;
	int paramCountRefsort = 0;
	int paramCountRefbitonic16 = 0;
	int paramCountRefbitonic32 = 0;
	int paramCountRefconst = 0;

	float f32ref[MAX_SIZE] = {0};
	float f32refsort[MAX_SIZE] = {0};
	float f32refbitonic16[MAX_SIZE] = {0};
	float f32refbitonic32[MAX_SIZE] = {0};
	float f32refcost[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFile[255] = {0};
#else
	void *inputFile;
	int inputFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFilesort[255] = {0};
#else
	void *inputFilesort;
	int inputFilesortLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFilebitonic16[255] = {0};
#else
	void *inputFilebitonic16;
	int inputFilebitonic16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFilebitonic32[255] = {0};
#else
	void *inputFilebitonic32;
	int inputFilebitonic32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileconst[255] = {0};
#else
	void *inputFileconst;
	int inputFileconstLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileweights[255] = {0};
#else
	void *inputFileweights;
	int inputFileweightsLen = 0;
#endif


#if defined(NOT_EMBEDDED)
	char referenceFile[255] = {0};
#else
	void *referenceFile;
	int referenceFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFilesort[255] = {0};
#else
	void *referenceFilesort;
	int referenceFilesortLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFilebitonic16[255] = {0};
#else
	void *referenceFilebitonic16;
	int referenceFilebitonic16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFilebitonic32[255] = {0};
#else
	void *referenceFilebitonic32;
	int referenceFilebitonic32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFileconst[255] = {0};
#else
	void *referenceFileconst;
	int referenceFileconstLen = 0;
#endif


#if defined(NOT_EMBEDDED)
	char sampleFilef32[255] = {0};
#else
	void *sampleFilef32;
	int sampleFilef32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char sampleFileq15[255] = {0};
#else
	void *sampleFileq15;
	int sampleFileq15Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char sampleFileq31[255] = {0};
#else
	void *sampleFileq31;
	int sampleFileq31Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char sampleFileq7[255] = {0};
#else
	void *sampleFileq7;
	int sampleFileq7Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char sampleFilef64[255] = {0};
#else
	void *sampleFilef64;
	int sampleFilef64Len = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile, sizeof(inputFile), "%s%s%s", Patterns_PATH, SupportF32, "Inputs6_f32.txt");
#else
	inputFile = SupportF32_Inputs6_f32;
	inputFileLen = sizeof(SupportF32_Inputs6_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFilesort, sizeof(inputFilesort), "%s%s%s", Patterns_PATH, SupportF32, "Input7_f32.txt");
#else
	inputFilesort = SupportF32_Input7_f32;
	inputFilesortLen = sizeof(SupportF32_Input7_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFilebitonic16, sizeof(inputFilebitonic16), "%s%s%s", Patterns_PATH, SupportF32, "Input8_f32.txt");
#else
	inputFilebitonic16 = SupportF32_Input8_f32;
	inputFilebitonic16Len = sizeof(SupportF32_Input8_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFilebitonic32, sizeof(inputFilebitonic32), "%s%s%s", Patterns_PATH, SupportF32, "Input9_f32.txt");
#else
	inputFilebitonic32 = SupportF32_Input9_f32;
	inputFilebitonic32Len = sizeof(SupportF32_Input9_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileconst, sizeof(inputFileconst), "%s%s%s", Patterns_PATH, SupportF32, "Input10_f32.txt");
#else
	inputFileconst = SupportF32_Input10_f32;
	inputFileconstLen = sizeof(SupportF32_Input10_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileweights, sizeof(inputFileweights), "%s%s%s", Patterns_PATH, SupportF32, "Weights6_f32.txt");
#else
	inputFileweights = SupportF32_Weights6_f32;
	inputFileweightsLen = sizeof(SupportF32_Weights6_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, SupportF32, "Ref6_f32.txt");
#else
	referenceFile = SupportF32_Ref6_f32;
	referenceFileLen = sizeof(SupportF32_Ref6_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFilesort, sizeof(referenceFilesort), "%s%s%s", Patterns_PATH, SupportF32, "Reference7_f32.txt");
#else
	referenceFilesort = SupportF32_Reference7_f32;
	referenceFilesortLen = sizeof(SupportF32_Reference7_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFilebitonic16, sizeof(referenceFilebitonic16), "%s%s%s", Patterns_PATH, SupportF32, "Reference8_f32.txt");
#else
	referenceFilebitonic16 = SupportF32_Reference8_f32;
	referenceFilebitonic16Len = sizeof(SupportF32_Reference8_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFilebitonic32, sizeof(referenceFilebitonic32), "%s%s%s", Patterns_PATH, SupportF32, "Reference9_f32.txt");
#else
	referenceFilebitonic32 = SupportF32_Reference9_f32;
	referenceFilebitonic32Len = sizeof(SupportF32_Reference9_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFileconst, sizeof(referenceFileconst), "%s%s%s", Patterns_PATH, SupportF32, "Reference10_f32.txt");
#else
	referenceFileconst = SupportF32_Reference10_f32;
	referenceFileconstLen = sizeof(SupportF32_Reference10_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(sampleFilef32, sizeof(sampleFilef32), "%s%s%s", Patterns_PATH, SupportF32, "Samples1_f32.txt");
#else
	sampleFilef32 = SupportF32_Samples1_f32;
	sampleFilef32Len = sizeof(SupportF32_Samples1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(sampleFileq15, sizeof(sampleFileq15), "%s%s%s", Patterns_PATH, SupportF32, "Samples3_q15.txt");
#else
	sampleFileq15 = SupportF32_Samples3_q15;
	sampleFileq15Len = sizeof(SupportF32_Samples3_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(sampleFileq31, sizeof(sampleFileq31), "%s%s%s", Patterns_PATH, SupportF32, "Samples4_q31.txt");
#else
	sampleFileq31 = SupportF32_Samples4_q31;
	sampleFileq31Len = sizeof(SupportF32_Samples4_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(sampleFileq7, sizeof(sampleFileq7), "%s%s%s", Patterns_PATH, SupportF32, "Samples5_q7.txt");
#else
	sampleFileq7 = SupportF32_Samples5_q7;
	sampleFileq7Len = sizeof(SupportF32_Samples5_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(sampleFilef64, sizeof(sampleFilef64), "%s%s%s", Patterns_PATH, SupportF32, "Samples6_f64.txt");
#else
	sampleFilef64 = SupportF32_Samples6_f64;
	sampleFilef64Len = sizeof(SupportF32_Samples6_f64);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile, &paramCountInput, f32input);
#else
	paramCountInput = inputFileLen;
	load_data_f32(inputFile, paramCountInput, f32input);
	paramCountInput = paramCountInput/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFilesort, &paramCountInputsort, f32inputsort);
#else
	paramCountInputsort = inputFilesortLen;
	load_data_f32(inputFilesort, paramCountInputsort, f32inputsort);
	paramCountInputsort = paramCountInputsort/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFilebitonic16, &paramCountInputbitonic16, f32inputbitonic16);
#else
	paramCountInputbitonic16 = inputFilebitonic16Len;
	load_data_f32(inputFilebitonic16, paramCountInputbitonic16, f32inputbitonic16);
	paramCountInputbitonic16 = paramCountInputbitonic16/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFilebitonic32, &paramCountInputbitonic32, f32inputbitonic32);
#else
	paramCountInputbitonic32 = inputFilebitonic32Len;
	load_data_f32(inputFilebitonic32, paramCountInputbitonic32, f32inputbitonic32);
	paramCountInputbitonic32 = paramCountInputbitonic32/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileconst, &paramCountInputconst, f32inputcost);
#else
	paramCountInputconst = inputFileconstLen;
	load_data_f32(inputFileconst, paramCountInputconst, f32inputcost);
	paramCountInputconst = paramCountInputconst/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileweights, &paramCountInputweights, f32inputweights);
#else
	paramCountInputweights = inputFileweightsLen;
	load_data_f32(inputFileweights, paramCountInputweights, f32inputweights);
	paramCountInputweights = paramCountInputweights/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFile, &paramCountReff32, f32ref);
#else
	paramCountReff32 = referenceFileLen;
	load_data_f32(referenceFile, paramCountReff32, f32ref);
	paramCountReff32 = paramCountReff32/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFilesort, &paramCountRefsort, f32refsort);
#else
	paramCountRefsort = referenceFilesortLen;
	load_data_f32(referenceFilesort, paramCountRefsort, f32refsort);
	paramCountRefsort = paramCountRefsort/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFilebitonic16, &paramCountRefbitonic16, f32refbitonic16);
#else
	paramCountRefbitonic16 = referenceFilebitonic16Len;
	load_data_f32(referenceFilebitonic16, paramCountRefbitonic16, f32refbitonic16);
	paramCountRefbitonic16 = paramCountRefbitonic16/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFilebitonic32, &paramCountRefbitonic32, f32refbitonic32);
#else
	paramCountRefbitonic32 = referenceFilebitonic32Len;
	load_data_f32(referenceFilebitonic32, paramCountRefbitonic32, f32refbitonic32);
	paramCountRefbitonic32 = paramCountRefbitonic32/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFileconst, &paramCountRefconst, f32refcost);
#else
	paramCountRefconst = referenceFileconstLen;
	load_data_f32(referenceFileconst, paramCountRefconst, f32refcost);
	paramCountRefconst = paramCountRefconst/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(sampleFilef32, &paramCountSamplesf32, f32samples);
#else
	paramCountSamplesf32 = sampleFilef32Len;
	load_data_f32(sampleFilef32, paramCountSamplesf32, f32samples);
	paramCountSamplesf32 = paramCountSamplesf32/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(sampleFileq15, &paramCountSamplesq15, q15samples);
#else
	paramCountSamplesq15 = sampleFileq15Len;
	load_data_q15(sampleFileq15, paramCountSamplesq15, q15samples);
	paramCountSamplesq15 = paramCountSamplesq15/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(sampleFileq31, &paramCountSamplesq31, q31samples);
#else
	paramCountSamplesq31 = sampleFileq31Len;
	load_data_q31(sampleFileq31, paramCountSamplesq31, q31samples);
	paramCountSamplesq31 = paramCountSamplesq31/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q7(sampleFileq7, &paramCountSamplesq7, q7samples);
#else
	paramCountSamplesq7 = sampleFileq7Len;
	load_data_q7(sampleFileq7, paramCountSamplesq7, q7samples);
	paramCountSamplesq7 = paramCountSamplesq7/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(sampleFilef64, &paramCountSamplesf64, f64samples);
#else
	paramCountSamplesf64 = sampleFilef64Len;
	load_data_f64(sampleFilef64, paramCountSamplesf64, f64samples);
	paramCountSamplesf64 = paramCountSamplesf64/sizeof(f64);
#endif


	float f32output[MAX_SIZE] = {0};
    double f64output[MAX_SIZE] = {0};
    q15 q15output[MAX_SIZE] = {0};
    q31 q31output[MAX_SIZE] = {0};
    q7 q7output[MAX_SIZE] = {0};

    float * poutf32;
    poutf32 = f32output;
    double * poutf64;
    poutf64 = f64output;
    q31 * pout31;
    pout31 = q31output;
    q15 * pout15;
    pout15 = q15output;
    q7 * pout7;
    pout7 = q7output;


// =====================
	printf("== mips_weighted_sum_f32 0 test ==  \n");

	f32output[0] = mips_weighted_sum_f32(f32input, f32inputweights, 3);
	printf("mips_weighted_sum_f32 0 finish \n");

	printf("mips_weighted_sum_f32 0 checking \n\n");

	rel_check_special_f32(&f32ref[0], poutf32, 1,REL_ERROR);

	printf("\n== mips_weighted_sum_f32 0 check done  == \n\n");

// =====================
	printf("== mips_weighted_sum_f32 1 test ==  \n");

	f32output[0] = mips_weighted_sum_f32(f32input, f32inputweights, 8);
	printf("mips_weighted_sum_f32 1 finish \n");

	printf("mips_weighted_sum_f32 1 checking \n\n");

	rel_check_special_f32(&f32ref[1], poutf32, 1,REL_ERROR);

	printf("\n== mips_weighted_sum_f32 1 check done  == \n\n");

// =====================
	printf("== mips_weighted_sum_f32 2 test ==  \n");

	f32output[0] = mips_weighted_sum_f32(f32input, f32inputweights, 11);
	printf("mips_weighted_sum_f32 2 finish \n");

	printf("mips_weighted_sum_f32 2 checking \n\n");

	rel_check_special_f32(&f32ref[2], poutf32, 1,REL_ERROR);

	printf("\n== mips_weighted_sum_f32 2 check done  == \n\n");


// =====================

	printf("== mips_copy_f32 3 test ==  \n");
	mips_copy_f32(f32samples, poutf32, 3);
	printf("mips_copy_f32 3 finish \n");

	printf("mips_copy_f32 3 checking \n\n");

    eq_check_special_f32(f32samples, poutf32, 3);

	printf("\n== mips_copy_f32 3 check done  == \n\n");

// =====================

	printf("== mips_copy_f32 8 test ==  \n");
	mips_copy_f32(f32samples, poutf32, 8);
	printf("mips_copy_f32 8 finish \n");

	printf("mips_copy_f32 8 checking \n\n");

    eq_check_special_f32(f32samples, poutf32, 8);

	printf("\n== mips_copy_f32 8 check done  == \n\n");

// =====================

	printf("== mips_copy_f32 11 test ==  \n");
	mips_copy_f32(f32samples, poutf32, 11);
	printf("mips_copy_f32 11 finish \n");

	printf("mips_copy_f32 11 checking \n\n");

    eq_check_special_f32(f32samples, poutf32, 11);

	printf("\n== mips_copy_f32 11 check done  == \n\n");


// =====================

    f32 val = 1.1;

	printf("== mips_fill_f32 3 test ==  \n");
	mips_fill_f32(val, poutf32, 3);

	printf("mips_fill_f32 3 finish \n");

	printf("mips_fill_f32 3 checking \n\n");

    for(int i=0 ; i < 3; i++){
    eq_check_special_f32(&val, poutf32, 1);
    poutf32++;
}

	printf("\n== mips_fill_f32 3 check done  == \n\n");

// =====================

	printf("== mips_fill_f32 8 test ==  \n");
	mips_fill_f32(val, poutf32, 8);

	printf("mips_fill_f32 8 finish \n");

	printf("mips_fill_f32 8 checking \n\n");

    for(int i=0 ; i < 8; i++){
    eq_check_special_f32(&val, poutf32, 1);
    poutf32++;
}

	printf("\n== mips_fill_f32 8 check done  == \n\n");

// =====================

	printf("== mips_fill_f32 11 test ==  \n");
	mips_fill_f32(val, poutf32, 11);

	printf("mips_fill_f32 11 finish \n");

	printf("mips_fill_f32 11 checking \n\n");

    for(int i=0 ; i < 11; i++){
    eq_check_special_f32(&val, poutf32, 1);
    poutf32++;
}

	printf("\n== mips_fill_f32 11 check done  == \n\n");

// =====================

	printf("== mips_float_to_q15 7 test ==  \n");
	mips_float_to_q15(f32samples, pout15, 7);

	printf("mips_float_to_q15 7 finish \n");

	printf("mips_float_to_q15 7 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q15(sampleFileq15, pout15, 7, ABS_Q15_ERROR);
#else
	near_check_special_q15(q15samples, pout15, 7, ABS_Q15_ERROR);
#endif


	printf("\n== mips_float_to_q15 7 check done  == \n\n");

// =====================

	printf("== mips_float_to_q15 16 test ==  \n");
	mips_float_to_q15(f32samples, pout15, 16);

	printf("mips_float_to_q15 16 finish \n");

	printf("mips_float_to_q15 16 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q15(sampleFileq15, pout15, 16, ABS_Q15_ERROR);
#else
	near_check_special_q15(q15samples, pout15, 16, ABS_Q15_ERROR);
#endif


	printf("\n== mips_float_to_q15 16 check done  == \n\n");

// =====================

	printf("== mips_float_to_q15 17 test ==  \n");
	mips_float_to_q15(f32samples, pout15, 17);

	printf("mips_float_to_q15 17 finish \n");

	printf("mips_float_to_q15 17 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q15(sampleFileq15, pout15, 17, ABS_Q15_ERROR);
#else
	near_check_special_q15(q15samples, pout15, 17, ABS_Q15_ERROR);
#endif


	printf("\n== mips_float_to_q15 17 check done  == \n\n");

// =====================

	printf("== mips_float_to_q31 3 test ==  \n");
	mips_float_to_q31(f32samples, pout31, 3);

	printf("mips_float_to_q31 3 finish \n");

	printf("mips_float_to_q31 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q31(sampleFileq31, pout31, 3, ABS_Q31_ERROR);
#else
	near_check_special_q31(q31samples, pout31, 3, ABS_Q31_ERROR);
#endif


	printf("\n== mips_float_to_q31 3 check done  == \n\n");

// =====================

	printf("== mips_float_to_q31 8 test ==  \n");
	mips_float_to_q31(f32samples, pout31, 8);

	printf("mips_float_to_q31 8 finish \n");

	printf("mips_float_to_q31 8 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q31(sampleFileq31, pout31, 8, ABS_Q31_ERROR);
#else
	near_check_special_q31(q31samples, pout31, 8, ABS_Q31_ERROR);
#endif


	printf("\n== mips_float_to_q31 8 check done  == \n\n");

// =====================

	printf("== mips_float_to_q31 11 test ==  \n");
	mips_float_to_q31(f32samples, pout31, 11);

	printf("mips_float_to_q31 11 finish \n");

	printf("mips_float_to_q31 11 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q31(sampleFileq31, pout31, 11, ABS_Q31_ERROR);
#else
	near_check_special_q31(q31samples, pout31, 11, ABS_Q31_ERROR);
#endif


	printf("\n== mips_float_to_q31 11 check done  == \n\n");

// =====================

	printf("== mips_float_to_q7 15 test ==  \n");
	mips_float_to_q7(f32samples, pout7, 15);

	printf("mips_float_to_q7 15 finish \n");

	printf("mips_float_to_q7 15 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q7(sampleFileq7, pout7, 15, ABS_Q7_ERROR);
#else
	near_check_special_q7(q7samples, pout7, 15, ABS_Q7_ERROR);
#endif


	printf("\n== mips_float_to_q7 15 check done  == \n\n");

// =====================

	printf("== mips_float_to_q7 32 test ==  \n");
	mips_float_to_q7(f32samples, pout7, 32);

	printf("mips_float_to_q7 32 finish \n");

	printf("mips_float_to_q7 32 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q7(sampleFileq7, pout7, 32, ABS_Q7_ERROR);
#else
	near_check_special_q7(q7samples, pout7, 32, ABS_Q7_ERROR);
#endif


	printf("\n== mips_float_to_q7 32 check done  == \n\n");

// =====================

	printf("== mips_float_to_q7 33 test ==  \n");
	mips_float_to_q7(f32samples, pout7, 33);

	printf("mips_float_to_q7 33 finish \n");

	printf("mips_float_to_q7 33 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q7(sampleFileq7, pout7, 33, ABS_Q7_ERROR);
#else
	near_check_special_q7(q7samples, pout7, 33, ABS_Q7_ERROR);
#endif


	printf("\n== mips_float_to_q7 33 check done  == \n\n");


// =====================

	printf("== mips_float_to_f64 7 test ==  \n");
	mips_float_to_f64(f32samples, poutf64, 7);

	printf("mips_float_to_f64 7 finish \n");

	printf("mips_float_to_f64 7 checking \n\n");

#if defined(NOT_EMBEDDED)
	rel_check_f64(sampleFilef64, poutf64, 7, REL_ERROR);
#else
	rel_check_special_f64(f64samples, poutf64, 7, REL_ERROR);
#endif


	printf("\n== mips_float_to_f64 7 check done  == \n\n");

// =====================

	printf("== mips_float_to_f64 16 test ==  \n");
	mips_float_to_f64(f32samples, poutf64, 16);

	printf("mips_float_to_f64 16 finish \n");

	printf("mips_float_to_f64 16 checking \n\n");

#if defined(NOT_EMBEDDED)
	rel_check_f64(sampleFilef64, poutf64, 16, REL_ERROR);
#else
	rel_check_special_f64(f64samples, poutf64, 16, REL_ERROR);
#endif


	printf("\n== mips_float_to_f64 16 check done  == \n\n");

// =====================

	printf("== mips_float_to_f64 17 test ==  \n");
	mips_float_to_f64(f32samples, poutf64, 17);

	printf("mips_float_to_f64 17 finish \n");

	printf("mips_float_to_f64 17 checking \n\n");

#if defined(NOT_EMBEDDED)
	rel_check_f64(sampleFilef64, poutf64, 17, REL_ERROR);
#else
	rel_check_special_f64(f64samples, poutf64, 17, REL_ERROR);
#endif


	printf("\n== mips_float_to_f64 17 check done  == \n\n");


// =====================

	printf("== test_bitonic_sort_out_f32 16 test ==  \n");

    mips_sort_instance_f32 S;
    mips_sort_init_f32(&S, MIPS_SORT_BITONIC, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputbitonic16,poutf32, 16);

	printf("test_bitonic_sort_out_f32 16 finish \n");

	printf("test_bitonic_sort_out_f32 16 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFilebitonic16, poutf32, 16);
#else
	eq_check_special_f32(SupportF32_Reference8_f32, poutf32, 16);
#endif


	printf("\n== test_bitonic_sort_out_f32 16 check done  == \n\n");

// =====================

	printf("== test_bitonic_sort_out_f32 32 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_BITONIC, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputbitonic32,poutf32, 32);

	printf("test_bitonic_sort_out_f32 32 finish \n");

	printf("test_bitonic_sort_out_f32 32 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFilebitonic32, poutf32, 32);
#else
	eq_check_special_f32(SupportF32_Reference9_f32, poutf32, 32);
#endif


	printf("\n== test_bitonic_sort_out_f32 32 check done  == \n\n");

// =====================

	printf("== test_bitonic_sort_in_f32 32 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_BITONIC, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputbitonic32,f32inputbitonic32, 32);

	printf("test_bitonic_sort_in_f32 32 finish \n");

	printf("test_bitonic_sort_in_f32 32 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFilebitonic32, f32inputbitonic32, 32);
#else
	eq_check_special_f32(SupportF32_Reference9_f32, f32inputbitonic32, 32);
#endif


	printf("\n== test_bitonic_sort_in_f32 32 check done  == \n\n");

// =====================

	printf("== test_bitonic_sort_const_f32 16 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_BITONIC, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputcost,poutf32, 16);

	printf("test_bitonic_sort_const_f32 16 finish \n");

	printf("test_bitonic_sort_const_f32 16 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFileconst, poutf32, 16);
#else
	eq_check_special_f32(SupportF32_Reference10_f32, poutf32, 16);
#endif


	printf("\n== test_bitonic_sort_const_f32 16 check done  == \n\n");

// =====================

	printf("== test_bubble_sort_out_f32 11 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_BUBBLE, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputsort,poutf32, 11);

	printf("test_bubble_sort_out_f32 11 finish \n");

	printf("test_bubble_sort_out_f32 11 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFilesort, poutf32, 11);
#else
	eq_check_special_f32(SupportF32_Reference7_f32, poutf32, 11);
#endif


	printf("\n== test_bubble_sort_out_f32 11 check done  == \n\n");

// =====================

	printf("== test_bubble_sort_in_f32 11 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_BUBBLE, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputsort,f32inputsort, 11);

	printf("test_bubble_sort_in_f32 11 finish \n");

	printf("test_bubble_sort_in_f32 11 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFilesort, f32inputsort, 11);
#else
	eq_check_special_f32(SupportF32_Reference7_f32, f32inputsort, 11);
#endif


	printf("\n== test_bubble_sort_in_f32 11 check done  == \n\n");

// =====================

	printf("== test_bubble_sort_const_f32 16 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_BUBBLE, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputcost,poutf32, 16);

	printf("test_bubble_sort_const_f32 16 finish \n");

	printf("test_bubble_sort_const_f32 16 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFileconst, poutf32, 16);
#else
	eq_check_special_f32(SupportF32_Reference10_f32, poutf32, 16);
#endif


	printf("\n== test_bubble_sort_const_f32 16 check done  == \n\n");

// =====================

	printf("== test_heap_sort_out_f32 11 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_HEAP, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputsort,poutf32, 11);

	printf("test_heap_sort_out_f32 11 finish \n");

	printf("test_heap_sort_out_f32 11 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFilesort, poutf32, 11);
#else
	eq_check_special_f32(SupportF32_Reference7_f32, poutf32, 11);
#endif


	printf("\n== test_heap_sort_out_f32 11 check done  == \n\n");

// =====================

	printf("== test_heap_sort_in_f32 11 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_HEAP, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputsort,f32inputsort, 11);

	printf("test_heap_sort_in_f32 11 finish \n");

	printf("test_heap_sort_in_f32 11 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFilesort, f32inputsort, 11);
#else
	eq_check_special_f32(SupportF32_Reference7_f32, f32inputsort, 11);
#endif


	printf("\n== test_heap_sort_in_f32 11 check done  == \n\n");

// =====================

	printf("== test_heap_sort_const_f32 16 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_HEAP, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputcost,poutf32, 16);

	printf("test_heap_sort_const_f32 16 finish \n");

	printf("test_heap_sort_const_f32 16 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFileconst, poutf32, 16);
#else
	eq_check_special_f32(SupportF32_Reference10_f32, poutf32, 16);
#endif


	printf("\n== test_heap_sort_const_f32 16 check done  == \n\n");

// =====================

	printf("== test_insertion_sort_out_f32 11 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_INSERTION, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputsort,poutf32, 11);

	printf("test_insertion_sort_out_f32 11 finish \n");

	printf("test_insertion_sort_out_f32 11 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFilesort, poutf32, 11);
#else
	eq_check_special_f32(SupportF32_Reference7_f32, poutf32, 11);
#endif


	printf("\n== test_insertion_sort_out_f32 11 check done  == \n\n");

// =====================

	printf("== test_insertion_sort_in_f32 11 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_INSERTION, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputsort,f32inputsort, 11);

	printf("test_insertion_sort_in_f32 11 finish \n");

	printf("test_insertion_sort_in_f32 11 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFilesort, f32inputsort, 11);
#else
	eq_check_special_f32(SupportF32_Reference7_f32, f32inputsort, 11);
#endif


	printf("\n== test_insertion_sort_in_f32 11 check done  == \n\n");

// =====================

	printf("== test_insertion_sort_const_f32 16 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_INSERTION, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputcost,poutf32, 16);

	printf("test_insertion_sort_const_f32 16 finish \n");

	printf("test_insertion_sort_const_f32 16 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFileconst, poutf32, 16);
#else
	eq_check_special_f32(SupportF32_Reference10_f32, poutf32, 16);
#endif


	printf("\n== test_insertion_sort_const_f32 16 check done  == \n\n");


// =====================

	printf("== test_merge_sort_out_f32 11 test ==  \n");

    f32 *buf1;
    f32 buffer1[11] = {0};
    buf1 = buffer1;
    buf1 = (f32 *)malloc((11)*sizeof(f32) );
    mips_merge_sort_instance_f32 S2;

    mips_merge_sort_init_f32(&S2, MIPS_SORT_ASCENDING, buf1);
    mips_merge_sort_f32(&S2,f32inputsort,poutf32,11);

	printf("test_merge_sort_out_f32 11 finish \n");

	printf("test_merge_sort_out_f32 11 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFilesort, poutf32, 11);
#else
	eq_check_special_f32(SupportF32_Reference7_f32, poutf32, 11);
#endif


	printf("\n== test_merge_sort_out_f32 11 check done  == \n\n");

// =====================

	printf("== test_merge_sort_const_f32 16 test ==  \n");
    
    f32 *buf2;
    f32 buffer2[16] = {0};
    buf2 = buffer2;
    buf2 = (f32 *)malloc((16)*sizeof(f32) );

    mips_merge_sort_init_f32(&S2, MIPS_SORT_ASCENDING, buf2);
    mips_merge_sort_f32(&S2,f32inputcost,poutf32,16);

	printf("test_merge_sort_const_f32 16 finish \n");

	printf("test_merge_sort_const_f32 16 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFileconst, poutf32, 16);
#else
	eq_check_special_f32(SupportF32_Reference10_f32, poutf32, 16);
#endif


	printf("\n== test_merge_sort_const_f32 16 check done  == \n\n");

// =====================

	printf("== test_quick_sort_out_f32 11 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_QUICK, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputsort,poutf32, 11);

	printf("test_quick_sort_out_f32 11 finish \n");

	printf("test_quick_sort_out_f32 11 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFilesort, poutf32, 11);
#else
	eq_check_special_f32(SupportF32_Reference7_f32, poutf32, 11);
#endif


	printf("\n== test_quick_sort_out_f32 11 check done  == \n\n");

// =====================

	printf("== test_quick_sort_in_f32 11 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_QUICK, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputsort,f32inputsort, 11);

	printf("test_quick_sort_in_f32 11 finish \n");

	printf("test_quick_sort_in_f32 11 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFilesort, f32inputsort, 11);
#else
	eq_check_special_f32(SupportF32_Reference7_f32, f32inputsort, 11);
#endif


	printf("\n== test_quick_sort_in_f32 11 check done  == \n\n");

// =====================

	printf("== test_quick_sort_const_f32 16 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_QUICK, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputcost,poutf32, 16);

	printf("test_quick_sort_const_f32 16 finish \n");

	printf("test_quick_sort_const_f32 16 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFileconst, poutf32, 16);
#else
	eq_check_special_f32(SupportF32_Reference10_f32, poutf32, 16);
#endif


	printf("\n== test_quick_sort_const_f32 16 check done  == \n\n");

// =====================

	printf("== test_selection_sort_out_f32 11 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_SELECTION, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputsort,poutf32, 11);

	printf("test_selection_sort_out_f32 11 finish \n");

	printf("test_selection_sort_out_f32 11 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFilesort, poutf32, 11);
#else
	eq_check_special_f32(SupportF32_Reference7_f32, poutf32, 11);
#endif


	printf("\n== test_selection_sort_out_f32 11 check done  == \n\n");

// =====================

	printf("== test_selection_sort_in_f32 11 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_SELECTION, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputsort,f32inputsort, 11);

	printf("test_selection_sort_in_f32 11 finish \n");

	printf("test_selection_sort_in_f32 11 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFilesort, f32inputsort, 11);
#else
	eq_check_special_f32(SupportF32_Reference7_f32, f32inputsort, 11);
#endif


	printf("\n== v 11 check done  == \n\n");

// =====================

	printf("== test_selection_sort_const_f32 16 test ==  \n");

    mips_sort_init_f32(&S, MIPS_SORT_SELECTION, MIPS_SORT_ASCENDING);
    mips_sort_f32(&S,f32inputcost,poutf32, 16);

	printf("test_selection_sort_const_f32 16 finish \n");

	printf("test_selection_sort_const_f32 16 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFileconst, poutf32, 16);
#else
	eq_check_special_f32(SupportF32_Reference10_f32, poutf32, 16);
#endif


	printf("\n== test_selection_sort_const_f32 16 check done  == \n\n");
    return 0;
   
}