#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/filtering_functions.h"


#define SNR_THRESHOLD 310
#define REL_ERROR (5.0e-5)


static void checkInnerTail(double *b)
{
    ASSERT_TRUE(b[0] == 0.0);
    ASSERT_TRUE(b[1] == 0.0);
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
	double f64input1[MAX_SIZE] = {0};
	double f64coefs1[MAX_SIZE] = {0};
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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, FIRF64, "FirInput1_f64.txt");
#else
	inputFile1 = FIRF64_FirInput1_f64;
	inputFile1Len = sizeof(FIRF64_FirInput1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(coefsFile1, sizeof(coefsFile1), "%s%s%s", Patterns_PATH, FIRF64, "FirCoefs1_f64.txt");
#else
	coefsFile1 = FIRF64_FirCoefs1_f64;
	coefsFile1Len = sizeof(FIRF64_FirCoefs1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(configsFile1, sizeof(configsFile1), "%s%s%s", Patterns_PATH, FIRF64, "FirConfigs1_s16.txt");
#else
	configsFile1 = FIRF64_FirConfigs1_s16;
	configsFile1Len = sizeof(FIRF64_FirConfigs1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FIRF64, "FirRefs1_f64.txt");
#else
	referenceFile = FIRF64_FirRefs1_f64;
	referenceFileLen = sizeof(FIRF64_FirRefs1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile1, &paramCountInput1, f64input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f64(inputFile1, paramCountInput1, f64input1);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(coefsFile1, &paramCountCoefs1, f64coefs1);
#else
	paramCountCoefs1 = coefsFile1Len;
	load_data_f64(coefsFile1, paramCountCoefs1, f64coefs1);
	paramCountCoefs1 = paramCountCoefs1/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(configsFile1, &paramCountConfig1, s16config1);
#else
	paramCountConfig1 = configsFile1Len;
	load_data_q15(configsFile1, paramCountConfig1, s16config1);
	paramCountConfig1 = paramCountConfig1/sizeof(q15);
#endif


	const double *coefsp;

	double state[47+47] = {0};
	double f64output1[MAX_SIZE] = {0};

    double *pstate;
    pstate = state;
    double *pf64output1;
    pf64output1 = f64output1;
    double *pf64input1;

    double *pf64coefs1;
    pf64coefs1 = f64coefs1;
    int16_t *ps16config1;
    ps16config1 = s16config1;
    

    printf("== mips_fir_f64 test ==  \n");

    unsigned long i;

    int blockSize;
    int numTaps;

		/*

        Python script is generating different tests with
        different blockSize and numTaps.

        We loop on those configs.

        */
        for(i=0; i < paramCountConfig1 ; i += 2)
        {
           blockSize = ps16config1[0];
           numTaps = ps16config1[1];

           coefsp = pf64coefs1;

           /*

           The filter is initialized with the coefs, blockSize and numTaps.

           */

           mips_fir_instance_f64 S;
           mips_fir_init_f64(&S,numTaps,coefsp,pstate,blockSize);

           /*
           
           Python script is filtering a 2*blockSize number of samples.
           We do the same filtering in two pass to check (indirectly that
           the state management of the fir is working.)

           */
           pf64input1 = f64input1;
           
           mips_fir_f64(&S,pf64input1,pf64output1,blockSize);


           pf64output1 += blockSize;
           checkInnerTail(pf64output1);
           
           pf64input1 += blockSize;
           mips_fir_f64(&S,pf64input1,pf64output1,blockSize);
           pf64output1 += blockSize;
           checkInnerTail(pf64output1);

           ps16config1 += 2;
           pf64coefs1 += numTaps;

		}
        printf("mips_fir_f64 finish \n");


       	printf("mips_fir_f64 checking \n\n");
	#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountInput1, SNR_THRESHOLD);
#endif

	#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, paramCountInput1, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, paramCountInput1, REL_ERROR);
#endif


		printf("\n== mips_fir_f64 check done  == \n\n");

	// for (size_t i = 0; i < paramCountInput1; i++)
	// {
	// 	printf("mips_fir_f64 output = %f \n", f64output1[i]);
	// }
	

	return 0;

}