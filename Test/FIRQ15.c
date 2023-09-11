#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/filtering_functions.h"


#define SNR_THRESHOLD 59

#define ABS_ERROR_Q15 ((q15)2)

#if defined(MIPS_MATH_MSA)
static __ALIGNED(8) q15 coeffArray[32];
#endif 

static void checkInnerTail(q15 *b)
{
    ASSERT_TRUE(b[0] == 0);
    ASSERT_TRUE(b[1] == 0);
    ASSERT_TRUE(b[2] == 0);
    ASSERT_TRUE(b[3] == 0);
}

// Coef must be padded to a multiple of 8
#define FIRCOEFPADDING 3

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
	q15 q15input1[MAX_SIZE] = {0};
	q15 q15coefs1[MAX_SIZE] = {0};
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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, FIRQ15, "FirInput1_q15.txt");
#else
	inputFile1 = FIRQ15_FirInput1_q15;
	inputFile1Len = sizeof(FIRQ15_FirInput1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(coefsFile1, sizeof(coefsFile1), "%s%s%s", Patterns_PATH, FIRQ15, "FirCoefs1_q15.txt");
#else
	coefsFile1 = FIRQ15_FirCoefs1_q15;
	coefsFile1Len = sizeof(FIRQ15_FirCoefs1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(configsFile1, sizeof(configsFile1), "%s%s%s", Patterns_PATH, FIRQ15, "FirConfigs1_s16.txt");
#else
	configsFile1 = FIRQ15_FirConfigs1_s16;
	configsFile1Len = sizeof(FIRQ15_FirConfigs1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FIRQ15, "FirRefs1_q15.txt");
#else
	referenceFile = FIRQ15_FirRefs1_q15;
	referenceFileLen = sizeof(FIRQ15_FirRefs1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile1, &paramCountInput1, q15input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q15(inputFile1, paramCountInput1, q15input1);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(coefsFile1, &paramCountCoefs1, q15coefs1);
#else
	paramCountCoefs1 = coefsFile1Len;
	load_data_q15(coefsFile1, paramCountCoefs1, q15coefs1);
	paramCountCoefs1 = paramCountCoefs1/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(configsFile1, &paramCountConfig1, s16config1);
#else
	paramCountConfig1 = configsFile1Len;
	load_data_q15(configsFile1, paramCountConfig1, s16config1);
	paramCountConfig1 = paramCountConfig1/sizeof(q15);
#endif


	const q15 *coefsp;

	q15 state[3 * 41] = {0};
	q15 q15output1[MAX_SIZE] = {0};

    q15 *pstate;
    pstate = state;
    q15 *pq15output1;
    pq15output1 = q15output1;
    q15 *pq15input1;

    q15 *pq15coefs1;
    pq15coefs1 = q15coefs1;
    int16_t *ps16config1;
    ps16config1 = s16config1;
    

    printf("== mips_fir_q15 test ==  \n");

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
           memset(coeffArray,127,32*sizeof(q15));
           round = numTaps >> FIRCOEFPADDING;
           if ((round << FIRCOEFPADDING) < numTaps)
           {
             round ++;
           }
           round = round<<FIRCOEFPADDING;
           memset(coeffArray,0,round*sizeof(q15));

           //printf("blockSize=%d, numTaps=%d, round=%d (%d)\n",blockSize,numTaps,round,round - numTaps);

           for(j=0;j < numTaps; j++)
           {
              coeffArray[j] = orgcoefsp[j];
           }
   
           coefsp = coeffArray;
#else
           coefsp = pq15coefs1;
#endif
           /*

           The filter is initialized with the coefs, blockSize and numTaps.

           */

           mips_fir_instance_q15 S;
           mips_fir_init_q15(&S,numTaps,coefsp,pstate,blockSize);

           /*
           
           Python script is filtering a 2*blockSize number of samples.
           We do the same filtering in two pass to check (indirectly that
           the state management of the fir is working.)

           */
           pq15input1 = q15input1;

           mips_fir_q15(&S,pq15input1,pq15output1,blockSize);
           pq15output1 += blockSize;
           checkInnerTail(pq15output1);
           
           pq15input1 += blockSize;
           mips_fir_q15(&S,pq15input1,pq15output1,blockSize);
           pq15output1 += blockSize;
           checkInnerTail(pq15output1);

           ps16config1 += 2;
           pq15coefs1 += numTaps;

		}
        printf("mips_fir_q15 finish \n");


       	printf("mips_fir_q15 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, (q15)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, ABS_ERROR_Q15);
#endif


		printf("\n== mips_fir_q15 check done  == \n\n");

	// for (size_t i = 0; i < paramCountInput1; i++)
	// {
	// 	printf("mips_fir_q15 output = %f \n", q15output1[i]);
	// }
	

	return 0;

}