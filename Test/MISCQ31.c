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

#define ABS_ERROR_FAST_Q31 ((q31)11)


/*

For tests of the error value of the Levinson Durbin algorithm

*/
#define ABS_LD_ERROR ((q31)30)


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

    q31 *inpA;
    q31 *inpB;
    q31 *outp;
    int nba,nbb,errOffset,first;

	// declare input value
	int paramCountInputA1 = 0;
	int paramCountInputB1 = 0;
    int paramCountInputA = 0;
	int paramCountInputB = 0;
	int paramCountInputC = 0;
	int paramCountInputErrors = 0;
    int paramCountInputA2 = 0;
	int paramCountInputB2 = 0;
    int paramCountReference1 = 0;
	q31 q31inputA1[MAX_SIZE] = {0};
	q31 q31inputB1[MAX_SIZE] = {0};
    q31 q31inputA[MAX_SIZE] = {0};
	q31 q31inputB[MAX_SIZE] = {0};
    q31 q31inputC[MAX_SIZE] = {0};
    q31 q31inputErrors[MAX_SIZE] = {0};
	q31 q31inputA2[MAX_SIZE] = {0};
    q31 q31inputB2[MAX_SIZE] = {0};
    q31 reference1[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFileA1[255] = {0};
#else
	void *inputFileA1;
	int inputFileA1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileB1[255] = {0};
#else
	void *inputFileB1;
	int inputFileB1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileA[255] = {0};
#else
	void *inputFileA;
	int inputFileALen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileB[255] = {0};
#else
	void *inputFileB;
	int inputFileBLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileC[255] = {0};
#else
	void *inputFileC;
	int inputFileCLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileErrors[255] = {0};
#else
	void *inputFileErrors;
	int inputFileErrorsLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileA2[255] = {0};
#else
	void *inputFileA2;
	int inputFileA2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileB2[255] = {0};
#else
	void *inputFileB2;
	int inputFileB2Len = 0;
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
	snprintf(inputFileA1, sizeof(inputFileA1), "%s%s%s", Patterns_PATH, MISCQ31, "InputsA1_q31.txt");
#else
	inputFileA1 = MISCQ31_InputsA1_q31;
	inputFileA1Len = sizeof(MISCQ31_InputsA1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB1, sizeof(inputFileB1), "%s%s%s", Patterns_PATH, MISCQ31, "InputsB1_q31.txt");
#else
	inputFileB1 = MISCQ31_InputsB1_q31;
	inputFileB1Len = sizeof(MISCQ31_InputsB1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileA, sizeof(inputFileA), "%s%s%s", Patterns_PATH, MISCQ31, "InputPhi81_q31.txt");
#else
	inputFileA = MISCQ31_InputPhi81_q31;
	inputFileALen = sizeof(MISCQ31_InputPhi81_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB, sizeof(inputFileB), "%s%s%s", Patterns_PATH, MISCQ31, "InputPhi82_q31.txt");
#else
	inputFileB = MISCQ31_InputPhi82_q31;
	inputFileBLen = sizeof(MISCQ31_InputPhi82_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileC, sizeof(inputFileC), "%s%s%s", Patterns_PATH, MISCQ31, "InputPhi83_q31.txt");
#else
	inputFileC = MISCQ31_InputPhi83_q31;
	inputFileCLen = sizeof(MISCQ31_InputPhi83_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileErrors, sizeof(inputFileErrors), "%s%s%s", Patterns_PATH, MISCQ31, "LDErrors81_q31.txt");
#else
	inputFileErrors = MISCQ31_LDErrors81_q31;
	inputFileErrorsLen = sizeof(MISCQ31_LDErrors81_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileA2, sizeof(inputFileA2), "%s%s%s", Patterns_PATH, MISCQ31, "InputsA2_q31.txt");
#else
	inputFileA2 = MISCQ31_InputsA2_q31;
	inputFileA2Len = sizeof(MISCQ31_InputsA2_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB2, sizeof(inputFileB2), "%s%s%s", Patterns_PATH, MISCQ31, "InputsB2_q31.txt");
#else
	inputFileB2 = MISCQ31_InputsB2_q31;
	inputFileB2Len = sizeof(MISCQ31_InputsB2_q31);
#endif




	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileA1, &paramCountInputA1, q31inputA1);
#else
	paramCountInputA1 = inputFileA1Len;
	load_data_q31(inputFileA1, paramCountInputA1, q31inputA1);
	paramCountInputA1 = paramCountInputA1/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileB1, &paramCountInputB1, q31inputB1);
#else
	paramCountInputB1 = inputFileB1Len;
	load_data_q31(inputFileB1, paramCountInputB1, q31inputB1);
	paramCountInputB1 = paramCountInputB1/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileA, &paramCountInputA, q31inputA);
#else
	paramCountInputA = inputFileALen;
	load_data_q31(inputFileA, paramCountInputA, q31inputA);
	paramCountInputA = paramCountInputA/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileB, &paramCountInputB, q31inputB);
#else
	paramCountInputB = inputFileBLen;
	load_data_q31(inputFileB, paramCountInputB, q31inputB);
	paramCountInputB = paramCountInputB/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileC, &paramCountInputC, q31inputC);
#else
	paramCountInputC = inputFileCLen;
	load_data_q31(inputFileC, paramCountInputC, q31inputC);
	paramCountInputC = paramCountInputC/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileErrors, &paramCountInputErrors, q31inputErrors);
#else
	paramCountInputErrors = inputFileErrorsLen;
	load_data_q31(inputFileErrors, paramCountInputErrors, q31inputErrors);
	paramCountInputErrors = paramCountInputErrors/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileA2, &paramCountInputA2, q31inputA2);
#else
	paramCountInputA2 = inputFileA2Len;
	load_data_q31(inputFileA2, paramCountInputA2, q31inputA2);
	paramCountInputA2 = paramCountInputA2/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileB2, &paramCountInputB2, q31inputB2);
#else
	paramCountInputB2 = inputFileB2Len;
	load_data_q31(inputFileB2, paramCountInputB2, q31inputB2);
	paramCountInputB2 = paramCountInputB2/sizeof(q31);
#endif

    int num = 0;
    q31 q31output1[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
    char *id[] = {"Reference1_q31.txt", "Reference2_q31.txt", "Reference3_q31.txt", "Reference4_q31.txt", "Reference5_q31.txt", "Reference6_q31.txt", "Reference7_q31.txt", "Reference8_q31.txt", "Reference9_q31.txt", "Reference10_q31.txt", "Reference11_q31.txt", "Reference12_q31.txt", "Reference13_q31.txt", "Reference14_q31.txt", "Reference15_q31.txt", "Reference16_q31.txt", "Reference17_q31.txt", "Reference18_q31.txt", "Reference19_q31.txt", "Reference20_q31.txt", "Reference21_q31.txt", "Reference22_q31.txt", "Reference23_q31.txt", "Reference24_q31.txt", "Reference25_q31.txt", "Reference26_q31.txt", "Reference27_q31.txt", "Reference28_q31.txt", "Reference29_q31.txt", "Reference30_q31.txt", "Reference31_q31.txt", "Reference32_q31.txt", "Reference33_q31.txt", "Reference34_q31.txt", "Reference35_q31.txt", "Reference36_q31.txt", "Reference37_q31.txt", "Reference38_q31.txt", "Reference39_q31.txt", "Reference40_q31.txt", "Reference41_q31.txt", "Reference42_q31.txt", "Reference43_q31.txt", "Reference44_q31.txt", "Reference45_q31.txt", "Reference46_q31.txt", "Reference47_q31.txt", "Reference48_q31.txt", "Reference49_q31.txt", "Reference50_q31.txt", "Reference51_q31.txt", "Reference52_q31.txt", "Reference53_q31.txt", "Reference54_q31.txt", "Reference55_q31.txt", "Reference56_q31.txt", "Reference57_q31.txt", "Reference58_q31.txt", "Reference59_q31.txt", "Reference60_q31.txt", "Reference61_q31.txt", "Reference62_q31.txt", "Reference63_q31.txt", "Reference64_q31.txt", "Reference65_q31.txt", "Reference66_q31.txt", "Reference67_q31.txt", "Reference68_q31.txt", "Reference69_q31.txt", "Reference70_q31.txt", "Reference71_q31.txt", "Reference72_q31.txt", "Reference73_q31.txt", "Reference74_q31.txt", "Reference75_q31.txt", "Reference76_q31.txt", "Reference77_q31.txt", "Reference78_q31.txt", "Reference79_q31.txt", "Reference80_q31.txt", "Reference81_q31.txt", "Reference82_q31.txt", "Reference83_q31.txt", "Reference84_q31.txt", "Reference85_q31.txt", "Reference86_q31.txt"};
#else
    u64 id[100] = {MISCQ31_Reference1_q31, MISCQ31_Reference2_q31, MISCQ31_Reference3_q31, MISCQ31_Reference4_q31, MISCQ31_Reference5_q31, MISCQ31_Reference6_q31, MISCQ31_Reference7_q31, MISCQ31_Reference8_q31, MISCQ31_Reference9_q31, MISCQ31_Reference10_q31, MISCQ31_Reference11_q31, MISCQ31_Reference12_q31, MISCQ31_Reference13_q31, MISCQ31_Reference14_q31, MISCQ31_Reference15_q31, MISCQ31_Reference16_q31, MISCQ31_Reference17_q31, MISCQ31_Reference18_q31, MISCQ31_Reference19_q31, MISCQ31_Reference20_q31, MISCQ31_Reference21_q31, MISCQ31_Reference22_q31, MISCQ31_Reference23_q31, MISCQ31_Reference24_q31, MISCQ31_Reference25_q31, MISCQ31_Reference26_q31, MISCQ31_Reference27_q31, MISCQ31_Reference28_q31, MISCQ31_Reference29_q31, MISCQ31_Reference30_q31, MISCQ31_Reference31_q31, MISCQ31_Reference32_q31, MISCQ31_Reference33_q31, MISCQ31_Reference34_q31, MISCQ31_Reference35_q31, MISCQ31_Reference36_q31, MISCQ31_Reference37_q31, MISCQ31_Reference38_q31, MISCQ31_Reference39_q31, MISCQ31_Reference40_q31, MISCQ31_Reference41_q31, MISCQ31_Reference42_q31, MISCQ31_Reference43_q31, MISCQ31_Reference44_q31, MISCQ31_Reference45_q31, MISCQ31_Reference46_q31, MISCQ31_Reference47_q31, MISCQ31_Reference48_q31, MISCQ31_Reference49_q31, MISCQ31_Reference50_q31, MISCQ31_Reference54_q31, MISCQ31_Reference55_q31, MISCQ31_Reference56_q31, MISCQ31_Reference54_q31, MISCQ31_Reference55_q31, MISCQ31_Reference56_q31, MISCQ31_Reference57_q31, MISCQ31_Reference58_q31, MISCQ31_Reference59_q31, MISCQ31_Reference60_q31, MISCQ31_Reference61_q31, MISCQ31_Reference62_q31, MISCQ31_Reference63_q31, MISCQ31_Reference64_q31, MISCQ31_Reference65_q31, MISCQ31_Reference66_q31, MISCQ31_Reference67_q31, MISCQ31_Reference68_q31, MISCQ31_Reference69_q31, MISCQ31_Reference70_q31, MISCQ31_Reference71_q31, MISCQ31_Reference72_q31, MISCQ31_Reference73_q31, MISCQ31_Reference74_q31, MISCQ31_Reference75_q31, MISCQ31_Reference76_q31, MISCQ31_Reference77_q31, MISCQ31_Reference78_q31, MISCQ31_Reference79_q31, MISCQ31_Reference80_q31, MISCQ31_Reference81_q31, MISCQ31_Reference82_q31, MISCQ31_Reference83_q31, MISCQ31_Reference84_q31, MISCQ31_Reference85_q31, MISCQ31_Reference86_q31};
    u32 size[100] = {sizeof(MISCQ31_Reference1_q31), sizeof(MISCQ31_Reference2_q31), sizeof(MISCQ31_Reference3_q31), sizeof(MISCQ31_Reference4_q31), sizeof(MISCQ31_Reference5_q31), sizeof(MISCQ31_Reference6_q31), sizeof(MISCQ31_Reference7_q31), sizeof(MISCQ31_Reference8_q31), sizeof(MISCQ31_Reference9_q31), sizeof(MISCQ31_Reference10_q31), sizeof(MISCQ31_Reference11_q31), sizeof(MISCQ31_Reference12_q31), sizeof(MISCQ31_Reference13_q31), sizeof(MISCQ31_Reference14_q31), sizeof(MISCQ31_Reference15_q31), sizeof(MISCQ31_Reference16_q31), sizeof(MISCQ31_Reference17_q31), sizeof(MISCQ31_Reference18_q31), sizeof(MISCQ31_Reference19_q31), sizeof(MISCQ31_Reference20_q31), sizeof(MISCQ31_Reference21_q31), sizeof(MISCQ31_Reference22_q31), sizeof(MISCQ31_Reference23_q31), sizeof(MISCQ31_Reference24_q31), sizeof(MISCQ31_Reference25_q31), sizeof(MISCQ31_Reference26_q31), sizeof(MISCQ31_Reference27_q31), sizeof(MISCQ31_Reference28_q31), sizeof(MISCQ31_Reference29_q31), sizeof(MISCQ31_Reference30_q31), sizeof(MISCQ31_Reference31_q31), sizeof(MISCQ31_Reference32_q31), sizeof(MISCQ31_Reference33_q31), sizeof(MISCQ31_Reference34_q31), sizeof(MISCQ31_Reference35_q31), sizeof(MISCQ31_Reference36_q31), sizeof(MISCQ31_Reference37_q31), sizeof(MISCQ31_Reference38_q31), sizeof(MISCQ31_Reference39_q31), sizeof(MISCQ31_Reference40_q31), sizeof(MISCQ31_Reference41_q31), sizeof(MISCQ31_Reference42_q31), sizeof(MISCQ31_Reference43_q31), sizeof(MISCQ31_Reference44_q31), sizeof(MISCQ31_Reference45_q31), sizeof(MISCQ31_Reference46_q31), sizeof(MISCQ31_Reference47_q31), sizeof(MISCQ31_Reference48_q31), sizeof(MISCQ31_Reference49_q31), sizeof(MISCQ31_Reference50_q31), sizeof(MISCQ31_Reference54_q31), sizeof(MISCQ31_Reference55_q31), sizeof(MISCQ31_Reference56_q31), sizeof(MISCQ31_Reference54_q31), sizeof(MISCQ31_Reference55_q31), sizeof(MISCQ31_Reference56_q31), sizeof(MISCQ31_Reference57_q31), sizeof(MISCQ31_Reference58_q31), sizeof(MISCQ31_Reference59_q31), sizeof(MISCQ31_Reference60_q31), sizeof(MISCQ31_Reference61_q31), sizeof(MISCQ31_Reference62_q31), sizeof(MISCQ31_Reference63_q31), sizeof(MISCQ31_Reference64_q31), sizeof(MISCQ31_Reference65_q31), sizeof(MISCQ31_Reference66_q31), sizeof(MISCQ31_Reference67_q31), sizeof(MISCQ31_Reference68_q31), sizeof(MISCQ31_Reference69_q31), sizeof(MISCQ31_Reference70_q31), sizeof(MISCQ31_Reference71_q31), sizeof(MISCQ31_Reference72_q31), sizeof(MISCQ31_Reference73_q31), sizeof(MISCQ31_Reference74_q31), sizeof(MISCQ31_Reference75_q31), sizeof(MISCQ31_Reference76_q31), sizeof(MISCQ31_Reference77_q31), sizeof(MISCQ31_Reference78_q31), sizeof(MISCQ31_Reference79_q31), sizeof(MISCQ31_Reference80_q31), sizeof(MISCQ31_Reference81_q31), sizeof(MISCQ31_Reference82_q31), sizeof(MISCQ31_Reference83_q31), sizeof(MISCQ31_Reference84_q31), sizeof(MISCQ31_Reference85_q31), sizeof(MISCQ31_Reference86_q31)};
#endif
// =======test_correlate_q31==============

    for(num = 1; num <= 40; num++){

    inpA = q31inputA1;
    inpB = q31inputB1;
    outp = q31output1;
    printf("test:%d \n",num);
    switch (num)
    {
    case 1:
        nba = 4;
        nbb = 1;
        break;
    case 2:
        nba = 4;
        nbb = 2;
        break;
    case 3:
        nba = 4;
        nbb = 3;
        break;
    case 4:
        nba = 4;
        nbb = 8;
        break;
    case 5:
        nba = 4;
        nbb = 11;
        break;
    case 6:
        nba = 5;
        nbb = 1;
        break;
    case 7:
        nba = 5;
        nbb = 2;
        break;
    case 8:
        nba = 5;
        nbb = 3;
        break;
    case 9:
        nba = 5;
        nbb = 8;
        break;
    case 10:
        nba = 5;
        nbb = 11;
        break;
     case 11:
        nba = 6;
        nbb = 1;
        break;
    case 12:
        nba = 6;
        nbb = 2;
        break;
    case 13:
        nba = 6;
        nbb = 3;
        break;
    case 14:
        nba = 6;
        nbb = 8;
        break;
    case 15:
        nba = 6;
        nbb = 11;
        break;
    case 16:
        nba = 9;
        nbb = 1;
        break;
    case 17:
        nba = 9;
        nbb = 2;
        break;
    case 18:
        nba = 9;
        nbb = 3;
        break;
    case 19:
        nba = 9;
        nbb = 8;
        break;
    case 20:
        nba = 9;
        nbb = 11;
        break;
    case 21:
        nba = 10;
        nbb = 1;
        break;
    case 22:
        nba = 10;
        nbb = 2;
        break;
    case 23:
        nba = 10;
        nbb = 3;
        break;
    case 24:
        nba = 10;
        nbb = 8;
        break;
    case 25:
        nba = 10;
        nbb = 11;
        break;
    case 26:
        nba = 11;
        nbb = 1;
        break;
    case 27:
        nba = 11;
        nbb = 2;
        break;
    case 28:
        nba = 11;
        nbb = 3;
        break;
    case 29:
        nba = 11;
        nbb = 8;
        break;
    case 30:
        nba = 11;
        nbb = 11;
        break;
     case 31:
        nba = 12;
        nbb = 1;
        break;
    case 32:
        nba = 12;
        nbb = 2;
        break;
    case 33:
        nba = 12;
        nbb = 3;
        break;
    case 34:
        nba = 12;
        nbb = 8;
        break;
    case 35:
        nba = 12;
        nbb = 11;
        break;
    case 36:
        nba = 13;
        nbb = 1;
        break;
    case 37:
        nba = 13;
        nbb = 2;
        break;
    case 38:
        nba = 13;
        nbb = 3;
        break;
    case 39:
        nba = 13;
        nbb = 8;
        break;
    case 40:
        nba = 13;
        nbb = 11;
        break;
    default:
        break;
    }
    printf("== correlate_q31  test ==  \n");

    mips_correlate_q31(inpA, nba,
      inpB, nbb,
      outp);
    
	printf("correlate_q31 finish \n");

	printf("correlate_q31 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCQ31, id[num-1]);
#else
	referenceFile1 = id[num-1];
	referenceFile1Len = size[num-1];
    load_data_q31(referenceFile1, referenceFile1Len, referenceData_q31);
    referenceFile1Len = referenceFile1Len/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile1, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile1, q31output1, 0, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFile1Len, ABS_ERROR_Q31);
#endif

    memset(q31output1, 0, sizeof(q31)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_q31, 0, sizeof(q31)*MAX_SIZE);
#endif
	printf("\n== correlate_q31 check done  == \n\n");
    };

// =======test_conv_q31 ==============

    for(num = 1; num <= 40; num++){

    inpA = q31inputA1;
    inpB = q31inputB1;
    outp = q31output1;
    printf("test:%d \n",(num+40));
    switch (num)
    {
    case 1:
        nba = 4;
        nbb = 1;
        break;
    case 2:
        nba = 4;
        nbb = 2;
        break;
    case 3:
        nba = 4;
        nbb = 3;
        break;
    case 4:
        nba = 4;
        nbb = 8;
        break;
    case 5:
        nba = 4;
        nbb = 11;
        break;
    case 6:
        nba = 5;
        nbb = 1;
        break;
    case 7:
        nba = 5;
        nbb = 2;
        break;
    case 8:
        nba = 5;
        nbb = 3;
        break;
    case 9:
        nba = 5;
        nbb = 8;
        break;
    case 10:
        nba = 5;
        nbb = 11;
        break;
     case 11:
        nba = 6;
        nbb = 1;
        break;
    case 12:
        nba = 6;
        nbb = 2;
        break;
    case 13:
        nba = 6;
        nbb = 3;
        break;
    case 14:
        nba = 6;
        nbb = 8;
        break;
    case 15:
        nba = 6;
        nbb = 11;
        break;
    case 16:
        nba = 9;
        nbb = 1;
        break;
    case 17:
        nba = 9;
        nbb = 2;
        break;
    case 18:
        nba = 9;
        nbb = 3;
        break;
    case 19:
        nba = 9;
        nbb = 8;
        break;
    case 20:
        nba = 9;
        nbb = 11;
        break;
    case 21:
        nba = 10;
        nbb = 1;
        break;
    case 22:
        nba = 10;
        nbb = 2;
        break;
    case 23:
        nba = 10;
        nbb = 3;
        break;
    case 24:
        nba = 10;
        nbb = 8;
        break;
    case 25:
        nba = 10;
        nbb = 11;
        break;
    case 26:
        nba = 11;
        nbb = 1;
        break;
    case 27:
        nba = 11;
        nbb = 2;
        break;
    case 28:
        nba = 11;
        nbb = 3;
        break;
    case 29:
        nba = 11;
        nbb = 8;
        break;
    case 30:
        nba = 11;
        nbb = 11;
        break;
     case 31:
        nba = 12;
        nbb = 1;
        break;
    case 32:
        nba = 12;
        nbb = 2;
        break;
    case 33:
        nba = 12;
        nbb = 3;
        break;
    case 34:
        nba = 12;
        nbb = 8;
        break;
    case 35:
        nba = 12;
        nbb = 11;
        break;
    case 36:
        nba = 13;
        nbb = 1;
        break;
    case 37:
        nba = 13;
        nbb = 2;
        break;
    case 38:
        nba = 13;
        nbb = 3;
        break;
    case 39:
        nba = 13;
        nbb = 8;
        break;
    case 40:
        nba = 13;
        nbb = 11;
        break;
    default:
        break;
    }
    printf("== conv_q31  test ==  \n");

    mips_conv_q31(inpA, nba,
      inpB, nbb,
      outp);
    
	printf("conv_q31 finish \n");

	printf("conv_q31 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCQ31, id[num+40-1]);
#else
	referenceFile1 = id[num+40-1];
	referenceFile1Len = size[num+40-1];
    load_data_q31(referenceFile1, referenceFile1Len, referenceData_q31);
    referenceFile1Len = referenceFile1Len/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile1, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile1, q31output1, 0, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFile1Len, ABS_ERROR_Q31);
#endif

    memset(q31output1, 0, sizeof(q31)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_q31, 0, sizeof(q31)*MAX_SIZE);
#endif
	printf("\n== conv_q31 check done  == \n\n");
    };
    
// =======test_levinson_durbin_q31==============

 for(num = 1; num <= 3; num++){
    q31 *errs;
    errs = q31inputErrors;
    q31 err;
    outp = q31output1;
    printf("test:%d \n",(num+80));
    switch (num)
    {
    case 1:
        inpA = q31inputA;
        nba = 3;
        errOffset = 0;
        break;
    case 2:
        inpA = q31inputB;
        nba = 8;
        errOffset = 1;
        break;
    case 3:
        inpA = q31inputC;
        nba = 11;
        errOffset = 2;
        break;

    default:
        break;
    }
    q31 refError = errs[errOffset];
    printf("== levinson_durbin_q31  test ==  \n");

    mips_levinson_durbin_q31(inpA,outp,&err,nba);
    
	printf("levinson_durbin_q31 finish \n");

	printf("levinson_durbin_q31 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCQ31, id[num+80-1]);
#else
	referenceFile1 = id[num+80-1];
	referenceFile1Len = size[num+80-1];
    load_data_q31(referenceFile1, referenceFile1Len, referenceData_q31);
    referenceFile1Len = referenceFile1Len/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile1, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile1, q31output1, 0, ABS_LD_ERROR);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFile1Len, ABS_LD_ERROR);
#endif


    if (abs(refError - err) > ABS_LD_ERROR)
		{
			char details[200];
			sprintf(details, "close error %g > %g: (val = %g, ref = %g)", abs(refError - err), ABS_LD_ERROR, refError, err);
			printf("invalid value, details : %s \n", details);
		}
        else{
            printf("closeError count = 0, CLOSE Test PASSED!  \n");
        };
    memset(q31output1, 0, sizeof(q31)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_q31, 0, sizeof(q31)*MAX_SIZE);
#endif

	printf("\n== levinson_durbin_q31 check done  == \n\n");
    };

// =======test_conv_partial_q31==============
    // This value must be coherent with the Python script
    // generating the test patterns
#define NBPOINTS 4

    q31 tmp[MAX_SIZE] = {0};
 for(num = 1; num <= 3; num++){
    inpA = q31inputA2;
    inpB = q31inputB2;
    outp = q31output1;
    q31 *tmpp;
    tmpp = tmp;
    printf("test:%d \n",(num+83));
    switch (num)
    {
    case 1:
        first=3;
        nba = 6;
        nbb = 8;
        break;
    case 2:
        first=9;
        nba = 6;
        nbb = 8;
        break;
    case 3:
        first=7;
        nba = 6;
        nbb = 8;
        break;

    default:
        break;
    }
    printf("== conv_partial_q31  test ==  \n");

    mips_status status=mips_conv_partial_q31(inpA, nba,
          inpB, nbb,
          outp,
          first,
          NBPOINTS);

    memcpy((void*)tmpp,(void*)&outp[first],NBPOINTS*sizeof(q31));

	printf("conv_partial_q31 finish \n");

	printf("conv_partial_q31 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCQ31, id[num+83-1]);
#else
	referenceFile1 = id[num+83-1];
	referenceFile1Len = size[num+83-1];
    load_data_q31(referenceFile1, referenceFile1Len, referenceData_q31);
    referenceFile1Len = referenceFile1Len/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile1, tmp, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, tmp, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile1, tmp, 0, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, tmp, referenceFile1Len, ABS_ERROR_Q31);
#endif

    ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

    memset(q31output1, 0, sizeof(q31)*MAX_SIZE);
    memset(tmp, 0, sizeof(q31)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_q31, 0, sizeof(q31)*MAX_SIZE);
#endif
	printf("\n== conv_partial_q31 check done  == \n\n");
    };

    return 0;
}

	

