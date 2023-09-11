#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/filtering_functions.h"


#define SNR_THRESHOLD 100

#define ABS_ERROR_Q31 ((q31)2)

#if defined(MIPS_MATH_MSA)
static __ALIGNED(8) q31 coeffArray[32];
#endif 

static void checkInnerTail(q31 *b)
{
    ASSERT_TRUE(b[0] == 0);
    ASSERT_TRUE(b[1] == 0);
    ASSERT_TRUE(b[2] == 0);
    ASSERT_TRUE(b[3] == 0);
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
	q31 q31input1[MAX_SIZE] = {0};
	q31 q31coefs1[MAX_SIZE] = {0};
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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, FIRQ31, "FirInput1_q31.txt");
#else
	inputFile1 = FIRQ31_FirInput1_q31;
	inputFile1Len = sizeof(FIRQ31_FirInput1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(coefsFile1, sizeof(coefsFile1), "%s%s%s", Patterns_PATH, FIRQ31, "FirCoefs1_q31.txt");
#else
	coefsFile1 = FIRQ31_FirCoefs1_q31;
	coefsFile1Len = sizeof(FIRQ31_FirCoefs1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(configsFile1, sizeof(configsFile1), "%s%s%s", Patterns_PATH, FIRQ31, "FirConfigs1_s16.txt");
#else
	configsFile1 = FIRQ31_FirConfigs1_s16;
	configsFile1Len = sizeof(FIRQ31_FirConfigs1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FIRQ31, "FirRefs1_q31.txt");
#else
	referenceFile = FIRQ31_FirRefs1_q31;
	referenceFileLen = sizeof(FIRQ31_FirRefs1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile1, &paramCountInput1, q31input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q31(inputFile1, paramCountInput1, q31input1);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(coefsFile1, &paramCountCoefs1, q31coefs1);
#else
	paramCountCoefs1 = coefsFile1Len;
	load_data_q31(coefsFile1, paramCountCoefs1, q31coefs1);
	paramCountCoefs1 = paramCountCoefs1/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(configsFile1, &paramCountConfig1, s16config1);
#else
	paramCountConfig1 = configsFile1Len;
	load_data_q15(configsFile1, paramCountConfig1, s16config1);
	paramCountConfig1 = paramCountConfig1/sizeof(q15);
#endif


	const q31 *coefsp;

	q31 state[47 + 47+47] = {0};
	q31 q31output1[MAX_SIZE] = {0};

    q31 *pstate;
    pstate = state;
    q31 *pq31output1;
    pq31output1 = q31output1;
    q31 *pq31input1;

    q31 *pq31coefs1;
    pq31coefs1 = q31coefs1;
    int16_t *ps16config1;
    ps16config1 = s16config1;
    

    printf("== mips_fir_q31 test ==  \n");

    unsigned long i;
#if defined(MIPS_MATH_MSA)
        int j;
        int round;
#endif
        int blockSize;
        int numTaps;
		/*

        Python script is generating different tests with
        different blockSize and numTaps.

        We loop on those configs.

        */
        for(i=0; i < paramCountConfig1; i += 2)
        {
           blockSize = ps16config1[0];
           numTaps = ps16config1[1];

#if defined(MIPS_MATH_MSA)
            /* Copy coefficients and pad to zero 
           */
           memset(coeffArray,127,32*sizeof(q31));
           round = numTaps >> FIRCOEFPADDING;
           if ((round << FIRCOEFPADDING) < numTaps)
           {
             round ++;
           }
           round = round<<FIRCOEFPADDING;
           memset(coeffArray,0,round*sizeof(q31));

           //printf("blockSize=%d, numTaps=%d, round=%d (%d)\n",blockSize,numTaps,round,round - numTaps);

           for(j=0;j < numTaps; j++)
           {
              coeffArray[j] = orgcoefsp[j];
           }
   
           coefsp = coeffArray;
#else
           coefsp = pq31coefs1;
#endif
           /*

           The filter is initialized with the coefs, blockSize and numTaps.

           */

           mips_fir_instance_q31 S;
           mips_fir_init_q31(&S,numTaps,coefsp,pstate,blockSize);

           /*
           
           Python script is filtering a 2*blockSize number of samples.
           We do the same filtering in two pass to check (indirectly that
           the state management of the fir is working.)

           */
           pq31input1 = q31input1;

           mips_fir_q31(&S,pq31input1,pq31output1,blockSize);
           pq31output1 += blockSize;
           checkInnerTail(pq31output1);
           
           pq31input1 += blockSize;
           mips_fir_q31(&S,pq31input1,pq31output1,blockSize);
           pq31output1 += blockSize;
           checkInnerTail(pq31output1);

           ps16config1 += 2;
           pq31coefs1 += numTaps;

		}
        printf("mips_fir_q31 finish \n");


       	printf("mips_fir_q31 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, paramCountInput1, (q31)SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, paramCountInput1, (q31)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, paramCountInput1, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, paramCountInput1, ABS_ERROR_Q31);
#endif


		printf("\n== mips_fir_q31 check done  == \n\n");

	// for (size_t i = 0; i < paramCountInput1; i++)
	// {
	// 	printf("mips_fir_q31 output = %f \n", q31output1[i]);
	// }
	

	return 0;

}