#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/svm_functions.h"

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

    int paramCountInputa1 = 0;
	int paramCountInputa2 = 0;
	int paramCountInputa3 = 0;
	int paramCountInputa4 = 0;

    int paramCountInputb1 = 0;
	int paramCountInputb2 = 0;
	int paramCountInputb3 = 0;
	int paramCountInputb4 = 0;


    int paramCountInputc1 = 0;
	int paramCountInputc2 = 0;
	int paramCountInputc3 = 0;
	int paramCountInputc4 = 0;

	float f32inputa1[MAX_SIZE] = {0};
	float f32inputa2[MAX_SIZE] = {0};
	float f32inputa3[MAX_SIZE] = {0};
	float f32inputa4[MAX_SIZE] = {0};

	float f32inputb1[MAX_SIZE] = {0};
	float f32inputb2[MAX_SIZE] = {0};
	float f32inputb3[MAX_SIZE] = {0};
	float f32inputb4[MAX_SIZE] = {0};

	float f32inputc1[MAX_SIZE] = {0};
	float f32inputc2[MAX_SIZE] = {0};
	float f32inputc3[MAX_SIZE] = {0};
	float f32inputc4[MAX_SIZE] = {0};


	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFilea1[255] = {0};
#else
	void *inputFilea1;
	int inputFilea1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFilea2[255] = {0};
#else
	void *inputFilea2;
	int inputFilea2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFilea3[255] = {0};
#else
	void *inputFilea3;
	int inputFilea3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFilea4[255] = {0};
#else
	void *inputFilea4;
	int inputFilea4Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char inputFileb1[255] = {0};
#else
	void *inputFileb1;
	int inputFileb1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileb2[255] = {0};
#else
	void *inputFileb2;
	int inputFileb2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileb3[255] = {0};
#else
	void *inputFileb3;
	int inputFileb3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileb4[255] = {0};
#else
	void *inputFileb4;
	int inputFileb4Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char inputFilec1[255] = {0};
#else
	void *inputFilec1;
	int inputFilec1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFilec2[255] = {0};
#else
	void *inputFilec2;
	int inputFilec2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFilec3[255] = {0};
#else
	void *inputFilec3;
	int inputFilec3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFilec4[255] = {0};
#else
	void *inputFilec4;
	int inputFilec4Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char referenceFile[255] = {0};
#else
	void *referenceFile;
	int referenceFileLen = 0;
#endif

    float f32output[MAX_SIZE] = {0};

	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFilea1, sizeof(inputFilea1), "%s%s%s", Patterns_PATH, SVMF32, "Samples1_f32.txt");
#else
	inputFilea1 = SVMF32_Samples1_f32;
	inputFilea1Len = sizeof(SVMF32_Samples1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea2, sizeof(inputFilea2), "%s%s%s", Patterns_PATH, SVMF32, "Samples2_f32.txt");
#else
	inputFilea2 = SVMF32_Samples2_f32;
	inputFilea2Len = sizeof(SVMF32_Samples2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea3, sizeof(inputFilea3), "%s%s%s", Patterns_PATH, SVMF32, "Samples3_f32.txt");
#else
	inputFilea3 = SVMF32_Samples3_f32;
	inputFilea3Len = sizeof(SVMF32_Samples3_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea4, sizeof(inputFilea4), "%s%s%s", Patterns_PATH, SVMF32, "Samples4_f32.txt");
#else
	inputFilea4 = SVMF32_Samples4_f32;
	inputFilea4Len = sizeof(SVMF32_Samples4_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFileb1, sizeof(inputFileb1), "%s%s%s", Patterns_PATH, SVMF32, "Params1_f32.txt");
#else
	inputFileb1 = SVMF32_Params1_f32;
	inputFileb1Len = sizeof(SVMF32_Params1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb2, sizeof(inputFileb2), "%s%s%s", Patterns_PATH, SVMF32, "Params2_f32.txt");
#else
	inputFileb2 = SVMF32_Params2_f32;
	inputFileb2Len = sizeof(SVMF32_Params2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb3, sizeof(inputFileb3), "%s%s%s", Patterns_PATH, SVMF32, "Params3_f32.txt");
#else
	inputFileb3 = SVMF32_Params3_f32;
	inputFileb3Len = sizeof(SVMF32_Params3_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb4, sizeof(inputFileb4), "%s%s%s", Patterns_PATH, SVMF32, "Params4_f32.txt");
#else
	inputFileb4 = SVMF32_Params4_f32;
	inputFileb4Len = sizeof(SVMF32_Params4_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFilec1, sizeof(inputFilec1), "%s%s%s", Patterns_PATH, SVMF32, "Dims1_s16.txt");
#else
	inputFilec1 = SVMF32_Dims1_s16;
	inputFilec1Len = sizeof(SVMF32_Dims1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFilec2, sizeof(inputFilec2), "%s%s%s", Patterns_PATH, SVMF32, "Dims2_s16.txt");
#else
	inputFilec2 = SVMF32_Dims2_s16;
	inputFilec2Len = sizeof(SVMF32_Dims2_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFilec3, sizeof(inputFilec3), "%s%s%s", Patterns_PATH, SVMF32, "Dims3_s16.txt");
#else
	inputFilec3 = SVMF32_Dims3_s16;
	inputFilec3Len = sizeof(SVMF32_Dims3_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFilec4, sizeof(inputFilec4), "%s%s%s", Patterns_PATH, SVMF32, "Dims4_s16.txt");
#else
	inputFilec4 = SVMF32_Dims4_s16;
	inputFilec4Len = sizeof(SVMF32_Dims4_s16);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, SVMF32, "Reference1_s32.txt");
#else
	referenceFile = SVMF32_Reference1_s32;
	referenceFileLen = sizeof(SVMF32_Reference1_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFilea1, &paramCountInputa1, f32inputa1);
#else
	paramCountInputa1 = inputFilea1Len;
	load_data_f32(inputFilea1, paramCountInputa1, f32inputa1);
	paramCountInputa1 = paramCountInputa1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFilea2, &paramCountInputa2, f32inputa2);
#else
	paramCountInputa2 = inputFilea2Len;
	load_data_f32(inputFilea2, paramCountInputa2, f32inputa2);
	paramCountInputa2 = paramCountInputa2/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFilea3, &paramCountInputa3, f32inputa3);
#else
	paramCountInputa3 = inputFilea3Len;
	load_data_f32(inputFilea3, paramCountInputa3, f32inputa3);
	paramCountInputa3 = paramCountInputa3/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFilea4, &paramCountInputa4, f32inputa4);
#else
	paramCountInputa4 = inputFilea4Len;
	load_data_f32(inputFilea4, paramCountInputa4, f32inputa4);
	paramCountInputa4 = paramCountInputa4/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileb1, &paramCountInputb1, f32inputb1);
#else
	paramCountInputb1 = inputFileb1Len;
	load_data_f32(inputFileb1, paramCountInputb1, f32inputb1);
	paramCountInputb1 = paramCountInputb1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileb2, &paramCountInputb2, f32inputb2);
#else
	paramCountInputb2 = inputFileb2Len;
	load_data_f32(inputFileb2, paramCountInputb2, f32inputb2);
	paramCountInputb2 = paramCountInputb2/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileb3, &paramCountInputb3, f32inputb3);
#else
	paramCountInputb3 = inputFileb3Len;
	load_data_f32(inputFileb3, paramCountInputb3, f32inputb3);
	paramCountInputb3 = paramCountInputb3/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileb4, &paramCountInputb4, f32inputb4);
#else
	paramCountInputb4 = inputFileb4Len;
	load_data_f32(inputFileb4, paramCountInputb4, f32inputb4);
	paramCountInputb4 = paramCountInputb4/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(inputFilec1, &paramCountInputc1, f32inputc1);
#else
	paramCountInputc1 = inputFilec1Len;
	load_data_q15(inputFilec1, paramCountInputc1, f32inputc1);
	paramCountInputc1 = paramCountInputc1/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFilec2, &paramCountInputc2, f32inputc2);
#else
	paramCountInputc2 = inputFilec2Len;
	load_data_q15(inputFilec2, paramCountInputc2, f32inputc2);
	paramCountInputc2 = paramCountInputc2/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFilec3, &paramCountInputc3, f32inputc3);
#else
	paramCountInputc3 = inputFilec3Len;
	load_data_q15(inputFilec3, paramCountInputc3, f32inputc3);
	paramCountInputc3 = paramCountInputc3/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFilec4, &paramCountInputc4, f32inputc4);
#else
	paramCountInputc4 = inputFilec4Len;
	load_data_q15(inputFilec4, paramCountInputc4, f32inputc4);
	paramCountInputc4 = paramCountInputc4/sizeof(q15);
#endif





    f32 *inp = f32inputa1;
    int32_t *outp = f32output;
    int32_t *result = outp;
    int vecDim,nbSupportVectors,nbTestSamples,degree;
    int32_t classes[2]={0,0};
    f32 intercept;
    const f32 *supportVectors;
    const f32 *dualCoefs;
    f32 coef0, gamma;

      const int16_t   *dimsp = f32inputc1;
      const f32  *paramsp = f32inputb1;
      
      int kind;
      kind = dimsp[0];
      
      classes[0] = dimsp[1];
      classes[1] = dimsp[2];
      nbTestSamples=dimsp[3];
      vecDim = dimsp[4];
      nbSupportVectors = dimsp[5];
      intercept=paramsp[vecDim*nbSupportVectors + nbSupportVectors];
      supportVectors=paramsp;
      dualCoefs=paramsp + (vecDim*nbSupportVectors);

        mips_svm_linear_instance_f32 linear;

        mips_svm_linear_init_f32(&linear, 
            nbSupportVectors,
            vecDim,
            intercept,
            dualCoefs,
            supportVectors,
            classes);
    



      for(int i =0; i < nbTestSamples; i++)
      {
         mips_svm_linear_predict_f32(&linear,inp,result);
         result++;
         inp += vecDim;
      }
    printf("%x\n", *outp);
#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFile, outp, 1);
#else
	eq_check_special_u32(referenceData_u32, outp, 1);
#endif



//=======
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, SVMF32, "Reference2_s32.txt");
#else
	referenceFile = SVMF32_Reference2_s32;
	referenceFileLen = sizeof(SVMF32_Reference2_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif

    inp = f32inputa2;
    outp = f32output;
    result = outp;


      dimsp = f32inputc2;
      paramsp = f32inputb2;
      classes[0] = dimsp[1];
      classes[1] = dimsp[2];
      nbTestSamples=dimsp[3];
      vecDim = dimsp[4];
      nbSupportVectors = dimsp[5];
      intercept=paramsp[vecDim*nbSupportVectors + nbSupportVectors];
      supportVectors=paramsp;
      dualCoefs=paramsp + (vecDim*nbSupportVectors);
             degree = dimsp[6];
             coef0 =paramsp[vecDim*nbSupportVectors + nbSupportVectors + 1] ;
             gamma=paramsp[vecDim*nbSupportVectors + nbSupportVectors + 2];      
                  mips_svm_polynomial_instance_f32 poly;
                    mips_svm_polynomial_init_f32(&poly, 
                  nbSupportVectors,
                  vecDim,
                  intercept,
                  dualCoefs,
                  supportVectors,
                  classes,
                  degree,
                  coef0,
                  gamma
                 );
    
    for(int i =0; i < nbTestSamples; i++)
      {
         mips_svm_polynomial_predict_f32(&poly,inp,result);
         result++;
         inp += vecDim;
      }
    printf("%x\n", *outp);
#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFile, outp, 1);
#else
	eq_check_special_u32(referenceData_u32, outp, 1);
#endif



//=======
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, SVMF32, "Reference3_s32.txt");
#else
	referenceFile = SVMF32_Reference3_s32;
	referenceFileLen = sizeof(SVMF32_Reference3_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif

    inp = f32inputa3;
    outp = f32output;
    result = outp;


      dimsp = f32inputc3;
      paramsp = f32inputb3;
      classes[0] = dimsp[1];
      classes[1] = dimsp[2];
      nbTestSamples=dimsp[3];
      vecDim = dimsp[4];
      nbSupportVectors = dimsp[5];
      intercept=paramsp[vecDim*nbSupportVectors + nbSupportVectors];
      supportVectors=paramsp;
      dualCoefs=paramsp + (vecDim*nbSupportVectors);
        gamma=paramsp[vecDim*nbSupportVectors + nbSupportVectors + 1];
            mips_svm_rbf_instance_f32 rbf;
            mips_svm_rbf_init_f32(&rbf, 
                 nbSupportVectors,
                 vecDim,
                 intercept,
                 dualCoefs,
                 supportVectors,
                 classes,
                 gamma
                 );
      for(int i =0; i < nbTestSamples; i++)
      {
         mips_svm_rbf_predict_f32(&rbf,inp,result);
         result++;
         inp += vecDim;
      }
    printf("%x\n", *outp);
#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFile, outp, 1);
#else
	eq_check_special_u32(referenceData_u32, outp, 1);
#endif



//=======
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, SVMF32, "Reference4_s32.txt");
#else
	referenceFile = SVMF32_Reference4_s32;
	referenceFileLen = sizeof(SVMF32_Reference4_s32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
#endif

    inp = f32inputa4;
    outp = f32output;
    result = outp;


      dimsp = f32inputc4;
      paramsp = f32inputb4;
      classes[0] = dimsp[1];
      classes[1] = dimsp[2];
      nbTestSamples=dimsp[3];
      vecDim = dimsp[4];
      nbSupportVectors = dimsp[5];
      intercept=paramsp[vecDim*nbSupportVectors + nbSupportVectors];
      supportVectors=paramsp;
      dualCoefs=paramsp + (vecDim*nbSupportVectors);
             coef0 =paramsp[vecDim*nbSupportVectors + nbSupportVectors + 1] ;
             gamma=paramsp[vecDim*nbSupportVectors + nbSupportVectors + 2];
            mips_svm_sigmoid_instance_f32 sigmoid;
             mips_svm_sigmoid_init_f32(&sigmoid, 
                 nbSupportVectors,
                 vecDim,
                 intercept,
                 dualCoefs,
                 supportVectors,
                 classes,
                 coef0,
                 gamma
                 );
    for(int i =0; i < nbTestSamples; i++)
      {
         mips_svm_sigmoid_predict_f32(&sigmoid,inp,result);
         result++;
         inp += vecDim;
      }
    printf("%x\n", *outp);
#if defined(NOT_EMBEDDED)
	eq_check_f32(referenceFile, outp, 1);
#else
	eq_check_special_f32(referenceData_f32, outp, 1);
#endif

      return 0;
}
