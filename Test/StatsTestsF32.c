#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/basic_math_functions.h"
#include "dsp/statistics_functions.h"
#define SNR_THRESHOLD (float)120
#define REL_ERROR (1.0e-5)
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

	float f32input1[MAX_SIZE] = {0};
	float f32input2[MAX_SIZE] = {0};

    float f32refmax[MAX_SIZE] = {0};
	float f32refmin[MAX_SIZE] = {0};

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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, StatsF32, "Input1_f32.txt");
#else
	inputFile1 = StatsF32_Input1_f32;
	inputFile1Len = sizeof(StatsF32_Input1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "MaxVals1_f32.txt");
#else
	referenceFile = StatsF32_MaxVals1_f32;
	referenceFileLen = sizeof(StatsF32_MaxVals1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsF32, "MaxIndexes1_s16.txt");
#else
	indexvalFile = StatsF32_MaxIndexes1_s16;
	indexvalFileLen = sizeof(StatsF32_MaxIndexes1_s16);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile1, &paramCountInput1, f32input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f32(inputFile1, paramCountInput1, f32input1);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

	float f32output1;
    uint16_t u16maxindex[MAX_SIZE] = {0};
    uint32_t index;
//===========max
	printf("== mips_max_f32 test ==  \n");
    mips_max_f32(f32input1, 3, &f32output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %f \n", f32input1[i]);
		printf("mips_max_f32 output = %f \n", f32output1);
        printf("index = %d \n", index);
	}
    printf("mips_max_f32 finish \n");
	printf("mips_max_f32 checking \n\n");


#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFile, &paramCountInput1, f32refmax);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f32(referenceFile, paramCountInput1, f32refmax);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(indexvalFile, &paramCountInput1, u16maxindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u16(indexvalFile, paramCountInput1, u16maxindex);
	paramCountInput1 = paramCountInput1/sizeof(uint16_t);
#endif

    eq_check_special_f32(&f32refmax[0], &f32output1, 1);
    eq_check_special_q15(&u16maxindex[0], &index, 1);
	printf("\n== mips_max_f32 check done  == \n\n");

//=======8
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile1, &paramCountInput1, f32input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f32(inputFile1, paramCountInput1, f32input1);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

    mips_max_f32(f32input1, 8, &f32output1, &index);
		//for (size_t i = 0; i < 8; i++)
	{
        //printf("input = %f \n", f32input1[i]);
		printf("mips_max_f32 output = %f \n", f32output1);
        printf("index = %d \n", index);
	}
    printf("mips_max_f32 finish \n");
		printf("mips_max_f32 output = %f \n", f32output1);
        printf("index = %d \n", index);
	printf("mips_max_f32 checking \n\n");
    eq_check_special_f32(&f32refmax[1], &f32output1, 1);
    eq_check_special_q15(&u16maxindex[1], &index, 1);
	printf("\n== mips_max_f32 check done  == \n\n");

//=======11
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile1, &paramCountInput1, f32input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f32(inputFile1, paramCountInput1, f32input1);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

    mips_max_f32(f32input1, 11, &f32output1, &index);
    printf("mips_max_f32 finish \n");
		printf("mips_max_f32 output = %f \n", f32output1);
        printf("index = %d \n", index);
	printf("mips_max_f32 checking \n\n");
    eq_check_special_f32(&f32refmax[2], &f32output1, 1);
    eq_check_special_q15(&u16maxindex[2], &index, 1);

	printf("\n== mips_max_f32 check done  == \n\n");


// =====================absmax

    float f32refabsmax[MAX_SIZE] = {0};
    uint16_t u16absmaxindex[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, StatsF32, "InputNew1_f32.txt");
#else
	inputFile2 = StatsF32_InputNew1_f32;
	inputFile2Len = sizeof(StatsF32_InputNew1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "AbsMaxVals26_f32.txt");
#else
	referenceFile = StatsF32_AbsMaxVals26_f32;
	referenceFileLen = sizeof(StatsF32_AbsMaxVals26_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsF32, "AbsMaxIndexes26_s16.txt");
#else
	indexvalFile = StatsF32_AbsMaxIndexes26_s16;
	indexvalFileLen = sizeof(StatsF32_AbsMaxIndexes26_s16);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile2, &paramCountInput2, f32input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_f32(inputFile2, paramCountInput2, f32input2);
	paramCountInput2 = paramCountInput2/sizeof(f32);
#endif


	printf("== mips_absmax_f32 test ==  \n");
    mips_absmax_f32(f32input2, 3, &f32output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %f \n", f32input1[i]);
		printf("mips_absmax_f32 output = %f \n", f32output1);
        printf("index = %d \n", index);
	}
    printf("mips_absmax_f32 finish \n");

	printf("mips_absmax_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFile, &paramCountInput1, f32refabsmax);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f32(referenceFile, paramCountInput1, f32refabsmax);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(indexvalFile, &paramCountInput1, u16absmaxindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u16(indexvalFile, paramCountInput1, u16absmaxindex);
	paramCountInput1 = paramCountInput1/sizeof(uint16_t);
#endif

    eq_check_special_f32(&f32refabsmax[0], &f32output1, 1);
    eq_check_special_q15(&u16absmaxindex[0], &index, 1);
	printf("\n== mips_absmax_f32 check done  == \n\n");


//=======8

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile2, &paramCountInput2, f32input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_f32(inputFile2, paramCountInput2, f32input2);
	paramCountInput2 = paramCountInput2/sizeof(f32);
#endif

	printf("== mips_absmax_f32 test ==  \n");
    mips_absmax_f32(f32input2, 8, &f32output1, &index);
	//for (size_t i = 0; i < 8; i++)
	{
       // printf("input = %f \n", f32input1[i]);
		printf("mips_absmax_f32 output = %f \n", f32output1);
        printf("index = %d \n", index);

	}
    printf("mips_absmax_f32 finish \n");

	printf("mips_absmax_f32 checking \n\n");

    eq_check_special_f32(&f32refabsmax[1], &f32output1, 1);
    eq_check_special_q15(&u16absmaxindex[1], &index, 1);
	printf("\n== mips_absmax_f32 check done  == \n\n");


//=======11
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile2, &paramCountInput2, f32input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_f32(inputFile2, paramCountInput2, f32input2);
	paramCountInput2 = paramCountInput2/sizeof(f32);
#endif

	printf("== mips_absmax_f32 test ==  \n");
    mips_absmax_f32(f32input2, 11, &f32output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %f \n", f32input1[i]);
		printf("mips_absmax_f32 output = %f \n", f32output1);
        printf("index = %d \n", index);

	}
    printf("mips_absmax_f32 finish \n");

	printf("mips_absmax_f32 checking \n\n");

    eq_check_special_f32(&f32refabsmax[2], &f32output1, 1);
    eq_check_special_q15(&u16absmaxindex[2], &index, 1);
	printf("\n== mips_absmax_f32 check done  == \n\n");

// =====================max_no_idx

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "MaxVals1_f32.txt");
#else
	referenceFile = StatsF32_MaxVals1_f32;
	referenceFileLen = sizeof(StatsF32_MaxVals1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif

	printf("== mips_max_no_idx_f32 test ==  \n");
    mips_max_no_idx_f32(f32input1, 3, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_max_no_idx_f32 output = %f \n", f32output1);
	}
    printf("mips_max_no_idx_f32 finish \n");
	printf("mips_max_no_idx_f32 checking \n\n");

    eq_check_special_f32(&f32refmax[0], &f32output1, 1);

	printf("\n== mips_max_no_idx_f32 check done  == \n\n");

// ===================8

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "MaxVals1_f32.txt");
#else
	referenceFile = StatsF32_MaxVals1_f32;
	referenceFileLen = sizeof(StatsF32_MaxVals1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif

	printf("== mips_max_no_idx_f32 test ==  \n");
    mips_max_no_idx_f32(f32input1, 8, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_max_no_idx_f32 output = %f \n", f32output1);
	}
    printf("mips_max_no_idx_f32 finish \n");
	printf("mips_max_no_idx_f32 checking \n\n");

    eq_check_special_f32(&f32refmax[1], &f32output1, 1);
	
	printf("\n== mips_max_no_idx_f32 check done  == \n\n");

// ===================11

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "MaxVals1_f32.txt");
#else
	referenceFile = StatsF32_MaxVals1_f32;
	referenceFileLen = sizeof(StatsF32_MaxVals1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif

	printf("== mips_max_no_idx_f32 test ==  \n");
    mips_max_no_idx_f32(f32input1, 11, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_max_no_idx_f32 output = %f \n", f32output1);
	}
    printf("mips_max_no_idx_f32 finish \n");
	printf("mips_max_no_idx_f32 checking \n\n");

    eq_check_special_f32(&f32refmax[2], &f32output1, 1);
	
	printf("\n== mips_max_no_idx_f32 check done  == \n\n");

//=====================abs_no_idx


	printf("== mips_absmax_no_idx_f32 test ==  \n");
    mips_absmax_no_idx_f32(f32input2, 3, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_absmax_no_idx_f32 output = %f \n", f32output1);
	}
    printf("mips_absmax_no_idx_f32 finish \n");
	printf("mips_absmax_no_idx_f32 checking \n\n");

    eq_check_special_f32(&f32refabsmax[0], &f32output1, 1);
	printf("\n== mips_absmax_no_idx_f32 check done  == \n\n");
    
//==============8

	printf("== mips_absmax_no_idx_f32 test ==  \n");
    mips_absmax_no_idx_f32(f32input2, 8, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_absmax_no_idx_f32 output = %f \n", f32output1);
	}
    printf("mips_absmax_no_idx_f32 finish \n");
	printf("mips_absmax_no_idx_f32 checking \n\n");

    eq_check_special_f32(&f32refabsmax[1], &f32output1, 1);
	printf("\n== mips_absmax_no_idx_f32 check done  == \n\n");


//==============11

	printf("== mips_absmax_no_idx_f32 test ==  \n");
    mips_absmax_no_idx_f32(f32input2, 11, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_absmax_no_idx_f32 output = %f \n", f32output1);
	}
    printf("mips_absmax_no_idx_f32 finish \n");
	printf("mips_absmax_no_idx_f32 checking \n\n");

    eq_check_special_f32(&f32refabsmax[2], &f32output1, 1);
	printf("\n== mips_absmax_no_idx_f32 check done  == \n\n");

//=====================min_no_idx

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "MinVals3_f32.txt");
#else
	referenceFile = StatsF32_MinVals3_f32;
	referenceFileLen = sizeof(StatsF32_MinVals3_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFile, &paramCountInput1, f32refmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f32(referenceFile, paramCountInput1, f32refmin);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

	printf("== mips_min_no_idx_f32 test ==  \n");
    mips_min_no_idx_f32(f32input1, 3, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_min_no_idx_f32 output = %f \n", f32output1);
	}
    printf("mips_min_no_idx_f32 finish \n");
	printf("mips_min_no_idx_f32 checking \n\n");

    eq_check_special_f32(&f32refmin[0], &f32output1, 1);
	printf("\n== mips_min_no_idx_f32 check done  == \n\n");

//=========8

	printf("== mips_min_no_idx_f32 test ==  \n");
    mips_min_no_idx_f32(f32input1, 8, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_min_no_idx_f32 output = %f \n", f32output1);
	}
    printf("mips_min_no_idx_f32 finish \n");
	printf("mips_min_no_idx_f32 checking \n\n");

    eq_check_special_f32(&f32refmin[1], &f32output1, 1);
	printf("\n== mips_min_no_idx_f32 check done  == \n\n");

//=========11

	printf("== mips_min_no_idx_f32 test ==  \n");
    mips_min_no_idx_f32(f32input1, 11, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_min_no_idx_f32 output = %f \n", f32output1);
	}
    printf("mips_min_no_idx_f32 finish \n");
	printf("mips_min_no_idx_f32 checking \n\n");

    eq_check_special_f32(&f32refmin[2], &f32output1, 1);
	printf("\n== mips_min_no_idx_f32 check done  == \n\n");


//=====================absmin_no_idx
    float f32refabsmin[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "AbsMinVals27_f32.txt");
#else
	referenceFile = StatsF32_AbsMinVals27_f32;
	referenceFileLen = sizeof(StatsF32_AbsMinVals27_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFile, &paramCountInput1, f32refabsmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f32(referenceFile, paramCountInput1, f32refabsmin);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

	printf("== mips_absmin_no_idx_f32 test ==  \n");
    mips_absmin_no_idx_f32(f32input2, 3, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_absmin_no_idx_f32 output = %f \n", f32output1);
	}
    printf("mips_absmin_no_idx_f32 finish \n");
	printf("mips_absmin_no_idx_f32 checking \n\n");

    eq_check_special_f32(&f32refabsmin[0], &f32output1, 1);

	printf("\n== mips_absmin_no_idx_f32 check done  == \n\n");

//=================8


	printf("== mips_absmin_no_idx_f32 test ==  \n");
    mips_absmin_no_idx_f32(f32input2, 8, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_absmin_no_idx_f32 output = %f \n", f32output1);
	}
    printf("mips_absmin_no_idx_f32 finish \n");
	printf("mips_absmin_no_idx_f32 checking \n\n");

    eq_check_special_f32(&f32refabsmin[1], &f32output1, 1);
	
	printf("\n== mips_absmin_no_idx_f32 check done  == \n\n");

//=================11


	printf("== mips_absmin_no_idx_f32 test ==  \n");
    mips_absmin_no_idx_f32(f32input2, 11, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_absmin_no_idx_f32 output = %f \n", f32output1);
	}
    printf("mips_absmin_no_idx_f32 finish \n");
	printf("mips_absmin_no_idx_f32 checking \n\n");

    eq_check_special_f32(&f32refabsmin[2], &f32output1, 1);
	
	printf("\n== mips_absmin_no_idx_f32 check done  == \n\n");

//=====================min_no_idx

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "MinVals3_f32.txt");
#else
	referenceFile = StatsF32_MinVals3_f32;
	referenceFileLen = sizeof(StatsF32_MinVals3_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsF32, "MinIndexes3_s16.txt");
#else
	indexvalFile = StatsF32_MinIndexes3_s16;
	indexvalFileLen = sizeof(StatsF32_MinIndexes3_s16);
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
	load_data_f32(referenceFile, &paramCountInput1, f32refmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f32(referenceFile, paramCountInput1, f32refmin);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

	printf("== mips_min_f32 test ==  \n");
    mips_min_f32(f32input1, 3, &f32output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_min_f32 output = %f \n", f32output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_f32 finish \n");
	printf("mips_min_f32 checking \n\n");

    eq_check_special_f32(&f32refmin[0], &f32output1, 1);
	eq_check_special_q15(&u16minindex[0], &index, 1);
	printf("\n== mips_min_f32 check done  == \n\n");

//===============8

	printf("== mips_min_f32 test ==  \n");
    mips_min_f32(f32input1, 8, &f32output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_min_f32 output = %f \n", f32output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_f32 finish \n");
	printf("mips_min_f32 checking \n\n");

    eq_check_special_f32(&f32refmin[1], &f32output1, 1);
	eq_check_special_q15(&u16minindex[1], &index, 1);
	printf("\n== mips_min_f32 check done  == \n\n");

//===============11

	printf("== mips_min_f32 test ==  \n");
    mips_min_f32(f32input1, 11, &f32output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_min_f32 output = %f \n", f32output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_f32 finish \n");
	printf("mips_min_f32 checking \n\n");

    eq_check_special_f32(&f32refmin[2], &f32output1, 1);
	eq_check_special_q15(&u16minindex[2], &index, 1);
	printf("\n== mips_min_f32 check done  == \n\n");

//=====================absmin

    uint16_t u16absminindex[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsF32, "AbsMinIndexes27_s16.txt");
#else
	indexvalFile = StatsF32_AbsMinIndexes27_s16;
	indexvalFileLen = sizeof(StatsF32_AbsMinIndexes27_s16);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(indexvalFile, &paramCountInput1, u16absminindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u16(indexvalFile, paramCountInput1, u16absminindex);
	paramCountInput1 = paramCountInput1/sizeof(uint16_t);
#endif

	printf("== mips_absmin_f32 test ==  \n");
    mips_absmin_f32(f32input2, 3, &f32output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_absmin_f32 output = %f \n", f32output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_f32 finish \n");
	printf("mips_absmin_f32 checking \n\n");

    eq_check_special_f32(&f32refabsmin[0], &f32output1, 1);
	eq_check_special_q15(&u16absminindex[0], &index, 1);

	printf("\n== mips_absmin_f32 check done  == \n\n");

//===============8

	printf("== mips_absmin_f32 test ==  \n");
    mips_absmin_f32(f32input2, 8, &f32output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_absmin_f32 output = %f \n", f32output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_f32 finish \n");
	printf("mips_absmin_f32 checking \n\n");

    eq_check_special_f32(&f32refabsmin[1], &f32output1, 1);
	eq_check_special_q15(&u16absminindex[1], &index, 1);

	printf("\n== mips_absmin_f32 check done  == \n\n");


//===============11

	printf("== mips_absmin_f32 test ==  \n");
    mips_absmin_f32(f32input2, 11, &f32output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_absmin_f32 output = %f \n", f32output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_f32 finish \n");
	printf("mips_absmin_f32 checking \n\n");

    eq_check_special_f32(&f32refabsmin[2], &f32output1, 1);
	eq_check_special_q15(&u16absminindex[2], &index, 1);

	printf("\n== mips_absmin_f32 check done  == \n\n");

//===========================mean_f32

    float f32input3[MAX_SIZE] = {0};
	float f32mean[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, StatsF32, "Input2_f32.txt");
#else
	inputFile3 = StatsF32_Input2_f32;
	inputFile3Len = sizeof(StatsF32_Input2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "MeanVals2_f32.txt");
#else
	referenceFile = StatsF32_MeanVals2_f32;
	referenceFileLen = sizeof(StatsF32_MeanVals2_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile3, &paramCountInput3, f32input3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_f32(inputFile3, paramCountInput3, f32input3);
	paramCountInput3 = paramCountInput3/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFile, &paramCountInput1, f32mean);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f32(referenceFile, paramCountInput1, f32mean);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

	printf("== mips_mean_f32 test ==  \n");
    mips_mean_f32(f32input3, 3, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_mean_f32 output = %f \n", f32output1);

	}
    printf("mips_mean_f32 finish \n");
	printf("mips_mean_f32 checking \n\n");

    snr_check_special_f32(&f32mean[0], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32mean[0], &f32output1, 1, REL_ERROR);
	
	printf("\n== mips_mean_f32 check done  == \n\n");

//===========8

	printf("== mips_mean_f32 test ==  \n");
    mips_mean_f32(f32input3, 8, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_mean_f32 output = %f \n", f32output1);

	}
    printf("mips_mean_f32 finish \n");
	printf("mips_mean_f32 checking \n\n");

    snr_check_special_f32(&f32mean[1], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32mean[1], &f32output1, 1, REL_ERROR);

	printf("\n== mips_mean_f32 check done  == \n\n");

//===========11

	printf("== mips_mean_f32 test ==  \n");
    mips_mean_f32(f32input3, 11, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_mean_f32 output = %f \n", f32output1);

	}
    printf("mips_mean_f32 finish \n");
	printf("mips_mean_f32 checking \n\n");

    snr_check_special_f32(&f32mean[2], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32mean[2], &f32output1, 1, REL_ERROR);

	printf("\n== mips_mean_f32 check done  == \n\n");

//===========================power_f32

	float f32power[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "PowerVals4_f32.txt");
#else
	referenceFile = StatsF32_PowerVals4_f32;
	referenceFileLen = sizeof(StatsF32_PowerVals4_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFile, &paramCountInput1, f32power);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f32(referenceFile, paramCountInput1, f32power);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

	printf("== mips_power_f32 test ==  \n");
    mips_power_f32(f32input1, 3, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_power_f32 output = %f \n", f32output1);

	}
    printf("mips_power_f32 finish \n");
	printf("mips_power_f32 checking \n\n");

    snr_check_special_f32(&f32power[0], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32power[0], &f32output1, 1, REL_ERROR);
	
	printf("\n== mips_power_f32 check done  == \n\n");

//=============8

	printf("== mips_power_f32 test ==  \n");
    mips_power_f32(f32input1, 8, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_power_f32 output = %f \n", f32output1);

	}
    printf("mips_power_f32 finish \n");
	printf("mips_power_f32 checking \n\n");

    snr_check_special_f32(&f32power[1], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32power[1], &f32output1, 1, REL_ERROR);
	
	printf("\n== mips_power_f32 check done  == \n\n");

//=============11

	printf("== mips_power_f32 test ==  \n");
    mips_power_f32(f32input1, 11, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_power_f32 output = %f \n", f32output1);

	}
    printf("mips_power_f32 finish \n");
	printf("mips_power_f32 checking \n\n");

    snr_check_special_f32(&f32power[2], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32power[2], &f32output1, 1, REL_ERROR);
	
	printf("\n== mips_power_f32 check done  == \n\n");



//===========================rms_f32

	float f32rms[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "RmsVals5_f32.txt");
#else
	referenceFile = StatsF32_RmsVals5_f32;
	referenceFileLen = sizeof(StatsF32_RmsVals5_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFile, &paramCountInput1, f32rms);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f32(referenceFile, paramCountInput1, f32rms);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

	printf("== mips_rms_f32 test ==  \n");
    mips_rms_f32(f32input1, 3, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_rms_f32 output = %f \n", f32output1);

	}
    printf("mips_rms_f32 finish \n");
	printf("mips_rms_f32 checking \n\n");

    snr_check_special_f32(&f32rms[0], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32rms[0], &f32output1, 1, REL_ERROR);
	
	printf("\n== mips_rms_f32 check done  == \n\n");

//=============8

	printf("== mips_rms_f32 test ==  \n");
    mips_rms_f32(f32input1, 8, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_rms_f32 output = %f \n", f32output1);

	}
    printf("mips_rms_f32 finish \n");
	printf("mips_rms_f32 checking \n\n");

    snr_check_special_f32(&f32rms[1], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32rms[1], &f32output1, 1, REL_ERROR);
	
	printf("\n== mips_rms_f32 check done  == \n\n");

//=============11

	printf("== mips_rms_f32 test ==  \n");
    mips_rms_f32(f32input1, 11, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_rms_f32 output = %f \n", f32output1);

	}
    printf("mips_rms_f32 finish \n");
	printf("mips_rms_f32 checking \n\n");

    snr_check_special_f32(&f32rms[2], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32rms[2], &f32output1, 1, REL_ERROR);
	
	printf("\n== mips_rms_f32 check done  == \n\n");


//===========================std_f32

	float f32std[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "StdVals6_f32.txt");
#else
	referenceFile = StatsF32_StdVals6_f32;
	referenceFileLen = sizeof(StatsF32_StdVals6_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFile, &paramCountInput1, f32std);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f32(referenceFile, paramCountInput1, f32std);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

	printf("== mips_std_f32 test ==  \n");
    mips_std_f32(f32input1, 3, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_std_f32 output = %f \n", f32output1);

	}
    printf("mips_std_f32 finish \n");
	printf("mips_std_f32 checking \n\n");

    snr_check_special_f32(&f32std[0], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32std[0], &f32output1, 1, REL_ERROR);
	
	printf("\n== mips_std_f32 check done  == \n\n");

//============8

	printf("== mips_std_f32 test ==  \n");
    mips_std_f32(f32input1, 8, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_std_f32 output = %f \n", f32output1);

	}
    printf("mips_std_f32 finish \n");
	printf("mips_std_f32 checking \n\n");

    snr_check_special_f32(&f32std[1], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32std[1], &f32output1, 1, REL_ERROR);
	
	printf("\n== mips_std_f32 check done  == \n\n");
	
//============11

	printf("== mips_std_f32 test ==  \n");
    mips_std_f32(f32input1, 11, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_std_f32 output = %f \n", f32output1);

	}
    printf("mips_std_f32 finish \n");
	printf("mips_std_f32 checking \n\n");

    snr_check_special_f32(&f32std[2], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32std[2], &f32output1, 1, REL_ERROR);
	
	printf("\n== mips_std_f32 check done  == \n\n");


//===========================var_f32

	float f32var[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "VarVals7_f32.txt");
#else
	referenceFile = StatsF32_VarVals7_f32;
	referenceFileLen = sizeof(StatsF32_VarVals7_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFile, &paramCountInput1, f32var);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f32(referenceFile, paramCountInput1, f32var);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

	printf("== mips_var_f32 test ==  \n");
    mips_var_f32(f32input1, 3, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_var_f32 output = %f \n", f32output1);

	}
    printf("mips_var_f32 finish \n");
	printf("mips_var_f32 checking \n\n");

    snr_check_special_f32(&f32var[0], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32var[0], &f32output1, 1, REL_ERROR);
	
	printf("\n== mips_var_f32 check done  == \n\n");


//===========8

	printf("== mips_var_f32 test ==  \n");
    mips_var_f32(f32input1, 8, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_var_f32 output = %f \n", f32output1);

	}
    printf("mips_var_f32 finish \n");
	printf("mips_var_f32 checking \n\n");

    snr_check_special_f32(&f32var[1], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32var[1], &f32output1, 1, REL_ERROR);
	
	printf("\n== mips_var_f32 check done  == \n\n");


//===========11

	printf("== mips_var_f32 test ==  \n");
    mips_var_f32(f32input1, 11, &f32output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_var_f32 output = %f \n", f32output1);

	}
    printf("mips_var_f32 finish \n");
	printf("mips_var_f32 checking \n\n");

    snr_check_special_f32(&f32var[2], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32var[2], &f32output1, 1, REL_ERROR);
	
	printf("\n== mips_var_f32 check done  == \n\n");

//===========================entropy_f32
	int paramCountInput4 = 0;
	int paramCountInput5 = 0;
	float f32entropy[MAX_SIZE] = {0};
	float f32input4[MAX_SIZE] = {0};
	float f32output2[MAX_SIZE] = {0};
	q15 q15input1[MAX_SIZE] = {0};
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
	snprintf(inputFile4, sizeof(inputFile4), "%s%s%s", Patterns_PATH, StatsF32, "Input22_f32.txt");
#else
	inputFile4 = StatsF32_Input22_f32;
	inputFile4Len = sizeof(StatsF32_Input22_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile5, sizeof(inputFile5), "%s%s%s", Patterns_PATH, StatsF32, "Dims22_s16.txt");
#else
	inputFile5 = StatsF32_Dims22_s16;
	inputFile5Len = sizeof(StatsF32_Dims22_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "RefEntropy22_f32.txt");
#else
	referenceFile = StatsF32_RefEntropy22_f32;
	referenceFileLen = sizeof(StatsF32_RefEntropy22_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile4, &paramCountInput4, f32input4);
#else
	paramCountInput4 = inputFile4Len;
	load_data_f32(inputFile4, paramCountInput4, f32input4);
	paramCountInput4 = paramCountInput4/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile5, &paramCountInput5, q15input1);
#else
	paramCountInput5 = inputFile5Len;
	load_data_q15(inputFile5, paramCountInput5, q15input1);
	paramCountInput5 = paramCountInput5/sizeof(q15);
#endif

	printf("== mips_entropy_f32 test ==  \n");

	f32 *inp = f32input4;

	int16_t *dimsp = q15input1;

	f32 *outp = f32output2;
      for(int i=0;i < 0x000A; i++)
      {
         *outp = mips_entropy_f32(inp,dimsp[i+1]);
         outp++;
          inp += dimsp[i+1];
      }


	for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_entropy_f32 output = %f \n", f32output2[j]);

	}
    printf("mips_entropy_f32 finish \n");
	printf("mips_entropy_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output2, 1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output2, 1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output2, 1, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output2, 1, REL_ERROR);
#endif

	
	printf("\n== mips_entropy_f32 check done  == \n\n");



//===========================logsum_f32

	int paramCountInput6 = 0;
	int paramCountInput7 = 0;
	float f32input6[MAX_SIZE] = {0};


#if defined(NOT_EMBEDDED)
	char inputFile6[255] = {0};
#else
	void *inputFile6;
	int inputFile6Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile7[255] = {0};
#else
	void *inputFile7;
	int inputFile7Len = 0;
#endif

	

#if defined(NOT_EMBEDDED)
	snprintf(inputFile6, sizeof(inputFile6), "%s%s%s", Patterns_PATH, StatsF32, "Input23_f32.txt");
#else
	inputFile6 = StatsF32_Input23_f32;
	inputFile6Len = sizeof(StatsF32_Input23_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile7, sizeof(inputFile7), "%s%s%s", Patterns_PATH, StatsF32, "Dims23_s16.txt");
#else
	inputFile7 = StatsF32_Dims23_s16;
	inputFile7Len = sizeof(StatsF32_Dims23_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "RefLogSumExp23_f32.txt");
#else
	referenceFile = StatsF32_RefLogSumExp23_f32;
	referenceFileLen = sizeof(StatsF32_RefLogSumExp23_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile6, &paramCountInput4, f32input6);
#else
	paramCountInput4 = inputFile6Len;
	load_data_f32(inputFile6, paramCountInput4, f32input6);
	paramCountInput4 = paramCountInput4/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile7, &paramCountInput7, q15input1);
#else
	paramCountInput7 = inputFile7Len;
	load_data_q15(inputFile7, paramCountInput7, q15input1);
	paramCountInput7 = paramCountInput7/sizeof(q15);
#endif

	printf("== mips_logsumexp_f32 test ==  \n");

	inp = f32input6;
	dimsp = q15input1;

	outp = f32output2;
	for(int i=0;i < dimsp[0]; i++)
      {
         *outp = mips_logsumexp_f32(inp,dimsp[i+1]);
         outp++;
         inp += dimsp[i+1];
      }
		for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_logsumexp_f32 output = %f \n", f32output2[j]);

	}
    printf("mips_logsumexp_f32 finish \n");
	printf("mips_logsumexp_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output2, 1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output2, 1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output2, 1, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output2, 1, REL_ERROR);
#endif


	printf("\n== mips_logsumexp_f32 check done  == \n\n");


//===========================kulback_f32

	int paramCountInputA = 0;
	int paramCountInputB = 0;
	int paramCountInput10 = 0;
	float f32inputa[MAX_SIZE] = {0};
	float f32inputb[MAX_SIZE] = {0};


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

#if defined(NOT_EMBEDDED)
	char inputFile10[255] = {0};
#else
	void *inputFile10;
	int inputFile10Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFilea, sizeof(inputFilea), "%s%s%s", Patterns_PATH, StatsF32, "InputA24_f32.txt");
#else
	inputFilea = StatsF32_InputA24_f32;
	inputFileaLen = sizeof(StatsF32_InputA24_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb, sizeof(inputFileb), "%s%s%s", Patterns_PATH, StatsF32, "InputB24_f32.txt");
#else
	inputFileb = StatsF32_InputB24_f32;
	inputFilebLen = sizeof(StatsF32_InputB24_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile10, sizeof(inputFile10), "%s%s%s", Patterns_PATH, StatsF32, "Dims24_s16.txt");
#else
	inputFile10 = StatsF32_Dims24_s16;
	inputFile10Len = sizeof(StatsF32_Dims24_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "RefKL24_f32.txt");
#else
	referenceFile = StatsF32_RefKL24_f32;
	referenceFileLen = sizeof(StatsF32_RefKL24_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFilea, &paramCountInputA, f32inputa);
#else
	paramCountInputA = inputFileaLen;
	load_data_f32(inputFilea, paramCountInputA, f32inputa);
	paramCountInputA = paramCountInputA/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileb, &paramCountInputB, f32inputb);
#else
	paramCountInputB = inputFilebLen;
	load_data_f32(inputFileb, paramCountInputB, f32inputb);
	paramCountInputB = paramCountInputB/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile10, &paramCountInput10, q15input1);
#else
	paramCountInput10 = inputFile10Len;
	load_data_q15(inputFile10, paramCountInput10, q15input1);
	paramCountInput10 = paramCountInput10/sizeof(q15);
#endif

	printf("== mips_kullback_leibler_f32 test ==  \n");

	f32 *inpA = f32inputa;
	f32 *inpB = f32inputb;
	dimsp = q15input1;

	outp = f32output2;
	for(int i=0;i < dimsp[0]; i++)
      {
         *outp = mips_kullback_leibler_f32(inpA,inpB,dimsp[i+1]);
         outp++;
         inpA += dimsp[i+1];
         inpB += dimsp[i+1];
      }

		for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_kullback_leibler_f32 output = %f \n", f32output2[j]);

	}
    printf("mips_kullback_leibler_f32 finish \n");
	printf("mips_kullback_leibler_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output2, 1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output2, 1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output2, 1, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output2, 1, REL_ERROR);
#endif


	printf("\n== mips_kullback_leibler_f32 check done  == \n\n");


//===========================logsumexp_dot

	float f32tmp[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea, sizeof(inputFilea), "%s%s%s", Patterns_PATH, StatsF32, "InputA25_f32.txt");
#else
	inputFilea = StatsF32_InputA25_f32;
	inputFileaLen = sizeof(StatsF32_InputA25_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb, sizeof(inputFileb), "%s%s%s", Patterns_PATH, StatsF32, "InputB25_f32.txt");
#else
	inputFileb = StatsF32_InputB25_f32;
	inputFilebLen = sizeof(StatsF32_InputB25_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile10, sizeof(inputFile10), "%s%s%s", Patterns_PATH, StatsF32, "Dims25_s16.txt");
#else
	inputFile10 = StatsF32_Dims25_s16;
	inputFile10Len = sizeof(StatsF32_Dims25_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "RefLogSumExpDot25_f32.txt");
#else
	referenceFile = StatsF32_RefLogSumExpDot25_f32;
	referenceFileLen = sizeof(StatsF32_RefLogSumExpDot25_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(inputFilea, &paramCountInputA, f32inputa);
#else
	paramCountInputA = inputFileaLen;
	load_data_f32(inputFilea, paramCountInputA, f32inputa);
	paramCountInputA = paramCountInputA/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileb, &paramCountInputB, f32inputb);
#else
	paramCountInputB = inputFilebLen;
	load_data_f32(inputFileb, paramCountInputB, f32inputb);
	paramCountInputB = paramCountInputB/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile10, &paramCountInput10, q15input1);
#else
	paramCountInput10 = inputFile10Len;
	load_data_q15(inputFile10, paramCountInput10, q15input1);
	paramCountInput10 = paramCountInput10/sizeof(q15);
#endif

	printf("== mips_logsumexp_dot_prod_f32 test ==  \n");

	inpA = f32inputa;
	inpB = f32inputb;
	dimsp = q15input1;
	f32 *tmpp = f32tmp;
	outp = f32output2;
	
	for(int i=0;i < dimsp[0]; i++)
      {
         *outp = mips_logsumexp_dot_prod_f32(inpA,inpB,dimsp[i+1],tmpp);
         outp++;
         inpA += dimsp[i+1];
         inpB += dimsp[i+1];
      }

		for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_logsumexp_dot_prod_f32 output = %f \n", f32output2[j]);

	}
    printf("mips_logsumexp_dot_prod_f32 finish \n");
	printf("mips_logsumexp_dot_prod_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output2, 1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output2, 1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output2, 1, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output2, 1, REL_ERROR);
#endif


	printf("\n== mips_logsumexp_dot_prod_f32 check done  == \n\n");

//===========================mse_f32

	float f32mse[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea, sizeof(inputFilea), "%s%s%s", Patterns_PATH, StatsF32, "InputNew1_f32.txt");
#else
	inputFilea = StatsF32_InputNew1_f32;
	inputFileaLen = sizeof(StatsF32_InputNew1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb, sizeof(inputFileb), "%s%s%s", Patterns_PATH, StatsF32, "InputNew2_f32.txt");
#else
	inputFileb = StatsF32_InputNew2_f32;
	inputFilebLen = sizeof(StatsF32_InputNew2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "MSEVals28_f32.txt");
#else
	referenceFile = StatsF32_MSEVals28_f32;
	referenceFileLen = sizeof(StatsF32_MSEVals28_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(inputFilea, &paramCountInputA, f32inputa);
#else
	paramCountInputA = inputFileaLen;
	load_data_f32(inputFilea, paramCountInputA, f32inputa);
	paramCountInputA = paramCountInputA/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileb, &paramCountInputB, f32inputb);
#else
	paramCountInputB = inputFilebLen;
	load_data_f32(inputFileb, paramCountInputB, f32inputb);
	paramCountInputB = paramCountInputB/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(referenceFile, &paramCountInput1, f32mse);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f32(referenceFile, paramCountInput1, f32mse);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif
	printf("== mips_mse_f32 test ==  \n");


    mips_mse_f32(f32inputa,f32inputb,3,&f32output1);
		//for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_mse_f32 output = %f \n", f32output1);

	}
    printf("mips_mse_f32 finish \n");
	printf("mips_mse_f32 checking \n\n");

    snr_check_special_f32(&f32mse[0], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32mse[0], &f32output1, 1, REL_ERROR);

	printf("\n== mips_mse_f32 check done  == \n\n");

//=============mse 100
	printf("== mips_mse_f32 test ==  \n");


    mips_mse_f32(f32inputa,f32inputb,100,&f32output1);
		//for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_mse_f32 output = %f \n", f32output1);

	}
    printf("mips_mse_f32 finish \n");
	printf("mips_mse_f32 checking \n\n");

    snr_check_special_f32(&f32mse[3], &f32output1, 1, SNR_THRESHOLD);
	rel_check_special_f32(&f32mse[3], &f32output1, 1, REL_ERROR);

	printf("\n== mips_mse_f32 check done  == \n\n");

//===========================accumulate

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea, sizeof(inputFilea), "%s%s%s", Patterns_PATH, StatsF32, "InputAccumulate1_f32.txt");
#else
	inputFilea = StatsF32_InputAccumulate1_f32;
	inputFileaLen = sizeof(StatsF32_InputAccumulate1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile10, sizeof(inputFile10), "%s%s%s", Patterns_PATH, StatsF32, "InputAccumulateConfig1_s16.txt");
#else
	inputFile10 = StatsF32_InputAccumulateConfig1_s16;
	inputFile10Len = sizeof(StatsF32_InputAccumulateConfig1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF32, "RefAccumulate1_f32.txt");
#else
	referenceFile = StatsF32_RefAccumulate1_f32;
	referenceFileLen = sizeof(StatsF32_RefAccumulate1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(inputFilea, &paramCountInputA, f32inputa);
#else
	paramCountInputA = inputFileaLen;
	load_data_f32(inputFilea, paramCountInputA, f32inputa);
	paramCountInputA = paramCountInputA/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile10, &paramCountInput10, q15input1);
#else
	paramCountInput10 = inputFile10Len;
	load_data_q15(inputFile10, paramCountInput10, q15input1);
	paramCountInput10 = paramCountInput10/sizeof(q15);
#endif

	printf("== mips_accumulate_f32 test ==  \n");

	inp = f32inputa;
	dimsp = q15input1;
	outp = f32output2;
	
	for(int i=0;i < dimsp[0]; i++)
      {
         mips_accumulate_f32(inp,dimsp[i+1],outp);
         outp++;
      }

		for (size_t j = 0; j < 4; j++)
	{
     //   printf("input = %f \n", f32input1[i]);
		printf("mips_accumulate_f32 output = %f \n", f32output2[j]);

	}
    printf("mips_accumulate_f32 finish \n");
	printf("mips_accumulate_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output2, 1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output2, 1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output2, 1, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output2, 1, REL_ERROR);
#endif


	printf("\n== mips_accumulate_f32 check done  == \n\n");


	return 0 ;
}
