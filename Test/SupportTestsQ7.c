#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/support_functions.h"

#define SNR_THRESHOLD 120
#define REL_ERROR (1.0e-5)
#define ABS_Q15_ERROR ((q15)(1<<8))
#define ABS_Q31_ERROR ((q31)(1<<24))
#define ABS_Q7_ERROR ((q7)10)

#if defined ( __CC_MIPS )
#pragma diag_specialpress 170
#endif

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
	snprintf(f64inputFile, sizeof(f64inputFile), "%s%s%s", Patterns_PATH, SupportQ7, "Samples6_f64.txt");
#else
	f64inputFile = SupportQ7_Samples6_f64;
	f64inputFileLen = sizeof(SupportQ7_Samples6_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFile, sizeof(q15inputFile), "%s%s%s", Patterns_PATH, SupportQ7, "Samples3_q15.txt");
#else
	q15inputFile = SupportQ7_Samples3_q15;
	q15inputFileLen = sizeof(SupportQ7_Samples3_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFile, sizeof(q31inputFile), "%s%s%s", Patterns_PATH, SupportQ7, "Samples4_q31.txt");
#else
	q31inputFile = SupportQ7_Samples4_q31;
	q31inputFileLen = sizeof(SupportQ7_Samples4_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q7inputFile, sizeof(q7inputFile), "%s%s%s", Patterns_PATH, SupportQ7, "Samples5_q7.txt");
#else
	q7inputFile = SupportQ7_Samples5_q7;
	q7inputFileLen = sizeof(SupportQ7_Samples5_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFile, sizeof(f32inputFile), "%s%s%s", Patterns_PATH, SupportQ7, "Samples1_f32.txt");
#else
	f32inputFile = SupportQ7_Samples1_f32;
	f32inputFileLen = sizeof(SupportQ7_Samples1_f32);
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
	printf("== mips_copy_q7 3 test ==  \n");
	mips_copy_q7(q7input, q7output, 15);
	printf("mips_copy_q7 3 finish \n");

	printf("mips_copy_q7 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_q7(q7inputFile, q7output, 15);
#else
	eq_check_special_q7(q7input, q7output, 15);
#endif


	printf("\n== mips_copy_q7 3 check done  == \n\n");

// =====================
	printf("== mips_copy_q7 4N test ==  \n");
	mips_copy_q7(q7input, q7output, 32);
	printf("mips_copy_q7 4N finish \n");

	printf("mips_copy_q7 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_q7(q7inputFile, q7output, 32);
#else
	eq_check_special_q7(q7input, q7output, 32);
#endif


	printf("\n== mips_copy_q7 4N check done  == \n\n");

// =====================
	printf("== mips_copy_q7 4N+1 test ==  \n");
	mips_copy_q7(q7input, q7output, 47);
	printf("mips_copy_q7 4N+1 finish \n");

	printf("mips_copy_q7 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_q7(q7inputFile, q7output, 47);
#else
	eq_check_special_q7(q7input, q7output, 47);
#endif


	printf("\n== mips_copy_q7 4N+1 check done  == \n\n");

// =====================
	printf("== mips_fill_q7 3 test ==  \n");

    q7 val = 0x40;
    int i;
	mips_fill_q7(val, q7output, 15);
	printf("mips_fill_q7 3 finish \n");

	printf("mips_fill_q7 3 checking \n\n");
    for(i = 0; i < 15; i++){
	eq_check_special_q7(&val, &q7output[i], 1);
    }


	printf("\n== mips_fill_q7 3 check done  == \n\n");

// =====================
	printf("== mips_fill_q7 4N test ==  \n");
	mips_fill_q7(val, q7output, 32);
	printf("mips_fill_q7 4N finish \n");

	printf("mips_fill_q7 4N checking \n\n");

    for(i = 0; i < 32; i++){
	eq_check_special_q7(&val, &q7output[i], 1);
    }

	printf("\n== mips_fill_q7 4N check done  == \n\n");

// =====================
	printf("== mips_fill_q7 4N+1 test ==  \n");
	mips_fill_q7(val, q7output, 47);
	printf("mips_fill_q7 4N+1 finish \n");

	printf("mips_fill_q7 4N+1 checking \n\n");

    for(i = 0; i < 47; i++){
	eq_check_special_q7(&val, &q7output[i], 1);
    }

	printf("\n== mips_fill_q7 4N+1 check done  == \n\n");

// =====================
	printf("== mips_q7_to_f64 3 test ==  \n");
	mips_q7_to_f64(q7input, f64output, 15);
	printf("mips_q7_to_f64 3 finish \n");

	printf("mips_q7_to_f64 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	close_check_f64(f64inputFile, f64output, 15, 0.01, REL_ERROR);
#else
	close_check_special_f64(f64input, f64output, 15, 0.01, REL_ERROR);
#endif



	printf("\n== mips_q7_to_f64 3 check done  == \n\n");

// =====================
	printf("== mips_q7_to_f64 4N test ==  \n");
	mips_q7_to_f64(q7input, f64output, 32);
	printf("mips_q7_to_f64 4N finish \n");

	printf("mips_q7_to_f64 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	close_check_f64(f64inputFile, f64output, 32, 0.01, REL_ERROR);
#else
	close_check_special_f64(f64input, f64output, 32, 0.01, REL_ERROR);
#endif


	printf("\n== mips_q7_to_f64 4N check done  == \n\n");

// =====================
	printf("== mips_q7_to_f64 4N+1 test ==  \n");
	mips_q7_to_f64(q7input, f64output, 47);
	printf("mips_q7_to_f64 4N+1 finish \n");

	printf("mips_q7_to_f64 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	close_check_f64(f64inputFile, f64output, 47, 0.01, REL_ERROR);
#else
	close_check_special_f64(f64input, f64output, 47, 0.01, REL_ERROR);
#endif


	printf("\n== mips_q7_to_f64 4N+1 check done  == \n\n");

// =====================
	printf("== mips_q7_to_float 3 test ==  \n");
	mips_q7_to_float(q7input, f32output, 15);
	printf("mips_q7_to_float 3 finish \n");

	printf("mips_q7_to_float 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	close_check_f32(f32inputFile, f32output, 15, 0.01, REL_ERROR);
#else
	close_check_special_f32(f32input, f32output, 15, 0.01, REL_ERROR);
#endif



	printf("\n== mips_q7_to_float 3 check done  == \n\n");

// =====================
	printf("== mips_q7_to_float 4N test ==  \n");
	mips_q7_to_float(q7input, f32output, 32);
	printf("mips_q7_to_float 4N finish \n");

	printf("mips_q7_to_float 4N checking \n\n");

#if defined(NOT_EMBEDDED)
	close_check_f32(f32inputFile, f32output, 32, 0.01, REL_ERROR);
#else
	close_check_special_f32(f32input, f32output, 32, 0.01, REL_ERROR);
#endif


	printf("\n== mips_q7_to_float 4N check done  == \n\n");

// =====================
	printf("== mips_q7_to_float 4N+1 test ==  \n");
	mips_q7_to_float(q7input, f32output, 47);
	printf("mips_q7_to_float 4N+1 finish \n");

	printf("mips_q7_to_float 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	close_check_f32(f32inputFile, f32output, 47, 0.01, REL_ERROR);
#else
	close_check_special_f32(f32input, f32output, 47, 0.01, REL_ERROR);
#endif


	printf("\n== mips_q7_to_float 4N+1 check done  == \n\n");

// =====================
	printf("== mips_q7_to_q31 3 test ==  \n");
	mips_q7_to_q31(q7input, q31output, 15);
	printf("mips_q7_to_q31 3 finish \n");

	printf("mips_q7_to_q31 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q31(q31inputFile, q31output, 15, ABS_Q31_ERROR);
#else
	near_check_special_q31(q31input, q31output, 15, ABS_Q31_ERROR);
#endif



	printf("\n== mips_q7_to_q31 3 check done  == \n\n");

// =====================
	printf("== mips_q7_to_q31 4N test ==  \n");
	mips_q7_to_q31(q7input, q31output, 32);
	printf("mips_q7_to_q31 4N finish \n");

	printf("mips_q7_to_q31 4N checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q31(q31inputFile, q31output, 15, ABS_Q31_ERROR);
#else
	near_check_special_q31(q31input, q31output, 15, ABS_Q31_ERROR);
#endif


	printf("\n== mips_q7_to_q31 4N check done  == \n\n");

// =====================
	printf("== mips_q7_to_q31 4N+1 test ==  \n");
	mips_q7_to_q31(q7input, q31output, 47);
	printf("mips_q7_to_q31 4N+1 finish \n");

	printf("mips_q7_to_q31 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q31(q31inputFile, q31output, 15, ABS_Q31_ERROR);
#else
	near_check_special_q31(q31input, q31output, 15, ABS_Q31_ERROR);
#endif


	printf("\n== mips_q7_to_q31 4N+1 check done  == \n\n");

// =====================
	printf("== mips_q7_to_q15 3 test ==  \n");
	mips_q7_to_q15(q7input, q15output, 15);
	printf("mips_q7_to_q15 3 finish \n");

	printf("mips_q7_to_q15 3 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q15(q15inputFile, q15output, 15, ABS_Q15_ERROR);
#else
	near_check_special_q15(q15input, q15output, 15, ABS_Q15_ERROR);
#endif



	printf("\n== mips_q7_to_q15 3 check done  == \n\n");

// =====================
	printf("== mips_q7_to_q15 4N test ==  \n");
	mips_q7_to_q15(q7input, q15output, 32);
	printf("mips_q7_to_q15 4N finish \n");

	printf("mips_q7_to_q15 4N checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q15(q15inputFile, q15output, 15, ABS_Q15_ERROR);
#else
	near_check_special_q15(q15input, q15output, 15, ABS_Q15_ERROR);
#endif


	printf("\n== mips_q7_to_q15 4N check done  == \n\n");

// =====================
	printf("== mips_q7_to_q15 4N+1 test ==  \n");
	mips_q7_to_q15(q7input, q15output, 47);
	printf("mips_q7_to_q15 4N+1 finish \n");

	printf("mips_q7_to_q15 4N+1 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q15(q15inputFile, q15output, 15, ABS_Q15_ERROR);
#else
	near_check_special_q15(q15input, q15output, 15, ABS_Q15_ERROR);
#endif


	printf("\n== mips_q7_to_q15 4N+1 check done  == \n\n");

// =====================


    static const q7 testReadQ7[4]={-4,-3,-2,1};
    static q7 testWriteQ7[4]={0,0,0,0};


        q31 result=0;
        q7 *p = (q7*)testReadQ7;

	printf("== test_read_q7x4_ia test ==  \n");
        result = read_q7x4_ia(&p);

        ASSERT_TRUE(result == 0x01FEFDFC);
        ASSERT_TRUE(p == testReadQ7 + 4);
	printf("\n== test_read_q7x4_ia check done  == \n\n");

	printf("== test_read_q7x4_da test ==  \n");

        q31 resultd=0;
        q7 *pd = (q7*)testReadQ7;

        resultd = read_q7x4_da(&pd);

        ASSERT_TRUE(resultd == 0x01FEFDFC);
        ASSERT_TRUE(pd == testReadQ7 - 4);
	printf("\n== test_read_q7x4_da check done  == \n\n");

	printf("== test_write_q7x4_ia test ==  \n");
        q31 q31val = 0x01FEFDFC;
        q7 *pw = (q7*)testWriteQ7;

        testWriteQ7[0] = 0;
        testWriteQ7[1] = 0;
        testWriteQ7[2] = 0;
        testWriteQ7[3] = 0;

        write_q7x4_ia(&pw,q31val);

        ASSERT_TRUE(testWriteQ7[0] == -4);
        ASSERT_TRUE(testWriteQ7[1] == -3);
        ASSERT_TRUE(testWriteQ7[2] == -2);
        ASSERT_TRUE(testWriteQ7[3] == 1);
        ASSERT_TRUE(pw == testWriteQ7 + 4);
	printf("\n== test_write_q7x4_ia check done  == \n\n");

    return 0;
}