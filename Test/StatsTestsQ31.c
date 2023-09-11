#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/basic_math_functions.h"
#include "dsp/statistics_functions.h"

#define SNR_THRESHOLD 100
#define SNR_THRESHOLD_MSE 100

/* 

Reference patterns are generated with
a double precision computation.

*/
#define ABS_ERROR_Q31 ((q31)(100))
#define ABS_ERROR_Q31_MSE ((q31)(100))

#define ABS_ERROR_Q63 ((q63)(1<<18))
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

	q31 q31input1[MAX_SIZE] = {0};
	q31 q31input2[MAX_SIZE] = {0};

    q31 q31refmax[MAX_SIZE] = {0};
	q31 q31refmin[MAX_SIZE] = {0};

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

#if defined(NOT_EMBEDDED)
	char indexvalFile[255] = {0};
#else
	void *indexvalFile;
	int indexvalFileLen = 0;
#endif

	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, StatsQ31, "Input1_q31.txt");
#else
	inputFile1 = StatsQ31_Input1_q31;
	inputFile1Len = sizeof(StatsQ31_Input1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ31, "MaxVals1_q31.txt");
#else
	referenceFile = StatsQ31_MaxVals1_q31;
	referenceFileLen = sizeof(StatsQ31_MaxVals1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsQ31, "MaxIndexes1_s16.txt");
#else
	indexvalFile = StatsQ31_MaxIndexes1_s16;
	indexvalFileLen = sizeof(StatsQ31_MaxIndexes1_s16);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile1, &paramCountInput1, q31input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q31(inputFile1, paramCountInput1, q31input1);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

	q31 q31output1;
	q63 q63output1;
    uint16_t u16maxindex[MAX_SIZE] = {0};
    uint32_t index;
//===========max
	printf("== mips_max_q31 test ==  \n");
    mips_max_q31(q31input1, 3, &q31output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %x \n", q31input1[i]);
		printf("mips_max_q31 output = %x \n", q31output1);
        printf("index = %d \n", index);
	}
    printf("mips_max_q31 finish \n");
	printf("mips_max_q31 checking \n\n");


#if defined(NOT_EMBEDDED)
	load_data_q31(referenceFile, &paramCountInput1, q31refmax);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q31(referenceFile, paramCountInput1, q31refmax);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(indexvalFile, &paramCountInput1, u16maxindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u16(indexvalFile, paramCountInput1, u16maxindex);
	paramCountInput1 = paramCountInput1/sizeof(uint16_t);
#endif

    eq_check_special_q31(&q31refmax[0], &q31output1, 1);
    eq_check_special_q31(&u16maxindex[0], &index, 1);
	printf("\n== mips_max_q31 check done  == \n\n");

//=========8
    mips_max_q31(q31input1, 8, &q31output1, &index);
		//for (size_t i = 0; i < 8; i++)
	{
        //printf("input = %x \n", q31input1[i]);
		printf("mips_max_q31 output = %x \n", q31output1);
        printf("index = %d \n", index);
	}
    printf("mips_max_q31 finish \n");
		printf("mips_max_q31 output = %x \n", q31output1);
        printf("index = %d \n", index);
	printf("mips_max_q31 checking \n\n");
    eq_check_special_q31(&q31refmax[1], &q31output1, 1);
    eq_check_special_q31(&u16maxindex[1], &index, 1);
	printf("\n== mips_max_q31 check done  == \n\n");

//=======11
#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile1, &paramCountInput1, q31input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q31(inputFile1, paramCountInput1, q31input1);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

    mips_max_q31(q31input1, 11, &q31output1, &index);
    printf("mips_max_q31 finish \n");
		printf("mips_max_q31 output = %x \n", q31output1);
        printf("index = %f \n", index);
	printf("mips_max_q31 checking \n\n");
    eq_check_special_q31(&q31refmax[2], &q31output1, 1);
    eq_check_special_q31(&u16maxindex[1], &index, 1);

	printf("\n== mips_max_q31 check done  == \n\n");


// =====================absmax

    q31 q31refabsmax[MAX_SIZE] = {0};
    uint32_t u32absmaxindex[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, StatsQ31, "InputNew1_q31.txt");
#else
	inputFile2 = StatsQ31_InputNew1_q31;
	inputFile2Len = sizeof(StatsQ31_InputNew1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ31, "AbsMaxVals8_q31.txt");
#else
	referenceFile = StatsQ31_AbsMaxVals8_q31;
	referenceFileLen = sizeof(StatsQ31_AbsMaxVals8_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsQ31, "AbsMaxIndexes8_s16.txt");
#else
	indexvalFile = StatsQ31_AbsMaxIndexes8_s16;
	indexvalFileLen = sizeof(StatsQ31_AbsMaxIndexes8_s16);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile2, &paramCountInput2, q31input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q31(inputFile2, paramCountInput2, q31input2);
	paramCountInput2 = paramCountInput2/sizeof(q31);
#endif


	printf("== mips_absmax_q31 test ==  \n");
    mips_absmax_q31(q31input2, 3, &q31output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %x \n", q31input1[i]);
		printf("mips_absmax_q31 output = %x \n", q31output1);
        printf("index = %d \n", index);
	}
    printf("mips_absmax_q31 finish \n");

	printf("mips_absmax_q31 checking \n\n");
#if defined(NOT_EMBEDDED)
	load_data_q31(referenceFile, &paramCountInput1, q31refabsmax);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q31(referenceFile, paramCountInput1, q31refabsmax);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u32(indexvalFile, &paramCountInput1, u32absmaxindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u32(indexvalFile, paramCountInput1, u32absmaxindex);
	paramCountInput1 = paramCountInput1/sizeof(uint32_t);
#endif

    eq_check_special_q31(&q31refabsmax[0], &q31output1, 1);
    eq_check_special_q31(&u32absmaxindex[0], &index, 1);
	printf("\n== mips_absmax_q31 check done  == \n\n");


//=======8

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile2, &paramCountInput2, q31input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q31(inputFile2, paramCountInput2, q31input2);
	paramCountInput2 = paramCountInput2/sizeof(q31);
#endif

	printf("== mips_absmax_q31 test ==  \n");
    mips_absmax_q31(q31input2, 8, &q31output1, &index);
	//for (size_t i = 0; i < 8; i++)
	{
       // printf("input = %x \n", q31input1[i]);
		printf("mips_absmax_q31 output = %x \n", q31output1);
        printf("index = %d \n", index);

	}
    printf("mips_absmax_q31 finish \n");

	printf("mips_absmax_q31 checking \n\n");

    eq_check_special_q31(&q31refabsmax[1], &q31output1, 1);
    eq_check_special_q31(&u32absmaxindex[1], &index, 1);
	printf("\n== mips_absmax_q31 check done  == \n\n");


//=======11
#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile2, &paramCountInput2, q31input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q31(inputFile2, paramCountInput2, q31input2);
	paramCountInput2 = paramCountInput2/sizeof(q31);
#endif

	printf("== mips_absmax_q31 test ==  \n");
    mips_absmax_q31(q31input2, 11, &q31output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %x \n", q31input1[i]);
		printf("mips_absmax_q31 output = %x \n", q31output1);
        printf("index = %d \n", index);

	}
    printf("mips_absmax_q31 finish \n");

	printf("mips_absmax_q31 checking \n\n");

    eq_check_special_q31(&q31refabsmax[2], &q31output1, 1);
    eq_check_special_q31(&u32absmaxindex[2], &index, 1);
	printf("\n== mips_absmax_q31 check done  == \n\n");

// =====================max_no_idx

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ31, "MaxVals1_q31.txt");
#else
	referenceFile = StatsQ31_MaxVals1_q31;
	referenceFileLen = sizeof(StatsQ31_MaxVals1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif

	printf("== mips_max_no_idx_q31 test ==  \n");
    mips_max_no_idx_q31(q31input1, 3, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_max_no_idx_q31 output = %x \n", q31output1);
	}
    printf("mips_max_no_idx_q31 finish \n");
	printf("mips_max_no_idx_q31 checking \n\n");

    eq_check_special_q31(&q31refmax[0], &q31output1, 1);

	printf("\n== mips_max_no_idx_q31 check done  == \n\n");

// ===================8

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ31, "MaxVals1_q31.txt");
#else
	referenceFile = StatsQ31_MaxVals1_q31;
	referenceFileLen = sizeof(StatsQ31_MaxVals1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif

	printf("== mips_max_no_idx_q31 test ==  \n");
    mips_max_no_idx_q31(q31input1, 8, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_max_no_idx_q31 output = %x \n", q31output1);
	}
    printf("mips_max_no_idx_q31 finish \n");
	printf("mips_max_no_idx_q31 checking \n\n");

    eq_check_special_q31(&q31refmax[1], &q31output1, 1);
	
	printf("\n== mips_max_no_idx_q31 check done  == \n\n");

// ===================11

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ31, "MaxVals1_q31.txt");
#else
	referenceFile = StatsQ31_MaxVals1_q31;
	referenceFileLen = sizeof(StatsQ31_MaxVals1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif

	printf("== mips_max_no_idx_q31 test ==  \n");
    mips_max_no_idx_q31(q31input1, 11, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_max_no_idx_q31 output = %x \n", q31output1);
	}
    printf("mips_max_no_idx_q31 finish \n");
	printf("mips_max_no_idx_q31 checking \n\n");

    eq_check_special_q31(&q31refmax[2], &q31output1, 1);
	
	printf("\n== mips_max_no_idx_q31 check done  == \n\n");

//=====================absmax_no_idx


	printf("== mips_absmax_no_idx_q31 test ==  \n");
    mips_absmax_no_idx_q31(q31input2, 3, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_absmax_no_idx_q31 output = %x \n", q31output1);
	}
    printf("mips_absmax_no_idx_q31 finish \n");
	printf("mips_absmax_no_idx_q31 checking \n\n");

    eq_check_special_q31(&q31refabsmax[0], &q31output1, 1);
	printf("\n== mips_absmax_no_idx_q31 check done  == \n\n");
    
//==============8

	printf("== mips_absmax_no_idx_q31 test ==  \n");
    mips_absmax_no_idx_q31(q31input2, 16, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_absmax_no_idx_q31 output = %x \n", q31output1);
	}
    printf("mips_absmax_no_idx_q31 finish \n");
	printf("mips_absmax_no_idx_q31 checking \n\n");

    eq_check_special_q31(&q31refabsmax[1], &q31output1, 1);
	printf("\n== mips_absmax_no_idx_q31 check done  == \n\n");


//==============11

	printf("== mips_absmax_no_idx_q31 test ==  \n");
    mips_absmax_no_idx_q31(q31input2, 11, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_absmax_no_idx_q31 output = %x \n", q31output1);
	}
    printf("mips_absmax_no_idx_q31 finish \n");
	printf("mips_absmax_no_idx_q31 checking \n\n");

    eq_check_special_q31(&q31refabsmax[2], &q31output1, 1);
	printf("\n== mips_absmax_no_idx_q31 check done  == \n\n");

//=====================min_no_idx

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ31, "MinVals3_q31.txt");
#else
	referenceFile = StatsQ31_MinVals3_q31;
	referenceFileLen = sizeof(StatsQ31_MinVals3_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(referenceFile, &paramCountInput1, q31refmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q31(referenceFile, paramCountInput1, q31refmin);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

	printf("== mips_min_no_idx_q31 test ==  \n");
    mips_min_no_idx_q31(q31input1, 3, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_min_no_idx_q31 output = %x \n", q31output1);
	}
    printf("mips_min_no_idx_q31 finish \n");
	printf("mips_min_no_idx_q31 checking \n\n");

    eq_check_special_q31(&q31refmin[0], &q31output1, 1);
	printf("\n== mips_min_no_idx_q31 check done  == \n\n");

//=========8

	printf("== mips_min_no_idx_q31 test ==  \n");
    mips_min_no_idx_q31(q31input1, 8, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_min_no_idx_q31 output = %x \n", q31output1);
	}
    printf("mips_min_no_idx_q31 finish \n");
	printf("mips_min_no_idx_q31 checking \n\n");

    eq_check_special_q31(&q31refmin[1], &q31output1, 1);
	printf("\n== mips_min_no_idx_q31 check done  == \n\n");

//=========11

	printf("== mips_min_no_idx_q31 test ==  \n");
    mips_min_no_idx_q31(q31input1, 11, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_min_no_idx_q31 output = %x \n", q31output1);
	}
    printf("mips_min_no_idx_q31 finish \n");
	printf("mips_min_no_idx_q31 checking \n\n");

    eq_check_special_q31(&q31refmin[2], &q31output1, 1);
	printf("\n== mips_min_no_idx_q31 check done  == \n\n");


//=====================absmin_no_idx
    q31 q31refabsmin[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ31, "AbsMinVals9_q31.txt");
#else
	referenceFile = StatsQ31_AbsMinVals9_q31;
	referenceFileLen = sizeof(StatsQ31_AbsMinVals9_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(referenceFile, &paramCountInput1, q31refabsmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q31(referenceFile, paramCountInput1, q31refabsmin);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

	printf("== mips_absmin_no_idx_q31 test ==  \n");
    mips_absmin_no_idx_q31(q31input2, 3, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_absmin_no_idx_q31 output = %x \n", q31output1);
	}
    printf("mips_absmin_no_idx_q31 finish \n");
	printf("mips_absmin_no_idx_q31 checking \n\n");

    eq_check_special_q31(&q31refabsmin[0], &q31output1, 1);

	printf("\n== mips_absmin_no_idx_q31 check done  == \n\n");

//================8


	printf("== mips_absmin_no_idx_q31 test ==  \n");
    mips_absmin_no_idx_q31(q31input2, 8, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_absmin_no_idx_q31 output = %x \n", q31output1);
	}
    printf("mips_absmin_no_idx_q31 finish \n");
	printf("mips_absmin_no_idx_q31 checking \n\n");

    eq_check_special_q31(&q31refabsmin[1], &q31output1, 1);
	
	printf("\n== mips_absmin_no_idx_q31 check done  == \n\n");

//=================11


	printf("== mips_absmin_no_idx_q31 test ==  \n");
    mips_absmin_no_idx_q31(q31input2, 11, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_absmin_no_idx_q31 output = %x \n", q31output1);
	}
    printf("mips_absmin_no_idx_q31 finish \n");
	printf("mips_absmin_no_idx_q31 checking \n\n");

    eq_check_special_q31(&q31refabsmin[2], &q31output1, 1);
	
	printf("\n== mips_absmin_no_idx_q31 check done  == \n\n");

//=====================min_idx

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ31, "MinVals3_q31.txt");
#else
	referenceFile = StatsQ31_MinVals3_q31;
	referenceFileLen = sizeof(StatsQ31_MinVals3_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsQ31, "MinIndexes3_s16.txt");
#else
	indexvalFile = StatsQ31_MinIndexes3_s16;
	indexvalFileLen = sizeof(StatsQ31_MinIndexes3_s16);
#endif


    uint32_t u32minindex[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	load_data_u32(indexvalFile, &paramCountInput1, u32minindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u32(indexvalFile, paramCountInput1, u32minindex);
	paramCountInput1 = paramCountInput1/sizeof(uint32_t);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(referenceFile, &paramCountInput1, q31refmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q31(referenceFile, paramCountInput1, q31refmin);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

	printf("== mips_min_q31 test ==  \n");
    mips_min_q31(q31input1, 3, &q31output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_min_q31 output = %x \n", q31output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_q31 finish \n");
	printf("mips_min_q31 checking \n\n");

    eq_check_special_q31(&q31refmin[0], &q31output1, 1);
	eq_check_special_q31(&u32minindex[0], &index, 1);
	printf("\n== mips_min_q31 check done  == \n\n");

//===============8

	printf("== mips_min_q31 test ==  \n");
    mips_min_q31(q31input1, 8, &q31output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_min_q31 output = %x \n", q31output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_q31 finish \n");
	printf("mips_min_q31 checking \n\n");

    eq_check_special_q31(&q31refmin[1], &q31output1, 1);
	eq_check_special_q31(&u32minindex[1], &index, 1);
	printf("\n== mips_min_q31 check done  == \n\n");

//===============11

	printf("== mips_min_q31 test ==  \n");
    mips_min_q31(q31input1, 11, &q31output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_min_q31 output = %x \n", q31output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_q31 finish \n");
	printf("mips_min_q31 checking \n\n");

    eq_check_special_q31(&q31refmin[2], &q31output1, 1);
	eq_check_special_q31(&u32minindex[2], &index, 1);
	printf("\n== mips_min_q31 check done  == \n\n");

//=====================absmin

    uint32_t u32absminindex[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsQ31, "AbsMinIndexes9_s16.txt");
#else
	indexvalFile = StatsQ31_AbsMinIndexes9_s16;
	indexvalFileLen = sizeof(StatsQ31_AbsMinIndexes9_s16);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u32(indexvalFile, &paramCountInput1, u32absminindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u32(indexvalFile, paramCountInput1, u32absminindex);
	paramCountInput1 = paramCountInput1/sizeof(uint32_t);
#endif

	printf("== mips_absmin_q31 test ==  \n");
    mips_absmin_q31(q31input2, 3, &q31output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_absmin_q31 output = %x \n", q31output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_q31 finish \n");
	printf("mips_absmin_q31 checking \n\n");

    eq_check_special_q31(&q31refabsmin[0], &q31output1, 1);
	eq_check_special_q31(&u32absminindex[0], &index, 1);

	printf("\n== mips_absmin_q31 check done  == \n\n");

//===============8

	printf("== mips_absmin_q31 test ==  \n");
    mips_absmin_q31(q31input2, 8, &q31output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_absmin_q31 output = %x \n", q31output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_q31 finish \n");
	printf("mips_absmin_q31 checking \n\n");

    eq_check_special_q31(&q31refabsmin[1], &q31output1, 1);
	eq_check_special_q31(&u32absminindex[1], &index, 1);

	printf("\n== mips_absmin_q31 check done  == \n\n");


//================11

	printf("== mips_absmin_q31 test ==  \n");
    mips_absmin_q31(q31input2, 11, &q31output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_absmin_q31 output = %x \n", q31output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_q31 finish \n");
	printf("mips_absmin_q31 checking \n\n");

    eq_check_special_q31(&q31refabsmin[2], &q31output1, 1);
	eq_check_special_q31(&u32absminindex[2], &index, 1);

	printf("\n== mips_absmin_q31 check done  == \n\n");

//===========================mean_q31

    q31 q31input3[MAX_SIZE] = {0};
	q31 q31mean[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, StatsQ31, "Input2_q31.txt");
#else
	inputFile3 = StatsQ31_Input2_q31;
	inputFile3Len = sizeof(StatsQ31_Input2_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ31, "MeanVals2_q31.txt");
#else
	referenceFile = StatsQ31_MeanVals2_q31;
	referenceFileLen = sizeof(StatsQ31_MeanVals2_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile3, &paramCountInput3, q31input3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_q31(inputFile3, paramCountInput3, q31input3);
	paramCountInput3 = paramCountInput3/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(referenceFile, &paramCountInput1, q31mean);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q31(referenceFile, paramCountInput1, q31mean);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

	printf("== mips_mean_q31 test ==  \n");
    mips_mean_q31(q31input3, 3, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_mean_q31 output = %x \n", q31output1);

	}
    printf("mips_mean_q31 finish \n");
	printf("mips_mean_q31 checking \n\n");

    snr_check_special_q31(&q31mean[0], &q31output1, 1, SNR_THRESHOLD);
	near_check_special_q31(&q31mean[0], &q31output1, 1, ABS_ERROR_Q31);
	
	printf("\n== mips_mean_q31 check done  == \n\n");

//===========8

	printf("== mips_mean_q31 test ==  \n");
    mips_mean_q31(q31input3, 8, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_mean_q31 output = %x \n", q31output1);

	}
    printf("mips_mean_q31 finish \n");
	printf("mips_mean_q31 checking \n\n");

    snr_check_special_q31(&q31mean[1], &q31output1, 1, SNR_THRESHOLD);
	near_check_special_q31(&q31mean[1], &q31output1, 1, ABS_ERROR_Q31);

	printf("\n== mips_mean_q31 check done  == \n\n");

//===========11

	printf("== mips_mean_q31 test ==  \n");
    mips_mean_q31(q31input3, 11, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_mean_q31 output = %x \n", q31output1);

	}
    printf("mips_mean_q31 finish \n");
	printf("mips_mean_q31 checking \n\n");

    snr_check_special_q31(&q31mean[2], &q31output1, 1, SNR_THRESHOLD);
	near_check_special_q31(&q31mean[2], &q31output1, 1, ABS_ERROR_Q31);

	printf("\n== mips_mean_q31 check done  == \n\n");

//===========================power_q31

	q63 q63power[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ31, "PowerVals4_q63.txt");
#else
	referenceFile = StatsQ31_PowerVals4_q63;
	referenceFileLen = sizeof(StatsQ31_PowerVals4_q63);
	load_data_q63(referenceFile, referenceFileLen, referenceData_q63);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q63(referenceFile, &paramCountInput1, q63power);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q63(referenceFile, paramCountInput1, q63power);
	paramCountInput1 = paramCountInput1/sizeof(q63);
#endif

	printf("== mips_power_q31 test ==  \n");
    mips_power_q31(q31input1, 3, &q63output1);
	//for (size_t i = 0; i < 2; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_power_q31 output = %llx \n", q63output1);

	}
    printf("mips_power_q31 finish \n");
	printf("mips_power_q31 checking \n\n");

    snr_check_special_q63(&q63power[0], &q63output1, 1, SNR_THRESHOLD);
	near_check_special_q63(&q63power[0], &q63output1, 1, ABS_ERROR_Q63);
	
	printf("\n== mips_power_q31 check done  == \n\n");

//=============8

	printf("== mips_power_q31 test ==  \n");
    mips_power_q31(q31input1, 8, &q63output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_power_q31 output = %llx \n", q63output1);

	}
    printf("mips_power_q31 finish \n");
	printf("mips_power_q31 checking \n\n");

    snr_check_special_q63(&q63power[1], &q63output1, 1, SNR_THRESHOLD);
	near_check_special_q63(&q63power[1], &q63output1, 1, ABS_ERROR_Q63);
	
	printf("\n== mips_power_q31 check done  == \n\n");

//=============11

	printf("== mips_power_q31 test ==  \n");
    mips_power_q31(q31input1, 11, &q63output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_power_q31 output = %llx \n", q63output1);

	}
    printf("mips_power_q31 finish \n");
	printf("mips_power_q31 checking \n\n");

    snr_check_special_q63(&q63power[2], &q63output1, 1, SNR_THRESHOLD);
	near_check_special_q63(&q63power[2], &q63output1, 1, ABS_ERROR_Q63);
	
	printf("\n== mips_power_q31 check done  == \n\n");



//===========================rms_q31

	q31 q31rms[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ31, "RmsVals5_q31.txt");
#else
	referenceFile = StatsQ31_RmsVals5_q31;
	referenceFileLen = sizeof(StatsQ31_RmsVals5_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q31(referenceFile, &paramCountInput1, q31rms);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q31(referenceFile, paramCountInput1, q31rms);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

	printf("== mips_rms_q31 test ==  \n");
    mips_rms_q31(q31input1, 3, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", q31input1[i]);
		printf("mips_rms_q31 output = %d \n", q31output1);

	}
    printf("mips_rms_q31 finish \n");
	printf("mips_rms_q31 checking \n\n");

    snr_check_special_q31(&q31rms[0], &q31output1, 1, SNR_THRESHOLD);
	near_check_special_q31(&q31rms[0], &q31output1, 1, ABS_ERROR_Q31);
	
	printf("\n== mips_rms_q31 check done  == \n\n");

//=============8

	printf("== mips_rms_q31 test ==  \n");
    mips_rms_q31(q31input1, 8, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", q31input1[i]);
		printf("mips_rms_q31 output = %d \n", q31output1);

	}
    printf("mips_rms_q31 finish \n");
	printf("mips_rms_q31 checking \n\n");

    snr_check_special_q31(&q31rms[1], &q31output1, 1, SNR_THRESHOLD);
	near_check_special_q31(&q31rms[1], &q31output1, 1, ABS_ERROR_Q31);
	
	printf("\n== mips_rms_q31 check done  == \n\n");

//=============11

	printf("== mips_rms_q31 test ==  \n");
    mips_rms_q31(q31input1, 11, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", q31input1[i]);
		printf("mips_rms_q31 output = %d \n", q31output1);

	}
    printf("mips_rms_q31 finish \n");
	printf("mips_rms_q31 checking \n\n");

    snr_check_special_q31(&q31rms[2], &q31output1, 1, SNR_THRESHOLD);
	near_check_special_q31(&q31rms[2], &q31output1, 1, ABS_ERROR_Q31);
	
	printf("\n== mips_rms_q31 check done  == \n\n");


//===========================std_q31

	q31 q31std[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ31, "StdVals6_q31.txt");
#else
	referenceFile = StatsQ31_StdVals6_q31;
	referenceFileLen = sizeof(StatsQ31_StdVals6_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q31(referenceFile, &paramCountInput1, q31std);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q31(referenceFile, paramCountInput1, q31std);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

	printf("== mips_std_q31 test ==  \n");
    mips_std_q31(q31input1, 3, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_std_q31 output = %x \n", q31output1);

	}
    printf("mips_std_q31 finish \n");
	printf("mips_std_q31 checking \n\n");

    snr_check_special_q31(&q31std[0], &q31output1, 1, SNR_THRESHOLD);
	near_check_special_q31(&q31std[0], &q31output1, 1, ABS_ERROR_Q31);
	
	printf("\n== mips_std_q31 check done  == \n\n");

//============8

	printf("== mips_std_q31 test ==  \n");
    mips_std_q31(q31input1, 8, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_std_q31 output = %x \n", q31output1);

	}
    printf("mips_std_q31 finish \n");
	printf("mips_std_q31 checking \n\n");

    snr_check_special_q31(&q31std[1], &q31output1, 1, SNR_THRESHOLD);
	near_check_special_q31(&q31std[1], &q31output1, 1, ABS_ERROR_Q31);
	
	printf("\n== mips_std_q31 check done  == \n\n");
	
//===========11

	printf("== mips_std_q31 test ==  \n");
    mips_std_q31(q31input1, 11, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_std_q31 output = %x \n", q31output1);

	}
    printf("mips_std_q31 finish \n");
	printf("mips_std_q31 checking \n\n");

    snr_check_special_q31(&q31std[2], &q31output1, 1, SNR_THRESHOLD);
	near_check_special_q31(&q31std[2], &q31output1, 1, ABS_ERROR_Q31);
	
	printf("\n== mips_std_q31 check done  == \n\n");


//===========================var_q31

	q31 q31var[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ31, "VarVals7_q31.txt");
#else
	referenceFile = StatsQ31_VarVals7_q31;
	referenceFileLen = sizeof(StatsQ31_VarVals7_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q31(referenceFile, &paramCountInput1, q31var);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q31(referenceFile, paramCountInput1, q31var);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

	printf("== mips_var_q31 test ==  \n");
    mips_var_q31(q31input1, 3, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_var_q31 output = %x \n", q31output1);

	}
    printf("mips_var_q31 finish \n");
	printf("mips_var_q31 checking \n\n");

    snr_check_special_q31(&q31var[0], &q31output1, 1, SNR_THRESHOLD);
	near_check_special_q31(&q31var[0], &q31output1, 1, ABS_ERROR_Q31);
	
	printf("\n== mips_var_q31 check done  == \n\n");


//===========8

	printf("== mips_var_q31 test ==  \n");
    mips_var_q31(q31input1, 8, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_var_q31 output = %x \n", q31output1);

	}
    printf("mips_var_q31 finish \n");
	printf("mips_var_q31 checking \n\n");

    snr_check_special_q31(&q31var[1], &q31output1, 1, SNR_THRESHOLD);
	near_check_special_q31(&q31var[1], &q31output1, 1, ABS_ERROR_Q31);
	
	printf("\n== mips_var_q31 check done  == \n\n");


//===========11 

	printf("== mips_var_q31 test ==  \n");
    mips_var_q31(q31input1, 11, &q31output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_var_q31 output = %x \n", q31output1);

	}
    printf("mips_var_q31 finish \n");
	printf("mips_var_q31 checking \n\n");

    snr_check_special_q31(&q31var[2], &q31output1, 1, SNR_THRESHOLD);
	near_check_special_q31(&q31var[2], &q31output1, 1, ABS_ERROR_Q31);
	
	printf("\n== mips_var_q31 check done  == \n\n");



//===========================mse_q31

	int paramCountInputA = 0;
	int paramCountInputB = 0;
	q31 q31inputa[MAX_SIZE] = {0};
	q31 q31inputb[MAX_SIZE] = {0};


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


	q31 q31mse[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea, sizeof(inputFilea), "%s%s%s", Patterns_PATH, StatsQ31, "InputNew1_q31.txt");
#else
	inputFilea = StatsQ31_InputNew1_q31;
	inputFileaLen = sizeof(StatsQ31_InputNew1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb, sizeof(inputFileb), "%s%s%s", Patterns_PATH, StatsQ31, "InputNew2_q31.txt");
#else
	inputFileb = StatsQ31_InputNew2_q31;
	inputFilebLen = sizeof(StatsQ31_InputNew2_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ31, "MSEVals10_q31.txt");
#else
	referenceFile = StatsQ31_MSEVals10_q31;
	referenceFileLen = sizeof(StatsQ31_MSEVals10_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q31(inputFilea, &paramCountInputA, q31inputa);
#else
	paramCountInputA = inputFileaLen;
	load_data_q31(inputFilea, paramCountInputA, q31inputa);
	paramCountInputA = paramCountInputA/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileb, &paramCountInputB, q31inputb);
#else
	paramCountInputB = inputFilebLen;
	load_data_q31(inputFileb, paramCountInputB, q31inputb);
	paramCountInputB = paramCountInputB/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(referenceFile, &paramCountInput1,q31mse);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q31(referenceFile, paramCountInput1,q31mse);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif
	printf("== mips_mse_q31 test ==  \n");


    mips_mse_q31(q31inputa,q31inputb,3,&q31output1);    
		//for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_mse_q31 output = %x \n", q31output1);

	}
    printf("mips_mse_q31 finish \n");
	printf("mips_mse_q31 checking \n\n");

    snr_check_special_q31(&q31mse[0], &q31output1, 1, SNR_THRESHOLD_MSE);
	near_check_special_q31(&q31mse[0], &q31output1, 1, ABS_ERROR_Q31_MSE);

	printf("\n== mips_mse_q31 check done  == \n\n");

//=============mse 100
	printf("== mips_mse_q31 test ==  \n");


    mips_mse_q31(q31inputa,q31inputb,100,&q31output1);
		//for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %x \n", q31input1[i]);
		printf("mips_mse_q31 output = %x \n", q31output1);

	}
    printf("mips_mse_q31 finish \n");
	printf("mips_mse_q31 checking \n\n");

    snr_check_special_q31(&q31mse[3], &q31output1, 1, SNR_THRESHOLD_MSE);
	near_check_special_q31(&q31mse[3], &q31output1, 1, ABS_ERROR_Q31_MSE);

	printf("\n== mips_mse_q31 check done  == \n\n");


	return 0 ;
}
