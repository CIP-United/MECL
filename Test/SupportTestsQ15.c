#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/support_functions.h"

#define SNR_THRESHOLD 120
#define REL_ERROR (1.0e-3)
#define ABS_Q15_ERROR ((q15)10)
#define ABS_Q31_ERROR ((q31)40000)
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
	snprintf(f64inputFile, sizeof(f64inputFile), "%s%s%s", Patterns_PATH, SupportQ15, "Samples6_f64.txt");
#else
	f64inputFile = SupportQ15_Samples6_f64;
	f64inputFileLen = sizeof(SupportQ15_Samples6_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFile, sizeof(q15inputFile), "%s%s%s", Patterns_PATH, SupportQ15, "Samples3_q15.txt");
#else
	q15inputFile = SupportQ15_Samples3_q15;
	q15inputFileLen = sizeof(SupportQ15_Samples3_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFile, sizeof(q31inputFile), "%s%s%s", Patterns_PATH, SupportQ15, "Samples4_q31.txt");
#else
	q31inputFile = SupportQ15_Samples4_q31;
	q31inputFileLen = sizeof(SupportQ15_Samples4_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q7inputFile, sizeof(q7inputFile), "%s%s%s", Patterns_PATH, SupportQ15, "Samples5_q7.txt");
#else
	q7inputFile = SupportQ15_Samples5_q7;
	q7inputFileLen = sizeof(SupportQ15_Samples5_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFile, sizeof(f32inputFile), "%s%s%s", Patterns_PATH, SupportQ15, "Samples1_f32.txt");
#else
	f32inputFile = SupportQ15_Samples1_f32;
	f32inputFileLen = sizeof(SupportQ15_Samples1_f32);
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
	printf("== mips_copy_q15 7 test ==  \n");
	mips_copy_q15(q15input, q15output, 7);
	printf("mips_copy_q15 7 finish \n");

	printf("mips_copy_q15 7 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_q15(q15inputFile, q15output, 7);
#else
	eq_check_special_q15(q15input, q15output, 7);
#endif


	printf("\n== mips_copy_q15 7 check done  == \n\n");

// =====================
	printf("== mips_copy_q15 16 test ==  \n");
	mips_copy_q15(q15input, q15output, 16);
	printf("mips_copy_q15 16 finish \n");

	printf("mips_copy_q15 16 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_q15(q15inputFile, q15output, 16);
#else
	eq_check_special_q15(q15input, q15output, 16);
#endif


	printf("\n== mips_copy_q15 16 check done  == \n\n");

// =====================
	printf("== mips_copy_q15 23 test ==  \n");
	mips_copy_q15(q15input, q15output, 23);
	printf("mips_copy_q15 23 finish \n");

	printf("mips_copy_q15 23 checking \n\n");

#if defined(NOT_EMBEDDED)
	eq_check_q15(q15inputFile, q15output, 23);
#else
	eq_check_special_q15(q15input, q15output, 23);
#endif


	printf("\n== mips_copy_q15 23 check done  == \n\n");

// =====================
	printf("== mips_fill_q15 7 test ==  \n");

    q15 val = 0x4000;
    int i;
	mips_fill_q15(val, q15output, 7);
	printf("mips_fill_q15 7 finish \n");

	printf("mips_fill_q15 7 checking \n\n");
    for(i = 0; i < 7; i++){
	eq_check_special_q15(&val, &q15output[i], 1);
    }


	printf("\n== mips_fill_q15 7 check done  == \n\n");

// =====================
	printf("== mips_fill_q15 16 test ==  \n");
	mips_fill_q15(val, q15output, 16);
	printf("mips_fill_q15 16 finish \n");

	printf("mips_fill_q15 16 checking \n\n");

    for(i = 0; i < 16; i++){
	eq_check_special_q15(&val, &q15output[i], 1);
    }

	printf("\n== mips_fill_q15 16 check done  == \n\n");

// =====================
	printf("== mips_fill_q15 23 test ==  \n");
	mips_fill_q15(val, q15output, 23);
	printf("mips_fill_q15 23 finish \n");

	printf("mips_fill_q15 23 checking \n\n");

    for(i = 0; i < 23; i++){
	eq_check_special_q15(&val, &q15output[i], 1);
    }

	printf("\n== mips_fill_q15 23 check done  == \n\n");

// =====================
	printf("== mips_q15_to_f64 7 test ==  \n");
	mips_q15_to_f64(q15input, f64output, 7);
	printf("mips_q15_to_f64 7 finish \n");

	printf("mips_q15_to_f64 7 checking \n\n");

#if defined(NOT_EMBEDDED)
	rel_check_f64(f64inputFile, f64output, 7, REL_ERROR);
#else
	rel_check_special_f64(f64input, f64output, 7, REL_ERROR);
#endif


	printf("\n== mips_q15_to_f64 7 check done  == \n\n");

// =====================
	printf("== mips_q15_to_f64 16 test ==  \n");
	mips_q15_to_f64(q15input, f64output, 16);
	printf("mips_q15_to_f64 16 finish \n");

	printf("mips_q15_to_f64 16 checking \n\n");

#if defined(NOT_EMBEDDED)
	rel_check_f64(f64inputFile, f64output, 16, REL_ERROR);
#else
	rel_check_special_f64(f64input, f64output, 16, REL_ERROR);
#endif


	printf("\n== mips_q15_to_f64 16 check done  == \n\n");

// =====================
	printf("== mips_q15_to_f64 23 test ==  \n");
	mips_q15_to_f64(q15input, f64output, 23);
	printf("mips_q15_to_f64 23 finish \n");

	printf("mips_q15_to_f64 23 checking \n\n");

#if defined(NOT_EMBEDDED)
	rel_check_f64(f64inputFile, f64output, 23, REL_ERROR);
#else
	rel_check_special_f64(f64input, f64output, 23, REL_ERROR);
#endif


	printf("\n== mips_q15_to_f64 23 check done  == \n\n");

// =====================
	printf("== mips_q15_to_float 7 test ==  \n");
	mips_q15_to_float(q15input, f32output, 7);
	printf("mips_q15_to_float 7 finish \n");

	printf("mips_q15_to_float 7 checking \n\n");

#if defined(NOT_EMBEDDED)
	rel_check_f32(f32inputFile, f32output, 7, REL_ERROR);
#else
	rel_check_special_f32(f32input, f32output, 7, REL_ERROR);
#endif



	printf("\n== mips_q15_to_float 7 check done  == \n\n");

// =====================
	printf("== mips_q15_to_float 16 test ==  \n");
	mips_q15_to_float(q15input, f32output, 16);
	printf("mips_q15_to_float 16 finish \n");

	printf("mips_q15_to_float 16 checking \n\n");

#if defined(NOT_EMBEDDED)
	rel_check_f32(f32inputFile, f32output, 16, REL_ERROR);
#else
	rel_check_special_f32(f32input, f32output, 16, REL_ERROR);
#endif


	printf("\n== mips_q15_to_float 16 check done  == \n\n");

// =====================
	printf("== mips_q15_to_float 23 test ==  \n");
	mips_q15_to_float(q15input, f32output, 23);
	printf("mips_q15_to_float 23 finish \n");

	printf("mips_q15_to_float 23 checking \n\n");

#if defined(NOT_EMBEDDED)
	rel_check_f32(f32inputFile, f32output, 23, REL_ERROR);
#else
	rel_check_special_f32(f32input, f32output, 23, REL_ERROR);
#endif


	printf("\n== mips_q15_to_float 23 check done  == \n\n");

// =====================
	printf("== mips_q15_to_q31 7 test ==  \n");
	mips_q15_to_q31(q15input, q31output, 7);
	printf("mips_q15_to_q31 7 finish \n");

	printf("mips_q15_to_q31 7 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q31(q31inputFile, q31output, 7, ABS_Q31_ERROR);
#else
	near_check_special_q31(q31input, q31output, 7, ABS_Q31_ERROR);
#endif



	printf("\n== mips_q15_to_q31 7 check done  == \n\n");

// =====================
	printf("== mips_q15_to_q31 16 test ==  \n");
	mips_q15_to_q31(q15input, q31output, 16);
	printf("mips_q15_to_q31 16 finish \n");

	printf("mips_q15_to_q31 16 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q31(q31inputFile, q31output, 16, ABS_Q31_ERROR);
#else
	near_check_special_q31(q31input, q31output, 16, ABS_Q31_ERROR);
#endif


	printf("\n== mips_q15_to_q31 16 check done  == \n\n");

// =====================
	printf("== mips_q15_to_q31 23 test ==  \n");
	mips_q15_to_q31(q15input, q31output, 23);
	printf("mips_q15_to_q31 23 finish \n");

	printf("mips_q15_to_q31 23 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q31(q31inputFile, q31output, 23, ABS_Q31_ERROR);
#else
	near_check_special_q31(q31input, q31output, 23, ABS_Q31_ERROR);
#endif


	printf("\n== mips_q15_to_q31 23 check done  == \n\n");

// =====================
	printf("== mips_q15_to_q7 7 test ==  \n");
	mips_q15_to_q7(q15input, q7output, 7);
	printf("mips_q15_to_q7 7 finish \n");

	printf("mips_q15_to_q7 7 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q7(q7inputFile, q7output, 7, ABS_Q7_ERROR);
#else
	near_check_special_q7(q7input, q7output, 7, ABS_Q7_ERROR);
#endif



	printf("\n== mips_q15_to_q7 7 check done  == \n\n");

// =====================
	printf("== mips_q15_to_q7 16 test ==  \n");
	mips_q15_to_q7(q15input, q7output, 16);
	printf("mips_q15_to_q7 16 finish \n");

	printf("mips_q15_to_q7 16 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q7(q7inputFile, q7output, 16, ABS_Q7_ERROR);
#else
	near_check_special_q7(q7input, q7output, 16, ABS_Q7_ERROR);
#endif


	printf("\n== mips_q15_to_q7 16 check done  == \n\n");

// =====================
	printf("== mips_q15_to_q7 23 test ==  \n");
	mips_q15_to_q7(q15input, q7output, 23);
	printf("mips_q15_to_q7 23 finish \n");

	printf("mips_q15_to_q7 23 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q7(q7inputFile, q7output, 23, ABS_Q7_ERROR);
#else
	near_check_special_q7(q7input, q7output, 23, ABS_Q7_ERROR);
#endif


	printf("\n== mips_q15_to_q7 23 check done  == \n\n");

// =====================


    __ALIGNED(2) static const q15 testReadQ15[2]={-2,1};
    __ALIGNED(2) static q15 testWriteQ15[2]={0,0};


        q31 result=0;
        q15 *p = (q15*)testReadQ15;

	printf("== test_read_q15x2 test ==  \n");
        result = read_q15x2((q15*)testReadQ15);

        ASSERT_TRUE(result == 0x0001FFFE);
	printf("\n== test_read_q15x2 check done  == \n\n");

	printf("== test_read_q15x2_ia test ==  \n");
        result = read_q15x2_ia(&p);

        ASSERT_TRUE(result == 0x0001FFFE);
        ASSERT_TRUE(p == testReadQ15 + 2);
	printf("\n== test_read_q15x2_ia check done  == \n\n");

	printf("== test_read_q15x2_da test ==  \n");

        q31 resultd=0;
        q15 *pd = (q15*)testReadQ15;

        resultd = read_q15x2_da(&pd);

        ASSERT_TRUE(resultd == 0x0001FFFE);
        ASSERT_TRUE(pd == testReadQ15 - 2);
	printf("\n== test_read_q15x2_da check done  == \n\n");

	printf("== test_write_q15x2_ia test ==  \n");
        q31 q31val = 0x0001FFFE;
        q15 *pw = (q15*)testWriteQ15;

        testWriteQ15[0] = 0;
        testWriteQ15[1] = 0;


        write_q15x2_ia(&pw,q31val);

        ASSERT_TRUE(testWriteQ15[0] == -2);
        ASSERT_TRUE(testWriteQ15[1] == 1);
        ASSERT_TRUE(pw == testWriteQ15 + 2);
	printf("\n== test_write_q15x2_ia check done  == \n\n");

	printf("== test_write_q15x2 test ==  \n");

         q31 q31valw = 0x0001FFFE;

         testWriteQ15[0] = 0;
         testWriteQ15[1] = 0;
        write_q15x2(testWriteQ15,q31valw);

        ASSERT_TRUE(testWriteQ15[0] == -2);
        ASSERT_TRUE(testWriteQ15[1] == 1);

	printf("\n== test_write_q15x2 check done  == \n\n");

    return 0;
}