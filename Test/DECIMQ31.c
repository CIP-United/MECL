#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/filtering_functions.h"

#define SNR_THRESHOLD 100

/* 

Reference patterns are generated with
a double precision computation.

*/
#define ABS_ERROR_Q31 ((q31)2)
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

	q31 q31output[MAX_SIZE] = {0};

// =======test_fir_decimate_q31==============

	// declare input value
	int paramCountInput2 = 0;
	int paramCountCoefs2 = 0;
    int paramCountConfigs2 = 0;
	q31 q31inputs2[MAX_SIZE] = {0};
	q31 q31coefs2[MAX_SIZE] = {0};
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
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, DECIMQ31, "Input2_q31.txt");
#else
	inputFile2 = DECIMQ31_Input2_q31;
	inputFile2Len = sizeof(DECIMQ31_Input2_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(coefsFile2, sizeof(coefsFile2), "%s%s%s", Patterns_PATH, DECIMQ31, "Coefs2_q31.txt");
#else
	coefsFile2 = DECIMQ31_Coefs2_q31;
	coefsFile2Len = sizeof(DECIMQ31_Coefs2_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(configsFile2, sizeof(configsFile2), "%s%s%s", Patterns_PATH, DECIMQ31, "Configs2_u32.txt");
#else
	configsFile2 = DECIMQ31_Configs2_u32;
	configsFile2Len = sizeof(DECIMQ31_Configs2_u32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile2, sizeof(referenceFile2), "%s%s%s", Patterns_PATH, DECIMQ31, "Reference2_q31.txt");
#else
	referenceFile2 = DECIMQ31_Reference2_q31;
	referenceFile2Len = sizeof(DECIMQ31_Reference2_q31);
	load_data_q31(referenceFile2, referenceFile2Len, referenceData_q31);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile2, &paramCountInput2, q31inputs2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q31(inputFile2, paramCountInput2, q31inputs2);
	paramCountInput2 = paramCountInput2/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(coefsFile2, &paramCountCoefs2, q31coefs2);
#else
	paramCountCoefs2 = coefsFile2Len;
	load_data_q31(coefsFile2, paramCountCoefs2, q31coefs2);
	paramCountCoefs2 = paramCountCoefs2/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u32(configsFile2, &paramCountConfigs2, u32configs2);
#else
	paramCountConfigs2 = configsFile2Len;
	load_data_u32(configsFile2, paramCountConfigs2, u32configs2);
	paramCountConfigs2 = paramCountConfigs2/sizeof(uint32_t);
#endif



	printf("== fir_decimate_q31 test ==  \n");

	q31 state2[16 + 768 - 1] = {0};
	int nbTests;
    int nb;
	// pointers
	q31 *pCoefs;
	pCoefs = q31coefs2;
	q31 *statep;
	statep = state2;
	q31 *pSrc;
	pSrc = q31inputs2;
	q31 *pDst;
	pDst = q31output;
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
			
			mips_fir_decimate_instance_q31 S;
            status=mips_fir_decimate_init_q31(&S,
               numTaps,
               q,
               pCoefs,
               statep,
               blocksize);



            ASSERT_TRUE(status == MIPS_MATH_SUCCESS);

            mips_fir_decimate_q31(
                 &S,
                 pSrc,
                 pDst,
                 blocksize);

            pSrc += blocksize;
            pDst += refsize;

            pCoefs += numTaps;
        }


	printf("fir_decimate_q31 finish \n");

	printf("fir_decimate_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile2, q31output, 0, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output, referenceFile2Len, ABS_ERROR_Q31);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile2, q31output, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output, referenceFile2Len, SNR_THRESHOLD);
#endif


	printf("\n== fir_decimate_q31 check done  == \n\n");


	// =======test_fir_interpolate_q31==============

	// declare input value
	int paramCountInput3 = 0;
	int paramCountCoefs3 = 0;
    int paramCountConfigs3 = 0;
	q31 q31inputs3[MAX_SIZE] = {0};
	q31 q31coefs3[MAX_SIZE] = {0};
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
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, DECIMQ31, "Input3_q31.txt");
#else
	inputFile3 = DECIMQ31_Input3_q31;
	inputFile3Len = sizeof(DECIMQ31_Input3_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(coefsFile3, sizeof(coefsFile3), "%s%s%s", Patterns_PATH, DECIMQ31, "Coefs3_q31.txt");
#else
	coefsFile3 = DECIMQ31_Coefs3_q31;
	coefsFile3Len = sizeof(DECIMQ31_Coefs3_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(configsFile3, sizeof(configsFile3), "%s%s%s", Patterns_PATH, DECIMQ31, "Configs3_u32.txt");
#else
	configsFile3 = DECIMQ31_Configs3_u32;
	configsFile3Len = sizeof(DECIMQ31_Configs3_u32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile3, sizeof(referenceFile3), "%s%s%s", Patterns_PATH, DECIMQ31, "Reference3_q31.txt");
#else
	referenceFile3 = DECIMQ31_Reference3_q31;
	referenceFile3Len = sizeof(DECIMQ31_Reference3_q31);
	load_data_q31(referenceFile3, referenceFile3Len, referenceData_q31);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile3, &paramCountInput3, q31inputs3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_q31(inputFile3, paramCountInput3, q31inputs3);
	paramCountInput3 = paramCountInput3/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(coefsFile3, &paramCountCoefs3, q31coefs3);
#else
	paramCountCoefs3 = coefsFile3Len;
	load_data_q31(coefsFile3, paramCountCoefs3, q31coefs3);
	paramCountCoefs3 = paramCountCoefs3/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_u32(configsFile3, &paramCountConfigs3, u32configs3);
#else
	paramCountConfigs3 = configsFile3Len;
	load_data_u32(configsFile3, paramCountConfigs3, u32configs3);
	paramCountConfigs3 = paramCountConfigs3/sizeof(uint32_t);
#endif

	printf("== fir_interpolate_q31 test ==  \n");
	q31 state3[16 + 768 - 1] = {0};
	// pointers
	pCoefs = q31coefs3;
	statep = state3;
	pSrc = q31inputs3;
	pDst = q31output;
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
			mips_fir_interpolate_instance_q31 SI;

            status=mips_fir_interpolate_init_q31(&SI,
               q,
               numTaps,
               pCoefs,
               statep,
               blocksize);

            ASSERT_TRUE(status == MIPS_MATH_SUCCESS);

            mips_fir_interpolate_q31(
                 &SI,
                 pSrc,
                 pDst,
                 blocksize);

            pSrc += blocksize;
            pDst += refsize;

            pCoefs += numTaps;
        }

	printf("fir_interpolate_q31 finish \n");

	printf("fir_interpolate_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile3, q31output, paramCountInput3, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output, paramCountInput3, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile3, q31output, paramCountInput3, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output, paramCountInput3, ABS_ERROR_Q31);
#endif


	printf("\n== fir_interpolate_q31 check done  == \n\n");


	// =====================

	return 0;
}