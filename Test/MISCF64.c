#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/filtering_functions.h"

#define SNR_THRESHOLD 310
/* 

Reference patterns are generated with
a double precision computation.

*/
#define REL_ERROR (2.0e-16)
#define ABS_ERROR (2.0e-16)

/*

For tests of the error value of the Levinson Durbin algorithm

*/
#define REL_LD_ERROR (1.0e-6)
#define ABS_LD_ERROR (1.0e-6)


int main()
{

#if !defined(NOT_EMBEDDED)
	// uint8_t referenceData_u8[MAX_SIZE] = {0};
	// uint16_t referenceData_u16[MAX_SIZE] = {0};
	// uint32_t referenceData_u32[MAX_SIZE] = {0};
	// uint64_t referenceData_u64[MAX_SIZE] = {0};
	// q7 referenceData_q7[MAX_SIZE] = {0};
	// q15 referenceData_q15[MAX_SIZE] = {0};
	// q31 referenceData_q31[MAX_SIZE] = {0};
	// q63 referenceData_q63[MAX_SIZE] = {0};
	// f32 referenceData_f32[MAX_SIZE] = {0};
	f64 referenceData_f64[MAX_SIZE] = {0};
#endif

    double *inpA;
    double *inpB;
    double *outp;
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
	double f64inputA1[MAX_SIZE] = {0};
	double f64inputB1[MAX_SIZE] = {0};
    double f64inputA[MAX_SIZE] = {0};
	double f64inputB[MAX_SIZE] = {0};
    double f64inputC[MAX_SIZE] = {0};
    double f64inputErrors[MAX_SIZE] = {0};
	double f64inputA2[MAX_SIZE] = {0};
    double f64inputB2[MAX_SIZE] = {0};
    double reference1[MAX_SIZE] = {0};

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
	snprintf(inputFileA1, sizeof(inputFileA1), "%s%s%s", Patterns_PATH, MISCF64, "InputsA1_f64.txt");
#else
	inputFileA1 = MISCF64_InputsA1_f64;
	inputFileA1Len = sizeof(MISCF64_InputsA1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB1, sizeof(inputFileB1), "%s%s%s", Patterns_PATH, MISCF64, "InputsB1_f64.txt");
#else
	inputFileB1 = MISCF64_InputsB1_f64;
	inputFileB1Len = sizeof(MISCF64_InputsB1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileA, sizeof(inputFileA), "%s%s%s", Patterns_PATH, MISCF64, "InputPhi81_f64.txt");
#else
	inputFileA = MISCF64_InputPhi81_f64;
	inputFileALen = sizeof(MISCF64_InputPhi81_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB, sizeof(inputFileB), "%s%s%s", Patterns_PATH, MISCF64, "InputPhi82_f64.txt");
#else
	inputFileB = MISCF64_InputPhi82_f64;
	inputFileBLen = sizeof(MISCF64_InputPhi82_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileC, sizeof(inputFileC), "%s%s%s", Patterns_PATH, MISCF64, "InputPhi83_f64.txt");
#else
	inputFileC = MISCF64_InputPhi83_f64;
	inputFileCLen = sizeof(MISCF64_InputPhi83_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileErrors, sizeof(inputFileErrors), "%s%s%s", Patterns_PATH, MISCF64, "LDErrors81_f64.txt");
#else
	inputFileErrors = MISCF64_LDErrors81_f64;
	inputFileErrorsLen = sizeof(MISCF64_LDErrors81_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileA2, sizeof(inputFileA2), "%s%s%s", Patterns_PATH, MISCF64, "InputsA2_f64.txt");
#else
	inputFileA2 = MISCF64_InputsA2_f64;
	inputFileA2Len = sizeof(MISCF64_InputsA2_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB2, sizeof(inputFileB2), "%s%s%s", Patterns_PATH, MISCF64, "InputsB2_f64.txt");
#else
	inputFileB2 = MISCF64_InputsB2_f64;
	inputFileB2Len = sizeof(MISCF64_InputsB2_f64);
#endif




	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileA1, &paramCountInputA1, f64inputA1);
#else
	paramCountInputA1 = inputFileA1Len;
	load_data_f64(inputFileA1, paramCountInputA1, f64inputA1);
	paramCountInputA1 = paramCountInputA1/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileB1, &paramCountInputB1, f64inputB1);
#else
	paramCountInputB1 = inputFileB1Len;
	load_data_f64(inputFileB1, paramCountInputB1, f64inputB1);
	paramCountInputB1 = paramCountInputB1/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileA, &paramCountInputA, f64inputA);
#else
	paramCountInputA = inputFileALen;
	load_data_f64(inputFileA, paramCountInputA, f64inputA);
	paramCountInputA = paramCountInputA/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileB, &paramCountInputB, f64inputB);
#else
	paramCountInputB = inputFileBLen;
	load_data_f64(inputFileB, paramCountInputB, f64inputB);
	paramCountInputB = paramCountInputB/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileC, &paramCountInputC, f64inputC);
#else
	paramCountInputC = inputFileCLen;
	load_data_f64(inputFileC, paramCountInputC, f64inputC);
	paramCountInputC = paramCountInputC/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileErrors, &paramCountInputErrors, f64inputErrors);
#else
	paramCountInputErrors = inputFileErrorsLen;
	load_data_f64(inputFileErrors, paramCountInputErrors, f64inputErrors);
	paramCountInputErrors = paramCountInputErrors/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileA2, &paramCountInputA2, f64inputA2);
#else
	paramCountInputA2 = inputFileA2Len;
	load_data_f64(inputFileA2, paramCountInputA2, f64inputA2);
	paramCountInputA2 = paramCountInputA2/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileB2, &paramCountInputB2, f64inputB2);
#else
	paramCountInputB2 = inputFileB2Len;
	load_data_f64(inputFileB2, paramCountInputB2, f64inputB2);
	paramCountInputB2 = paramCountInputB2/sizeof(f64);
#endif

    int num = 0;
    double f64output1[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
    char *id[] = {"Reference1_f64.txt", "Reference2_f64.txt", "Reference3_f64.txt", "Reference4_f64.txt", "Reference5_f64.txt", "Reference6_f64.txt", "Reference7_f64.txt", "Reference8_f64.txt", "Reference9_f64.txt", "Reference10_f64.txt", "Reference11_f64.txt", "Reference12_f64.txt", "Reference13_f64.txt", "Reference14_f64.txt", "Reference15_f64.txt", "Reference16_f64.txt", "Reference17_f64.txt", "Reference18_f64.txt", "Reference19_f64.txt", "Reference20_f64.txt", "Reference21_f64.txt", "Reference22_f64.txt", "Reference23_f64.txt", "Reference24_f64.txt", "Reference25_f64.txt", "Reference26_f64.txt", "Reference27_f64.txt", "Reference28_f64.txt", "Reference29_f64.txt", "Reference30_f64.txt", "Reference31_f64.txt", "Reference32_f64.txt", "Reference33_f64.txt", "Reference34_f64.txt", "Reference35_f64.txt", "Reference36_f64.txt", "Reference37_f64.txt", "Reference38_f64.txt", "Reference39_f64.txt", "Reference40_f64.txt", "Reference41_f64.txt", "Reference42_f64.txt", "Reference43_f64.txt", "Reference44_f64.txt", "Reference45_f64.txt", "Reference46_f64.txt", "Reference47_f64.txt", "Reference48_f64.txt", "Reference49_f64.txt", "Reference50_f64.txt", "Reference51_f64.txt", "Reference52_f64.txt", "Reference53_f64.txt", "Reference54_f64.txt", "Reference55_f64.txt", "Reference56_f64.txt", "Reference57_f64.txt", "Reference58_f64.txt", "Reference59_f64.txt", "Reference60_f64.txt", "Reference61_f64.txt", "Reference62_f64.txt", "Reference63_f64.txt", "Reference64_f64.txt", "Reference65_f64.txt", "Reference66_f64.txt", "Reference67_f64.txt", "Reference68_f64.txt", "Reference69_f64.txt", "Reference70_f64.txt", "Reference71_f64.txt", "Reference72_f64.txt", "Reference73_f64.txt", "Reference74_f64.txt", "Reference75_f64.txt", "Reference76_f64.txt", "Reference77_f64.txt", "Reference78_f64.txt", "Reference79_f64.txt", "Reference80_f64.txt", "Reference81_f64.txt", "Reference82_f64.txt", "Reference83_f64.txt", "Reference84_f64.txt", "Reference85_f64.txt", "Reference86_f64.txt"};
#else
    u64 id[100] = {MISCF64_Reference1_f64, MISCF64_Reference2_f64, MISCF64_Reference3_f64, MISCF64_Reference4_f64, MISCF64_Reference5_f64, MISCF64_Reference6_f64, MISCF64_Reference7_f64, MISCF64_Reference8_f64, MISCF64_Reference9_f64, MISCF64_Reference10_f64, MISCF64_Reference11_f64, MISCF64_Reference12_f64, MISCF64_Reference13_f64, MISCF64_Reference14_f64, MISCF64_Reference15_f64, MISCF64_Reference16_f64, MISCF64_Reference17_f64, MISCF64_Reference18_f64, MISCF64_Reference19_f64, MISCF64_Reference20_f64, MISCF64_Reference21_f64, MISCF64_Reference22_f64, MISCF64_Reference23_f64, MISCF64_Reference24_f64, MISCF64_Reference25_f64, MISCF64_Reference26_f64, MISCF64_Reference27_f64, MISCF64_Reference28_f64, MISCF64_Reference29_f64, MISCF64_Reference30_f64, MISCF64_Reference31_f64, MISCF64_Reference32_f64, MISCF64_Reference33_f64, MISCF64_Reference34_f64, MISCF64_Reference35_f64, MISCF64_Reference36_f64, MISCF64_Reference37_f64, MISCF64_Reference38_f64, MISCF64_Reference39_f64, MISCF64_Reference40_f64, MISCF64_Reference41_f64, MISCF64_Reference42_f64, MISCF64_Reference43_f64, MISCF64_Reference44_f64, MISCF64_Reference45_f64, MISCF64_Reference46_f64, MISCF64_Reference47_f64, MISCF64_Reference48_f64, MISCF64_Reference49_f64, MISCF64_Reference50_f64, MISCF64_Reference51_f64, MISCF64_Reference52_f64, MISCF64_Reference53_f64, MISCF64_Reference54_f64, MISCF64_Reference55_f64, MISCF64_Reference56_f64, MISCF64_Reference57_f64, MISCF64_Reference58_f64, MISCF64_Reference59_f64, MISCF64_Reference60_f64, MISCF64_Reference61_f64, MISCF64_Reference62_f64, MISCF64_Reference63_f64, MISCF64_Reference64_f64, MISCF64_Reference65_f64, MISCF64_Reference66_f64, MISCF64_Reference67_f64, MISCF64_Reference68_f64, MISCF64_Reference69_f64, MISCF64_Reference70_f64, MISCF64_Reference71_f64, MISCF64_Reference72_f64, MISCF64_Reference73_f64, MISCF64_Reference74_f64, MISCF64_Reference75_f64, MISCF64_Reference76_f64, MISCF64_Reference77_f64, MISCF64_Reference78_f64, MISCF64_Reference79_f64, MISCF64_Reference80_f64, MISCF64_Reference81_f64, MISCF64_Reference82_f64, MISCF64_Reference83_f64, MISCF64_Reference84_f64, MISCF64_Reference85_f64, MISCF64_Reference86_f64};
    u32 size[100] = {sizeof(MISCF64_Reference1_f64), sizeof(MISCF64_Reference2_f64), sizeof(MISCF64_Reference3_f64), sizeof(MISCF64_Reference4_f64), sizeof(MISCF64_Reference5_f64), sizeof(MISCF64_Reference6_f64), sizeof(MISCF64_Reference7_f64), sizeof(MISCF64_Reference8_f64), sizeof(MISCF64_Reference9_f64), sizeof(MISCF64_Reference10_f64), sizeof(MISCF64_Reference11_f64), sizeof(MISCF64_Reference12_f64), sizeof(MISCF64_Reference13_f64), sizeof(MISCF64_Reference14_f64), sizeof(MISCF64_Reference15_f64), sizeof(MISCF64_Reference16_f64), sizeof(MISCF64_Reference17_f64), sizeof(MISCF64_Reference18_f64), sizeof(MISCF64_Reference19_f64), sizeof(MISCF64_Reference20_f64), sizeof(MISCF64_Reference21_f64), sizeof(MISCF64_Reference22_f64), sizeof(MISCF64_Reference23_f64), sizeof(MISCF64_Reference24_f64), sizeof(MISCF64_Reference25_f64), sizeof(MISCF64_Reference26_f64), sizeof(MISCF64_Reference27_f64), sizeof(MISCF64_Reference28_f64), sizeof(MISCF64_Reference29_f64), sizeof(MISCF64_Reference30_f64), sizeof(MISCF64_Reference31_f64), sizeof(MISCF64_Reference32_f64), sizeof(MISCF64_Reference33_f64), sizeof(MISCF64_Reference34_f64), sizeof(MISCF64_Reference35_f64), sizeof(MISCF64_Reference36_f64), sizeof(MISCF64_Reference37_f64), sizeof(MISCF64_Reference38_f64), sizeof(MISCF64_Reference39_f64), sizeof(MISCF64_Reference40_f64), sizeof(MISCF64_Reference41_f64), sizeof(MISCF64_Reference42_f64), sizeof(MISCF64_Reference43_f64), sizeof(MISCF64_Reference44_f64), sizeof(MISCF64_Reference45_f64), sizeof(MISCF64_Reference46_f64), sizeof(MISCF64_Reference47_f64), sizeof(MISCF64_Reference48_f64), sizeof(MISCF64_Reference49_f64), sizeof(MISCF64_Reference50_f64), sizeof(MISCF64_Reference51_f64), sizeof(MISCF64_Reference52_f64), sizeof(MISCF64_Reference53_f64), sizeof(MISCF64_Reference54_f64), sizeof(MISCF64_Reference55_f64), sizeof(MISCF64_Reference56_f64), sizeof(MISCF64_Reference57_f64), sizeof(MISCF64_Reference58_f64), sizeof(MISCF64_Reference59_f64), sizeof(MISCF64_Reference60_f64), sizeof(MISCF64_Reference61_f64), sizeof(MISCF64_Reference62_f64), sizeof(MISCF64_Reference63_f64), sizeof(MISCF64_Reference64_f64), sizeof(MISCF64_Reference65_f64), sizeof(MISCF64_Reference66_f64), sizeof(MISCF64_Reference67_f64), sizeof(MISCF64_Reference68_f64), sizeof(MISCF64_Reference69_f64), sizeof(MISCF64_Reference70_f64), sizeof(MISCF64_Reference71_f64), sizeof(MISCF64_Reference72_f64), sizeof(MISCF64_Reference73_f64), sizeof(MISCF64_Reference74_f64), sizeof(MISCF64_Reference75_f64), sizeof(MISCF64_Reference76_f64), sizeof(MISCF64_Reference77_f64), sizeof(MISCF64_Reference78_f64), sizeof(MISCF64_Reference79_f64), sizeof(MISCF64_Reference80_f64), sizeof(MISCF64_Reference81_f64), sizeof(MISCF64_Reference82_f64), sizeof(MISCF64_Reference83_f64), sizeof(MISCF64_Reference84_f64), sizeof(MISCF64_Reference85_f64), sizeof(MISCF64_Reference86_f64)};
#endif
// =======test_correlate_f64==============

    for(num = 1; num <= 40; num++){

    inpA = f64inputA1;
    inpB = f64inputB1;
    outp = f64output1;
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
    printf("== correlate_f64  test ==  \n");

    mips_correlate_f64(inpA, nba,
      inpB, nbb,
      outp);
    
	printf("correlate_f64 finish \n");

	printf("correlate_f64 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCF64, id[num-1]);
#else
	referenceFile1 = id[num-1];
	referenceFile1Len = size[num-1];
    load_data_f64(referenceFile1, referenceFile1Len, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile1, f64output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile1, f64output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, referenceFile1Len, ABS_ERROR, REL_ERROR);
#endif

    memset(f64output1, 0, sizeof(double)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_f64, 0, sizeof(double)*MAX_SIZE);
#endif
	printf("\n== correlate_f64 check done  == \n\n");
    };

/*
// =======test_conv_f64 ==============

    for(num = 1; num <= 40; num++){

    inpA = f64inputA1;
    inpB = f64inputB1;
    outp = f64output1;
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
    printf("== conv_f64  test ==  \n");

    mips_conv_f64(inpA, nba,
      inpB, nbb,
      outp);
    
	printf("conv_f64 finish \n");

	printf("conv_f64 checking \n\n");

    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCF64, id[num+40-1]);

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile1, f64output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile1, f64output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

    memset(f64output1, 0, sizeof(double)*MAX_SIZE);
	printf("\n== conv_f64 check done  == \n\n");
    };
    
// =======test_levinson_durbin_f64==============

 for(num = 1; num <= 3; num++){
    double *errs;
    errs = f64inputErrors;
    double err;
    double refError = errs[errOffset];
    outp = f64output1;
    printf("test:%d \n",(num+80));
    switch (num)
    {
    case 1:
        inpA = f64inputA;
        nba = 3;
        errOffset = 0;
        break;
    case 2:
        inpA = f64inputB;
        nba = 8;
        errOffset = 1;
        break;
    case 3:
        inpA = f64inputC;
        nba = 11;
        errOffset = 2;
        break;

    default:
        break;
    }
    printf("== levinson_durbin_f64  test ==  \n");

    mips_levinson_durbin_f64(inpA,outp,&err,nba);
    
	printf("levinson_durbin_f64 finish \n");

	printf("levinson_durbin_f64 checking \n\n");

    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCF64, id[num+80-1]);

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile1, f64output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile1, f64output1, 0, ABS_LD_ERROR, REL_LD_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, referenceFileLen, ABS_LD_ERROR, REL_LD_ERROR);
#endif


    if (abs(err - refError) > (ABS_LD_ERROR + REL_LD_ERROR * abs(refError)))
		{
			char details[200];
			sprintf(details, "close error %g > %g: (val = %g, ref = %g)", abs(err - refError), ABS_LD_ERROR + REL_LD_ERROR * abs(refError), err, refError);
			printf("invalid value, details : %s \n", details);
		}
        else{
            printf("closeError count = 0, CLOSE Test PASSED!  \n");
        };
    memset(f64output1, 0, sizeof(double)*MAX_SIZE);

	printf("\n== levinson_durbin_f64 check done  == \n\n");
    };

// =======test_conv_partial_f64==============
    // This value must be coherent with the Python script
    // generating the test patterns
#define NBPOINTS 4

 for(num = 1; num <= 3; num++){
    inpA = f64inputA2;
    inpB = f64inputB2;
    outp = f64output1;
    double tmp[MAX_SIZE] = {0};
    double *tmpp;
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
    printf("== conv_partial_f64  test ==  \n");

    mips_status status=mips_conv_partial_f64(inpA, nba,
          inpB, nbb,
          outp,
          first,
          NBPOINTS);

    memcpy((void*)tmpp,(void*)&outp[first],NBPOINTS*sizeof(double));

	printf("conv_partial_f64 finish \n");

	printf("conv_partial_f64 checking \n\n");

    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCF64, id[num+83-1]);

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile1, tmp, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, tmp, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile1, tmp, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, tmp, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

    ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

    memset(f64output1, 0, sizeof(double)*MAX_SIZE);
    memset(tmp, 0, sizeof(double)*MAX_SIZE);
	printf("\n== conv_partial_f64 check done  == \n\n");
    };
*/

    return 0;
}

	

