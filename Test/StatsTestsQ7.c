#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/basic_math_functions.h"
#include "dsp/statistics_functions.h"
#define SNR_THRESHOLD 20
#define SNR_THRESHOLD_MSE 20

/* 

Reference patterns are generated with
a q7 precision computation.

*/
#define ABS_ERROR_Q7 ((q7)20)
#define ABS_ERROR_Q31 ((q31)(1<<15))

#define ABS_ERROR_Q7_MSE ((q7)6)

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

    q7 q7refmax[MAX_SIZE] = {0};
	q7 q7refmin[MAX_SIZE] = {0};

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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, StatsQ7, "Input1_q7.txt");
#else
	inputFile1 = StatsQ7_Input1_q7;
	inputFile1Len = sizeof(StatsQ7_Input1_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ7, "MaxVals1_q7.txt");
#else
	referenceFile = StatsQ7_MaxVals1_q7;
	referenceFileLen = sizeof(StatsQ7_MaxVals1_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsQ7, "MaxIndexes1_s16.txt");
#else
	indexvalFile = StatsQ7_MaxIndexes1_s16;
	indexvalFileLen = sizeof(StatsQ7_MaxIndexes1_s16);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q7(inputFile1, &paramCountInput1, q7input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q7(inputFile1, paramCountInput1, q7input1);
	paramCountInput1 = paramCountInput1/sizeof(q7);
#endif

	q7 q7output1;
    uint16_t u16maxindex[MAX_SIZE] = {0};
    uint32_t index;
//===========max
	printf("== mips_max_q7 test ==  \n");
    mips_max_q7(q7input1, 15, &q7output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %x \n", q7input1[i]);
		printf("mips_max_q7 output = %x \n", q7output1);
        printf("index = %d \n", index);
	}
    printf("mips_max_q7 finish \n");
	printf("mips_max_q7 checking \n\n");


#if defined(NOT_EMBEDDED)
	load_data_q7(referenceFile, &paramCountInput1, q7refmax);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q7(referenceFile, paramCountInput1, q7refmax);
	paramCountInput1 = paramCountInput1/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(indexvalFile, &paramCountInput1, u16maxindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u16(indexvalFile, paramCountInput1, u16maxindex);
	paramCountInput1 = paramCountInput1/sizeof(uint16_t);
#endif

    eq_check_special_q7(&q7refmax[0], &q7output1, 1);
    eq_check_special_q15(&u16maxindex[0], &index, 1);
	printf("\n== mips_max_q7 check done  == \n\n");

//=========32
    mips_max_q7(q7input1, 32, &q7output1, &index);
		//for (size_t i = 0; i < 8; i++)
	{
        //printf("input = %x \n", q7input1[i]);
		printf("mips_max_q7 output = %x \n", q7output1);
        printf("index = %d \n", index);
	}
    printf("mips_max_q7 finish \n");
		printf("mips_max_q7 output = %x \n", q7output1);
        printf("index = %d \n", index);
	printf("mips_max_q7 checking \n\n");
    eq_check_special_q7(&q7refmax[1], &q7output1, 1);
    eq_check_special_q15(&u16maxindex[1], &index, 1);
	printf("\n== mips_max_q7 check done  == \n\n");

//=======47
#if defined(NOT_EMBEDDED)
	load_data_q7(inputFile1, &paramCountInput1, q7input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q7(inputFile1, paramCountInput1, q7input1);
	paramCountInput1 = paramCountInput1/sizeof(q7);
#endif

    mips_max_q7(q7input1, 47, &q7output1, &index);
    printf("mips_max_q7 finish \n");
		printf("mips_max_q7 output = %x \n", q7output1);
        printf("index = %d \n", index);
	printf("mips_max_q7 checking \n\n");
    eq_check_special_q7(&q7refmax[2], &q7output1, 1);
    eq_check_special_q15(&u16maxindex[2], &index, 1);

	printf("\n== mips_max_q7 check done  == \n\n");


// =====================absmax

    q7 q7refabsmax[MAX_SIZE] = {0};
    uint16_t u16absmaxindex[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, StatsQ7, "InputNew1_q7.txt");
#else
	inputFile2 = StatsQ7_InputNew1_q7;
	inputFile2Len = sizeof(StatsQ7_InputNew1_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ7, "AbsMaxVals8_q7.txt");
#else
	referenceFile = StatsQ7_AbsMaxVals8_q7;
	referenceFileLen = sizeof(StatsQ7_AbsMaxVals8_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsQ7, "AbsMaxIndexes8_s16.txt");
#else
	indexvalFile = StatsQ7_AbsMaxIndexes8_s16;
	indexvalFileLen = sizeof(StatsQ7_AbsMaxIndexes8_s16);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q7(inputFile2, &paramCountInput2, q7input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q7(inputFile2, paramCountInput2, q7input2);
	paramCountInput2 = paramCountInput2/sizeof(q7);
#endif


	printf("== mips_absmax_q7 test ==  \n");
    mips_absmax_q7(q7input2, 15, &q7output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %x \n", q7input1[i]);
		printf("mips_absmax_q7 output = %x \n", q7output1);
        printf("index = %d \n", index);
	}
    printf("mips_absmax_q7 finish \n");

	printf("mips_absmax_q7 checking \n\n");
#if defined(NOT_EMBEDDED)
	load_data_q7(referenceFile, &paramCountInput1, q7refabsmax);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q7(referenceFile, paramCountInput1, q7refabsmax);
	paramCountInput1 = paramCountInput1/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(indexvalFile, &paramCountInput1, u16absmaxindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u16(indexvalFile, paramCountInput1, u16absmaxindex);
	paramCountInput1 = paramCountInput1/sizeof(uint16_t);
#endif

    eq_check_special_q7(&q7refabsmax[0], &q7output1, 1);
    eq_check_special_q15(&u16absmaxindex[0], &index, 1);
	printf("\n== mips_absmax_q7 check done  == \n\n");


//=======32

#if defined(NOT_EMBEDDED)
	load_data_q7(inputFile2, &paramCountInput2, q7input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q7(inputFile2, paramCountInput2, q7input2);
	paramCountInput2 = paramCountInput2/sizeof(q7);
#endif

	printf("== mips_absmax_q7 test ==  \n");
    mips_absmax_q7(q7input2, 32, &q7output1, &index);
	//for (size_t i = 0; i < 8; i++)
	{
       // printf("input = %x \n", q7input1[i]);
		printf("mips_absmax_q7 output = %x \n", q7output1);
        printf("index = %d \n", index);

	}
    printf("mips_absmax_q7 finish \n");

	printf("mips_absmax_q7 checking \n\n");

    eq_check_special_q7(&q7refabsmax[1], &q7output1, 1);
    eq_check_special_q15(&u16absmaxindex[1], &index, 1);
	printf("\n== mips_absmax_q7 check done  == \n\n");


//=======47
#if defined(NOT_EMBEDDED)
	load_data_q7(inputFile2, &paramCountInput2, q7input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q7(inputFile2, paramCountInput2, q7input2);
	paramCountInput2 = paramCountInput2/sizeof(q7);
#endif

	printf("== mips_absmax_q7 test ==  \n");
    mips_absmax_q7(q7input2, 47, &q7output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %x \n", q7input1[i]);
		printf("mips_absmax_q7 output = %x \n", q7output1);
        printf("index = %d \n", index);

	}
    printf("mips_absmax_q7 finish \n");

	printf("mips_absmax_q7 checking \n\n");

    eq_check_special_q7(&q7refabsmax[2], &q7output1, 1);
    eq_check_special_q15(&u16absmaxindex[2], &index, 1);
	printf("\n== mips_absmax_q7 check done  == \n\n");

// =====================max_no_idx

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ7, "MaxVals1_q7.txt");
#else
	referenceFile = StatsQ7_MaxVals1_q7;
	referenceFileLen = sizeof(StatsQ7_MaxVals1_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif

	printf("== mips_max_no_idx_q7 test ==  \n");
    mips_max_no_idx_q7(q7input1, 15, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_max_no_idx_q7 output = %x \n", q7output1);
	}
    printf("mips_max_no_idx_q7 finish \n");
	printf("mips_max_no_idx_q7 checking \n\n");

    eq_check_special_q7(&q7refmax[0], &q7output1, 1);

	printf("\n== mips_max_no_idx_q7 check done  == \n\n");

// ===================32

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ7, "MaxVals1_q7.txt");
#else
	referenceFile = StatsQ7_MaxVals1_q7;
	referenceFileLen = sizeof(StatsQ7_MaxVals1_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif

	printf("== mips_max_no_idx_q7 test ==  \n");
    mips_max_no_idx_q7(q7input1, 32, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_max_no_idx_q7 output = %x \n", q7output1);
	}
    printf("mips_max_no_idx_q7 finish \n");
	printf("mips_max_no_idx_q7 checking \n\n");

    eq_check_special_q7(&q7refmax[1], &q7output1, 1);
	
	printf("\n== mips_max_no_idx_q7 check done  == \n\n");

// ===================47

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ7, "MaxVals1_q7.txt");
#else
	referenceFile = StatsQ7_MaxVals1_q7;
	referenceFileLen = sizeof(StatsQ7_MaxVals1_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif

	printf("== mips_max_no_idx_q7 test ==  \n");
    mips_max_no_idx_q7(q7input1, 47, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_max_no_idx_q7 output = %x \n", q7output1);
	}
    printf("mips_max_no_idx_q7 finish \n");
	printf("mips_max_no_idx_q7 checking \n\n");

    eq_check_special_q7(&q7refmax[2], &q7output1, 1);
	
	printf("\n== mips_max_no_idx_q7 check done  == \n\n");

//=====================abs_no_idx


	printf("== mips_absmax_no_idx_q7 test ==  \n");
    mips_absmax_no_idx_q7(q7input2, 15, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_absmax_no_idx_q7 output = %x \n", q7output1);
	}
    printf("mips_absmax_no_idx_q7 finish \n");
	printf("mips_absmax_no_idx_q7 checking \n\n");

    eq_check_special_q7(&q7refabsmax[0], &q7output1, 1);
	printf("\n== mips_absmax_no_idx_q7 check done  == \n\n");
    
//==============32

	printf("== mips_absmax_no_idx_q7 test ==  \n");
    mips_absmax_no_idx_q7(q7input2, 32, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_absmax_no_idx_q7 output = %x \n", q7output1);
	}
    printf("mips_absmax_no_idx_q7 finish \n");
	printf("mips_absmax_no_idx_q7 checking \n\n");

    eq_check_special_q7(&q7refabsmax[1], &q7output1, 1);
	printf("\n== mips_absmax_no_idx_q7 check done  == \n\n");


//==============47

	printf("== mips_absmax_no_idx_q7 test ==  \n");
    mips_absmax_no_idx_q7(q7input2, 47, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_absmax_no_idx_q7 output = %x \n", q7output1);
	}
    printf("mips_absmax_no_idx_q7 finish \n");
	printf("mips_absmax_no_idx_q7 checking \n\n");

    eq_check_special_q7(&q7refabsmax[2], &q7output1, 1);
	printf("\n== mips_absmax_no_idx_q7 check done  == \n\n");

//=====================min_no_idx

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ7, "MinVals3_q7.txt");
#else
	referenceFile = StatsQ7_MinVals3_q7;
	referenceFileLen = sizeof(StatsQ7_MinVals3_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q7(referenceFile, &paramCountInput1, q7refmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q7(referenceFile, paramCountInput1, q7refmin);
	paramCountInput1 = paramCountInput1/sizeof(q7);
#endif

	printf("== mips_min_no_idx_q7 test ==  \n");
    mips_min_no_idx_q7(q7input1, 15, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_min_no_idx_q7 output = %x \n", q7output1);
	}
    printf("mips_min_no_idx_q7 finish \n");
	printf("mips_min_no_idx_q7 checking \n\n");

    eq_check_special_q7(&q7refmin[0], &q7output1, 1);
	printf("\n== mips_min_no_idx_q7 check done  == \n\n");

//=========32

	printf("== mips_min_no_idx_q7 test ==  \n");
    mips_min_no_idx_q7(q7input1, 32, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_min_no_idx_q7 output = %x \n", q7output1);
	}
    printf("mips_min_no_idx_q7 finish \n");
	printf("mips_min_no_idx_q7 checking \n\n");

    eq_check_special_q7(&q7refmin[1], &q7output1, 1);
	printf("\n== mips_min_no_idx_q7 check done  == \n\n");

//=========47

	printf("== mips_min_no_idx_q7 test ==  \n");
    mips_min_no_idx_q7(q7input1, 47, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_min_no_idx_q7 output = %x \n", q7output1);
	}
    printf("mips_min_no_idx_q7 finish \n");
	printf("mips_min_no_idx_q7 checking \n\n");

    eq_check_special_q7(&q7refmin[2], &q7output1, 1);
	printf("\n== mips_min_no_idx_q7 check done  == \n\n");


//=====================absmin_no_idx
    q7 q7refabsmin[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ7, "AbsMinVals9_q7.txt");
#else
	referenceFile = StatsQ7_AbsMinVals9_q7;
	referenceFileLen = sizeof(StatsQ7_AbsMinVals9_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q7(referenceFile, &paramCountInput1, q7refabsmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q7(referenceFile, paramCountInput1, q7refabsmin);
	paramCountInput1 = paramCountInput1/sizeof(q7);
#endif

	printf("== mips_absmin_no_idx_q7 test ==  \n");
    mips_absmin_no_idx_q7(q7input2, 15, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_absmin_no_idx_q7 output = %x \n", q7output1);
	}
    printf("mips_absmin_no_idx_q7 finish \n");
	printf("mips_absmin_no_idx_q7 checking \n\n");

    eq_check_special_q7(&q7refabsmin[0], &q7output1, 1);

	printf("\n== mips_absmin_no_idx_q7 check done  == \n\n");

//================32


	printf("== mips_absmin_no_idx_q7 test ==  \n");
    mips_absmin_no_idx_q7(q7input2, 32, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_absmin_no_idx_q7 output = %x \n", q7output1);
	}
    printf("mips_absmin_no_idx_q7 finish \n");
	printf("mips_absmin_no_idx_q7 checking \n\n");

    eq_check_special_q7(&q7refabsmin[1], &q7output1, 1);
	
	printf("\n== mips_absmin_no_idx_q7 check done  == \n\n");

//=================47


	printf("== mips_absmin_no_idx_q7 test ==  \n");
    mips_absmin_no_idx_q7(q7input2, 47, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_absmin_no_idx_q7 output = %x \n", q7output1);
	}
    printf("mips_absmin_no_idx_q7 finish \n");
	printf("mips_absmin_no_idx_q7 checking \n\n");

    eq_check_special_q7(&q7refabsmin[2], &q7output1, 1);
	
	printf("\n== mips_absmin_no_idx_q7 check done  == \n\n");

//=====================min_no_idx

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ7, "MinVals3_q7.txt");
#else
	referenceFile = StatsQ7_MinVals3_q7;
	referenceFileLen = sizeof(StatsQ7_MinVals3_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsQ7, "MinIndexes3_s16.txt");
#else
	indexvalFile = StatsQ7_MinIndexes3_s16;
	indexvalFileLen = sizeof(StatsQ7_MinIndexes3_s16);
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
	load_data_q7(referenceFile, &paramCountInput1, q7refmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q7(referenceFile, paramCountInput1, q7refmin);
	paramCountInput1 = paramCountInput1/sizeof(q7);
#endif

	printf("== mips_min_q7 test ==  \n");
    mips_min_q7(q7input1, 15, &q7output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_min_q7 output = %x \n", q7output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_q7 finish \n");
	printf("mips_min_q7 checking \n\n");

    eq_check_special_q7(&q7refmin[0], &q7output1, 1);
	eq_check_special_q15(&u16minindex[0], &index, 1);
	printf("\n== mips_min_q7 check done  == \n\n");

//===============32

	printf("== mips_min_q7 test ==  \n");
    mips_min_q7(q7input1, 32, &q7output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_min_q7 output = %x \n", q7output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_q7 finish \n");
	printf("mips_min_q7 checking \n\n");

    eq_check_special_q7(&q7refmin[1], &q7output1, 1);
	eq_check_special_q15(&u16minindex[1], &index, 1);
	printf("\n== mips_min_q7 check done  == \n\n");

//===============47

	printf("== mips_min_q7 test ==  \n");
    mips_min_q7(q7input1, 47, &q7output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_min_q7 output = %x \n", q7output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_q7 finish \n");
	printf("mips_min_q7 checking \n\n");

    eq_check_special_q7(&q7refmin[2], &q7output1, 1);
	eq_check_special_q15(&u16minindex[2], &index, 1);
	printf("\n== mips_min_q7 check done  == \n\n");

//=====================absmin

    uint16_t u16absminindex[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsQ7, "AbsMinIndexes9_s16.txt");
#else
	indexvalFile = StatsQ7_AbsMinIndexes9_s16;
	indexvalFileLen = sizeof(StatsQ7_AbsMinIndexes9_s16);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(indexvalFile, &paramCountInput1, u16absminindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u16(indexvalFile, paramCountInput1, u16absminindex);
	paramCountInput1 = paramCountInput1/sizeof(uint16_t);
#endif

	printf("== mips_absmin_q7 test ==  \n");
    mips_absmin_q7(q7input2, 15, &q7output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_absmin_q7 output = %x \n", q7output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_q7 finish \n");
	printf("mips_absmin_q7 checking \n\n");

    eq_check_special_q7(&q7refabsmin[0], &q7output1, 1);
	eq_check_special_q15(&u16absminindex[0], &index, 1);

	printf("\n== mips_absmin_q7 check done  == \n\n");

//===============32

	printf("== mips_absmin_q7 test ==  \n");
    mips_absmin_q7(q7input2, 32, &q7output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_absmin_q7 output = %x \n", q7output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_q7 finish \n");
	printf("mips_absmin_q7 checking \n\n");

    eq_check_special_q7(&q7refabsmin[1], &q7output1, 1);
	eq_check_special_q15(&u16absminindex[1], &index, 1);

	printf("\n== mips_absmin_q7 check done  == \n\n");


//================47

	printf("== mips_absmin_q7 test ==  \n");
    mips_absmin_q7(q7input2, 47, &q7output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_absmin_q7 output = %x \n", q7output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_q7 finish \n");
	printf("mips_absmin_q7 checking \n\n");

    eq_check_special_q7(&q7refabsmin[2], &q7output1, 1);
	eq_check_special_q15(&u16absminindex[2], &index, 1);

	printf("\n== mips_absmin_q7 check done  == \n\n");

//===========================mean_q7

    q7 q7input3[MAX_SIZE] = {0};
	q7 q7mean[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, StatsQ7, "Input2_q7.txt");
#else
	inputFile3 = StatsQ7_Input2_q7;
	inputFile3Len = sizeof(StatsQ7_Input2_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ7, "MeanVals2_q7.txt");
#else
	referenceFile = StatsQ7_MeanVals2_q7;
	referenceFileLen = sizeof(StatsQ7_MeanVals2_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q7(inputFile3, &paramCountInput3, q7input3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_q7(inputFile3, paramCountInput3, q7input3);
	paramCountInput3 = paramCountInput3/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q7(referenceFile, &paramCountInput1, q7mean);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q7(referenceFile, paramCountInput1, q7mean);
	paramCountInput1 = paramCountInput1/sizeof(q7);
#endif

	printf("== mips_mean_q7 test ==  \n");
    mips_mean_q7(q7input3, 15, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_mean_q7 output = %x \n", q7output1);

	}
    printf("mips_mean_q7 finish \n");
	printf("mips_mean_q7 checking \n\n");

    snr_check_special_q7(&q7mean[0], &q7output1, 1, SNR_THRESHOLD);
	near_check_special_q7(&q7mean[0], &q7output1, 1, ABS_ERROR_Q7);
	
	printf("\n== mips_mean_q7 check done  == \n\n");

//===========32

	printf("== mips_mean_q7 test ==  \n");
    mips_mean_q7(q7input3, 32, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_mean_q7 output = %x \n", q7output1);

	}
    printf("mips_mean_q7 finish \n");
	printf("mips_mean_q7 checking \n\n");

    snr_check_special_q7(&q7mean[1], &q7output1, 1, SNR_THRESHOLD);
	near_check_special_q7(&q7mean[1], &q7output1, 1, ABS_ERROR_Q7);

	printf("\n== mips_mean_q7 check done  == \n\n");

//===========47

	printf("== mips_mean_q7 test ==  \n");
    mips_mean_q7(q7input3, 47, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_mean_q7 output = %x \n", q7output1);

	}
    printf("mips_mean_q7 finish \n");
	printf("mips_mean_q7 checking \n\n");

    snr_check_special_q7(&q7mean[2], &q7output1, 1, SNR_THRESHOLD);
	near_check_special_q7(&q7mean[2], &q7output1, 1, ABS_ERROR_Q7);

	printf("\n== mips_mean_q7 check done  == \n\n");

//===========================power_q7

	q31 q31power[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ7, "PowerVals4_q31.txt");
#else
	referenceFile = StatsQ7_PowerVals4_q31;
	referenceFileLen = sizeof(StatsQ7_PowerVals4_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q31(referenceFile, &paramCountInput1, q31power);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q31(referenceFile, paramCountInput1, q31power);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

	printf("== mips_power_q7 test ==  \n");
    mips_power_q7(q7input1, 15, &q7output1);
	//for (size_t i = 0; i < 2; i++)
	{
     //   printf("input = %x \n", q7inpu%ft1[i]);
		printf("mips_power_q7 output = %x \n", &q7output1);

	}
    printf("mips_power_q7 finish \n");
	printf("mips_power_q7 checking \n\n");

    snr_check_special_q7(&q31power[0], &q7output1, 1, SNR_THRESHOLD);
	near_check_special_q7(&q31power[0], &q7output1, 1, ABS_ERROR_Q31);
	
	printf("\n== mips_power_q7 check done  == \n\n");

//=============32

	printf("== mips_power_q7 test ==  \n");
    mips_power_q7(q7input1, 32, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_power_q7 output = %x \n", &q7output1);

	}
    printf("mips_power_q7 finish \n");
	printf("mips_power_q7 checking \n\n");

    snr_check_special_q7(&q31power[1], &q7output1, 1, SNR_THRESHOLD);
	near_check_special_q7(&q31power[1], &q7output1, 1, ABS_ERROR_Q31);
	
	printf("\n== mips_power_q7 check done  == \n\n");

//=============47

	printf("== mips_power_q7 test ==  \n");
    mips_power_q7(q7input1, 47, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_power_q7 output = %x \n", &q7output1);

	}
    printf("mips_power_q7 finish \n");
	printf("mips_power_q7 checking \n\n");

    snr_check_special_q7(&q31power[2], &q7output1, 1, SNR_THRESHOLD);
	near_check_special_q7(&q31power[2], &q7output1, 1, ABS_ERROR_Q31);
	
	printf("\n== mips_power_q7 check done  == \n\n");


#if 0

//===========================std_q7

	q7 q7std[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ7, "StdVals6_q7.txt");
#else
	referenceFile = StatsQ7_StdVals6_q7;
	referenceFileLen = sizeof(StatsQ7_StdVals6_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q7(referenceFile, &paramCountInput1, q7std);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q7(referenceFile, paramCountInput1, q7std);
	paramCountInput1 = paramCountInput1/sizeof(q7);
#endif

	printf("== mips_std_q7 test ==  \n");
    mips_std_q7(q7input1, 2, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_std_q7 output = %x \n", q7output1);

	}
    printf("mips_std_q7 finish \n");
	printf("mips_std_q7 checking \n\n");

    snr_check_special_q7(&q7std[0], &q7output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&q7std[0], &q7output1, 1, ABS_ERROR_Q7);
	
	printf("\n== mips_std_q7 check done  == \n\n");

//============4

	printf("== mips_std_q7 test ==  \n");
    mips_std_q7(q7input1, 4, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_std_q7 output = %x \n", q7output1);

	}
    printf("mips_std_q7 finish \n");
	printf("mips_std_q7 checking \n\n");

    snr_check_special_q7(&q7std[1], &q7output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&q7std[1], &q7output1, 1, ABS_ERROR_Q7);
	
	printf("\n== mips_std_q7 check done  == \n\n");
	
//============5

	printf("== mips_std_q7 test ==  \n");
    mips_std_q7(q7input1, 5, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_std_q7 output = %x \n", q7output1);

	}
    printf("mips_std_q7 finish \n");
	printf("mips_std_q7 checking \n\n");

    snr_check_special_q7(&q7std[2], &q7output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&q7std[2], &q7output1, 1, ABS_ERROR_Q7);
	
	printf("\n== mips_std_q7 check done  == \n\n");


//===========================var_q7

	q7 q7var[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ7, "VarVals7_q7.txt");
#else
	referenceFile = StatsQ7_VarVals7_q7;
	referenceFileLen = sizeof(StatsQ7_VarVals7_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q7(referenceFile, &paramCountInput1, q7var);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q7(referenceFile, paramCountInput1, q7var);
	paramCountInput1 = paramCountInput1/sizeof(q7);
#endif

	printf("== mips_var_q7 test ==  \n");
    mips_var_q7(q7input1, 2, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_var_q7 output = %x \n", q7output1);

	}
    printf("mips_var_q7 finish \n");
	printf("mips_var_q7 checking \n\n");

    snr_check_special_q7(&q7var[0], &q7output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&q7var[0], &q7output1, 1, ABS_ERROR_Q7);
	
	printf("\n== mips_var_q7 check done  == \n\n");


//===========4

	printf("== mips_var_q7 test ==  \n");
    mips_var_q7(q7input1, 4, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_var_q7 output = %x \n", q7output1);

	}
    printf("mips_var_q7 finish \n");
	printf("mips_var_q7 checking \n\n");

    snr_check_special_q7(&q7var[1], &q7output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&q7var[1], &q7output1, 1, ABS_ERROR_Q7);
	
	printf("\n== mips_var_q7 check done  == \n\n");


//===========5

	printf("== mips_var_q7 test ==  \n");
    mips_var_q7(q7input1, 5, &q7output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_var_q7 output = %x \n", q7output1);

	}
    printf("mips_var_q7 finish \n");
	printf("mips_var_q7 checking \n\n");

    snr_check_special_q7(&q7var[2], &q7output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&q7var[2], &q7output1, 1, ABS_ERROR_Q7);
	
	printf("\n== mips_var_q7 check done  == \n\n");
#endif

//===========================mse_q7

	int paramCountInputA = 0;
	int paramCountInputB = 0;
	q7 q7inputa[MAX_SIZE] = {0};
	q7 q7inputb[MAX_SIZE] = {0};


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


	q7 q7mse[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea, sizeof(inputFilea), "%s%s%s", Patterns_PATH, StatsQ7, "InputNew1_q7.txt");
#else
	inputFilea = StatsQ7_InputNew1_q7;
	inputFileaLen = sizeof(StatsQ7_InputNew1_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb, sizeof(inputFileb), "%s%s%s", Patterns_PATH, StatsQ7, "InputNew2_q7.txt");
#else
	inputFileb = StatsQ7_InputNew2_q7;
	inputFilebLen = sizeof(StatsQ7_InputNew2_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsQ7, "MSEVals10_q7.txt");
#else
	referenceFile = StatsQ7_MSEVals10_q7;
	referenceFileLen = sizeof(StatsQ7_MSEVals10_q7);
	load_data_q7(referenceFile, referenceFileLen, referenceData_q7);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q7(inputFilea, &paramCountInputA, q7inputa);
#else
	paramCountInputA = inputFileaLen;
	load_data_q7(inputFilea, paramCountInputA, q7inputa);
	paramCountInputA = paramCountInputA/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q7(inputFileb, &paramCountInputB, q7inputb);
#else
	paramCountInputB = inputFilebLen;
	load_data_q7(inputFileb, paramCountInputB, q7inputb);
	paramCountInputB = paramCountInputB/sizeof(q7);
#endif
#if defined(NOT_EMBEDDED)
	load_data_q7(referenceFile, &paramCountInput1,q7mse);
#else
	paramCountInput1 = referenceFileLen;
	load_data_q7(referenceFile, paramCountInput1,q7mse);
	paramCountInput1 = paramCountInput1/sizeof(q7);
#endif
	printf("== mips_mse_q7 test ==  \n");


    mips_mse_q7(q7inputa,q7inputb,32,&q7output1);
		//for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_mse_q7 output = %x \n", q7output1);

	}
    printf("mips_mse_q7 finish \n");
	printf("mips_mse_q7 checking \n\n");

    snr_check_special_q7(&q7mse[0], &q7output1, 1, SNR_THRESHOLD_MSE);
	near_check_special_q7(&q7mse[0], &q7output1, 1, ABS_ERROR_Q7_MSE);

	printf("\n== mips_mse_q7 check done  == \n\n");

//=============mse 100
	printf("== mips_mse_q7 test ==  \n");


    mips_mse_q7(q7inputa,q7inputb,100,&q7output1);
		//for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %x \n", q7input1[i]);
		printf("mips_mse_q7 output = %x \n", q7output1);

	}
    printf("mips_mse_q7 finish \n");
	printf("mips_mse_q7 checking \n\n");

    snr_check_special_q7(&q7mse[3], &q7output1, 1, SNR_THRESHOLD_MSE);
	near_check_special_q7(&q7mse[3], &q7output1, 1, ABS_ERROR_Q7_MSE);

	printf("\n== mips_mse_q7 check done  == \n\n");


	return 0 ;
}
