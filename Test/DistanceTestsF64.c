#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/distance_functions.h"

#define REL_ERROR (f64)(2.0e-14)

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
	int paramCountInputA1 = 0;
	int paramCountInputB1 = 0;
	int paramCountInputA8 = 0;
	int paramCountInputB8 = 0;
	int paramCountDims = 0;
	f64 f64inputA1[MAX_SIZE] = {0};
	f64 f64inputB1[MAX_SIZE] = {0};
	f64 f64inputA8[MAX_SIZE] = {0};
	f64 f64inputB8[MAX_SIZE] = {0};
	q15 s16Dims[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFileA1[255] = {0};
#else
	void *inputFileA1;
	int inputFileA1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileB1[255] = {0};
#else
	void *inputFileB1;
	int inputFileB1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileA8[255] = {0};
#else
	void *inputFileA8;
	int inputFileA8Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileB8[255] = {0};
#else
	void *inputFileB8;
	int inputFileB8Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char dimsFile[255] = {0};
#else
	void *dimsFile;
	int dimsFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFile[255] = {0};
#else
	void *referenceFile;
	int referenceFileLen = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFileA1, sizeof(inputFileA1), "%s%s%s", Patterns_PATH, DistanceF64, "InputA1_f64.txt");
#else
	inputFileA1 = DistanceF64_InputA1_f64;
	inputFileA1Len = sizeof(DistanceF64_InputA1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB1, sizeof(inputFileB1), "%s%s%s", Patterns_PATH, DistanceF64, "InputB1_f64.txt");
#else
	inputFileB1 = DistanceF64_InputB1_f64;
	inputFileB1Len = sizeof(DistanceF64_InputB1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileA8, sizeof(inputFileA8), "%s%s%s", Patterns_PATH, DistanceF64, "InputA8_f64.txt");
#else
	inputFileA8 = DistanceF64_InputA8_f64;
	inputFileA8Len = sizeof(DistanceF64_InputA8_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB8, sizeof(inputFileB8), "%s%s%s", Patterns_PATH, DistanceF64, "InputB8_f64.txt");
#else
	inputFileB8 = DistanceF64_InputB8_f64;
	inputFileB8Len = sizeof(DistanceF64_InputB8_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile, sizeof(dimsFile), "%s%s%s", Patterns_PATH, DistanceF64, "Dims1_s16.txt");
#else
	dimsFile = DistanceF64_Dims1_s16;
	dimsFileLen = sizeof(DistanceF64_Dims1_s16);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileA1, &paramCountInputA1, f64inputA1);
#else
	paramCountInputA1 = inputFileA1Len;
	load_data_f64(inputFileA1, paramCountInputA1, f64inputA1);
	paramCountInputA1 = paramCountInputA1/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileB1, &paramCountInputB1, f64inputB1);
#else
	paramCountInputB1 = inputFileB1Len;
	load_data_f64(inputFileB1, paramCountInputB1, f64inputB1);
	paramCountInputB1 = paramCountInputB1/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileA8, &paramCountInputA8, f64inputA8);
#else
	paramCountInputA8 = inputFileA8Len;
	load_data_f64(inputFileA8, paramCountInputA8, f64inputA8);
	paramCountInputA8 = paramCountInputA8/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileB8, &paramCountInputB8, f64inputB8);
#else
	paramCountInputB8 = inputFileB8Len;
	load_data_f64(inputFileB8, paramCountInputB8, f64inputB8);
	paramCountInputB8 = paramCountInputB8/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile, &paramCountDims, s16Dims);
#else
	paramCountDims = dimsFileLen;
	load_data_q15(dimsFile, paramCountDims, s16Dims);
	paramCountDims = paramCountDims/sizeof(q15);
#endif


	f64 f64output1[MAX_SIZE] = {0};
	f64 tmpA[MAX_SIZE] = {0};
	f64 tmpB[MAX_SIZE] = {0};
	q7 tmpC[MAX_SIZE] = {0};
	int16_t outPath[MAX_SIZE] = {0};
	int16_t refPath[MAX_SIZE] = {0};

	int vecDim;
	int nbPatterns;

	int queryLength;
	int templateLength;

	nbPatterns = s16Dims[0];
	vecDim = s16Dims[1];

	// =====================

	f64 *inpA = f64inputA1;
	f64 *inpB = f64inputB1;

	f64 *outp = f64output1;

	printf("== mips_chebyshev_distance_f64 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_chebyshev_distance_f64(inpA, inpB, vecDim);

		inpA += vecDim;
		inpB += vecDim;
		outp++;
	}
	printf("mips_chebyshev_distance_f64 finish \n");

	printf("mips_chebyshev_distance_f64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF64, "Ref3_f64.txt");
#else
	referenceFile = DistanceF64_Ref3_f64;
	referenceFileLen = sizeof(DistanceF64_Ref3_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f64(referenceFile, f64output1, 0, REL_ERROR);
#else
	near_check_special_f64(referenceData_f64, f64output1, referenceFileLen, REL_ERROR);
#endif

	printf("\n== mips_chebyshev_distance_f64 check done  == \n\n");

	// =====================

	inpA = f64inputA1;
	inpB = f64inputB1;

	outp = f64output1;

	printf("== mips_cityblock_distance_f64 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_cityblock_distance_f64(inpA, inpB, vecDim);

		inpA += vecDim;
		inpB += vecDim;
		outp++;
	}
	printf("mips_cityblock_distance_f64 finish \n");

	printf("mips_cityblock_distance_f64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF64, "Ref4_f64.txt");
#else
	referenceFile = DistanceF64_Ref4_f64;
	referenceFileLen = sizeof(DistanceF64_Ref4_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f64(referenceFile, f64output1, 0, REL_ERROR);
#else
	near_check_special_f64(referenceData_f64, f64output1, referenceFileLen, REL_ERROR);
#endif

	printf("\n== mips_cityblock_distance_f64 check done  == \n\n");

	// =====================

	inpA = f64inputA1;
	inpB = f64inputB1;

	outp = f64output1;

	printf("== mips_cosine_distance_f64 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_cosine_distance_f64(inpA, inpB, vecDim);

		inpA += vecDim;
		inpB += vecDim;
		outp++;
	}

	printf("mips_cosine_distance_f64 finish \n");

	printf("mips_cosine_distance_f64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF64, "Ref6_f64.txt");
#else
	referenceFile = DistanceF64_Ref6_f64;
	referenceFileLen = sizeof(DistanceF64_Ref6_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f64(referenceFile, f64output1, 0, REL_ERROR);
#else
	near_check_special_f64(referenceData_f64, f64output1, referenceFileLen, REL_ERROR);
#endif

	printf("\n== mips_cosine_distance_f64 check done  == \n\n");

	// =====================

	inpA = f64inputA1;
	inpB = f64inputB1;

	outp = f64output1;

	printf("== mips_euclidean_distance_f64 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_euclidean_distance_f64(inpA, inpB, vecDim);

		inpA += vecDim;
		inpB += vecDim;
		outp++;
	}
	printf("mips_euclidean_distance_f64 finish \n");

	printf("mips_euclidean_distance_f64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF64, "Ref7_f64.txt");
#else
	referenceFile = DistanceF64_Ref7_f64;
	referenceFileLen = sizeof(DistanceF64_Ref7_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f64(referenceFile, f64output1, 0, REL_ERROR);
#else
	near_check_special_f64(referenceData_f64, f64output1, referenceFileLen, REL_ERROR);
#endif

	printf("\n== mips_euclidean_distance_f64 check done  == \n\n");

	// =====================

	return 0;
}