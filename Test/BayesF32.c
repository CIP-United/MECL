#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/bayes_functions.h"

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
	int paramCountParam = 0;
	int paramCountPronas = 0;
	int paramCountDims = 0;
	int paramCountPredict = 0;
	float f32input1[MAX_SIZE] = {0};
	float f32Param[MAX_SIZE] = {0};
	float f32Probas[MAX_SIZE] = {0};
	q15 s16Dims[MAX_SIZE] = {0};
	q15 s16Predict[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFile1[255] = {0};
#else
	void *inputFile1;
	int inputFile1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char paramFile[255] = {0};
#else
	void *paramFile;
	int paramFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char probasFile[255] = {0};
#else
	void *probasFile;
	int probasFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char dimsFile[255] = {0};
#else
	void *dimsFile;
	int dimsFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char predictFile[255] = {0};
#else
	void *predictFile;
	int predictFileLen = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, BayesF32, "Inputs1_f32.txt");
#else
	inputFile1 = BayesF32_Inputs1_f32;
	inputFile1Len = sizeof(BayesF32_Inputs1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(paramFile, sizeof(paramFile), "%s%s%s", Patterns_PATH, BayesF32, "Params1_f32.txt");
#else
	paramFile = BayesF32_Params1_f32;
	paramFileLen = sizeof(BayesF32_Params1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(probasFile, sizeof(probasFile), "%s%s%s", Patterns_PATH, BayesF32, "Probas1_f32.txt");
#else
	probasFile = BayesF32_Probas1_f32;
	probasFileLen = sizeof(BayesF32_Probas1_f32);
	load_data_f32(probasFile, probasFileLen, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile, sizeof(dimsFile), "%s%s%s", Patterns_PATH, BayesF32, "Dims1_s16.txt");
#else
	dimsFile = BayesF32_Dims1_s16;
	dimsFileLen = sizeof(BayesF32_Dims1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(predictFile, sizeof(predictFile), "%s%s%s", Patterns_PATH, BayesF32, "Predicts1_s16.txt");
#else
	predictFile = BayesF32_Predicts1_s16;
	predictFileLen = sizeof(BayesF32_Predicts1_s16);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile1, &paramCountInput1, f32input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f32(inputFile1, paramCountInput1, f32input1);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(paramFile, &paramCountParam, f32Param);
#else
	paramCountParam = paramFileLen;
	load_data_f32(paramFile, paramCountParam, f32Param);
	paramCountParam = paramCountParam/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile, &paramCountDims, s16Dims);
#else
	paramCountDims = dimsFileLen;
	load_data_q15(dimsFile, paramCountDims, s16Dims);
	paramCountDims = paramCountDims/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(predictFile, &paramCountPredict, s16Predict);
#else
	paramCountPredict = predictFileLen;
	load_data_q15(predictFile, paramCountPredict, s16Predict);
	paramCountPredict = paramCountPredict/sizeof(q15);
#endif

	
	mips_gaussian_naive_bayes_instance_f32 bayes = {0};
	float f32outProbas[MAX_SIZE] = {0};
	float f32outBuffer = 0.f;
	int16_t f32outputRes[MAX_SIZE] = {0};
	q15 s16output1[MAX_SIZE] = {0};

	int nbPatterns, classNb, vecDim;
	nbPatterns = s16Dims[0];
	classNb = s16Dims[1];
	vecDim = s16Dims[2];

	bayes.vectorDimension = vecDim;
	bayes.numberOfClasses = classNb;
	bayes.theta = f32Param;
	bayes.sigma = f32Param + (classNb * vecDim);
	bayes.classPriors = f32Param + 2 * (classNb * vecDim);
	bayes.epsilon = f32Param[classNb + 2 * (classNb * vecDim)];

	printf("== mips_gaussian_naive_bayes_predict_f32 test ==  \n");

	int16_t *p = f32outputRes;
	float *inp = f32input1;
	float *bufp = f32outProbas;
	for (size_t i = 0; i < nbPatterns; i++)
	{
		*p = mips_gaussian_naive_bayes_predict_f32(&bayes, inp, bufp, &f32outBuffer);
		inp += vecDim;
		bufp += classNb;
		p++;
	}

	printf("mips_gaussian_naive_bayes_predict_f32 finish \n");

	printf("mips_gaussian_naive_bayes_predict_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	rel_check_f32(probasFile, f32outProbas, 0, (f32)5e-6);
#else
	rel_check_special_f32(referenceData_f32, f32outProbas, probasFileLen, (f32)5e-6);
#endif

#if defined(NOT_EMBEDDED)
	eq_check_q15(predictFile, f32outputRes, 0);
#else
	eq_check_special_q15(s16Predict, f32outputRes, paramCountPredict);
#endif


	printf("\n== mips_gaussian_naive_bayes_predict_f32 check done  == \n\n");

// =====================

	return 0;

}