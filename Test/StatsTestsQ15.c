#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/basic_math_functions.h"
#include "dsp/statistics_functions.h"

#define SNR_THRESHOLD 50
#define SNR_THRESHOLD_MSE 50

/* 

Reference patterns are generated with
a double precision computation.

*/
#define ABS_ERROR_Q15 ((q15)100)
#define ABS_ERROR_Q15_MSE ((q15)100)

#define ABS_ERROR_Q63 (1<<17)

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

	q15 q15input1[MAX_SIZE] = {0};
	q15 q15input2[MAX_SIZE] = {0};

    q15 q15refmax[MAX_SIZE] = {0};
	q15 q15refmin[MAX_SIZE] = {0};

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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, StatsQ15, "Input1_q15.txt");
#else
	inputFile1 = StatsQ15_Input1_q15;
	inputFile1Len = sizeof(StatsQ15_Input1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ15, "MaxVals1_q15.txt");
#else
	referenceFile = StatsQ15_MaxVals1_q15;
	referenceFileLen = sizeof(StatsQ15_MaxVals1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsQ15, "MaxIndexes1_s16.txt");
#else
	indexvalFile = StatsQ15_MaxIndexes1_s16;
	indexvalFileLen = sizeof(StatsQ15_MaxIndexes1_s16);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile1, &paramCountInput1, q15input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q15(inputFile1, paramCountInput1, q15input1);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif

	q15 q15output1;
    uint16_t u16maxindex[MAX_SIZE] = {0};
    uint32_t index;
//===========max
	printf("== mips_max_q15 test ==  \n");
    mips_max_q15(q15input1, 7, &q15output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %x \n", q15input1[i]);
		printf("mips_max_q15 output = %x \n", q15output1);
        printf("index = %d \n", index);
	}
    printf("mips_max_q15 finish \n");
	printf("mips_max_q15 checking \n\n");


#if defined(NOT_EMBEDDED)
	load_data_q15(referenceFile, &paramCountInput1, q15refmax);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q15(referenceFile, paramCountInput1, q15refmax);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(indexvalFile, &paramCountInput1, u16maxindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u16(indexvalFile, paramCountInput1, u16maxindex);
	paramCountInput1 = paramCountInput1/sizeof(uint16_t);
#endif

    eq_check_special_q15(&q15refmax[0], &q15output1, 1);
    eq_check_special_q15(&u16maxindex[0], &index, 1);
	printf("\n== mips_max_q15 check done  == \n\n");

//=========16
    mips_max_q15(q15input1, 16, &q15output1, &index);
		//for (size_t i = 0; i < 8; i++)
	{
        //printf("input = %x \n", q15input1[i]);
		printf("mips_max_q15 output = %x \n", q15output1);
        printf("index = %d \n", index);
	}
    printf("mips_max_q15 finish \n");
		printf("mips_max_q15 output = %x \n", q15output1);
        printf("index = %d \n", index);
	printf("mips_max_q15 checking \n\n");
    eq_check_special_q15(&q15refmax[1], &q15output1, 1);
    eq_check_special_q15(&u16maxindex[1], &index, 1);
	printf("\n== mips_max_q15 check done  == \n\n");

//=======23
#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile1, &paramCountInput1, q15input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q15(inputFile1, paramCountInput1, q15input1);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif

    mips_max_q15(q15input1, 23, &q15output1, &index);
    printf("mips_max_q15 finish \n");
		printf("mips_max_q15 output = %x \n", q15output1);
        printf("index = %d \n", index);
	printf("mips_max_q15 checking \n\n");
    eq_check_special_q15(&q15refmax[2], &q15output1, 1);
    eq_check_special_q15(&u16maxindex[2], &index, 1);

	printf("\n== mips_max_q15 check done  == \n\n");


// =====================absmax

    q15 q15refabsmax[MAX_SIZE] = {0};
    uint16_t u16absmaxindex[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, StatsQ15, "InputNew1_q15.txt");
#else
	inputFile2 = StatsQ15_InputNew1_q15;
	inputFile2Len = sizeof(StatsQ15_InputNew1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ15, "AbsMaxVals8_q15.txt");
#else
	referenceFile = StatsQ15_AbsMaxVals8_q15;
	referenceFileLen = sizeof(StatsQ15_AbsMaxVals8_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsQ15, "AbsMaxIndexes8_s16.txt");
#else
	indexvalFile = StatsQ15_AbsMaxIndexes8_s16;
	indexvalFileLen = sizeof(StatsQ15_AbsMaxIndexes8_s16);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile2, &paramCountInput2, q15input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q15(inputFile2, paramCountInput2, q15input2);
	paramCountInput2 = paramCountInput2/sizeof(q15);
#endif


	printf("== mips_absmax_q15 test ==  \n");
    mips_absmax_q15(q15input2, 7, &q15output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %x \n", q15input1[i]);
		printf("mips_absmax_q15 output = %x \n", q15output1);
        printf("index = %d \n", index);
	}
    printf("mips_absmax_q15 finish \n");

	printf("mips_absmax_q15 checking \n\n");
#if defined(NOT_EMBEDDED)
	load_data_q15(referenceFile, &paramCountInput1, q15refabsmax);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q15(referenceFile, paramCountInput1, q15refabsmax);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(indexvalFile, &paramCountInput1, u16absmaxindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u16(indexvalFile, paramCountInput1, u16absmaxindex);
	paramCountInput1 = paramCountInput1/sizeof(uint16_t);
#endif

    eq_check_special_q15(&q15refabsmax[0], &q15output1, 1);
    eq_check_special_q15(&u16absmaxindex[0], &index, 1);
	printf("\n== mips_absmax_q15 check done  == \n\n");


//=======16

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile2, &paramCountInput2, q15input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q15(inputFile2, paramCountInput2, q15input2);
	paramCountInput2 = paramCountInput2/sizeof(q15);
#endif

	printf("== mips_absmax_q15 test ==  \n");
    mips_absmax_q15(q15input2, 16, &q15output1, &index);
	//for (size_t i = 0; i < 8; i++)
	{
       // printf("input = %x \n", q15input1[i]);
		printf("mips_absmax_q15 output = %x \n", q15output1);
        printf("index = %d \n", index);

	}
    printf("mips_absmax_q15 finish \n");

	printf("mips_absmax_q15 checking \n\n");

    eq_check_special_q15(&q15refabsmax[1], &q15output1, 1);
    eq_check_special_q15(&u16absmaxindex[1], &index, 1);
	printf("\n== mips_absmax_q15 check done  == \n\n");


//=======23
#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile2, &paramCountInput2, q15input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q15(inputFile2, paramCountInput2, q15input2);
	paramCountInput2 = paramCountInput2/sizeof(q15);
#endif

	printf("== mips_absmax_q15 test ==  \n");
    mips_absmax_q15(q15input2, 23, &q15output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %x \n", q15input1[i]);
		printf("mips_absmax_q15 output = %x \n", q15output1);
        printf("index = %d \n", index);

	}
    printf("mips_absmax_q15 finish \n");

	printf("mips_absmax_q15 checking \n\n");

    eq_check_special_q15(&q15refabsmax[2], &q15output1, 1);
    eq_check_special_q15(&u16absmaxindex[2], &index, 1);
	printf("\n== mips_absmax_q15 check done  == \n\n");

// =====================max_no_idx

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ15, "MaxVals1_q15.txt");
#else
	referenceFile = StatsQ15_MaxVals1_q15;
	referenceFileLen = sizeof(StatsQ15_MaxVals1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif

	printf("== mips_max_no_idx_q15 test ==  \n");
    mips_max_no_idx_q15(q15input1, 7, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_max_no_idx_q15 output = %x \n", q15output1);
	}
    printf("mips_max_no_idx_q15 finish \n");
	printf("mips_max_no_idx_q15 checking \n\n");

    eq_check_special_q15(&q15refmax[0], &q15output1, 1);

	printf("\n== mips_max_no_idx_q15 check done  == \n\n");

// ===================16

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ15, "MaxVals1_q15.txt");
#else
	referenceFile = StatsQ15_MaxVals1_q15;
	referenceFileLen = sizeof(StatsQ15_MaxVals1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif

	printf("== mips_max_no_idx_q15 test ==  \n");
    mips_max_no_idx_q15(q15input1, 16, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_max_no_idx_q15 output = %x \n", q15output1);
	}
    printf("mips_max_no_idx_q15 finish \n");
	printf("mips_max_no_idx_q15 checking \n\n");

    eq_check_special_q15(&q15refmax[1], &q15output1, 1);
	
	printf("\n== mips_max_no_idx_q15 check done  == \n\n");

// ===================23

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ15, "MaxVals1_q15.txt");
#else
	referenceFile = StatsQ15_MaxVals1_q15;
	referenceFileLen = sizeof(StatsQ15_MaxVals1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif

	printf("== mips_max_no_idx_q15 test ==  \n");
    mips_max_no_idx_q15(q15input1, 23, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_max_no_idx_q15 output = %x \n", q15output1);
	}
    printf("mips_max_no_idx_q15 finish \n");
	printf("mips_max_no_idx_q15 checking \n\n");

    eq_check_special_q15(&q15refmax[2], &q15output1, 1);
	
	printf("\n== mips_max_no_idx_q15 check done  == \n\n");

//=====================abs_no_idx


	printf("== mips_absmax_no_idx_q15 test ==  \n");
    mips_absmax_no_idx_q15(q15input2, 7, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_absmax_no_idx_q15 output = %x \n", q15output1);
	}
    printf("mips_absmax_no_idx_q15 finish \n");
	printf("mips_absmax_no_idx_q15 checking \n\n");

    eq_check_special_q15(&q15refabsmax[0], &q15output1, 1);
	printf("\n== mips_absmax_no_idx_q15 check done  == \n\n");
    
//==============16

	printf("== mips_absmax_no_idx_q15 test ==  \n");
    mips_absmax_no_idx_q15(q15input2, 16, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_absmax_no_idx_q15 output = %x \n", q15output1);
	}
    printf("mips_absmax_no_idx_q15 finish \n");
	printf("mips_absmax_no_idx_q15 checking \n\n");

    eq_check_special_q15(&q15refabsmax[1], &q15output1, 1);
	printf("\n== mips_absmax_no_idx_q15 check done  == \n\n");


//==============23

	printf("== mips_absmax_no_idx_q15 test ==  \n");
    mips_absmax_no_idx_q15(q15input2, 23, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_absmax_no_idx_q15 output = %x \n", q15output1);
	}
    printf("mips_absmax_no_idx_q15 finish \n");
	printf("mips_absmax_no_idx_q15 checking \n\n");

    eq_check_special_q15(&q15refabsmax[2], &q15output1, 1);
	printf("\n== mips_absmax_no_idx_q15 check done  == \n\n");

//=====================min_no_idx

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ15, "MinVals3_q15.txt");
#else
	referenceFile = StatsQ15_MinVals3_q15;
	referenceFileLen = sizeof(StatsQ15_MinVals3_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(referenceFile, &paramCountInput1, q15refmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q15(referenceFile, paramCountInput1, q15refmin);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif

	printf("== mips_min_no_idx_q15 test ==  \n");
    mips_min_no_idx_q15(q15input1, 7, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_min_no_idx_q15 output = %x \n", q15output1);
	}
    printf("mips_min_no_idx_q15 finish \n");
	printf("mips_min_no_idx_q15 checking \n\n");

    eq_check_special_q15(&q15refmin[0], &q15output1, 1);
	printf("\n== mips_min_no_idx_q15 check done  == \n\n");

//=========16

	printf("== mips_min_no_idx_q15 test ==  \n");
    mips_min_no_idx_q15(q15input1, 16, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_min_no_idx_q15 output = %x \n", q15output1);
	}
    printf("mips_min_no_idx_q15 finish \n");
	printf("mips_min_no_idx_q15 checking \n\n");

    eq_check_special_q15(&q15refmin[1], &q15output1, 1);
	printf("\n== mips_min_no_idx_q15 check done  == \n\n");

//=========23

	printf("== mips_min_no_idx_q15 test ==  \n");
    mips_min_no_idx_q15(q15input1, 23, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_min_no_idx_q15 output = %x \n", q15output1);
	}
    printf("mips_min_no_idx_q15 finish \n");
	printf("mips_min_no_idx_q15 checking \n\n");

    eq_check_special_q15(&q15refmin[2], &q15output1, 1);
	printf("\n== mips_min_no_idx_q15 check done  == \n\n");


//=====================absmin_no_idx
    q15 q15refabsmin[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ15, "AbsMinVals9_q15.txt");
#else
	referenceFile = StatsQ15_AbsMinVals9_q15;
	referenceFileLen = sizeof(StatsQ15_AbsMinVals9_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(referenceFile, &paramCountInput1, q15refabsmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q15(referenceFile, paramCountInput1, q15refabsmin);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif

	printf("== mips_absmin_no_idx_q15 test ==  \n");
    mips_absmin_no_idx_q15(q15input2, 7, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_absmin_no_idx_q15 output = %x \n", q15output1);
	}
    printf("mips_absmin_no_idx_q15 finish \n");
	printf("mips_absmin_no_idx_q15 checking \n\n");

    eq_check_special_q15(&q15refabsmin[0], &q15output1, 1);

	printf("\n== mips_absmin_no_idx_q15 check done  == \n\n");

//================16


	printf("== mips_absmin_no_idx_q15 test ==  \n");
    mips_absmin_no_idx_q15(q15input2, 16, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_absmin_no_idx_q15 output = %x \n", q15output1);
	}
    printf("mips_absmin_no_idx_q15 finish \n");
	printf("mips_absmin_no_idx_q15 checking \n\n");

    eq_check_special_q15(&q15refabsmin[1], &q15output1, 1);
	
	printf("\n== mips_absmin_no_idx_q15 check done  == \n\n");

//=================23


	printf("== mips_absmin_no_idx_q15 test ==  \n");
    mips_absmin_no_idx_q15(q15input2, 23, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_absmin_no_idx_q15 output = %x \n", q15output1);
	}
    printf("mips_absmin_no_idx_q15 finish \n");
	printf("mips_absmin_no_idx_q15 checking \n\n");

    eq_check_special_q15(&q15refabsmin[2], &q15output1, 1);
	
	printf("\n== mips_absmin_no_idx_q15 check done  == \n\n");

//=====================min

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ15, "MinVals3_q15.txt");
#else
	referenceFile = StatsQ15_MinVals3_q15;
	referenceFileLen = sizeof(StatsQ15_MinVals3_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsQ15, "MinIndexes3_s16.txt");
#else
	indexvalFile = StatsQ15_MinIndexes3_s16;
	indexvalFileLen = sizeof(StatsQ15_MinIndexes3_s16);
#endif


    uint16_t u16minindex[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	load_data_u16(indexvalFile, &paramCountInput1, u16minindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u16(indexvalFile, paramCountInput1, u16minindex);
	paramCountInput1 = paramCountInput1/sizeof(uint16_t);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(referenceFile, &paramCountInput1, q15refmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q15(referenceFile, paramCountInput1, q15refmin);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif

	printf("== mips_min_q15 test ==  \n");
    mips_min_q15(q15input1, 7, &q15output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_min_q15 output = %x \n", q15output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_q15 finish \n");
	printf("mips_min_q15 checking \n\n");

    eq_check_special_q15(&q15refmin[0], &q15output1, 1);
	eq_check_special_q15(&u16minindex[0], &index, 1);
	printf("\n== mips_min_q15 check done  == \n\n");

//===============16

	printf("== mips_min_q15 test ==  \n");
    mips_min_q15(q15input1, 16, &q15output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_min_q15 output = %x \n", q15output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_q15 finish \n");
	printf("mips_min_q15 checking \n\n");

    eq_check_special_q15(&q15refmin[1], &q15output1, 1);
	eq_check_special_q15(&u16minindex[1], &index, 1);
	printf("\n== mips_min_q15 check done  == \n\n");

//===============23

	printf("== mips_min_q15 test ==  \n");
    mips_min_q15(q15input1, 23, &q15output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_min_q15 output = %x \n", q15output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_q15 finish \n");
	printf("mips_min_q15 checking \n\n");

    eq_check_special_q15(&q15refmin[2], &q15output1, 1);
	eq_check_special_q15(&u16minindex[2], &index, 1);
	printf("\n== mips_min_q15 check done  == \n\n");

//=====================absmin

    uint16_t u16absminindex[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsQ15, "AbsMinIndexes9_s16.txt");
#else
	indexvalFile = StatsQ15_AbsMinIndexes9_s16;
	indexvalFileLen = sizeof(StatsQ15_AbsMinIndexes9_s16);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(indexvalFile, &paramCountInput1, u16absminindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u16(indexvalFile, paramCountInput1, u16absminindex);
	paramCountInput1 = paramCountInput1/sizeof(uint16_t);
#endif

	printf("== mips_absmin_q15 test ==  \n");
    mips_absmin_q15(q15input2, 7, &q15output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_absmin_q15 output = %x \n", q15output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_q15 finish \n");
	printf("mips_absmin_q15 checking \n\n");

    eq_check_special_q15(&q15refabsmin[0], &q15output1, 1);
	eq_check_special_q15(&u16absminindex[0], &index, 1);

	printf("\n== mips_absmin_q15 check done  == \n\n");

//===============16

	printf("== mips_absmin_q15 test ==  \n");
    mips_absmin_q15(q15input2, 16, &q15output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_absmin_q15 output = %x \n", q15output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_q15 finish \n");
	printf("mips_absmin_q15 checking \n\n");

    eq_check_special_q15(&q15refabsmin[1], &q15output1, 1);
	eq_check_special_q15(&u16absminindex[1], &index, 1);

	printf("\n== mips_absmin_q15 check done  == \n\n");


//================23

	printf("== mips_absmin_q15 test ==  \n");
    mips_absmin_q15(q15input2, 23, &q15output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_absmin_q15 output = %x \n", q15output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_q15 finish \n");
	printf("mips_absmin_q15 checking \n\n");

    eq_check_special_q15(&q15refabsmin[2], &q15output1, 1);
	eq_check_special_q15(&u16absminindex[2], &index, 1);

	printf("\n== mips_absmin_q15 check done  == \n\n");

//===========================mean_q15

    q15 q15input3[MAX_SIZE] = {0};
	q15 q15mean[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, StatsQ15, "Input2_q15.txt");
#else
	inputFile3 = StatsQ15_Input2_q15;
	inputFile3Len = sizeof(StatsQ15_Input2_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ15, "MeanVals2_q15.txt");
#else
	referenceFile = StatsQ15_MeanVals2_q15;
	referenceFileLen = sizeof(StatsQ15_MeanVals2_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile3, &paramCountInput3, q15input3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_q15(inputFile3, paramCountInput3, q15input3);
	paramCountInput3 = paramCountInput3/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(referenceFile, &paramCountInput1, q15mean);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q15(referenceFile, paramCountInput1, q15mean);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif

	printf("== mips_mean_q15 test ==  \n");
    mips_mean_q15(q15input3, 7, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_mean_q15 output = %x \n", q15output1);

	}
    printf("mips_mean_q15 finish \n");
	printf("mips_mean_q15 checking \n\n");

    snr_check_special_q15(&q15mean[0], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q15mean[0], &q15output1, 1, ABS_ERROR_Q15);
	
	printf("\n== mips_mean_q15 check done  == \n\n");

//===========16

	printf("== mips_mean_q15 test ==  \n");
    mips_mean_q15(q15input3, 16, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_mean_q15 output = %x \n", q15output1);

	}
    printf("mips_mean_q15 finish \n");
	printf("mips_mean_q15 checking \n\n");

    snr_check_special_q15(&q15mean[1], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q15mean[1], &q15output1, 1, ABS_ERROR_Q15);

	printf("\n== mips_mean_q15 check done  == \n\n");

//===========23

	printf("== mips_mean_q15 test ==  \n");
    mips_mean_q15(q15input3, 23, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_mean_q15 output = %x \n", q15output1);

	}
    printf("mips_mean_q15 finish \n");
	printf("mips_mean_q15 checking \n\n");

    snr_check_special_q15(&q15mean[2], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q15mean[2], &q15output1, 1, ABS_ERROR_Q15);

	printf("\n== mips_mean_q15 check done  == \n\n");

//===========================power_q15

	q63 q63power[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ15, "PowerVals4_q63.txt");
#else
	referenceFile = StatsQ15_PowerVals4_q63;
	referenceFileLen = sizeof(StatsQ15_PowerVals4_q63);
	load_data_q63(referenceFile, referenceFileLen, referenceData_q63);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q63(referenceFile, &paramCountInput1, q63power);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q63(referenceFile, paramCountInput1, q63power);
	paramCountInput1 = paramCountInput1/sizeof(q63);
#endif

	printf("== mips_power_q15 test ==  \n");
    mips_power_q15(q15input1, 7, &q15output1);
	//for (size_t i = 0; i < 2; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_power_q15 output = %x \n", q15output1);

	}
    printf("mips_power_q15 finish \n");
	printf("mips_power_q15 checking \n\n");

    snr_check_special_q15(&q63power[0], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q63power[0], &q15output1, 1, ABS_ERROR_Q63);
	
	printf("\n== mips_power_q15 check done  == \n\n");

//=============16

	printf("== mips_power_q15 test ==  \n");
    mips_power_q15(q15input1, 16, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_power_q15 output = %x \n", q15output1);

	}
    printf("mips_power_q15 finish \n");
	printf("mips_power_q15 checking \n\n");

    snr_check_special_q15(&q63power[1], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q63power[1], &q15output1, 1, ABS_ERROR_Q63);
	
	printf("\n== mips_power_q15 check done  == \n\n");

//=============23

	printf("== mips_power_q15 test ==  \n");
    mips_power_q15(q15input1, 23, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_power_q15 output = %x \n", q15output1);

	}
    printf("mips_power_q15 finish \n");
	printf("mips_power_q15 checking \n\n");

    snr_check_special_q15(&q63power[2], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q63power[2], &q15output1, 1, ABS_ERROR_Q63);
	
	printf("\n== mips_power_q15 check done  == \n\n");


//===========================rms_q15

	q15 q15rms[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ15, "RmsVals5_q15.txt");
#else
	referenceFile = StatsQ15_RmsVals5_q15;
	referenceFileLen = sizeof(StatsQ15_RmsVals5_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(referenceFile, &paramCountInput1, q15rms);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q15(referenceFile, paramCountInput1, q15rms);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif

	printf("== mips_rms_q15 test ==  \n");
    mips_rms_q15(q15input1, 7, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", q15input1[i]);
		printf("mips_rms_q15 output = %x \n", q15output1);

	}
    printf("mips_rms_q15 finish \n");
	printf("mips_rms_q15 checking \n\n");

    snr_check_special_q15(&q15rms[0], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q15rms[0], &q15output1, 1, ABS_ERROR_Q15);
	
	printf("\n== mips_rms_q15 check done  == \n\n");

//=============16

	printf("== mips_rms_q15 test ==  \n");
    mips_rms_q15(q15input1, 16, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", q15input1[i]);
		printf("mips_rms_q15 output = %x \n", q15output1);

	}
    printf("mips_rms_q15 finish \n");
	printf("mips_rms_q15 checking \n\n");

    snr_check_special_q15(&q15rms[1], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q15rms[1], &q15output1, 1, ABS_ERROR_Q15);
	
	printf("\n== mips_rms_q15 check done  == \n\n");

//=============23

	printf("== mips_rms_q15 test ==  \n");
    mips_rms_q15(q15input1, 23, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", q15input1[i]);
		printf("mips_rms_q15 output = %x \n", q15output1);

	}
    printf("mips_rms_q15 finish \n");
	printf("mips_rms_q15 checking \n\n");

    snr_check_special_q15(&q15rms[2], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q15rms[2], &q15output1, 1, ABS_ERROR_Q15);
	
	printf("\n== mips_rms_q15 check done  == \n\n");

//===========================std_q15

	q15 q15std[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ15, "StdVals6_q15.txt");
#else
	referenceFile = StatsQ15_StdVals6_q15;
	referenceFileLen = sizeof(StatsQ15_StdVals6_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(referenceFile, &paramCountInput1, q15std);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q15(referenceFile, paramCountInput1, q15std);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif

	printf("== mips_std_q15 test ==  \n");
    mips_std_q15(q15input1, 7, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_std_q15 output = %x \n", q15output1);

	}
    printf("mips_std_q15 finish \n");
	printf("mips_std_q15 checking \n\n");

    snr_check_special_q15(&q15std[0], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q15std[0], &q15output1, 1, ABS_ERROR_Q15);
	
	printf("\n== mips_std_q15 check done  == \n\n");

//============16

	printf("== mips_std_q15 test ==  \n");
    mips_std_q15(q15input1, 16, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_std_q15 output = %x \n", q15output1);

	}
    printf("mips_std_q15 finish \n");
	printf("mips_std_q15 checking \n\n");

    snr_check_special_q15(&q15std[1], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q15std[1], &q15output1, 1, ABS_ERROR_Q15);
	
	printf("\n== mips_std_q15 check done  == \n\n");
	
//============23

	printf("== mips_std_q15 test ==  \n");
    mips_std_q15(q15input1, 23, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_std_q15 output = %x \n", q15output1);

	}
    printf("mips_std_q15 finish \n");
	printf("mips_std_q15 checking \n\n");

    snr_check_special_q15(&q15std[2], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q15std[2], &q15output1, 1, ABS_ERROR_Q15);
	
	printf("\n== mips_std_q15 check done  == \n\n");


//===========================var_q15

	q15 q15var[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ15, "VarVals7_q15.txt");
#else
	referenceFile = StatsQ15_VarVals7_q15;
	referenceFileLen = sizeof(StatsQ15_VarVals7_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(referenceFile, &paramCountInput1, q15var);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q15(referenceFile, paramCountInput1, q15var);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif

	printf("== mips_var_q15 test ==  \n");
    mips_var_q15(q15input1, 7, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_var_q15 output = %x \n", q15output1);

	}
    printf("mips_var_q15 finish \n");
	printf("mips_var_q15 checking \n\n");

    snr_check_special_q15(&q15var[0], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q15var[0], &q15output1, 1, ABS_ERROR_Q15);
	
	printf("\n== mips_var_q15 check done  == \n\n");


//===========16

	printf("== mips_var_q15 test ==  \n");
    mips_var_q15(q15input1, 16, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_var_q15 output = %x \n", q15output1);

	}
    printf("mips_var_q15 finish \n");
	printf("mips_var_q15 checking \n\n");

    snr_check_special_q15(&q15var[1], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q15var[1], &q15output1, 1, ABS_ERROR_Q15);
	
	printf("\n== mips_var_q15 check done  == \n\n");


//===========23

	printf("== mips_var_q15 test ==  \n");
    mips_var_q15(q15input1, 23, &q15output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_var_q15 output = %x \n", q15output1);

	}
    printf("mips_var_q15 finish \n");
	printf("mips_var_q15 checking \n\n");

    snr_check_special_q15(&q15var[2], &q15output1, 1, SNR_THRESHOLD);
	near_check_special_q15(&q15var[2], &q15output1, 1, ABS_ERROR_Q15);
	
	printf("\n== mips_var_q15 check done  == \n\n");



//===========================mse_q15

	int paramCountInputA = 0;
	int paramCountInputB = 0;
	q15 q15inputa[MAX_SIZE] = {0};
	q15 q15inputb[MAX_SIZE] = {0};


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


	q15 q15mse[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea, sizeof(inputFilea), "%s%s%s", Patterns_PATH, StatsQ15, "InputNew1_q15.txt");
#else
	inputFilea = StatsQ15_InputNew1_q15;
	inputFileaLen = sizeof(StatsQ15_InputNew1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb, sizeof(inputFileb), "%s%s%s", Patterns_PATH, StatsQ15, "InputNew2_q15.txt");
#else
	inputFileb = StatsQ15_InputNew2_q15;
	inputFilebLen = sizeof(StatsQ15_InputNew2_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ15, "MSEVals10_q15.txt");
#else
	referenceFile = StatsQ15_MSEVals10_q15;
	referenceFileLen = sizeof(StatsQ15_MSEVals10_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(inputFilea, &paramCountInputA, q15inputa);
#else
	paramCountInputA = inputFileaLen;
	load_data_q15(inputFilea, paramCountInputA, q15inputa);
	paramCountInputA = paramCountInputA/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFileb, &paramCountInputB, q15inputb);
#else
	paramCountInputB = inputFilebLen;
	load_data_q15(inputFileb, paramCountInputB, q15inputb);
	paramCountInputB = paramCountInputB/sizeof(q15);
#endif
#if defined(NOT_EMBEDDED)
	load_data_q15(referenceFile, &paramCountInput1,q15mse);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q15(referenceFile, paramCountInput1,q15mse);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif
	printf("== mips_mse_q15 test ==  \n");


    mips_mse_q15(q15inputa,q15inputb,7,&q15output1);    
		//for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_mse_q15 output = %x \n", q15output1);

	}
    printf("mips_mse_q15 finish \n");
	printf("mips_mse_q15 checking \n\n");

    snr_check_special_q15(&q15mse[0], &q15output1, 1, SNR_THRESHOLD_MSE);
	near_check_special_q15(&q15mse[0], &q15output1, 1, ABS_ERROR_Q15_MSE);

	printf("\n== mips_mse_q15 check done  == \n\n");

//=============mse 100
	printf("== mips_mse_q15 test ==  \n");


    mips_mse_q15(q15inputa,q15inputb,100,&q15output1);
		//for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %x \n", q15input1[i]);
		printf("mips_mse_q15 output = %x \n", q15output1);

	}
    printf("mips_mse_q15 finish \n");
	printf("mips_mse_q15 checking \n\n");

    snr_check_special_q15(&q15mse[3], &q15output1, 1, SNR_THRESHOLD_MSE);
	near_check_special_q15(&q15mse[3], &q15output1, 1, ABS_ERROR_Q15_MSE);

	printf("\n== mips_mse_q15 check done  == \n\n");


	return 0 ;
}
