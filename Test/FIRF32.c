#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/filtering_functions.h"


#define SNR_THRESHOLD 120
#define REL_ERROR (3.0e-5)

#if defined(MIPS_MATH_MSA)
static __ALIGNED(8) float coeffArray[32];
#endif 

static void checkInnerTail(float *b)
{
    ASSERT_TRUE(b[0] == 0.0f);
    ASSERT_TRUE(b[1] == 0.0f);
    ASSERT_TRUE(b[2] == 0.0f);
    ASSERT_TRUE(b[3] == 0.0f);
}

// Coef must be padded to a multiple of 4
#define FIRCOEFPADDING 2

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
	int paramCountCoefs1 = 0;
	int paramCountConfig1 = 0;
	float f32input1[MAX_SIZE] = {0};
	float f32coefs1[MAX_SIZE] = {0};
    int16_t s16config1[MAX_SIZE] = {0};

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
	char configsFile1[255] = {0};
#else
	void *configsFile1;
	int configsFile1Len = 0;
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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, FIRF32, "FirInput1_f32.txt");
#else
	inputFile1 = FIRF32_FirInput1_f32;
	inputFile1Len = sizeof(FIRF32_FirInput1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(coefsFile1, sizeof(coefsFile1), "%s%s%s", Patterns_PATH, FIRF32, "FirCoefs1_f32.txt");
#else
	coefsFile1 = FIRF32_FirCoefs1_f32;
	coefsFile1Len = sizeof(FIRF32_FirCoefs1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(configsFile1, sizeof(configsFile1), "%s%s%s", Patterns_PATH, FIRF32, "FirConfigs1_s16.txt");
#else
	configsFile1 = FIRF32_FirConfigs1_s16;
	configsFile1Len = sizeof(FIRF32_FirConfigs1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FIRF32, "FirRefs1_f32.txt");
#else
	referenceFile = FIRF32_FirRefs1_f32;
	referenceFileLen = sizeof(FIRF32_FirRefs1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
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
	load_data_f32(coefsFile1, &paramCountCoefs1, f32coefs1);
#else
	paramCountCoefs1 = coefsFile1Len;
	load_data_f32(coefsFile1, paramCountCoefs1, f32coefs1);
	paramCountCoefs1 = paramCountCoefs1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(configsFile1, &paramCountConfig1, s16config1);
#else
	paramCountConfig1 = configsFile1Len;
	load_data_q15(configsFile1, paramCountConfig1, s16config1);
	paramCountConfig1 = paramCountConfig1/sizeof(q15);
#endif


	const float *coefsp;

	float state[47+47] = {0};
	float f32output1[MAX_SIZE] = {0};

    float *pstate;
    pstate = state;
    float *pf32output1;
    pf32output1 = f32output1;
    float *pf32input1;

    float *pf32coefs1;
    pf32coefs1 = f32coefs1;
    int16_t *ps16config1;
    ps16config1 = s16config1;
    

    printf("== mips_fir_f32 test ==  \n");

    unsigned long i;
#if defined(MIPS_MATH_MSA)
    int j;
#endif
    int blockSize;
    int numTaps;
#if defined(MIPS_MATH_MSA)
    int round;
#endif
		/*

        Python script is generating different tests with
        different blockSize and numTaps.

        We loop on those configs.

        */
        for(i=0; i < paramCountConfig1 ; i += 2)
        {
           blockSize = ps16config1[0];
           numTaps = ps16config1[1];

#if defined(MIPS_MATH_MSA)
           /* Copy coefficients and pad to zero 
           */
           memset(coeffArray,127,32*sizeof(f32));
           round = numTaps >> FIRCOEFPADDING;
           if ((round << FIRCOEFPADDING) < numTaps)
           {
             round ++;
           }
           round = round<<FIRCOEFPADDING;
           memset(coeffArray,0,round*sizeof(f32));

           //printf("blockSize=%d, numTaps=%d, round=%d (%d)\n",blockSize,numTaps,round,round - numTaps);


           for(j=0;j < numTaps; j++)
           {
              coeffArray[j] = pf32coefs1[j];
           }
   
           coefsp = coeffArray;
#else
           coefsp = pf32coefs1;
#endif
           /*

           The filter is initialized with the coefs, blockSize and numTaps.

           */

           mips_fir_instance_f32 S;
           mips_fir_init_f32(&S,numTaps,coefsp,pstate,blockSize);

           /*
           
           Python script is filtering a 2*blockSize number of samples.
           We do the same filtering in two pass to check (indirectly that
           the state management of the fir is working.)

           */
           pf32input1 = f32input1;

           mips_fir_f32(&S,pf32input1,pf32output1,blockSize);


           pf32output1 += blockSize;
           checkInnerTail(pf32output1);
           
           pf32input1 += blockSize;
           mips_fir_f32(&S,pf32input1,pf32output1,blockSize);
           pf32output1 += blockSize;
           checkInnerTail(pf32output1);

           ps16config1 += 2;
           pf32coefs1 += numTaps;

		}
        printf("mips_fir_f32 finish \n");


       	printf("mips_fir_f32 checking \n\n");
	#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountInput1, SNR_THRESHOLD);
#endif

	#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile, f32output1, paramCountInput1, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output1, paramCountInput1, REL_ERROR);
#endif


		printf("\n== mips_fir_f32 check done  == \n\n");

	// for (size_t i = 0; i < paramCountInput1; i++)
	// {
	// 	printf("mips_fir_f32 output = %f \n", f32output1[i]);
	// }
	

	return 0;

}