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
	int paramCountInputf64 = 0;
    int paramCountInputf32 = 0;
    int paramCountInputq15 = 0;
    int paramCountInputq31 = 0;
    int paramCountInputq7 = 0;

	f64 f64input[MAX_SIZE] = {0};
    f32 f32input[MAX_SIZE] = {0};
    q15 q15input[MAX_SIZE] = {0};
    q31 q31input[MAX_SIZE] = {0};
    q7 q7input[MAX_SIZE] = {0};


	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char f64inputFile[255] = {0};
#else
	void *f64inputFile;
	int f64inputFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFile[255] = {0};
#else
	void *f32inputFile;
	int f32inputFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFile[255] = {0};
#else
	void *q15inputFile;
	int q15inputFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFile[255] = {0};
#else
	void *q31inputFile;
	int q31inputFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q7inputFile[255] = {0};
#else
	void *q7inputFile;
	int q7inputFileLen = 0;
#endif



	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(f64inputFile, sizeof(f64inputFile), "%s%s%s", Patterns_PATH, SupportF64, "Samples1_f64.txt");
#else
	f64inputFile = SupportF64_Samples1_f64;
	f64inputFileLen = sizeof(SupportF64_Samples1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFile, sizeof(q15inputFile), "%s%s%s", Patterns_PATH, SupportF64, "Samples3_q15.txt");
#else
	q15inputFile = SupportF64_Samples3_q15;
	q15inputFileLen = sizeof(SupportF64_Samples3_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFile, sizeof(q31inputFile), "%s%s%s", Patterns_PATH, SupportF64, "Samples4_q31.txt");
#else
	q31inputFile = SupportF64_Samples4_q31;
	q31inputFileLen = sizeof(SupportF64_Samples4_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q7inputFile, sizeof(q7inputFile), "%s%s%s", Patterns_PATH, SupportF64, "Samples5_q7.txt");
#else
	q7inputFile = SupportF64_Samples5_q7;
	q7inputFileLen = sizeof(SupportF64_Samples5_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFile, sizeof(f32inputFile), "%s%s%s", Patterns_PATH, SupportF64, "Samples6_f32.txt");
#else
	f32inputFile = SupportF64_Samples6_f32;
	f32inputFileLen = sizeof(SupportF64_Samples6_f32);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFile, &paramCountInputf64, f64input);
#else
	paramCountInputf64 = f64inputFileLen;
	load_data_f64(f64inputFile, paramCountInputf64, f64input);
	paramCountInputf64 = paramCountInputf64/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFile, &paramCountInputq15, q15input);
#else
	paramCountInputq15 = q15inputFileLen;
	load_data_q15(q15inputFile, paramCountInputq15, q15input);
	paramCountInputq15 = paramCountInputq15/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFile, &paramCountInputq31, q31input);
#else
	paramCountInputq31 = q31inputFileLen;
	load_data_q31(q31inputFile, paramCountInputq31, q31input);
	paramCountInputq31 = paramCountInputq31/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q7(q7inputFile, &paramCountInputq7, q7input);
#else
	paramCountInputq7 = q7inputFileLen;
	load_data_q7(q7inputFile, paramCountInputq7, q7input);
	paramCountInputq7 = paramCountInputq7/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFile, &paramCountInputf32, f32input);
#else
	paramCountInputf32 = f32inputFileLen;
	load_data_f32(f32inputFile, paramCountInputf32, f32input);
	paramCountInputf32 = paramCountInputf32/sizeof(f32);
#endif


	f64 f64output[MAX_SIZE] = {0};
    f32 f32output[MAX_SIZE] = {0};
    q15 q15output[MAX_SIZE] = {0};
    q31 q31output[MAX_SIZE] = {0};
    q7 q7output[MAX_SIZE] = {0};

// =====================
	printf("== mips_copy_f64 2 test ==  \n");
	mips_copy_f64(f64input, f64output, 2);
	printf("mips_copy_f64 2 finish \n");

	printf("mips_copy_f64 2 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f64(f64inputFile, f64output, 2);
#else
	eq_check_special_f64(f64input, f64output, 2);
#endif


	printf("\n== mips_copy_f64 2 check done  == \n\n");

// =====================
	printf("== mips_copy_f64 4 test ==  \n");
	mips_copy_f64(f64input, f64output, 4);
	printf("mips_copy_f64 4 finish \n");

	printf("mips_copy_f64 4 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f64(f64inputFile, f64output, 4);
#else
	eq_check_special_f64(f64input, f64output, 4);
#endif


	printf("\n== mips_copy_f64 4 check done  == \n\n");

// =====================
	printf("== mips_copy_f64 5 test ==  \n");
	mips_copy_f64(f64input, f64output, 5);
	printf("mips_copy_f64 5 finish \n");

	printf("mips_copy_f64 5 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_f64(f64inputFile, f64output, 5);
#else
	eq_check_special_f64(f64input, f64output, 5);
#endif


	printf("\n== mips_copy_f64 5 check done  == \n\n");


// =====================
	printf("== test_fill_f64 2 test ==  \n");

    f64 val = 1.1;
    int i;
	mips_fill_f64(val, f64output, 2);

	printf("test_fill_f64 2 finish \n");

	printf("test_fill_f64 2 checking \n\n");
    for(i = 0; i < 2; i++){
	eq_check_special_f64(&val, &f64output[i], 1);
    }

	printf("\n== test_fill_f64 2 check done  == \n\n");

// =====================
	printf("== test_fill_f64 4 test ==  \n");
	mips_fill_f64(val, f64output, 4);

	printf("test_fill_f64 4 finish \n");

	printf("test_fill_f64 4 checking \n\n");
    for(i = 0; i < 4; i++){
	eq_check_special_f64(&val, &f64output[i], 1);
    }
	printf("\n== test_fill_f64 4 check done  == \n\n");

// =====================
	printf("== test_fill_f64 5 test ==  \n");
	mips_fill_f64(val, f64output, 5);

	printf("test_fill_f64 5 finish \n");

	printf("test_fill_f64 5 checking \n\n");
    for(i = 0; i < 5; i++){
	eq_check_special_f64(&val, &f64output[i], 1);
    }
	printf("\n== test_fill_f64 5 check done  == \n\n");

// =====================
	printf("== mips_f64_to_float 1 test ==  \n");
	mips_f64_to_float(f64input, f32output, 1);

	printf("mips_f64_to_float 1 finish \n");

	printf("mips_f64_to_float 1 checking \n\n");
#if defined(NOT_EMBEDDED)
	rel_check_f32(f32inputFile, f32output, 1, REL_ERROR);
#else
	rel_check_special_f32(f32input, f32output, 1, REL_ERROR);
#endif

	printf("\n== mips_f64_to_float 1 check done  == \n\n");

// =====================
	printf("== mips_f64_to_float 4 test ==  \n");
	mips_f64_to_float(f64input, f32output, 4);

	printf("mips_f64_to_float 4 finish \n");

	printf("mips_f64_to_float 4 checking \n\n");
#if defined(NOT_EMBEDDED)
	rel_check_f32(f32inputFile, f32output, 4, REL_ERROR);
#else
	rel_check_special_f32(f32input, f32output, 4, REL_ERROR);
#endif

	printf("\n== mips_f64_to_float 4 check done  == \n\n");

// =====================
	printf("== mips_f64_to_float 5 test ==  \n");
	mips_f64_to_float(f64input, f32output, 5);

	printf("mips_f64_to_float 5 finish \n");

	printf("mips_f64_to_float 5 checking \n\n");
#if defined(NOT_EMBEDDED)
	rel_check_f32(f32inputFile, f32output, 5, REL_ERROR);
#else
	rel_check_special_f32(f32input, f32output, 5, REL_ERROR);
#endif

	printf("\n== mips_f64_to_float 5 check done  == \n\n");



// =====================
	printf("== mips_f64_to_q15 1 test ==  \n");
	mips_f64_to_q15(f64input, q15output, 1);

	printf("mips_f64_to_q15 1 finish \n");

	printf("mips_f64_to_q15 1 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q15(q15inputFile, q15output, 1, ABS_Q15_ERROR);
#else
	near_check_special_q15(q15input, q15output, 1, ABS_Q15_ERROR);
#endif

	printf("\n== mips_f64_to_q15 1 check done  == \n\n");

// =====================
	printf("== mips_f64_to_q15 4 test ==  \n");
	mips_f64_to_q15(f64input, q15output, 4);

	printf("mips_f64_to_q15 4 finish \n");

	printf("mips_f64_to_q15 4 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q15(q15inputFile, q15output, 4, ABS_Q15_ERROR);
#else
	near_check_special_q15(q15input, q15output, 4, ABS_Q15_ERROR);
#endif

	printf("\n== mips_f64_to_q15 4 check done  == \n\n");

// =====================
	printf("== mips_f64_to_q15 5 test ==  \n");
	mips_f64_to_q15(f64input, q15output, 5);

	printf("mips_f64_to_q15 5 finish \n");

	printf("mips_f64_to_q15 5 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q15(q15inputFile, q15output, 5, ABS_Q15_ERROR);
#else
	near_check_special_q15(q15input, q15output, 5, ABS_Q15_ERROR);
#endif

	printf("\n== mips_f64_to_q15 5 check done  == \n\n");

// =====================
	printf("== mips_f64_to_q31 1 test ==  \n");
	mips_f64_to_q31(f64input, q31output, 1);

	printf("mips_f64_to_q31 1 finish \n");

	printf("mips_f64_to_q31 1 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q31(q31inputFile, q31output, 1, ABS_Q31_ERROR);
#else
	near_check_special_q31(q31input, q31output, 1, ABS_Q31_ERROR);
#endif

	printf("\n== mips_f64_to_q31 1 check done  == \n\n");

// =====================
	printf("== mips_f64_to_q31 4 test ==  \n");
	mips_f64_to_q31(f64input, q31output, 4);

	printf("mips_f64_to_q31 4 finish \n");

	printf("mips_f64_to_q31 4 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q31(q31inputFile, q31output, 4, ABS_Q31_ERROR);
#else
	near_check_special_q31(q31input, q31output, 4, ABS_Q31_ERROR);
#endif

	printf("\n== mips_f64_to_q31 4 check done  == \n\n");

// =====================
	printf("== mips_f64_to_q31 6 test ==  \n");
	mips_f64_to_q31(f64input, q31output, 6);

	printf("mips_f64_to_q31 6 finish \n");

	printf("mips_f64_to_q31 6 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q31(q31inputFile, q31output, 6, ABS_Q31_ERROR);
#else
	near_check_special_q31(q31input, q31output, 6, ABS_Q31_ERROR);
#endif

	printf("\n== mips_f64_to_q31 6 check done  == \n\n");

// =====================
	printf("== mips_f64_to_q7 1 test ==  \n");
	mips_f64_to_q7(f64input, q7output, 1);

	printf("mips_f64_to_q7 1 finish \n");

	printf("mips_f64_to_q7 1 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q7(q7inputFile, q7output, 1, ABS_Q7_ERROR);
#else
	near_check_special_q7(q7input, q7output, 1, ABS_Q7_ERROR);
#endif

	printf("\n== mips_f64_to_q7 1 check done  == \n\n");

// =====================
	printf("== mips_f64_to_q7 4 test ==  \n");
	mips_f64_to_q7(f64input, q7output, 4);

	printf("mips_f64_to_q7 4 finish \n");

	printf("mips_f64_to_q7 4 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q7(q7inputFile, q7output, 4, ABS_Q7_ERROR);
#else
	near_check_special_q7(q7input, q7output, 4, ABS_Q7_ERROR);
#endif

	printf("\n== mips_f64_to_q7 4 check done  == \n\n");

// =====================
	printf("== mips_f64_to_q7 5 test ==  \n");
	mips_f64_to_q7(f64input, q7output, 5);

	printf("mips_f64_to_q7 5 finish \n");

	printf("mips_f64_to_q7 5 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q7(q7inputFile, q7output, 5, ABS_Q7_ERROR);
#else
	near_check_special_q7(q7input, q7output, 5, ABS_Q7_ERROR);
#endif

	printf("\n== mips_f64_to_q7 5 check done  == \n\n");

    return 0;

}