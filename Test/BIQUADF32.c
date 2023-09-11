#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/filtering_functions.h"

#define SNR_THRESHOLD 98

/*

Reference patterns are generated with
a double precision computation.

*/
#define REL_ERROR (1.2e-3)

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

	float state[128] = {0};
	float f32output1[MAX_SIZE] = {0};

	// DF1_REF_1 and DF2T_REF_2

	// declare input value
	int paramCountInput1 = 0;
	int paramCountCoefs1 = 0;
	float f32inputs1[MAX_SIZE] = {0};
	float f32coefs1[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFile1[255] = {0};
#else
	void *inputFile1;
	int inputFile1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char coefsFile1[255] = {0};
#else
	void *coefsFile1;
	int coefsFile1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFile1[255] = {0};
#else
	void *referenceFile1;
	int referenceFile1Len = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, BIQUADF32, "BiquadInput1_f32.txt");
#else
	inputFile1 = BIQUADF32_BiquadInput1_f32;
	inputFile1Len = sizeof(BIQUADF32_BiquadInput1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(coefsFile1, sizeof(coefsFile1), "%s%s%s", Patterns_PATH, BIQUADF32, "BiquadCoefs1_f32.txt");
#else
	coefsFile1 = BIQUADF32_BiquadCoefs1_f32;
	coefsFile1Len = sizeof(BIQUADF32_BiquadCoefs1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, BIQUADF32, "BiquadOutput1_f32.txt");
#else
	referenceFile1 = BIQUADF32_BiquadOutput1_f32;
	referenceFile1Len = sizeof(BIQUADF32_BiquadOutput1_f32);
	load_data_f32(referenceFile1, referenceFile1Len, referenceData_f32);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile1, &paramCountInput1, f32inputs1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f32(inputFile1, paramCountInput1, f32inputs1);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(coefsFile1, &paramCountCoefs1, f32coefs1);
#else
	paramCountCoefs1 = coefsFile1Len;
	load_data_f32(coefsFile1, paramCountCoefs1, f32coefs1);
	paramCountCoefs1 = paramCountCoefs1/sizeof(f32);
#endif


	// =======test_biquad_cascade_df1_ref==============

	printf("== biquad_cascade_df1_ref test ==  \n");

	float debugstate[2 * 64] = {0};
	// pointers
	float *coefsp;
	coefsp = f32coefs1;
	float *statep;
	statep = state;
	float *inputp;
	inputp = f32inputs1;
	float *outp;
	outp = f32output1;
	float *debugstatep;
	debugstatep = debugstate;

	int blockSize;

	blockSize = paramCountInput1 >> 1;

	mips_biquad_casd_df1_inst_f32 Sdf1;
	mips_biquad_cascade_df1_init_f32(&Sdf1, 3, coefsp, statep);
	mips_biquad_cascade_df1_f32(&Sdf1, inputp, outp, blockSize);

	memcpy(debugstatep, statep, 3 * 4 * sizeof(float));
	debugstatep += 3 * 4;

	outp += blockSize;

	inputp += blockSize;
	mips_biquad_cascade_df1_f32(&Sdf1, inputp, outp, blockSize);
	outp += blockSize;

	memcpy(debugstatep, statep, 3 * 4 * sizeof(float));
	debugstatep += 3 * 4;

	printf("biquad_cascade_df1_ref finish \n");

	printf("biquad_cascade_df1_ref checking \n\n");

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile1, f32output1, paramCountInput1, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, paramCountInput1, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile1, f32output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountInput1, SNR_THRESHOLD);
#endif


	printf("\n== biquad_cascade_df1_ref check done  == \n\n");

	// =======test_biquad_cascade_df2T_ref==============

	printf("== _biquad_cascade_df2T_ref test ==  \n");

	float vecCoefs1[64] = {0};
	// pointers
	coefsp = f32coefs1;
	statep = state;
	inputp = f32inputs1;
	outp = f32output1;

	//    int blockSize;

	//    blockSize = paramCountInput1 >> 1;

	/*

The filter is initialized with the coefs, blockSize and numTaps.

*/
#if !defined(MIPS_MATH_NEON)
	mips_biquad_cascade_df2T_instance_f32 Sdf2T;
	mips_biquad_cascade_df2T_init_f32(&Sdf2T, 3, coefsp, statep);
#else
	float *vecCoefsPtr;
	vecCoefsPtr = vecCoefs1;

	// Those Neon coefs must be computed from original coefs
	mips_biquad_cascade_df2T_compute_coefs_f32(3, coefsp, vecCoefsPtr);

	mips_biquad_cascade_df2T_init_f32(&Sdf2T,
									  3,
									  vecCoefsPtr,
									  statep);
#endif

	/*

	Python script is filtering a 2*blockSize number of samples.
	We do the same filtering in two pass to check (indirectly that
	the state management of the fir is working.)

	*/

	mips_biquad_cascade_df2T_f32(&Sdf2T, inputp, outp, blockSize);
	outp += blockSize;

	inputp += blockSize;
	mips_biquad_cascade_df2T_f32(&Sdf2T, inputp, outp, blockSize);
	outp += blockSize;

	printf("_biquad_cascade_df2T_ref finish \n");

	printf("_biquad_cascade_df2T_ref checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile1, f32output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountInput1, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile1, f32output1, paramCountInput1, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, paramCountInput1, REL_ERROR);
#endif


	printf("\n== _biquad_cascade_df2T_ref check done  == \n\n");

	// DF1_RAND_3 and DF2T_RAND_4

	// declare input value
	int paramCountInput2 = 0;
	int paramCountCoefs2 = 0;
	int paramCountConfigs2 = 0;
	float f32inputs2[MAX_SIZE] = {0};
	float f32coefs2[MAX_SIZE] = {0};
	q15 s16configs2[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFile2[255] = {0};
#else
	void *inputFile2;
	int inputFile2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char coefsFile2[255] = {0};
#else
	void *coefsFile2;
	int coefsFile2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char configsFile2[255] = {0};
#else
	void *configsFile2;
	int configsFile2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFile2[255] = {0};
#else
	void *referenceFile2;
	int referenceFile2Len = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, BIQUADF32, "AllBiquadInputs2_f32.txt");
#else
	inputFile2 = BIQUADF32_AllBiquadInputs2_f32;
	inputFile2Len = sizeof(BIQUADF32_AllBiquadInputs2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(coefsFile2, sizeof(coefsFile2), "%s%s%s", Patterns_PATH, BIQUADF32, "AllBiquadCoefs2_f32.txt");
#else
	coefsFile2 = BIQUADF32_AllBiquadCoefs2_f32;
	coefsFile2Len = sizeof(BIQUADF32_AllBiquadCoefs2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(configsFile2, sizeof(configsFile2), "%s%s%s", Patterns_PATH, BIQUADF32, "AllBiquadConfigs2_s16.txt");
#else
	configsFile2 = BIQUADF32_AllBiquadConfigs2_s16;
	configsFile2Len = sizeof(BIQUADF32_AllBiquadConfigs2_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile2, sizeof(referenceFile2), "%s%s%s", Patterns_PATH, BIQUADF32, "AllBiquadRefs2_f32.txt");
#else
	referenceFile2 = BIQUADF32_AllBiquadRefs2_f32;
	referenceFile2Len = sizeof(BIQUADF32_AllBiquadRefs2_f32);
	load_data_f32(referenceFile2, referenceFile2Len, referenceData_f32);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile2, &paramCountInput2, f32inputs2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_f32(inputFile2, paramCountInput2, f32inputs2);
	paramCountInput2 = paramCountInput2/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(coefsFile2, &paramCountCoefs2, f32coefs2);
#else
	paramCountCoefs2 = coefsFile2Len;
	load_data_f32(coefsFile2, paramCountCoefs2, f32coefs2);
	paramCountCoefs2 = paramCountCoefs2/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(configsFile2, &paramCountConfigs2, s16configs2);
#else
	paramCountConfigs2 = configsFile2Len;
	load_data_q15(configsFile2, paramCountConfigs2, s16configs2);
	paramCountConfigs2 = paramCountConfigs2/sizeof(q15);
#endif


	// =======test_biquad_cascade_df1_rand==============

	printf("== biquad_cascade_df1_rand test ==  \n");

	int numStages;
	unsigned long i;
	// pointers
	int16_t *configsp;
	configsp = s16configs2;
	coefsp = f32coefs2;
	statep = state;
	inputp = f32inputs2;
	outp = f32output1;

	for (i = 0; i < paramCountConfigs2; i += 2)
	{
		/*

		Python script is generating different tests with
		different blockSize and numTaps.

		We loop on those configs.

		*/

		numStages = configsp[0];
		blockSize = configsp[1];

		configsp += 2;

		/*

		The filter is initialized with the coefs, blockSize and numTaps.

		*/
		mips_biquad_casd_df1_inst_f32 Sdf1;
		mips_biquad_cascade_df1_init_f32(&Sdf1, numStages, coefsp, statep);

		/*

		Python script is filtering a 2*blockSize number of samples.
		We do the same filtering in two pass to check (indirectly that
		the state management of the fir is working.)

		*/

		mips_biquad_cascade_df1_f32(&Sdf1, inputp, outp, blockSize);

		inputp += blockSize;
		outp += blockSize;
		coefsp += numStages * 5;
	}

	printf("biquad_cascade_df1_rand finish \n");

	printf("biquad_cascade_df1_rand checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile2, f32output1, paramCountInput2, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountInput2, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile2, f32output1, paramCountInput2, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, paramCountInput2, REL_ERROR);
#endif


	printf("\n== biquad_cascade_df1_rand check done  == \n\n");

	// =======test_biquad_cascade_df2T_rand==============

	printf("== biquad_cascade_df2T_rand test ==  \n");
	float vecCoefs2[512] = {0};
	// pointers
	configsp = s16configs2;
	coefsp = f32coefs2;
	statep = state;
	inputp = f32inputs2;
	outp = f32output1;

	for (i = 0; i < paramCountConfigs2; i += 2)
	{

		/*

		Python script is generating different tests with
		different blockSize and numTaps.

		We loop on those configs.

		*/

		numStages = configsp[0];
		blockSize = configsp[1];

		configsp += 2;

		/*

		The filter is initialized with the coefs, blockSize and numTaps.

		*/
#if !defined(MIPS_MATH_NEON)
		mips_biquad_cascade_df2T_instance_f32 Sdf2T;
		mips_biquad_cascade_df2T_init_f32(&Sdf2T, numStages, coefsp, statep);
#else
		float *vecCoefsPtr;
		vecCoefsPtr = vecCoefs2;

		// Those Neon coefs must be computed from original coefs
		mips_biquad_cascade_df2T_compute_coefs_f32(numStages, coefsp, vecCoefsPtr);

		mips_biquad_cascade_df2T_init_f32(&Sdf2T,
										  numStages,
										  vecCoefsPtr,
										  statep);
#endif
		coefsp += numStages * 5;

		/*

		Python script is filtering a 2*blockSize number of samples.
		We do the same filtering in two pass to check (indirectly that
		the state management of the fir is working.)

		*/

		mips_biquad_cascade_df2T_f32(&Sdf2T, inputp, outp, blockSize);
		outp += blockSize;
		inputp += blockSize;
	}
	printf("biquad_cascade_df2T_rand finish \n");

	printf("biquad_cascade_df2T_rand checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile2, f32output1, paramCountInput2, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountInput2, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile2, f32output1, paramCountInput2, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, paramCountInput2, REL_ERROR);
#endif


	printf("\n== biquad_cascade_df2T_rand check done  == \n\n");

	// biquad_cascade_stereo_df2T

	// declare input value
	int paramCountInput3 = 0;
	float f32inputs3[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFile3[255] = {0};
#else
	void *inputFile3;
	int inputFile3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFile3[255] = {0};
#else
	void *referenceFile3;
	int referenceFile3Len = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, BIQUADF32, "AllBiquadStereoInputs2_f32.txt");
#else
	inputFile3 = BIQUADF32_AllBiquadStereoInputs2_f32;
	inputFile3Len = sizeof(BIQUADF32_AllBiquadStereoInputs2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile3, sizeof(referenceFile3), "%s%s%s", Patterns_PATH, BIQUADF32, "AllBiquadStereoRefs2_f32.txt");
#else
	referenceFile3 = BIQUADF32_AllBiquadStereoRefs2_f32;
	referenceFile3Len = sizeof(BIQUADF32_AllBiquadStereoRefs2_f32);
	load_data_f32(referenceFile3, referenceFile3Len, referenceData_f32);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile3, &paramCountInput3, f32inputs3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_f32(inputFile3, paramCountInput3, f32inputs3);
	paramCountInput3 = paramCountInput3/sizeof(f32);
#endif

	// =======test_biquad_cascade_stereo_df2T_rand==============

	printf("== biquad_cascade_stereo_df2T_rand test ==  \n");
	// pointers
	configsp = s16configs2;
	coefsp = f32coefs2;
	statep = state;
	outp = f32output1;
	inputp = f32inputs3;

	for (i = 0; i < paramCountConfigs2; i += 2)
	{

		/*

		Python script is generating different tests with
		different blockSize and numTaps.

		We loop on those configs.

		*/

		numStages = configsp[0];
		blockSize = configsp[1];

		configsp += 2;

		/*

		The filter is initialized with the coefs, blockSize and numTaps.

		*/
		mips_biquad_cascade_stereo_df2T_instance_f32 SStereodf2T;
		mips_biquad_cascade_stereo_df2T_init_f32(&SStereodf2T, numStages, coefsp, statep);

		coefsp += numStages * 5;

		/*

		Python script is filtering a 2*blockSize number of samples.
		We do the same filtering in two pass to check (indirectly that
		the state management of the fir is working.)

		*/

		mips_biquad_cascade_stereo_df2T_f32(&SStereodf2T, inputp, outp, blockSize);
		outp += 2 * blockSize;
		inputp += 2 * blockSize;
	}
	printf("biquad_cascade_stereo_df2T_rand finish \n");

	printf("biquad_cascade_stereo_df2T_rand checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile3, f32output1, paramCountInput3, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountInput3, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile3, f32output1, paramCountInput3, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, paramCountInput3, REL_ERROR);
#endif


	printf("\n== biquad_cascade_stereo_df2T_rand check done  == \n\n");

	// =====================

	return 0;
}