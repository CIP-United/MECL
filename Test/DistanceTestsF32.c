#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/distance_functions.h"
#include "dsp/matrix_functions.h"

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
	f32 f32inputA1[MAX_SIZE] = {0};
	f32 f32inputB1[MAX_SIZE] = {0};
	f32 f32inputA8[MAX_SIZE] = {0};
	f32 f32inputB8[MAX_SIZE] = {0};
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
	snprintf(inputFileA1, sizeof(inputFileA1), "%s%s%s", Patterns_PATH, DistanceF32, "InputA1_f32.txt");
#else
	inputFileA1 = DistanceF32_InputA1_f32;
	inputFileA1Len = sizeof(DistanceF32_InputA1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB1, sizeof(inputFileB1), "%s%s%s", Patterns_PATH, DistanceF32, "InputB1_f32.txt");
#else
	inputFileB1 = DistanceF32_InputB1_f32;
	inputFileB1Len = sizeof(DistanceF32_InputB1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileA8, sizeof(inputFileA8), "%s%s%s", Patterns_PATH, DistanceF32, "InputA8_f32.txt");
#else
	inputFileA8 = DistanceF32_InputA8_f32;
	inputFileA8Len = sizeof(DistanceF32_InputA8_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB8, sizeof(inputFileB8), "%s%s%s", Patterns_PATH, DistanceF32, "InputB8_f32.txt");
#else
	inputFileB8 = DistanceF32_InputB8_f32;
	inputFileB8Len = sizeof(DistanceF32_InputB8_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile, sizeof(dimsFile), "%s%s%s", Patterns_PATH, DistanceF32, "Dims1_s16.txt");
#else
	dimsFile = DistanceF32_Dims1_s16;
	dimsFileLen = sizeof(DistanceF32_Dims1_s16);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileA1, &paramCountInputA1, f32inputA1);
#else
	paramCountInputA1 = inputFileA1Len;
	load_data_f32(inputFileA1, paramCountInputA1, f32inputA1);
	paramCountInputA1 = paramCountInputA1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileB1, &paramCountInputB1, f32inputB1);
#else
	paramCountInputB1 = inputFileB1Len;
	load_data_f32(inputFileB1, paramCountInputB1, f32inputB1);
	paramCountInputB1 = paramCountInputB1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileA8, &paramCountInputA8, f32inputA8);
#else
	paramCountInputA8 = inputFileA8Len;
	load_data_f32(inputFileA8, paramCountInputA8, f32inputA8);
	paramCountInputA8 = paramCountInputA8/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileB8, &paramCountInputB8, f32inputB8);
#else
	paramCountInputB8 = inputFileB8Len;
	load_data_f32(inputFileB8, paramCountInputB8, f32inputB8);
	paramCountInputB8 = paramCountInputB8/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile, &paramCountDims, s16Dims);
#else
	paramCountDims = dimsFileLen;
	load_data_q15(dimsFile, paramCountDims, s16Dims);
	paramCountDims = paramCountDims/sizeof(q15);
#endif


	f32 f32output1[MAX_SIZE] = {0};
	f32 tmpA[MAX_SIZE] = {0};
	f32 tmpB[MAX_SIZE] = {0};
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

	f32 *inpA = f32inputA1;
	f32 *inpB = f32inputB1;

	f32 *outp = f32output1;

	printf("== mips_braycurtis_distance_f32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_braycurtis_distance_f32(inpA, inpB, vecDim);

		inpA += vecDim;
		inpB += vecDim;
		outp++;
	}
	printf("mips_braycurtis_distance_f32 finish \n");

	printf("mips_braycurtis_distance_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF32, "Ref1_f32.txt");
#else
	referenceFile = DistanceF32_Ref1_f32;
	referenceFileLen = sizeof(DistanceF32_Ref1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, (f32)1e-3);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)1e-3);
#endif

	printf("\n== mips_braycurtis_distance_f32 check done  == \n\n");

	// =====================

	inpA = f32inputA1;
	inpB = f32inputB1;

	outp = f32output1;

	printf("== mips_canberra_distance_f32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_canberra_distance_f32(inpA, inpB, vecDim);

		inpA += vecDim;
		inpB += vecDim;
		outp++;
	}
	printf("mips_canberra_distance_f32 finish \n");

	printf("mips_canberra_distance_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF32, "Ref2_f32.txt");
#else
	referenceFile = DistanceF32_Ref2_f32;
	referenceFileLen = sizeof(DistanceF32_Ref2_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, (f32)1e-3);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)1e-3);
#endif

	printf("\n== mips_canberra_distance_f32 check done  == \n\n");

	// =====================

	inpA = f32inputA1;
	inpB = f32inputB1;

	outp = f32output1;

	printf("== mips_chebyshev_distance_f32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_chebyshev_distance_f32(inpA, inpB, vecDim);

		inpA += vecDim;
		inpB += vecDim;
		outp++;
	}
	printf("mips_chebyshev_distance_f32 finish \n");

	printf("mips_chebyshev_distance_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF32, "Ref3_f32.txt");
#else
	referenceFile = DistanceF32_Ref3_f32;
	referenceFileLen = sizeof(DistanceF32_Ref3_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, (f32)1e-3);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)1e-3);
#endif

	printf("\n== mips_chebyshev_distance_f32 check done  == \n\n");

	// =====================

	inpA = f32inputA1;
	inpB = f32inputB1;

	outp = f32output1;

	printf("== mips_cityblock_distance_f32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_cityblock_distance_f32(inpA, inpB, vecDim);

		inpA += vecDim;
		inpB += vecDim;
		outp++;
	}
	printf("mips_cityblock_distance_f32 finish \n");

	printf("mips_cityblock_distance_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF32, "Ref4_f32.txt");
#else
	referenceFile = DistanceF32_Ref4_f32;
	referenceFileLen = sizeof(DistanceF32_Ref4_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, (f32)1e-3);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)1e-3);
#endif

	printf("\n== mips_cityblock_distance_f32 check done  == \n\n");

	// =====================

	f32 *tmpap = tmpA;
	f32 *tmpbp = tmpB;

	inpA = f32inputA1;
	inpB = f32inputB1;

	outp = f32output1;

	printf("== mips_correlation_distance_f32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		memcpy(tmpap, inpA, sizeof(f32) * vecDim);
		memcpy(tmpbp, inpB, sizeof(f32) * vecDim);

		*outp = mips_correlation_distance_f32(tmpap, tmpbp, vecDim);

		inpA += vecDim;
		inpB += vecDim;
		outp++;
	}
	printf("mips_correlation_distance_f32 finish \n");

	printf("mips_correlation_distance_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF32, "Ref5_f32.txt");
#else
	referenceFile = DistanceF32_Ref5_f32;
	referenceFileLen = sizeof(DistanceF32_Ref5_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, (f32)1e-3);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)1e-3);
#endif

	printf("\n== mips_correlation_distance_f32 check done  == \n\n");

	// =====================

	inpA = f32inputA1;
	inpB = f32inputB1;

	outp = f32output1;

	printf("== mips_cosine_distance_f32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_cosine_distance_f32(inpA, inpB, vecDim);

		inpA += vecDim;
		inpB += vecDim;
		outp++;
	}

	printf("mips_cosine_distance_f32 finish \n");

	printf("mips_cosine_distance_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF32, "Ref6_f32.txt");
#else
	referenceFile = DistanceF32_Ref6_f32;
	referenceFileLen = sizeof(DistanceF32_Ref6_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, (f32)1e-3);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)1e-3);
#endif

	printf("\n== mips_cosine_distance_f32 check done  == \n\n");

	// =====================

	inpA = f32inputA1;
	inpB = f32inputB1;

	outp = f32output1;

	printf("== mips_euclidean_distance_f32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_euclidean_distance_f32(inpA, inpB, vecDim);

		inpA += vecDim;
		inpB += vecDim;
		outp++;
	}
	printf("mips_euclidean_distance_f32 finish \n");

	printf("mips_euclidean_distance_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF32, "Ref7_f32.txt");
#else
	referenceFile = DistanceF32_Ref7_f32;
	referenceFileLen = sizeof(DistanceF32_Ref7_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, (f32)1e-3);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)1e-3);
#endif

	printf("\n== mips_euclidean_distance_f32 check done  == \n\n");

	// =====================

	inpA = f32inputA8;
	inpB = f32inputB8;

	outp = f32output1;

	printf("== mips_jensenshannon_distance_f32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_jensenshannon_distance_f32(inpA, inpB, vecDim);

		inpA += vecDim;
		inpB += vecDim;
		outp++;
	}
	printf("mips_jensenshannon_distance_f32 finish \n");

	printf("mips_jensenshannon_distance_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF32, "Ref8_f32.txt");
#else
	referenceFile = DistanceF32_Ref8_f32;
	referenceFileLen = sizeof(DistanceF32_Ref8_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, (f32)1e-3);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)1e-3);
#endif

	printf("\n== mips_jensenshannon_distance_f32 check done  == \n\n");

	// =====================

	inpA = f32inputA1;
	inpB = f32inputB1;

	outp = f32output1;

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile, sizeof(dimsFile), "%s%s%s", Patterns_PATH, DistanceF32, "Dims9_s16.txt");
#else
	dimsFile = DistanceF32_Dims9_s16;
	dimsFileLen = sizeof(DistanceF32_Dims9_s16);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile, &paramCountDims, s16Dims);
#else
	paramCountDims = dimsFileLen;
	load_data_q15(dimsFile, paramCountDims, s16Dims);
	paramCountDims = paramCountDims/sizeof(q15);
#endif


	int16_t *dimsp = s16Dims;

	nbPatterns = dimsp[0];
	vecDim = dimsp[1];

	dimsp += 2;

	printf("== mips_minkowski_distance_f32 test ==  \n");

	for (int i = 0; i < nbPatterns; i++)
	{
		*outp = mips_minkowski_distance_f32(inpA, inpB, *dimsp, vecDim);

		inpA += vecDim;
		inpB += vecDim;
		outp++;
		dimsp++;
	}
	printf("mips_minkowski_distance_f32 finish \n");

	printf("mips_minkowski_distance_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF32, "Ref9_f32.txt");
#else
	referenceFile = DistanceF32_Ref9_f32;
	referenceFileLen = sizeof(DistanceF32_Ref9_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, (f32)1e-3);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)1e-3);
#endif

	printf("\n== mips_minkowski_distance_f32 check done  == \n\n");

	// =====================

#if defined(NOT_EMBEDDED)
	snprintf(inputFileA1, sizeof(inputFileA1), "%s%s%s", Patterns_PATH, DistanceF32, "Query10_f32.txt");
#else
	inputFileA1 = DistanceF32_Query10_f32;
	inputFileA1Len = sizeof(DistanceF32_Query10_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB1, sizeof(inputFileB1), "%s%s%s", Patterns_PATH, DistanceF32, "Template10_f32.txt");
#else
	inputFileB1 = DistanceF32_Template10_f32;
	inputFileB1Len = sizeof(DistanceF32_Template10_f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileA1, &paramCountInputA1, f32inputA1);
#else
	paramCountInputA1 = inputFileA1Len;
	load_data_f32(inputFileA1, paramCountInputA1, f32inputA1);
	paramCountInputA1 = paramCountInputA1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileB1, &paramCountInputB1, f32inputB1);
#else
	paramCountInputB1 = inputFileB1Len;
	load_data_f32(inputFileB1, paramCountInputB1, f32inputB1);
	paramCountInputB1 = paramCountInputB1/sizeof(f32);
#endif


	inpA = f32inputA1;
	inpB = f32inputB1;
	mips_matrix_instance_f32 distances;
	mips_matrix_instance_f32 costs;
	mips_matrix_instance_q7 window;

	nbPatterns = 1;
	queryLength = paramCountInputA1;
	templateLength = paramCountInputB1;

	distances.numRows = queryLength;
	distances.numCols = templateLength;
	distances.pData = tmpA;

	costs.numRows = queryLength;
	costs.numCols = templateLength;
	costs.pData = tmpB;

	window.numRows = queryLength;
	window.numCols = templateLength;
	window.pData = tmpC;

	outp = f32output1;
	int16_t *outPathp = outPath;
	uint32_t pathLength;

	printf("== mips_dtw_distance_f32 test ==  \n");
	for (int i = 0; i < nbPatterns; i++)
	{
		f32 *c = distances.pData;
		for (int q = 0; q < queryLength; q++)
		{
			for (int t = 0; t < templateLength; t++)
			{
				*c = fabs(inpA[q] - inpB[t]);
				c++;
			}
		}

		mips_status status = mips_dtw_distance_f32(&distances, NULL, &costs, outp);
		outp++;
		ASSERT_TRUE(status == MIPS_MATH_SUCCESS);

		mips_dtw_path_f32(&costs, outPathp, &pathLength);

		/* MIPS_DTW_SAKOE_CHIBA_WINDOW 5*/
		status = mips_dtw_init_window_q7(MIPS_DTW_SAKOE_CHIBA_WINDOW, 5, &window);
		ASSERT_TRUE(status == MIPS_MATH_SUCCESS);

		c = distances.pData;
		for (int q = 0; q < queryLength; q++)
		{
			for (int t = 0; t < templateLength; t++)
			{
				/* Distance does not have
				   to be computed outside of
				   the window */
				if (window.pData[q * templateLength + t])
				{
					*c = fabs(inpA[q] - inpB[t]);
				}
				c++;
			}
		}

		status = mips_dtw_distance_f32(&distances, &window, &costs, outp);
		ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
		outp++;

		/* MIPS_DTW_SAKOE_CHIBA_WINDOW 3 */
		status = mips_dtw_init_window_q7(MIPS_DTW_SAKOE_CHIBA_WINDOW, 3, &window);
		ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
		status = mips_dtw_distance_f32(&distances, &window, &costs, outp);
		ASSERT_TRUE(status == MIPS_MATH_ARGUMENT_ERROR);

		/* MIPS_DTW_SLANTED_BAND_WINDOW 1*/
		status = mips_dtw_init_window_q7(MIPS_DTW_SLANTED_BAND_WINDOW, 1, &window);
		ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
		/* Here again we could compute the distance matrix
		only on a subset */

		status = mips_dtw_distance_f32(&distances, &window, &costs, outp);
		ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
		outp++;

		inpA += queryLength;
		inpB += templateLength;
		outPathp += 2 * pathLength;
	}

	printf("mips_dtw_distance_f32 finish \n");

	printf("mips_dtw_distance_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF32, "DTWRef10_f32.txt");
#else
	referenceFile = DistanceF32_DTWRef10_f32;
	referenceFileLen = sizeof(DistanceF32_DTWRef10_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output1, 0, (f32)1e-3);
#else
	near_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)1e-3);
#endif

	
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, DistanceF32, "PathRef10_s16.txt");
#else
	referenceFile = DistanceF32_PathRef10_s16;
	referenceFileLen = sizeof(DistanceF32_PathRef10_s16);
	load_data_u16(referenceFile, referenceFileLen, referenceData_u16);
	referenceFileLen = referenceFileLen/sizeof(uint16_t);
#endif

	
#if defined(NOT_EMBEDDED)
	eq_check_u16(referenceFile, outPath, 0);
#else
	eq_check_special_u16(referenceData_u16, outPath, referenceFileLen);
#endif


	printf("\n== mips_dtw_distance_f32 check done  == \n\n");

	// =====================

	return 0;
}