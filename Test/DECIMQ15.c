#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/filtering_functions.h"

#define SNR_THRESHOLD 70

/* 

Reference patterns are generated with
a double precision computation.

*/
#define ABS_ERROR_Q15 ((q15)5)
#define ABS_ERROR_Q63 ((q63)(1<<17))

#define ONEHALF 0x40000000

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

	q15 q15output[MAX_SIZE] = {0};

// =======test_fir_decimate_q15==============

	// declare input value
	int paramCountInput2 = 0;
	int paramCountCoefs2 = 0;
    int paramCountConfigs2 = 0;
	q15 q15inputs2[MAX_SIZE] = {0};
	q15 q15coefs2[MAX_SIZE] = {0};
    uint32_t u32configs2[MAX_SIZE] = {0};

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
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, DECIMQ15, "Input2_q15.txt");
#else
	inputFile2 = DECIMQ15_Input2_q15;
	inputFile2Len = sizeof(DECIMQ15_Input2_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(coefsFile2, sizeof(coefsFile2), "%s%s%s", Patterns_PATH, DECIMQ15, "Coefs2_q15.txt");
#else
	coefsFile2 = DECIMQ15_Coefs2_q15;
	coefsFile2Len = sizeof(DECIMQ15_Coefs2_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(configsFile2, sizeof(configsFile2), "%s%s%s", Patterns_PATH, DECIMQ15, "Configs2_u32.txt");
#else
	configsFile2 = DECIMQ15_Configs2_u32;
	configsFile2Len = sizeof(DECIMQ15_Configs2_u32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile2, sizeof(referenceFile2), "%s%s%s", Patterns_PATH, DECIMQ15, "Reference2_q15.txt");
#else
	referenceFile2 = DECIMQ15_Reference2_q15;
	referenceFile2Len = sizeof(DECIMQ15_Reference2_q15);
	load_data_q15(referenceFile2, referenceFile2Len, referenceData_q15);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile2, &paramCountInput2, q15inputs2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q15(inputFile2, paramCountInput2, q15inputs2);
	paramCountInput2 = paramCountInput2/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(coefsFile2, &paramCountCoefs2, q15coefs2);
#else
	paramCountCoefs2 = coefsFile2Len;
	load_data_q15(coefsFile2, paramCountCoefs2, q15coefs2);
	paramCountCoefs2 = paramCountCoefs2/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u32(configsFile2, &paramCountConfigs2, u32configs2);
#else
	paramCountConfigs2 = configsFile2Len;
	load_data_u32(configsFile2, paramCountConfigs2, u32configs2);
	paramCountConfigs2 = paramCountConfigs2/sizeof(uint32_t);
#endif



	printf("== fir_decimate_q15 test ==  \n");

	q15 state2[16 + 768 - 1] = {0};
	int nbTests;
    int nb;
	// pointers
	q15 *pCoefs;
	pCoefs = q15coefs2;
	q15 *statep;
	statep = state2;
	q15 *pSrc;
	pSrc = q15inputs2;
	q15 *pDst;
	pDst = q15output;
	uint32_t *pConfig;
	pConfig = u32configs2;

	nbTests=paramCountConfigs2 / 4;

        for(nb=0;nb < nbTests; nb++)
        {
			int q;
            int numTaps;
            int blocksize;
            int refsize;

			mips_status status;

            q = pConfig[0];
            numTaps = pConfig[1];
            blocksize = pConfig[2];
            refsize = pConfig[3];


            pConfig += 4;
			
			mips_fir_decimate_instance_q15 S;
            status=mips_fir_decimate_init_q15(&S,
               numTaps,
               q,
               pCoefs,
               statep,
               blocksize);



            ASSERT_TRUE(status == MIPS_MATH_SUCCESS);

            mips_fir_decimate_q15(
                 &S,
                 pSrc,
                 pDst,
                 blocksize);

            pSrc += blocksize;
            pDst += refsize;

            pCoefs += numTaps;
        }


	printf("fir_decimate_q15 finish \n");

	printf("fir_decimate_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile2, q15output, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output, referenceFile2Len, ABS_ERROR_Q15);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile2, q15output, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output, referenceFile2Len, SNR_THRESHOLD);
#endif


	printf("\n== fir_decimate_q15 check done  == \n\n");


	// =======test_fir_interpolate_q15==============

	// declare input value
	int paramCountInput3 = 0;
	int paramCountCoefs3 = 0;
    int paramCountConfigs3 = 0;
	q15 q15inputs3[MAX_SIZE] = {0};
	q15 q15coefs3[MAX_SIZE] = {0};
    uint32_t u32configs3[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFile3[255] = {0};
#else
	void *inputFile3;
	int inputFile3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char coefsFile3[255] = {0};
#else
	void *coefsFile3;
	int coefsFile3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char configsFile3[255] = {0};
#else
	void *configsFile3;
	int configsFile3Len = 0;
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
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, DECIMQ15, "Input3_q15.txt");
#else
	inputFile3 = DECIMQ15_Input3_q15;
	inputFile3Len = sizeof(DECIMQ15_Input3_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(coefsFile3, sizeof(coefsFile3), "%s%s%s", Patterns_PATH, DECIMQ15, "Coefs3_q15.txt");
#else
	coefsFile3 = DECIMQ15_Coefs3_q15;
	coefsFile3Len = sizeof(DECIMQ15_Coefs3_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(configsFile3, sizeof(configsFile3), "%s%s%s", Patterns_PATH, DECIMQ15, "Configs3_u32.txt");
#else
	configsFile3 = DECIMQ15_Configs3_u32;
	configsFile3Len = sizeof(DECIMQ15_Configs3_u32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile3, sizeof(referenceFile3), "%s%s%s", Patterns_PATH, DECIMQ15, "Reference3_q15.txt");
#else
	referenceFile3 = DECIMQ15_Reference3_q15;
	referenceFile3Len = sizeof(DECIMQ15_Reference3_q15);
	load_data_q15(referenceFile3, referenceFile3Len, referenceData_q15);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile3, &paramCountInput3, q15inputs3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_q15(inputFile3, paramCountInput3, q15inputs3);
	paramCountInput3 = paramCountInput3/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(coefsFile3, &paramCountCoefs3, q15coefs3);
#else
	paramCountCoefs3 = coefsFile3Len;
	load_data_q15(coefsFile3, paramCountCoefs3, q15coefs3);
	paramCountCoefs3 = paramCountCoefs3/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u32(configsFile3, &paramCountConfigs3, u32configs3);
#else
	paramCountConfigs3 = configsFile3Len;
	load_data_u32(configsFile3, paramCountConfigs3, u32configs3);
	paramCountConfigs3 = paramCountConfigs3/sizeof(uint32_t);
#endif

	printf("== fir_interpolate_q15 test ==  \n");
	q15 state3[16 + 768 - 1] = {0};
	// pointers
	pCoefs = q15coefs3;
	statep = state3;
	pSrc = q15inputs3;
	pDst = q15output;
	pConfig = u32configs3;


	nbTests=paramCountConfigs3 / 4;

        for(nb=0;nb < nbTests; nb++)
        {
			int q;
            int numTaps;
            int blocksize;
            int refsize;

            q = pConfig[0];
            numTaps = pConfig[1];
            blocksize = pConfig[2];
            refsize = pConfig[3];

            pConfig += 4;
			
			mips_status status;
			mips_fir_interpolate_instance_q15 SI;

            status=mips_fir_interpolate_init_q15(&SI,
               q,
               numTaps,
               pCoefs,
               statep,
               blocksize);

            ASSERT_TRUE(status == MIPS_MATH_SUCCESS);

            mips_fir_interpolate_q15(
                 &SI,
                 pSrc,
                 pDst,
                 blocksize);

            pSrc += blocksize;
            pDst += refsize;

            pCoefs += numTaps;
        }

	printf("fir_interpolate_q15 finish \n");

	printf("fir_interpolate_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile3, q15output, paramCountInput3, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output, paramCountInput3, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile3, q15output, paramCountInput3, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output, paramCountInput3, ABS_ERROR_Q15);
#endif


	printf("\n== fir_interpolate_q15 check done  == \n\n");


	// =====================

	return 0;
}