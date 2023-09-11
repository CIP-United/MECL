#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/distance_functions.h"
#include "dsp/matrix_functions.h"

#define ERROR_THRESHOLD (f32)1e-8

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
	int paramCountDims = 0;
	uint32_t u32inputA1[MAX_SIZE] = {0};
	uint32_t u32inputB1[MAX_SIZE] = {0};
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
	snprintf(inputFileA1, sizeof(inputFileA1), "%s%s%s", Patterns_PATH, DistanceU32, "InputA1_u32.txt");
#else
	inputFileA1 = DistanceU32_InputA1_u32;
	inputFileA1Len = sizeof(DistanceU32_InputA1_u32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB1, sizeof(inputFileB1), "%s%s%s", Patterns_PATH, DistanceU32, "InputB1_u32.txt");
#else
	inputFileB1 = DistanceU32_InputB1_u32;
	inputFileB1Len = sizeof(DistanceU32_InputB1_u32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile, sizeof(dimsFile), "%s%s%s", Patterns_PATH, DistanceU32, "Dims1_s16.txt");
#else
	dimsFile = DistanceU32_Dims1_s16;
	dimsFileLen = sizeof(DistanceU32_Dims1_s16);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_u32(inputFileA1, &paramCountInputA1, u32inputA1);
#else
	paramCountInputA1 = inputFileA1Len;
	load_data_u32(inputFileA1, paramCountInputA1, u32inputA1);
	paramCountInputA1 = paramCountInputA1/sizeof(uint32_t);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u32(inputFileB1, &paramCountInputB1, u32inputB1);
#else
	paramCountInputB1 = inputFileB1Len;
	load_data_u32(inputFileB1, paramCountInputB1, u32inputB1);
	paramCountInputB1 = paramCountInputB1/sizeof(uint32_t);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile, &paramCountDims, s16Dims);
#else
	paramCountDims = dimsFileLen;
	load_data_q15(dimsFile, paramCountDims, s16Dims);
	paramCountDims = paramCountDims/sizeof(q15);
#endif


	f32 f32output1[MAX_SIZE] = {0};
	int16_t outPath[MAX_SIZE] = {0};
	int16_t refPath[MAX_SIZE] = {0};

	int vecDim;
	int bitVecDim;
	int nbPatterns;

	nbPatterns = s16Dims[0];
	vecDim = s16Dims[1];
	bitVecDim = s16Dims[2];

	// =====================

	uint32_t *inpA = u32inputA1;
	uint32_t *inpB = u32inputB1;

	f32 *outp = f32output1;

	printf("== mips_dice_distance_u32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_dice_distance(inpA, inpB, vecDim);

		inpA += bitVecDim;
		inpB += bitVecDim;
		outp++;
	}
	printf("mips_dice_distance_u32 finish \n");

	printf("mips_dice_distance_u32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceU32, "Ref1_f32.txt");
#else
	referenceFile = DistanceU32_Ref1_f32;
	referenceFileLen = sizeof(DistanceU32_Ref1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, 0, ERROR_THRESHOLD);
#else
	rel_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ERROR_THRESHOLD);
#endif

	printf("\n== mips_dice_distance_u32 check done  == \n\n");

	// =====================

	inpA = u32inputA1;
	inpB = u32inputB1;

	outp = f32output1;

	printf("== mips_hamming_distance_u32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_hamming_distance(inpA, inpB, vecDim);

		inpA += bitVecDim;
		inpB += bitVecDim;
		outp++;
	}
	printf("mips_hamming_distance_u32 finish \n");

	printf("mips_hamming_distance_u32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceU32, "Ref2_f32.txt");
#else
	referenceFile = DistanceU32_Ref2_f32;
	referenceFileLen = sizeof(DistanceU32_Ref2_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, ERROR_THRESHOLD);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ERROR_THRESHOLD);
#endif

	printf("\n== mips_hamming_distance_u32 check done  == \n\n");

	// =====================

	inpA = u32inputA1;
	inpB = u32inputB1;

	outp = f32output1;

	printf("== mips_jaccard_distance_u32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_jaccard_distance(inpA, inpB, vecDim);

		inpA += bitVecDim;
		inpB += bitVecDim;
		outp++;
	}
	printf("mips_jaccard_distance_u32 finish \n");

	printf("mips_jaccard_distance_u32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceU32, "Ref3_f32.txt");
#else
	referenceFile = DistanceU32_Ref3_f32;
	referenceFileLen = sizeof(DistanceU32_Ref3_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, ERROR_THRESHOLD);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ERROR_THRESHOLD);
#endif

	printf("\n== mips_jaccard_distance_u32 check done  == \n\n");

	// =====================

	inpA = u32inputA1;
	inpB = u32inputB1;

	outp = f32output1;

	printf("== mips_kulsinski_distance_u32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_kulsinski_distance(inpA, inpB, vecDim);

		inpA += bitVecDim;
		inpB += bitVecDim;
		outp++;
	}
	printf("mips_kulsinski_distance_u32 finish \n");

	printf("mips_kulsinski_distance_u32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceU32, "Ref4_f32.txt");
#else
	referenceFile = DistanceU32_Ref4_f32;
	referenceFileLen = sizeof(DistanceU32_Ref4_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, ERROR_THRESHOLD);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ERROR_THRESHOLD);
#endif

	printf("\n== mips_kulsinski_distance_u32 check done  == \n\n");

	// =====================

	inpA = u32inputA1;
	inpB = u32inputB1;

	outp = f32output1;

	printf("== mips_rogerstanimoto_distance_u32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_rogerstanimoto_distance(inpA, inpB, vecDim);

		inpA += bitVecDim;
		inpB += bitVecDim;
		outp++;
	}

	printf("mips_rogerstanimoto_distance_u32 finish \n");

	printf("mips_rogerstanimoto_distance_u32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceU32, "Ref5_f32.txt");
#else
	referenceFile = DistanceU32_Ref5_f32;
	referenceFileLen = sizeof(DistanceU32_Ref5_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, ERROR_THRESHOLD);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ERROR_THRESHOLD);
#endif

	printf("\n== mips_rogerstanimoto_distance_u32 check done  == \n\n");

	// =====================

	inpA = u32inputA1;
	inpB = u32inputB1;

	outp = f32output1;

	printf("== mips_russellrao_distance_u32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_russellrao_distance(inpA, inpB, vecDim);

		inpA += bitVecDim;
		inpB += bitVecDim;
		outp++;
	}
	printf("mips_russellrao_distance_u32 finish \n");

	printf("mips_russellrao_distance_u32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceU32, "Ref6_f32.txt");
#else
	referenceFile = DistanceU32_Ref6_f32;
	referenceFileLen = sizeof(DistanceU32_Ref6_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, ERROR_THRESHOLD);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ERROR_THRESHOLD);
#endif

	printf("\n== mips_russellrao_distance_u32 check done  == \n\n");

	// =====================

	inpA = u32inputA1;
	inpB = u32inputB1;

	outp = f32output1;

	printf("== mips_sokalmichener_distance_u32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_sokalmichener_distance(inpA, inpB, vecDim);

		inpA += bitVecDim;
		inpB += bitVecDim;
		outp++;
	}
	printf("mips_sokalmichener_distance_u32 finish \n");

	printf("mips_sokalmichener_distance_u32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceU32, "Ref7_f32.txt");
#else
	referenceFile = DistanceU32_Ref7_f32;
	referenceFileLen = sizeof(DistanceU32_Ref7_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, ERROR_THRESHOLD);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ERROR_THRESHOLD);
#endif

	printf("\n== mips_sokalmichener_distance_u32 check done  == \n\n");

	// =====================

	inpA = u32inputA1;
	inpB = u32inputB1;

	outp = f32output1;

	printf("== mips_sokalsneath_distance_u32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_sokalsneath_distance(inpA, inpB, vecDim);

		inpA += bitVecDim;
		inpB += bitVecDim;
		outp++;
	}
	printf("mips_sokalsneath_distance_u32 finish \n");

	printf("mips_sokalsneath_distance_u32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceU32, "Ref8_f32.txt");
#else
	referenceFile = DistanceU32_Ref8_f32;
	referenceFileLen = sizeof(DistanceU32_Ref8_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, ERROR_THRESHOLD);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ERROR_THRESHOLD);
#endif

	printf("\n== mips_sokalsneath_distance_u32 check done  == \n\n");

	// =====================

	inpA = u32inputA1;
	inpB = u32inputB1;

	outp = f32output1;

	printf("== mips_yule_distance_u32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_yule_distance(inpA, inpB, vecDim);

		inpA += bitVecDim;
		inpB += bitVecDim;
		outp++;
	}
	printf("mips_yule_distance_u32 finish \n");

	printf("mips_yule_distance_u32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceU32, "Ref9_f32.txt");
#else
	referenceFile = DistanceU32_Ref9_f32;
	referenceFileLen = sizeof(DistanceU32_Ref9_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, ERROR_THRESHOLD);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ERROR_THRESHOLD);
#endif

	printf("\n== mips_yule_distance_u32 check done  == \n\n");

	// =====================

	return 0;
}