#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/support_functions.h"
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
	int paramCountInput = 0;
    int paramCountweights = 0;
    int paramCountdims = 0;

	float f32input[MAX_SIZE] = {0};
    float f32weights[MAX_SIZE] = {0};
    q15 f32dims[MAX_SIZE] = {0};


	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFile[255] = {0};
#else
	void *inputFile;
	int inputFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char weightsFile[255] = {0};
#else
	void *weightsFile;
	int weightsFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFile[255] = {0};
#else
	void *referenceFile;
	int referenceFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char dimsFile[255] = {0};
#else
	void *dimsFile;
	int dimsFileLen = 0;
#endif



	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile, sizeof(inputFile), "%s%s%s", Patterns_PATH, SupportBarF32, "Inputs1_f32.txt");
#else
	inputFile = SupportBarF32_Inputs1_f32;
	inputFileLen = sizeof(SupportBarF32_Inputs1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(weightsFile, sizeof(weightsFile), "%s%s%s", Patterns_PATH, SupportBarF32, "Weights1_f32.txt");
#else
	weightsFile = SupportBarF32_Weights1_f32;
	weightsFileLen = sizeof(SupportBarF32_Weights1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, SupportBarF32, "Ref1_f32.txt");
#else
	referenceFile = SupportBarF32_Ref1_f32;
	referenceFileLen = sizeof(SupportBarF32_Ref1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile, sizeof(dimsFile), "%s%s%s", Patterns_PATH, SupportBarF32, "Dims1_s16.txt");
#else
	dimsFile = SupportBarF32_Dims1_s16;
	dimsFileLen = sizeof(SupportBarF32_Dims1_s16);
#endif

	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile, &paramCountInput, f32input);
#else
	paramCountInput = inputFileLen;
	load_data_f32(inputFile, paramCountInput, f32input);
	paramCountInput = paramCountInput/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(weightsFile, &paramCountweights, f32weights);
#else
	paramCountweights = weightsFileLen;
	load_data_f32(weightsFile, paramCountweights, f32weights);
	paramCountweights = paramCountweights/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile, &paramCountdims, f32dims);
#else
	paramCountdims = dimsFileLen;
	load_data_q15(dimsFile, paramCountdims, f32dims);
	paramCountdims = paramCountdims/sizeof(q15);
#endif

	float f32output[MAX_SIZE] = {0};

	printf("== mips_barycenter_f32 test ==  \n");

    int nbVecs,vecDim;
    const float *inp;
    inp = f32input;
    const float *coefsp;
    coefsp = f32weights;
    float *outp;
    outp = f32output;

    for(int i=0; i < f32dims[0]; i ++)
       {
          nbVecs = f32dims[2*i+1];
          vecDim = f32dims[2*i+2];

          mips_barycenter_f32(inp, coefsp, outp, nbVecs, vecDim);
          inp += vecDim * nbVecs;
          coefsp += nbVecs;
          outp += vecDim;
       }

	printf("mips_barycenter_f32 finish \n");

	printf("mips_barycenter_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_f32(referenceFile, f32output, 0, (float)1e-3);
#else
	near_check_special_f32(referenceData_f32, f32output, referenceFileLen, (float)1e-3);
#endif


	printf("\n== mips_barycenter_f32 check done  == \n\n");
}