#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/basic_math_functions.h"
#include "dsp/statistics_functions.h"
#define SNR_THRESHOLD 300
#define REL_ERROR (4.0e-15)
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

	double f64input1[MAX_SIZE] = {0};
	double f64input2[MAX_SIZE] = {0};

    double f64refmax[MAX_SIZE] = {0};
	double f64refmin[MAX_SIZE] = {0};

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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, StatsF64, "Input1_f64.txt");
#else
	inputFile1 = StatsF64_Input1_f64;
	inputFile1Len = sizeof(StatsF64_Input1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "MaxVals1_f64.txt");
#else
	referenceFile = StatsF64_MaxVals1_f64;
	referenceFileLen = sizeof(StatsF64_MaxVals1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsF64, "MaxIndexes1_s16.txt");
#else
	indexvalFile = StatsF64_MaxIndexes1_s16;
	indexvalFileLen = sizeof(StatsF64_MaxIndexes1_s16);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile1, &paramCountInput1, f64input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f64(inputFile1, paramCountInput1, f64input1);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

	double f64output1;
    uint16_t u16maxindex[MAX_SIZE] = {0};
    uint32_t index;
//===========max
	printf("== mips_max_f64 test ==  \n");
    mips_max_f64(f64input1, 2, &f64output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %f \n", f64input1[i]);
		printf("mips_max_f64 output = %f \n", f64output1);
        printf("index = %d \n", index);
	}
    printf("mips_max_f64 finish \n");
	printf("mips_max_f64 checking \n\n");


#if defined(NOT_EMBEDDED)
	load_data_f64(referenceFile, &paramCountInput1, f64refmax);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f64(referenceFile, paramCountInput1, f64refmax);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(indexvalFile, &paramCountInput1, u16maxindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u16(indexvalFile, paramCountInput1, u16maxindex);
	paramCountInput1 = paramCountInput1/sizeof(uint16_t);
#endif

    eq_check_special_f64(&f64refmax[0], &f64output1, 1);
    eq_check_special_q15(&u16maxindex[0], &index, 1);
	printf("\n== mips_max_f64 check done  == \n\n");

//=========4
    mips_max_f64(f64input1, 4, &f64output1, &index);
		//for (size_t i = 0; i < 8; i++)
	{
        //printf("input = %f \n", f64input1[i]);
		printf("mips_max_f64 output = %f \n", f64output1);
        printf("index = %d \n", index);
	}
    printf("mips_max_f64 finish \n");
		printf("mips_max_f64 output = %f \n", f64output1);
        printf("index = %d \n", index);
	printf("mips_max_f64 checking \n\n");
    eq_check_special_f64(&f64refmax[1], &f64output1, 1);
    eq_check_special_q15(&u16maxindex[1], &index, 1);
	printf("\n== mips_max_f64 check done  == \n\n");

//=======5
#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile1, &paramCountInput1, f64input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f64(inputFile1, paramCountInput1, f64input1);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

    mips_max_f64(f64input1, 5, &f64output1, &index);
    printf("mips_max_f64 finish \n");
		printf("mips_max_f64 output = %f \n", f64output1);
        printf("index = %d \n", index);
	printf("mips_max_f64 checking \n\n");
    eq_check_special_f64(&f64refmax[2], &f64output1, 1);
    eq_check_special_q15(&u16maxindex[2], &index, 1);

	printf("\n== mips_max_f64 check done  == \n\n");


// =====================absmax

    double f64refabsmax[MAX_SIZE] = {0};
    uint16_t u16absmaxindex[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, StatsF64, "InputNew1_f64.txt");
#else
	inputFile2 = StatsF64_InputNew1_f64;
	inputFile2Len = sizeof(StatsF64_InputNew1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "AbsMaxVals26_f64.txt");
#else
	referenceFile = StatsF64_AbsMaxVals26_f64;
	referenceFileLen = sizeof(StatsF64_AbsMaxVals26_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsF64, "AbsMaxIndexes26_s16.txt");
#else
	indexvalFile = StatsF64_AbsMaxIndexes26_s16;
	indexvalFileLen = sizeof(StatsF64_AbsMaxIndexes26_s16);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile2, &paramCountInput2, f64input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_f64(inputFile2, paramCountInput2, f64input2);
	paramCountInput2 = paramCountInput2/sizeof(f64);
#endif


	printf("== mips_absmax_f64 test ==  \n");
    mips_absmax_f64(f64input2, 2, &f64output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %f \n", f64input1[i]);
		printf("mips_absmax_f64 output = %f \n", f64output1);
        printf("index = %d \n", index);
	}
    printf("mips_absmax_f64 finish \n");

	printf("mips_absmax_f64 checking \n\n");
#if defined(NOT_EMBEDDED)
	load_data_f64(referenceFile, &paramCountInput1, f64refabsmax);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f64(referenceFile, paramCountInput1, f64refabsmax);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(indexvalFile, &paramCountInput1, u16absmaxindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u16(indexvalFile, paramCountInput1, u16absmaxindex);
	paramCountInput1 = paramCountInput1/sizeof(uint16_t);
#endif

    eq_check_special_f64(&f64refabsmax[0], &f64output1, 1);
    eq_check_special_q15(&u16absmaxindex[0], &index, 1);
	printf("\n== mips_absmax_f64 check done  == \n\n");


//=======4

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile2, &paramCountInput2, f64input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_f64(inputFile2, paramCountInput2, f64input2);
	paramCountInput2 = paramCountInput2/sizeof(f64);
#endif

	printf("== mips_absmax_f64 test ==  \n");
    mips_absmax_f64(f64input2, 4, &f64output1, &index);
	//for (size_t i = 0; i < 8; i++)
	{
       // printf("input = %f \n", f64input1[i]);
		printf("mips_absmax_f64 output = %f \n", f64output1);
        printf("index = %d \n", index);

	}
    printf("mips_absmax_f64 finish \n");

	printf("mips_absmax_f64 checking \n\n");

    eq_check_special_f64(&f64refabsmax[1], &f64output1, 1);
    eq_check_special_q15(&u16absmaxindex[1], &index, 1);
	printf("\n== mips_absmax_f64 check done  == \n\n");


//=======5
#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile2, &paramCountInput2, f64input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_f64(inputFile2, paramCountInput2, f64input2);
	paramCountInput2 = paramCountInput2/sizeof(f64);
#endif

	printf("== mips_absmax_f64 test ==  \n");
    mips_absmax_f64(f64input2, 5, &f64output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
        //printf("input = %f \n", f64input1[i]);
		printf("mips_absmax_f64 output = %f \n", f64output1);
        printf("index = %d \n", index);

	}
    printf("mips_absmax_f64 finish \n");

	printf("mips_absmax_f64 checking \n\n");

    eq_check_special_f64(&f64refabsmax[2], &f64output1, 1);
    eq_check_special_q15(&u16absmaxindex[2], &index, 1);
	printf("\n== mips_absmax_f64 check done  == \n\n");

// =====================max_no_idx

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "MaxVals1_f64.txt");
#else
	referenceFile = StatsF64_MaxVals1_f64;
	referenceFileLen = sizeof(StatsF64_MaxVals1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

	printf("== mips_max_no_idx_f64 test ==  \n");
    mips_max_no_idx_f64(f64input1, 2, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_max_no_idx_f64 output = %f \n", f64output1);
	}
    printf("mips_max_no_idx_f64 finish \n");
	printf("mips_max_no_idx_f64 checking \n\n");

    eq_check_special_f64(&f64refmax[0], &f64output1, 1);

	printf("\n== mips_max_no_idx_f64 check done  == \n\n");

// ===================4

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "MaxVals1_f64.txt");
#else
	referenceFile = StatsF64_MaxVals1_f64;
	referenceFileLen = sizeof(StatsF64_MaxVals1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

	printf("== mips_max_no_idx_f64 test ==  \n");
    mips_max_no_idx_f64(f64input1, 4, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_max_no_idx_f64 output = %f \n", f64output1);
	}
    printf("mips_max_no_idx_f64 finish \n");
	printf("mips_max_no_idx_f64 checking \n\n");

    eq_check_special_f64(&f64refmax[1], &f64output1, 1);
	
	printf("\n== mips_max_no_idx_f64 check done  == \n\n");

// ===================5

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "MaxVals1_f64.txt");
#else
	referenceFile = StatsF64_MaxVals1_f64;
	referenceFileLen = sizeof(StatsF64_MaxVals1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

	printf("== mips_max_no_idx_f64 test ==  \n");
    mips_max_no_idx_f64(f64input1, 5, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_max_no_idx_f64 output = %f \n", f64output1);
	}
    printf("mips_max_no_idx_f64 finish \n");
	printf("mips_max_no_idx_f64 checking \n\n");

    eq_check_special_f64(&f64refmax[2], &f64output1, 1);
	
	printf("\n== mips_max_no_idx_f64 check done  == \n\n");

//=====================abs_no_idx


	printf("== mips_absmax_no_idx_f64 test ==  \n");
    mips_absmax_no_idx_f64(f64input2, 2, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_absmax_no_idx_f64 output = %f \n", f64output1);
	}
    printf("mips_absmax_no_idx_f64 finish \n");
	printf("mips_absmax_no_idx_f64 checking \n\n");

    eq_check_special_f64(&f64refabsmax[0], &f64output1, 1);
	printf("\n== mips_absmax_no_idx_f64 check done  == \n\n");
    
//==============4

	printf("== mips_absmax_no_idx_f64 test ==  \n");
    mips_absmax_no_idx_f64(f64input2, 4, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_absmax_no_idx_f64 output = %f \n", f64output1);
	}
    printf("mips_absmax_no_idx_f64 finish \n");
	printf("mips_absmax_no_idx_f64 checking \n\n");

    eq_check_special_f64(&f64refabsmax[1], &f64output1, 1);
	printf("\n== mips_absmax_no_idx_f64 check done  == \n\n");


//==============5

	printf("== mips_absmax_no_idx_f64 test ==  \n");
    mips_absmax_no_idx_f64(f64input2, 5, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_absmax_no_idx_f64 output = %f \n", f64output1);
	}
    printf("mips_absmax_no_idx_f64 finish \n");
	printf("mips_absmax_no_idx_f64 checking \n\n");

    eq_check_special_f64(&f64refabsmax[2], &f64output1, 1);
	printf("\n== mips_absmax_no_idx_f64 check done  == \n\n");

//=====================min_no_idx

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "MinVals3_f64.txt");
#else
	referenceFile = StatsF64_MinVals3_f64;
	referenceFileLen = sizeof(StatsF64_MinVals3_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(referenceFile, &paramCountInput1, f64refmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f64(referenceFile, paramCountInput1, f64refmin);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

	printf("== mips_min_no_idx_f64 test ==  \n");
    mips_min_no_idx_f64(f64input1, 2, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_min_no_idx_f64 output = %f \n", f64output1);
	}
    printf("mips_min_no_idx_f64 finish \n");
	printf("mips_min_no_idx_f64 checking \n\n");

    eq_check_special_f64(&f64refmin[0], &f64output1, 1);
	printf("\n== mips_min_no_idx_f64 check done  == \n\n");

//=========4

	printf("== mips_min_no_idx_f64 test ==  \n");
    mips_min_no_idx_f64(f64input1, 4, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_min_no_idx_f64 output = %f \n", f64output1);
	}
    printf("mips_min_no_idx_f64 finish \n");
	printf("mips_min_no_idx_f64 checking \n\n");

    eq_check_special_f64(&f64refmin[1], &f64output1, 1);
	printf("\n== mips_min_no_idx_f64 check done  == \n\n");

//=========5

	printf("== mips_min_no_idx_f64 test ==  \n");
    mips_min_no_idx_f64(f64input1, 5, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_min_no_idx_f64 output = %f \n", f64output1);
	}
    printf("mips_min_no_idx_f64 finish \n");
	printf("mips_min_no_idx_f64 checking \n\n");

    eq_check_special_f64(&f64refmin[2], &f64output1, 1);
	printf("\n== mips_min_no_idx_f64 check done  == \n\n");


//=====================absmin_no_idx
    double f64refabsmin[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "AbsMinVals27_f64.txt");
#else
	referenceFile = StatsF64_AbsMinVals27_f64;
	referenceFileLen = sizeof(StatsF64_AbsMinVals27_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(referenceFile, &paramCountInput1, f64refabsmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f64(referenceFile, paramCountInput1, f64refabsmin);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

	printf("== mips_absmin_no_idx_f64 test ==  \n");
    mips_absmin_no_idx_f64(f64input2, 2, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_absmin_no_idx_f64 output = %f \n", f64output1);
	}
    printf("mips_absmin_no_idx_f64 finish \n");
	printf("mips_absmin_no_idx_f64 checking \n\n");

    eq_check_special_f64(&f64refabsmin[0], &f64output1, 1);

	printf("\n== mips_absmin_no_idx_f64 check done  == \n\n");

//================4


	printf("== mips_absmin_no_idx_f64 test ==  \n");
    mips_absmin_no_idx_f64(f64input2, 4, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_absmin_no_idx_f64 output = %f \n", f64output1);
	}
    printf("mips_absmin_no_idx_f64 finish \n");
	printf("mips_absmin_no_idx_f64 checking \n\n");

    eq_check_special_f64(&f64refabsmin[1], &f64output1, 1);
	
	printf("\n== mips_absmin_no_idx_f64 check done  == \n\n");

//=================5


	printf("== mips_absmin_no_idx_f64 test ==  \n");
    mips_absmin_no_idx_f64(f64input2, 5, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_absmin_no_idx_f64 output = %f \n", f64output1);
	}
    printf("mips_absmin_no_idx_f64 finish \n");
	printf("mips_absmin_no_idx_f64 checking \n\n");

    eq_check_special_f64(&f64refabsmin[2], &f64output1, 1);
	
	printf("\n== mips_absmin_no_idx_f64 check done  == \n\n");

//=====================min_no_idx

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "MinVals3_f64.txt");
#else
	referenceFile = StatsF64_MinVals3_f64;
	referenceFileLen = sizeof(StatsF64_MinVals3_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsF64, "MinIndexes3_s16.txt");
#else
	indexvalFile = StatsF64_MinIndexes3_s16;
	indexvalFileLen = sizeof(StatsF64_MinIndexes3_s16);
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
	load_data_f64(referenceFile, &paramCountInput1, f64refmin);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f64(referenceFile, paramCountInput1, f64refmin);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

	printf("== mips_min_f64 test ==  \n");
    mips_min_f64(f64input1, 2, &f64output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_min_f64 output = %f \n", f64output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_f64 finish \n");
	printf("mips_min_f64 checking \n\n");

    eq_check_special_f64(&f64refmin[0], &f64output1, 1);
	eq_check_special_q15(&u16minindex[0], &index, 1);
	printf("\n== mips_min_f64 check done  == \n\n");

//===============4

	printf("== mips_min_f64 test ==  \n");
    mips_min_f64(f64input1, 4, &f64output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_min_f64 output = %f \n", f64output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_f64 finish \n");
	printf("mips_min_f64 checking \n\n");

    eq_check_special_f64(&f64refmin[1], &f64output1, 1);
	eq_check_special_q15(&u16minindex[1], &index, 1);
	printf("\n== mips_min_f64 check done  == \n\n");

//===============5

	printf("== mips_min_f64 test ==  \n");
    mips_min_f64(f64input1, 5, &f64output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_min_f64 output = %f \n", f64output1);
		printf("index = %d \n", index);

	}
    printf("mips_min_f64 finish \n");
	printf("mips_min_f64 checking \n\n");

    eq_check_special_f64(&f64refmin[2], &f64output1, 1);
	eq_check_special_q15(&u16minindex[2], &index, 1);
	printf("\n== mips_min_f64 check done  == \n\n");

//=====================absmin

    uint16_t u16absminindex[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(indexvalFile, sizeof(indexvalFile), "%s%s%s", Patterns_PATH, StatsF64, "AbsMinIndexes27_s16.txt");
#else
	indexvalFile = StatsF64_AbsMinIndexes27_s16;
	indexvalFileLen = sizeof(StatsF64_AbsMinIndexes27_s16);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u16(indexvalFile, &paramCountInput1, u16absminindex);
#else
	paramCountInput1 = indexvalFileLen;
	load_data_u16(indexvalFile, paramCountInput1, u16absminindex);
	paramCountInput1 = paramCountInput1/sizeof(uint16_t);
#endif

	printf("== mips_absmin_f64 test ==  \n");
    mips_absmin_f64(f64input2, 2, &f64output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_absmin_f64 output = %f \n", f64output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_f64 finish \n");
	printf("mips_absmin_f64 checking \n\n");

    eq_check_special_f64(&f64refabsmin[0], &f64output1, 1);
	eq_check_special_q15(&u16absminindex[0], &index, 1);

	printf("\n== mips_absmin_f64 check done  == \n\n");

//===============4

	printf("== mips_absmin_f64 test ==  \n");
    mips_absmin_f64(f64input2, 4, &f64output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_absmin_f64 output = %f \n", f64output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_f64 finish \n");
	printf("mips_absmin_f64 checking \n\n");

    eq_check_special_f64(&f64refabsmin[1], &f64output1, 1);
	eq_check_special_q15(&u16absminindex[1], &index, 1);

	printf("\n== mips_absmin_f64 check done  == \n\n");


//================5

	printf("== mips_absmin_f64 test ==  \n");
    mips_absmin_f64(f64input2, 5, &f64output1, &index);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_absmin_f64 output = %f \n", f64output1);
		printf("index = %d \n", index);

	}
    printf("mips_absmin_f64 finish \n");
	printf("mips_absmin_f64 checking \n\n");

    eq_check_special_f64(&f64refabsmin[2], &f64output1, 1);
	eq_check_special_q15(&u16absminindex[2], &index, 1);

	printf("\n== mips_absmin_f64 check done  == \n\n");

//===========================mean_f64

    double f64input3[MAX_SIZE] = {0};
	double f64mean[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, StatsF64, "Input2_f64.txt");
#else
	inputFile3 = StatsF64_Input2_f64;
	inputFile3Len = sizeof(StatsF64_Input2_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "MeanVals2_f64.txt");
#else
	referenceFile = StatsF64_MeanVals2_f64;
	referenceFileLen = sizeof(StatsF64_MeanVals2_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile3, &paramCountInput3, f64input3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_f64(inputFile3, paramCountInput3, f64input3);
	paramCountInput3 = paramCountInput3/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(referenceFile, &paramCountInput1, f64mean);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f64(referenceFile, paramCountInput1, f64mean);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

	printf("== mips_mean_f64 test ==  \n");
    mips_mean_f64(f64input3, 2, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_mean_f64 output = %f \n", f64output1);

	}
    printf("mips_mean_f64 finish \n");
	printf("mips_mean_f64 checking \n\n");

    snr_check_special_f64(&f64mean[0], &f64output1, 1, SNR_THRESHOLD);
	rel_check_special_f64(&f64mean[0], &f64output1, 1, REL_ERROR);
	
	printf("\n== mips_mean_f64 check done  == \n\n");

//===========4

	printf("== mips_mean_f64 test ==  \n");
    mips_mean_f64(f64input3, 4, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_mean_f64 output = %f \n", f64output1);

	}
    printf("mips_mean_f64 finish \n");
	printf("mips_mean_f64 checking \n\n");

    snr_check_special_f64(&f64mean[1], &f64output1, 1, SNR_THRESHOLD);
	rel_check_special_f64(&f64mean[1], &f64output1, 1, REL_ERROR);

	printf("\n== mips_mean_f64 check done  == \n\n");

//===========5

	printf("== mips_mean_f64 test ==  \n");
    mips_mean_f64(f64input3, 5, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_mean_f64 output = %f \n", f64output1);

	}
    printf("mips_mean_f64 finish \n");
	printf("mips_mean_f64 checking \n\n");

    snr_check_special_f64(&f64mean[2], &f64output1, 1, SNR_THRESHOLD);
	rel_check_special_f64(&f64mean[2], &f64output1, 1, REL_ERROR);

	printf("\n== mips_mean_f64 check done  == \n\n");

//===========================power_f64

	double f64power[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "PowerVals4_f64.txt");
#else
	referenceFile = StatsF64_PowerVals4_f64;
	referenceFileLen = sizeof(StatsF64_PowerVals4_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f64(referenceFile, &paramCountInput1, f64power);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f64(referenceFile, paramCountInput1, f64power);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

	printf("== mips_power_f64 test ==  \n");
    mips_power_f64(f64input1, 2, &f64output1);
	//for (size_t i = 0; i < 2; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_power_f64 output = %f \n", f64output1);

	}
    printf("mips_power_f64 finish \n");
	printf("mips_power_f64 checking \n\n");

    snr_check_special_f64(&f64power[0], &f64output1, 1, SNR_THRESHOLD);
	rel_check_special_f64(&f64power[0], &f64output1, 1, REL_ERROR);
	
	printf("\n== mips_power_f64 check done  == \n\n");

//=============4

	printf("== mips_power_f64 test ==  \n");
    mips_power_f64(f64input1, 4, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_power_f64 output = %f \n", f64output1);

	}
    printf("mips_power_f64 finish \n");
	printf("mips_power_f64 checking \n\n");

    snr_check_special_f64(&f64power[1], &f64output1, 1, SNR_THRESHOLD);
	rel_check_special_f64(&f64power[1], &f64output1, 1, REL_ERROR);
	
	printf("\n== mips_power_f64 check done  == \n\n");

//=============5

	printf("== mips_power_f64 test ==  \n");
    mips_power_f64(f64input1, 5, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_power_f64 output = %f \n", f64output1);

	}
    printf("mips_power_f64 finish \n");
	printf("mips_power_f64 checking \n\n");

    snr_check_special_f64(&f64power[2], &f64output1, 1, SNR_THRESHOLD);
	rel_check_special_f64(&f64power[2], &f64output1, 1, REL_ERROR);
	
	printf("\n== mips_power_f64 check done  == \n\n");




//===========================std_f64

	double f64std[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "StdVals6_f64.txt");
#else
	referenceFile = StatsF64_StdVals6_f64;
	referenceFileLen = sizeof(StatsF64_StdVals6_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f64(referenceFile, &paramCountInput1, f64std);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f64(referenceFile, paramCountInput1, f64std);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

	printf("== mips_std_f64 test ==  \n");
    mips_std_f64(f64input1, 2, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_std_f64 output = %f \n", f64output1);

	}
    printf("mips_std_f64 finish \n");
	printf("mips_std_f64 checking \n\n");

    snr_check_special_f64(&f64std[0], &f64output1, 1, SNR_THRESHOLD);
	rel_check_special_f64(&f64std[0], &f64output1, 1, REL_ERROR);
	
	printf("\n== mips_std_f64 check done  == \n\n");

//============4

	printf("== mips_std_f64 test ==  \n");
    mips_std_f64(f64input1, 4, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_std_f64 output = %f \n", f64output1);

	}
    printf("mips_std_f64 finish \n");
	printf("mips_std_f64 checking \n\n");

    snr_check_special_f64(&f64std[1], &f64output1, 1, SNR_THRESHOLD);
	rel_check_special_f64(&f64std[1], &f64output1, 1, REL_ERROR);
	
	printf("\n== mips_std_f64 check done  == \n\n");
	
//============5

	printf("== mips_std_f64 test ==  \n");
    mips_std_f64(f64input1, 5, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_std_f64 output = %f \n", f64output1);

	}
    printf("mips_std_f64 finish \n");
	printf("mips_std_f64 checking \n\n");

    snr_check_special_f64(&f64std[2], &f64output1, 1, SNR_THRESHOLD);
	rel_check_special_f64(&f64std[2], &f64output1, 1, REL_ERROR);
	
	printf("\n== mips_std_f64 check done  == \n\n");


//===========================var_f64

	double f64var[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "VarVals7_f64.txt");
#else
	referenceFile = StatsF64_VarVals7_f64;
	referenceFileLen = sizeof(StatsF64_VarVals7_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f64(referenceFile, &paramCountInput1, f64var);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f64(referenceFile, paramCountInput1, f64var);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

	printf("== mips_var_f64 test ==  \n");
    mips_var_f64(f64input1, 2, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_var_f64 output = %f \n", f64output1);

	}
    printf("mips_var_f64 finish \n");
	printf("mips_var_f64 checking \n\n");

    snr_check_special_f64(&f64var[0], &f64output1, 1, SNR_THRESHOLD);
	rel_check_special_f64(&f64var[0], &f64output1, 1, REL_ERROR);
	
	printf("\n== mips_var_f64 check done  == \n\n");


//===========4

	printf("== mips_var_f64 test ==  \n");
    mips_var_f64(f64input1, 4, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_var_f64 output = %f \n", f64output1);

	}
    printf("mips_var_f64 finish \n");
	printf("mips_var_f64 checking \n\n");

    snr_check_special_f64(&f64var[1], &f64output1, 1, SNR_THRESHOLD);
	rel_check_special_f64(&f64var[1], &f64output1, 1, REL_ERROR);
	
	printf("\n== mips_var_f64 check done  == \n\n");


//===========5

	printf("== mips_var_f64 test ==  \n");
    mips_var_f64(f64input1, 5, &f64output1);
	//for (size_t i = 0; i < 3; i++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_var_f64 output = %f \n", f64output1);

	}
    printf("mips_var_f64 finish \n");
	printf("mips_var_f64 checking \n\n");

    snr_check_special_f64(&f64var[2], &f64output1, 1, SNR_THRESHOLD);
	rel_check_special_f64(&f64var[2], &f64output1, 1, REL_ERROR);
	
	printf("\n== mips_var_f64 check done  == \n\n");

//===========================entropy_f64
	int paramCountInput4 = 0;
	int paramCountInput5 = 0;
	double f64entropy[MAX_SIZE] = {0};
	double f64input4[MAX_SIZE] = {0};
	double f64output2[MAX_SIZE] = {0};
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
	snprintf(inputFile4, sizeof(inputFile4), "%s%s%s", Patterns_PATH, StatsF64, "Input22_f64.txt");
#else
	inputFile4 = StatsF64_Input22_f64;
	inputFile4Len = sizeof(StatsF64_Input22_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile5, sizeof(inputFile5), "%s%s%s", Patterns_PATH, StatsF64, "Dims22_s16.txt");
#else
	inputFile5 = StatsF64_Dims22_s16;
	inputFile5Len = sizeof(StatsF64_Dims22_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "RefEntropy22_f64.txt");
#else
	referenceFile = StatsF64_RefEntropy22_f64;
	referenceFileLen = sizeof(StatsF64_RefEntropy22_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile4, &paramCountInput4, f64input4);
#else
	paramCountInput4 = inputFile4Len;
	load_data_f64(inputFile4, paramCountInput4, f64input4);
	paramCountInput4 = paramCountInput4/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile5, &paramCountInput5, q15input1);
#else
	paramCountInput5 = inputFile5Len;
	load_data_q15(inputFile5, paramCountInput5, q15input1);
	paramCountInput5 = paramCountInput5/sizeof(q15);
#endif

	printf("== mips_entropy_f64 test ==  \n");

	f64 *inp = f64input4;

	int16_t *dimsp = q15input1;

	f64 *outp = f64output2;
      for(int i=0;i < 0x000A; i++)
      {
         *outp = mips_entropy_f64(inp,dimsp[i+1]);
         outp++;
          inp += dimsp[i+1];
      }


	for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_entropy_f64 output = %f \n", f64output2[j]);

	}
    printf("mips_entropy_f64 finish \n");
	printf("mips_entropy_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output2, 1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output2, 1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output2, 1, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output2, 1, REL_ERROR);
#endif

	
	printf("\n== mips_entropy_f64 check done  == \n\n");




//===========================kulback_f64

	int paramCountInputA = 0;
	int paramCountInputB = 0;
	int paramCountInput10 = 0;
	double f64inputa[MAX_SIZE] = {0};
	double f64inputb[MAX_SIZE] = {0};


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
	snprintf(inputFilea, sizeof(inputFilea), "%s%s%s", Patterns_PATH, StatsF64, "InputA24_f64.txt");
#else
	inputFilea = StatsF64_InputA24_f64;
	inputFileaLen = sizeof(StatsF64_InputA24_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb, sizeof(inputFileb), "%s%s%s", Patterns_PATH, StatsF64, "InputB24_f64.txt");
#else
	inputFileb = StatsF64_InputB24_f64;
	inputFilebLen = sizeof(StatsF64_InputB24_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile10, sizeof(inputFile10), "%s%s%s", Patterns_PATH, StatsF64, "Dims24_s16.txt");
#else
	inputFile10 = StatsF64_Dims24_s16;
	inputFile10Len = sizeof(StatsF64_Dims24_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "RefKL24_f64.txt");
#else
	referenceFile = StatsF64_RefKL24_f64;
	referenceFileLen = sizeof(StatsF64_RefKL24_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFilea, &paramCountInputA, f64inputa);
#else
	paramCountInputA = inputFileaLen;
	load_data_f64(inputFilea, paramCountInputA, f64inputa);
	paramCountInputA = paramCountInputA/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileb, &paramCountInputB, f64inputb);
#else
	paramCountInputB = inputFilebLen;
	load_data_f64(inputFileb, paramCountInputB, f64inputb);
	paramCountInputB = paramCountInputB/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile10, &paramCountInput10, q15input1);
#else
	paramCountInput10 = inputFile10Len;
	load_data_q15(inputFile10, paramCountInput10, q15input1);
	paramCountInput10 = paramCountInput10/sizeof(q15);
#endif

	printf("== mips_kullback_leibler_f64 test ==  \n");

	f64 *inpA = f64inputa;
	f64 *inpB = f64inputb;
	dimsp = q15input1;

	outp = f64output2;
	for(int i=0;i < dimsp[0]; i++)
      {
         *outp = mips_kullback_leibler_f64(inpA,inpB,dimsp[i+1]);
         outp++;
         inpA += dimsp[i+1];
         inpB += dimsp[i+1];
      }

		for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_kullback_leibler_f64 output = %f \n", f64output2[j]);

	}
    printf("mips_kullback_leibler_f64 finish \n");
	printf("mips_kullback_leibler_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output2, 1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output2, 1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output2, 1, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output2, 1, REL_ERROR);
#endif


	printf("\n== mips_kullback_leibler_f64 check done  == \n\n");



//===========================mse_f64

	double f64mse[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea, sizeof(inputFilea), "%s%s%s", Patterns_PATH, StatsF64, "InputNew1_f64.txt");
#else
	inputFilea = StatsF64_InputNew1_f64;
	inputFileaLen = sizeof(StatsF64_InputNew1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb, sizeof(inputFileb), "%s%s%s", Patterns_PATH, StatsF64, "InputNew2_f64.txt");
#else
	inputFileb = StatsF64_InputNew2_f64;
	inputFilebLen = sizeof(StatsF64_InputNew2_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "MSEVals28_f64.txt");
#else
	referenceFile = StatsF64_MSEVals28_f64;
	referenceFileLen = sizeof(StatsF64_MSEVals28_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f64(inputFilea, &paramCountInputA, f64inputa);
#else
	paramCountInputA = inputFileaLen;
	load_data_f64(inputFilea, paramCountInputA, f64inputa);
	paramCountInputA = paramCountInputA/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileb, &paramCountInputB, f64inputb);
#else
	paramCountInputB = inputFilebLen;
	load_data_f64(inputFileb, paramCountInputB, f64inputb);
	paramCountInputB = paramCountInputB/sizeof(f64);
#endif
#if defined(NOT_EMBEDDED)
	load_data_f64(referenceFile, &paramCountInput1,f64mse);
#else
	paramCountInput1 = referenceFileLen;
	load_data_f32(referenceFile, paramCountInput1, f64mse);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

	printf("== mips_mse_f64 test ==  \n");


    mips_mse_f64(f64inputa,f64inputb,2,&f64output1);
		//for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_mse_f64 output = %f \n", f64output1);

	}
    printf("mips_mse_f64 finish \n");
	printf("mips_mse_f64 checking \n\n");

    snr_check_special_f64(&f64mse[0], &f64output1, 1, SNR_THRESHOLD);
	rel_check_special_f64(&f64mse[0], &f64output1, 1, REL_ERROR);

	printf("\n== mips_mse_f64 check done  == \n\n");

//=============mse 100
	printf("== mips_mse_f64 test ==  \n");


    mips_mse_f64(f64inputa,f64inputb,100,&f64output1);
		//for (size_t j = 0; j < 10; j++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_mse_f64 output = %f \n", f64output1);

	}
    printf("mips_mse_f64 finish \n");
	printf("mips_mse_f64 checking \n\n");

    snr_check_special_f64(&f64mse[3], &f64output1, 1, SNR_THRESHOLD);
	rel_check_special_f64(&f64mse[3], &f64output1, 1, REL_ERROR);

	printf("\n== mips_mse_f64 check done  == \n\n");

//===========================accumulate

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea, sizeof(inputFilea), "%s%s%s", Patterns_PATH, StatsF64, "InputAccumulate1_f64.txt");
#else
	inputFilea = StatsF64_InputAccumulate1_f64;
	inputFileaLen = sizeof(StatsF64_InputAccumulate1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile10, sizeof(inputFile10), "%s%s%s", Patterns_PATH, StatsF64, "InputAccumulateConfig1_s16.txt");
#else
	inputFile10 = StatsF64_InputAccumulateConfig1_s16;
	inputFile10Len = sizeof(StatsF64_InputAccumulateConfig1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, StatsF64, "RefAccumulate1_f64.txt");
#else
	referenceFile = StatsF64_RefAccumulate1_f64;
	referenceFileLen = sizeof(StatsF64_RefAccumulate1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f64(inputFilea, &paramCountInputA, f64inputa);
#else
	paramCountInputA = inputFileaLen;
	load_data_f64(inputFilea, paramCountInputA, f64inputa);
	paramCountInputA = paramCountInputA/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile10, &paramCountInput10, q15input1);
#else
	paramCountInput10 = inputFile10Len;
	load_data_q15(inputFile10, paramCountInput10, q15input1);
	paramCountInput10 = paramCountInput10/sizeof(q15);
#endif

	printf("== mips_accumulate_f64 test ==  \n");

	inp = f64inputa;
	dimsp = q15input1;
	outp = f64output2;
	
	for(int i=0;i < dimsp[0]; i++)
      {
         mips_accumulate_f64(inp,dimsp[i+1],outp);
         outp++;
      }

		for (size_t j = 0; j < 4; j++)
	{
     //   printf("input = %f \n", f64input1[i]);
		printf("mips_accumulate_f64 output = %f \n", f64output2[j]);

	}
    printf("mips_accumulate_f64 finish \n");
	printf("mips_accumulate_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output2, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output2, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output2, 0, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output2, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_accumulate_f64 check done  == \n\n");


	return 0 ;
}
