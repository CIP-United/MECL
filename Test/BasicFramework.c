
#include "BasicFramework.h"


// =================================================================

/* loading data */

#if defined(NOT_EMBEDDED)
// f32
int load_data_f32(char *fileName, int *paramCount, float *loadedData)
{
	FILE *fp;
	int dataCount = 0;
	char buffer[256];

	// char file[20] = "Input1_f32.txt";

	fp = fopen(fileName, "r");
	if (!fp) // if file not exist
	{
		printf("File not exist! loading \033[1;31;40mFAILED \033[0m! filename: %s \n", fileName);
		return -1;
	}

	int currentLineNumber = 1; // current reading line
	char line[32];

	// get data counts
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (currentLineNumber == 2)
		{
			dataCount = atoi(line);
			// printf("Line %d \n", dataCount);
			break;
		}
		currentLineNumber++;
	}

	// total file lines
	int readEndline = dataCount + 2 + 1;

	// read line 3
	fgets(line, sizeof(line), fp);

	int dataSN = 0;

	// read following line
	// vaild data start from line 4
	// for (size_t i = 4; i < readEndline; i += 2)
	for (size_t i = 0; i < dataCount; i++)
	{

		uint32_t val;
		fscanf(fp, "0x%08X\n", &val);
		fgets(line, sizeof(line), fp);
		// printf("result1111 %08x \n", val);
		loadedData[dataSN] = *(float *)&val;
		dataSN++;
	}
	*paramCount = dataCount;

	fclose(fp);
	return 0;
}

// f64
int load_data_f64(char *fileName, int *paramCount, double *loadedData)
{
	FILE *fp;
	int dataCount = 0;
	char buffer[256];

	// char file[20] = "Input1_f32.txt";

	fp = fopen(fileName, "r");
	if (!fp) // if file not exist
	{
		printf("File not exist! loading \033[1;31;40mFAILED \033[0m! filename: %s \n", fileName);
		return -1;
	}

	int currentLineNumber = 1; // current reading line
	char line[32];

	// get data counts
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (currentLineNumber == 2)
		{
			dataCount = atoi(line);
			// printf("Line %d \n", dataCount);
			break;
		}
		currentLineNumber++;
	}

	// total file lines
	int readEndline = dataCount + 2 + 1;

	// read line 3
	fgets(line, sizeof(line), fp);

	int dataSN = 0;

	// read following line
	// vaild data start from line 4
	// for (size_t i = 4; i < readEndline; i += 2)
	for (size_t i = 0; i < dataCount; i++)
	{

		uint64_t val;
		fscanf(fp, "0x%16llx\n", &val);
		fgets(line, sizeof(line), fp);
		// printf("result1111 %08x \n", val);
		loadedData[dataSN] = *(double *)&val;
		dataSN++;
	}
	*paramCount = dataCount;

	fclose(fp);
	return 0;
}

// q63
int load_data_q63(char *fileName, int *paramCount, q63 *loadedData)
{
	FILE *fp;
	int dataCount = 0;
	char buffer[256];

	// char file[20] = "Input1_f32.txt";

	fp = fopen(fileName, "r");
	if (!fp) // if file not exist
	{
		printf("File not exist! loading \033[1;31;40mFAILED \033[0m! filename: %s \n", fileName);
		return -1;
	}

	int currentLineNumber = 1; // current reading line
	char line[32];

	// get data counts
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (currentLineNumber == 2)
		{
			dataCount = atoi(line);
			// printf("Line %d \n", dataCount);
			break;
		}
		currentLineNumber++;
	}

	// total file lines
	int readEndline = dataCount + 2 + 1;

	// read line 3
	fgets(line, sizeof(line), fp);

	int dataSN = 0;

	// read following line
	// vaild data start from line 4
	// for (size_t i = 4; i < readEndline; i += 2)
	for (size_t i = 0; i < dataCount; i++)
	{

		uint64_t val;
		fscanf(fp, "0x%16llx\n", &val);
		fgets(line, sizeof(line), fp);
		// printf("result1111 %08x \n", val);
		loadedData[dataSN] = *(q63 *)&val;
		dataSN++;
	}
	*paramCount = dataCount;

	fclose(fp);
	return 0;
}

// q31
int load_data_q31(char *fileName, int *paramCount, q31 *loadedData)
{
	FILE *fp;
	int dataCount = 0;
	char buffer[256];

	// char file[20] = "Input1_f32.txt";

	fp = fopen(fileName, "r");
	if (!fp) // if file not exist
	{
		printf("File not exist! loading \033[1;31;40mFAILED \033[0m! filename: %s \n", fileName);
		return -1;
	}

	int currentLineNumber = 1; // current reading line
	char line[32];

	// get data counts
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (currentLineNumber == 2)
		{
			dataCount = atoi(line);
			// printf("Line %d \n", dataCount);
			break;
		}
		currentLineNumber++;
	}

	// total file lines
	int readEndline = dataCount + 2 + 1;

	// read line 3
	fgets(line, sizeof(line), fp);

	int dataSN = 0;

	// read following line
	// vaild data start from line 4
	// for (size_t i = 4; i < readEndline; i += 2)
	for (size_t i = 0; i < dataCount; i++)
	{

		uint32_t val;
		fscanf(fp, "0x%08X\n", &val);
		fgets(line, sizeof(line), fp);
		// printf("result1111 %08x \n", val);
		loadedData[dataSN] = *(q31 *)&val;
		dataSN++;
	}
	*paramCount = dataCount;

	fclose(fp);
	return 0;
}

// q15
int load_data_q15(char *fileName, int *paramCount, q15 *loadedData)
{
	FILE *fp;
	int dataCount = 0;
	char buffer[256];

	// char file[20] = "Input1_f32.txt";

	fp = fopen(fileName, "r");
	if (!fp) // if file not exist
	{
		printf("File not exist! loading \033[1;31;40mFAILED \033[0m! filename: %s \n", fileName);
		return -1;
	}

	int currentLineNumber = 1; // current reading line
	char line[32];

	// get data counts
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (currentLineNumber == 2)
		{
			dataCount = atoi(line);
			// printf("Line %d \n", dataCount);
			break;
		}
		currentLineNumber++;
	}

	// total file lines
	int readEndline = dataCount + 2 + 1;

	// read line 3
	fgets(line, sizeof(line), fp);

	int dataSN = 0;

	// read following line
	// vaild data start from line 4
	// for (size_t i = 4; i < readEndline; i += 2)
	for (size_t i = 0; i < dataCount; i++)
	{

		uint32_t val;
		fscanf(fp, "0x%08X\n", &val);
		fgets(line, sizeof(line), fp);
		// printf("result1111 %08x \n", val);
		loadedData[dataSN] = *(q15 *)&val;
		dataSN++;
	}
	*paramCount = dataCount;

	fclose(fp);
	return 0;
}

// q7
int load_data_q7(char *fileName, int *paramCount, q7 *loadedData)
{
	FILE *fp;
	int dataCount = 0;
	char buffer[256];

	// char file[20] = "Input1_f32.txt";

	fp = fopen(fileName, "r");
	if (!fp) // if file not exist
	{
		printf("File not exist! loading \033[1;31;40mFAILED \033[0m! filename: %s \n", fileName);
		return -1;
	}

	int currentLineNumber = 1; // current reading line
	char line[32];

	// get data counts
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (currentLineNumber == 2)
		{
			dataCount = atoi(line);
			// printf("Line %d \n", dataCount);
			break;
		}
		currentLineNumber++;
	}

	// total file lines
	int readEndline = dataCount + 2 + 1;

	// read line 3
	fgets(line, sizeof(line), fp);

	int dataSN = 0;

	// read following line
	// vaild data start from line 4
	// for (size_t i = 4; i < readEndline; i += 2)
	for (size_t i = 0; i < dataCount; i++)
	{

		uint32_t val;
		fscanf(fp, "0x%08X\n", &val);
		fgets(line, sizeof(line), fp);
		// printf("result1111 %08x \n", val);
		loadedData[dataSN] = *(q7 *)&val;
		dataSN++;
	}
	*paramCount = dataCount;

	fclose(fp);
	return 0;
}

// u64
int load_data_u64(char *fileName, int *paramCount, uint64_t *loadedData)
{
	FILE *fp;
	int dataCount = 0;
	char buffer[256];

	// char file[20] = "Input1_f32.txt";

	fp = fopen(fileName, "r");
	if (!fp) // if file not exist
	{
		printf("File not exist! loading \033[1;31;40mFAILED \033[0m! filename: %s \n", fileName);
		return -1;
	}

	int currentLineNumber = 1; // current reading line
	char line[32];

	// get data counts
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (currentLineNumber == 2)
		{
			dataCount = atoi(line);
			// printf("Line %d \n", dataCount);
			break;
		}
		currentLineNumber++;
	}

	// total file lines
	int readEndline = dataCount + 2 + 1;

	// read line 3
	fgets(line, sizeof(line), fp);

	int dataSN = 0;

	// read following line
	// vaild data start from line 4
	// for (size_t i = 4; i < readEndline; i += 2)
	for (size_t i = 0; i < dataCount; i++)
	{
		uint64_t val;
		fscanf(fp, "0x%16llx\n", &val);
		fgets(line, sizeof(line), fp);
		// printf("result1111 %08x \n", val);
		loadedData[dataSN] = *(uint64_t *)&val;
		dataSN++;
	}
	*paramCount = dataCount;

	fclose(fp);
	return 0;
}

// u32
int load_data_u32(char *fileName, int *paramCount, uint32_t *loadedData)
{
	FILE *fp;
	int dataCount = 0;
	char buffer[256];

	// char file[20] = "Input1_f32.txt";

	fp = fopen(fileName, "r");
	if (!fp) // if file not exist
	{
		printf("File not exist! loading \033[1;31;40mFAILED \033[0m! filename: %s \n", fileName);
		return -1;
	}

	int currentLineNumber = 1; // current reading line
	char line[32];

	// get data counts
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (currentLineNumber == 2)
		{
			dataCount = atoi(line);
			// printf("Line %d \n", dataCount);
			break;
		}
		currentLineNumber++;
	}

	// total file lines
	int readEndline = dataCount + 2 + 1;

	// read line 3
	fgets(line, sizeof(line), fp);

	int dataSN = 0;

	// read following line
	// vaild data start from line 4
	// for (size_t i = 4; i < readEndline; i += 2)
	for (size_t i = 0; i < dataCount; i++)
	{

		uint32_t val;
		fscanf(fp, "0x%08X\n", &val);
		fgets(line, sizeof(line), fp);
		// printf("result1111 %08x \n", val);
		loadedData[dataSN] = *(uint32_t *)&val;
		dataSN++;
	}
	*paramCount = dataCount;

	fclose(fp);
	return 0;
}

// u16
int load_data_u16(char *fileName, int *paramCount, uint16_t *loadedData)
{
	FILE *fp;
	int dataCount = 0;
	char buffer[256];

	// char file[20] = "Input1_f32.txt";

	fp = fopen(fileName, "r");
	if (!fp) // if file not exist
	{
		printf("File not exist! loading \033[1;31;40mFAILED \033[0m! filename: %s \n", fileName);
		return -1;
	}

	int currentLineNumber = 1; // current reading line
	char line[32];

	// get data counts
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (currentLineNumber == 2)
		{
			dataCount = atoi(line);
			// printf("Line %d \n", dataCount);
			break;
		}
		currentLineNumber++;
	}

	// total file lines
	int readEndline = dataCount + 2 + 1;

	// read line 3
	fgets(line, sizeof(line), fp);

	int dataSN = 0;

	// read following line
	// vaild data start from line 4
	// for (size_t i = 4; i < readEndline; i += 2)
	for (size_t i = 0; i < dataCount; i++)
	{

		uint32_t val;
		fscanf(fp, "0x%08X\n", &val);
		fgets(line, sizeof(line), fp);
		// printf("result1111 %08x \n", val);
		loadedData[dataSN] = *(uint16_t *)&val;
		dataSN++;
	}
	*paramCount = dataCount;

	fclose(fp);
	return 0;
}

// u8
int load_data_u8(char *fileName, int *paramCount, uint8_t *loadedData)
{
	FILE *fp;
	int dataCount = 0;
	char buffer[256];

	// char file[20] = "Input1_f32.txt";

	fp = fopen(fileName, "r");
	if (!fp) // if file not exist
	{
		printf("File not exist! loading \033[1;31;40mFAILED \033[0m! filename: %s \n", fileName);
		return -1;
	}

	int currentLineNumber = 1; // current reading line
	char line[32];

	// get data counts
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (currentLineNumber == 2)
		{
			dataCount = atoi(line);
			// printf("Line %d \n", dataCount);
			break;
		}
		currentLineNumber++;
	}

	// total file lines
	int readEndline = dataCount + 2 + 1;

	// read line 3
	fgets(line, sizeof(line), fp);

	int dataSN = 0;

	// read following line
	// vaild data start from line 4
	// for (size_t i = 4; i < readEndline; i += 2)
	for (size_t i = 0; i < dataCount; i++)
	{

		uint32_t val;
		fscanf(fp, "0x%08X\n", &val);
		fgets(line, sizeof(line), fp);
		// printf("result1111 %08x \n", val);
		loadedData[dataSN] = *(uint8_t *)&val;
		dataSN++;
	}
	*paramCount = dataCount;

	fclose(fp);
	return 0;
}

#else

void load_data_f32(void *valuePointer, int dataSize, float *loadedData)
{
	memcpy(loadedData, valuePointer, dataSize);
}

void load_data_f64(void *valuePointer, int dataSize, double *loadedData)
{
	memcpy(loadedData, valuePointer, dataSize);
}

void load_data_q63(void *valuePointer, int dataSize, q63 *loadedData)
{
	memcpy(loadedData, valuePointer, dataSize);
}

void load_data_q31(void *valuePointer, int dataSize, q31 *loadedData)
{
	memcpy(loadedData, valuePointer, dataSize);
}

void load_data_q15(void *valuePointer, int dataSize, q15 *loadedData)
{
	memcpy(loadedData, valuePointer, dataSize);
}

void load_data_q7(void *valuePointer, int dataSize, q7 *loadedData)
{
	memcpy(loadedData, valuePointer, dataSize);
}


void load_data_u64(void *valuePointer, int dataSize, uint64_t *loadedData)
{
	memcpy(loadedData, valuePointer, dataSize);
}

void load_data_u32(void *valuePointer, int dataSize, uint32_t *loadedData)
{
	memcpy(loadedData, valuePointer, dataSize);
}

void load_data_u16(void *valuePointer, int dataSize, uint16_t *loadedData)
{
	memcpy(loadedData, valuePointer, dataSize);
}

void load_data_u8(void *valuePointer, int dataSize, uint8_t *loadedData)
{
	memcpy(loadedData, valuePointer, dataSize);
}

#endif

// =================================================================

static int max_paramCount_check(int maxCount,int readCount)
{
	int res = 0;
	if (maxCount < readCount)
	{
		printf(" Reference File Record Count less than check Count ! \n");
		res = 1;
	}
	return res;
}
// =================================================================

// assert function. DO NOT use it directly.
/* REL error check */
int assert_relative_error_f32(int count, float *pa, float *pb, float threshold)
{

	if (count == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int i = 0;
	int invalidCount = 0;

	float *ptrA = pa;
	float *ptrB = pb;
	char id[40];

	for (i = 0; i < count; i++)
	{
		float a = ptrA[i];
		float b = ptrB[i];
		double rel, delta, average;

		delta = abs(a - b);
		average = (abs((float)a) + abs((float)b)) / 2.0f;
		if (average != 0)
		{
			rel = delta / average;
			// printf("%6.9f %6.9f %6.9f %g %g\n",a,b,rel,delta,average);
			if (rel > threshold)
			{
				// printf("rel = %g, threshold %g \n",rel,threshold);
				char details[200];
				sprintf(details, "diff (%g,%g), %g > %g", a, b, rel, threshold);
				// throw (Error(RELATIVE_ERROR,nb,details));
				printf("invalid value SN = %d, details : %s \n", i, details);
				invalidCount++;
			}
			// else
			// 	printf("result %f , %f, %f \n", delta, rel, average); // debug only
		}
	}
	return invalidCount;
};

int assert_relative_error_f64(int count, double *pa, double *pb, double threshold)
{

	if (count == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int i = 0;
	int invalidCount = 0;

	double *ptrA = pa;
	double *ptrB = pb;
	char id[40];

	for (i = 0; i < count; i++)
	{
		double a = ptrA[i];
		double b = ptrB[i];
		double rel, delta, average;

		delta = abs(a - b);
		average = (abs(a) + abs(b)) / 2.0f;
		if (average != 0)
		{
			rel = delta / average;
			// printf("%6.9f %6.9f %6.9f %g %g\n",a,b,rel,delta,average);
			if (rel > threshold)
			{
				// printf("rel = %g, threshold %g \n",rel,threshold);
				char details[200];
				sprintf(details, "diff (%g,%g), %g > %g", a, b, rel, threshold);
				// throw (Error(RELATIVE_ERROR,nb,details));
				printf("invalid value SN = %d, details : %s \n", i, details);
				invalidCount++;
			}
			// else
			// 	printf("result %f , %f, %f \n", delta, rel, average); // debug only
		}
	}
	return invalidCount;
};

// =================================================================

/* Close error check */
int assert_close_error_f32(int count, float *pa, float *pb, double absthreshold, double relthreshold)
{
	// a: reference, b: value

	if (count == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int i = 0;
	int invalidCount = 0;

	float *ptrA = pa;
	float *ptrB = pb;
	char id[40];

	for (i = 0; i < count; i++)
	{
		float a = ptrA[i];
		float b = ptrB[i];
		double rel, delta, average;

		if (abs(b - a) > (absthreshold + relthreshold * abs(a)))
		{
			char details[200];
			sprintf(details, "close error %g > %g: (val = %g, ref = %g)", abs(b - a), absthreshold + relthreshold * abs(a), b, a);
			printf("invalid value SN = %d, details : %s \n", i, details);
		}
	}
	return invalidCount;
};

int assert_close_error_f64(int count, double *pa, double *pb, double absthreshold, double relthreshold)
{
	// a: reference, b: value

	if (count == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int i = 0;
	int invalidCount = 0;

	double *ptrA = pa;
	double *ptrB = pb;
	char id[40];

	for (i = 0; i < count; i++)
	{
		double a = ptrA[i];
		double b = ptrB[i];

		if (abs(b - a) > (absthreshold + relthreshold * abs(a)))
		{
			char details[200];
			sprintf(details, "close error %g > %g: (val = %g, ref = %g)", abs(b - a), absthreshold + relthreshold * abs(a), b, a);
			printf("invalid value SN = %d, details : %s \n", i, details);
		}
	}
	return invalidCount;
};

// =================================================================

/* SNR check */

/**
 * @brief  Calculation of SNR
 * @param  float*   Pointer to the reference buffer
 * @param  float*   Pointer to the test buffer
 * @param  uint32_t     total number of samples
 * @return float    SNR
 * The function calculates signal to noise ratio for the reference output
 * and test output
 */

/* If NaN, force SNR to 0.0 to ensure test will fail */
#define IFNANRETURNZERO(val) \
	if (isnan((val)))        \
	{                        \
		return (0.0);        \
	}

#define IFINFINITERETURN(val, def) \
	if (isinf((val)))              \
	{                              \
		if ((val) > 0)             \
		{                          \
			return (def);          \
		}                          \
		else                       \
		{                          \
			return (-def);         \
		}                          \
	}

float arm_snr_q63(q63 *pRef, q63 *pTest, uint32_t buffSize)
{
	double EnergySignal = 0.0, EnergyError = 0.0;
	uint32_t i;
	float SNR;

	double testVal, refVal;

	for (i = 0; i < buffSize; i++)
	{

		testVal = ((double)pTest[i]) / 9223372036854775808.0;
		refVal = ((double)pRef[i]) / 9223372036854775808.0;

		EnergySignal += refVal * refVal;
		EnergyError += (refVal - testVal) * (refVal - testVal);
	}

	SNR = 10 * log10(EnergySignal / EnergyError);

	/* Checking for a NAN value in SNR */
	IFNANRETURNZERO(SNR);
	IFINFINITERETURN(SNR, 100000.0);

	// printf("SNR = %f\n",SNR);

	return (SNR);
}

float arm_snr_q31(q31 *pRef, q31 *pTest, uint32_t buffSize)
{
	float EnergySignal = 0.0, EnergyError = 0.0;
	uint32_t i;
	float SNR;

	float testVal, refVal;

	for (i = 0; i < buffSize; i++)
	{

		testVal = ((float)pTest[i]) / 2147483648.0f;
		refVal = ((float)pRef[i]) / 2147483648.0f;

		EnergySignal += refVal * refVal;
		EnergyError += (refVal - testVal) * (refVal - testVal);
	}

	SNR = 10 * log10f(EnergySignal / EnergyError);

	/* Checking for a NAN value in SNR */
	IFNANRETURNZERO(SNR);
	IFINFINITERETURN(SNR, 100000.0);

	// printf("SNR = %f\n",SNR);

	return (SNR);
}

float arm_snr_q15(q15 *pRef, q15 *pTest, uint32_t buffSize)
{
	float EnergySignal = 0.0, EnergyError = 0.0;
	uint32_t i;
	float SNR;

	float testVal, refVal;

	for (i = 0; i < buffSize; i++)
	{

		testVal = ((float)pTest[i]) / 32768.0f;
		refVal = ((float)pRef[i]) / 32768.0f;

		EnergySignal += refVal * refVal;
		EnergyError += (refVal - testVal) * (refVal - testVal);
	}

	SNR = 10 * log10f(EnergySignal / EnergyError);

	/* Checking for a NAN value in SNR */
	IFNANRETURNZERO(SNR);
	IFINFINITERETURN(SNR, 100000.0);

	// printf("SNR = %f\n",SNR);

	return (SNR);
}

float arm_snr_q7(q7 *pRef, q7 *pTest, uint32_t buffSize)
{
	float EnergySignal = 0.0, EnergyError = 0.0;
	uint32_t i;
	float SNR;

	float testVal, refVal;

	for (i = 0; i < buffSize; i++)
	{

		testVal = ((float)pTest[i]) / 128.0f;
		refVal = ((float)pRef[i]) / 128.0f;

		EnergySignal += refVal * refVal;
		EnergyError += (refVal - testVal) * (refVal - testVal);
	}

	SNR = 10 * log10f(EnergySignal / EnergyError);

	IFNANRETURNZERO(SNR);
	IFINFINITERETURN(SNR, 100000.0);

	return (SNR);
}

int assert_snr_error_q63(int nb, q63 *pa, q63 *pb, float threshold)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	float snr;
	int i = 0;
	int res = 0;
	int invalidCount = 0;

#if SNR_MULTI
	snr = arm_snr_q63(pa, pb, nb);

	// printf("SNR = %f\n",snr);

	if (snr < threshold)
	{
		char details[200];
		sprintf(details, "SNR %g < %g", snr, threshold);
		printf("SNR_ERROR, details : %s \n", details);
		//  throw (Error(SNR_ERROR,nb,details));
		invalidCount = 1;
	}
#endif
#if SNR_SINGLE

	for (i = 0; i < nb; i++)
	{
		q63 a = pa[i];
		q63 b = pb[i];
		snr = arm_snr_q63(&a, &b, 1);

		// printf("SNR = %f\n",snr);

		if (snr < threshold)
		{
			char details[200];
			sprintf(details, "SNR %g < %g", snr, threshold);
			printf("SNR_ERROR, details : %s \n", details);
			//  throw (Error(SNR_ERROR,nb,details));
			invalidCount++;
			//  return 1;
		}
	}
#endif

	return invalidCount;
}

int assert_snr_error_q31(int nb, q31 *pa, q31 *pb, float threshold)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	float snr;
	int i = 0;
	int res = 0;
	int invalidCount = 0;

#if SNR_MULTI
	snr = arm_snr_q31(pa, pb, nb);

	// printf("SNR = %f\n",snr);

	if (snr < threshold)
	{
		char details[200];
		sprintf(details, "SNR %g < %g", snr, threshold);
		printf("SNR_ERROR, details : %s \n", details);
		//  throw (Error(SNR_ERROR,nb,details));
		invalidCount = 1;
	}
#endif
#if SNR_SINGLE

	for (i = 0; i < nb; i++)
	{
		q31 a = pa[i];
		q31 b = pb[i];
		snr = arm_snr_q31(&a, &b, 1);

		// printf("SNR = %f\n",snr);

		if (snr < threshold)
		{
			char details[200];
			sprintf(details, "SNR %g < %g", snr, threshold);
			printf("SNR_ERROR, details : %s \n", details);
			//  throw (Error(SNR_ERROR,nb,details));
			invalidCount++;
			//  return 1;
		}
	}
#endif

	return invalidCount;
}

int assert_snr_error_q15(int nb, q15 *pa, q15 *pb, float threshold)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	float snr;
	int i = 0;
	int res = 0;
	int invalidCount = 0;

#if SNR_MULTI
	snr = arm_snr_q15(pa, pb, nb);

	// printf("SNR = %f\n",snr);

	if (snr < threshold)
	{
		char details[200];
		sprintf(details, "SNR %g < %g", snr, threshold);
		printf("SNR_ERROR, details : %s \n", details);
		//  throw (Error(SNR_ERROR,nb,details));
		invalidCount = 1;
	}
#endif
#if SNR_SINGLE

	for (i = 0; i < nb; i++)
	{
		q15 a = pa[i];
		q15 b = pb[i];
		snr = arm_snr_q15(&a, &b, 1);

		// printf("SNR = %f\n",snr);

		if (snr < threshold)
		{
			char details[200];
			sprintf(details, "SNR %g < %g", snr, threshold);
			printf("SNR_ERROR, details : %s \n", details);
			//  throw (Error(SNR_ERROR,nb,details));
			invalidCount++;
			//  return 1;
		}
	}
#endif

	return invalidCount;
}

int assert_snr_error_q7(int nb, q7 *pa, q7 *pb, float threshold)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	float snr;
	int i = 0;
	int res = 0;
	int invalidCount = 0;

#if SNR_MULTI
	snr = arm_snr_q7(pa, pb, nb);

	// printf("SNR = %f\n",snr);

	if (snr < threshold)
	{
		char details[200];
		sprintf(details, "SNR %g < %g", snr, threshold);
		printf("SNR_ERROR, details : %s \n", details);
		//  throw (Error(SNR_ERROR,nb,details));
		invalidCount = 1;
	}
#endif
#if SNR_SINGLE

	for (i = 0; i < nb; i++)
	{
		q7 a = pa[i];
		q7 b = pb[i];
		snr = arm_snr_q7(&a, &b, 1);

		// printf("SNR = %f\n",snr);

		if (snr < threshold)
		{
			char details[200];
			sprintf(details, "SNR %g < %g", snr, threshold);
			printf("SNR_ERROR, details : %s \n", details);
			//  throw (Error(SNR_ERROR,nb,details));
			invalidCount++;
			//  return 1;
		}
	}
#endif

	return invalidCount;
}

float arm_snr_f32(float *pRef, float *pTest, uint32_t buffSize)
{
	float EnergySignal = 0.0, EnergyError = 0.0;
	uint32_t i;
	float SNR;

	for (i = 0; i < buffSize; i++)
	{
		/* Checking for a NAN value in pRef array */
		IFNANRETURNZERO(pRef[i]);

		/* Checking for a NAN value in pTest array */
		IFNANRETURNZERO(pTest[i]);

		EnergySignal += pRef[i] * pRef[i];
		EnergyError += (pRef[i] - pTest[i]) * (pRef[i] - pTest[i]);
	}

	/* Checking for a NAN value in EnergyError */
	IFNANRETURNZERO(EnergyError);

	SNR = 10 * log10f(EnergySignal / EnergyError);

	/* Checking for a NAN value in SNR */
	IFNANRETURNZERO(SNR);
	IFINFINITERETURN(SNR, 100000.0);

	return (SNR);
}

double arm_snr_f64(double *pRef, double *pTest, uint32_t buffSize)
{
	double EnergySignal = 0.0, EnergyError = 0.0;
	uint32_t i;
	double SNR;

	for (i = 0; i < buffSize; i++)
	{
		/* Checking for a NAN value in pRef array */
		IFNANRETURNZERO(pRef[i]);

		/* Checking for a NAN value in pTest array */
		IFNANRETURNZERO(pTest[i]);

		EnergySignal += pRef[i] * pRef[i];
		EnergyError += (pRef[i] - pTest[i]) * (pRef[i] - pTest[i]);
	}

	/* Checking for a NAN value in EnergyError */
	IFNANRETURNZERO(EnergyError);

	SNR = 10 * log10(EnergySignal / EnergyError);

	/* Checking for a NAN value in SNR */
	IFNANRETURNZERO(SNR);
	IFINFINITERETURN(SNR, 100000.0);

	return (SNR);
}

int assert_snr_error_f32(int nb, float *pa, float *pb, float threshold)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	float snr;
	int res = 0;

	snr = arm_snr_f32(pa, pb, nb);

	//    printf("SNR = %f\n",snr);

	if (snr < threshold)
	{
		char details[200];
		sprintf(details, "SNR %g < %g", snr, threshold);
		printf("SNR_ERROR, details : %s \n", details);
		res = 1;
	}

	return res;
}

int assert_snr_error_f64(int nb, double *a, double *b, double threshold)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	float snr;
	int res = 0;

	snr = arm_snr_f64(a, b, nb);

	// printf("SNR = %f\n",snr);

	if (snr < threshold)
	{
		char details[200];
		sprintf(details, "SNR %g < %g", snr, threshold);
		printf("SNR_ERROR, details : %s \n", details);
		res = 1;
	}
	return res;
}

int assert_near_equal_f64(int nb, double *pa, double *pb, double threshold)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int invalidCount = 0;
	for (int i = 0; i < nb; i++)
	{
		double a = pa[i];
		double b = pb[i];
		if (fabs(a - b) > threshold)
		{
			char details[200];
			sprintf(details, "diff %g > %g (%g,%g)", fabs(a - b), threshold, a, b);
			printf("invalid value SN = %d, details : %s \n", i, details);
			invalidCount++;
		}
	}
	return invalidCount;
};

int assert_near_equal_f32(int nb, float *pa, float *pb, float threshold)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int invalidCount = 0;
	for (int i = 0; i < nb; i++)
	{
		float a = pa[i];
		float b = pb[i];
		if (fabs(a - b) > threshold)
		{
			char details[200];
			sprintf(details, "diff %g > %g (%g,%g)", fabs(a - b), threshold, a, b);
			printf("invalid value SN = %d, details : %s \n", i, details);
			invalidCount++;
		}
	}
	return invalidCount;
};

int assert_near_equal_q63(int nb, q63 *pa, q63 *pb, q63 threshold)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int invalidCount = 0;
	for (int i = 0; i < nb; i++)
	{
		q63 a = pa[i];
		q63 b = pb[i];
		if (abs(a - b) > threshold)
		{
			char details[200];
#if __sizeof_long == 8
			sprintf(details, "diff %ld > %ld (0x%016lX,0x%016lX)", abs(pa - pb), threshold, pa, pb);
#else
			sprintf(details, "diff %lld > %lld (0x%016llX,0x%016llX)", abs(a - b), threshold, a, b);
#endif
			printf("invalid value SN = %d, details : %s \n", i, details);
			invalidCount++;
		}
	}
	return invalidCount;
};

int assert_near_equal_q31(int nb, q31 *pa, q31 *pb, q31 threshold)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int invalidCount = 0;
	for (int i = 0; i < nb; i++)
	{
		q31 a = pa[i];
		q31 b = pb[i];
		if (abs(a - b) > threshold)
		{
			char details[200];
			sprintf(details, "diff %d > %d (0x%08X,0x%08X)", abs(a - b), threshold, a, b);
			printf("invalid value SN = %d, details : %s \n", i, details);
			invalidCount++;
		}
	}
	return invalidCount;
};

int assert_near_equal_q15(int nb, q15 *pa, q15 *pb, q15 threshold)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int invalidCount = 0;
	for (int i = 0; i < nb; i++)
	{
		q15 a = pa[i];
		q15 b = pb[i];
		if (abs(a - b) > threshold)
		{
			char details[200];
			sprintf(details, "diff %d > %d (0x%04X,0x%04X)", abs(a - b), threshold, a, b);
			printf("invalid value SN = %d, details : %s \n", i, details);
			invalidCount++;
		}
	}
	return invalidCount;
};

int assert_near_equal_q7(int nb, q7 *pa, q7 *pb, q7 threshold)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int invalidCount = 0;
	for (int i = 0; i < nb; i++)
	{
		q7 a = pa[i];
		q7 b = pb[i];
		if (abs(a - b) > threshold)
		{
			char details[200];
			sprintf(details, "diff %d > %d (0x%02X,0x%02X)", abs(a - b), threshold, a, b);
			printf("invalid value SN = %d, details : %s \n", i, details);
			invalidCount++;
		}
	}
	return invalidCount;
};

int assert_equal_f64(int nb, double *pa, double *pb)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int invalidCount = 0;

	for (int i = 0; i < nb; i++)
	{
		double a = pa[i];
		double b = pb[i];
		if (a != b)
		{
			printf("invalid value SN = %d \n", i);
			invalidCount++;
		}
	}
	return invalidCount;
};

int assert_equal_f32(int nb, float *pa, float *pb)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int invalidCount = 0;

	for (int i = 0; i < nb; i++)
	{
		float a = pa[i];
		float b = pb[i];
		if (a != b)
		{
			printf("invalid value SN = %d \n", i);
			invalidCount++;
		}
	}
	return invalidCount;
};

int assert_equal_q63(int nb, q63 *pa, q63 *pb)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int invalidCount = 0;

	for (int i = 0; i < nb; i++)
	{
		q63 a = pa[i];
		q63 b = pb[i];
		if (a != b)
		{
			printf("invalid value SN = %d \n", i);
			invalidCount++;
		}
	}
	return invalidCount;
};

int assert_equal_q31(int nb, q31 *pa, q31 *pb)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int invalidCount = 0;

	for (int i = 0; i < nb; i++)
	{
		q31 a = pa[i];
		q31 b = pb[i];
		if (a != b)
		{
			printf("invalid value SN = %d , reference 0x%08X diff with value 0x%08X, \n", i, a, b);
			invalidCount++;
		}
	}
	return invalidCount;
};

int assert_equal_q15(int nb, q15 *pa, q15 *pb)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int invalidCount = 0;

	for (int i = 0; i < nb; i++)
	{
		q15 a = pa[i];
		q15 b = pb[i];
		if (a != b)
		{
			printf("invalid value SN = %d , reference 0x%04X diff with value 0x%04X, \n", i, a, b);
			invalidCount++;
		}
	}
	return invalidCount;
};

int assert_equal_q7(int nb, q7 *pa, q7 *pb)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}


	int invalidCount = 0;

	for (int i = 0; i < nb; i++)
	{
		q7 a = pa[i];
		q7 b = pb[i];
		if (a != b)
		{
			printf("invalid value SN = %d , reference 0x%02X diff with value 0x%02X, \n", i, a, b);
			invalidCount++;
		}
	}
	return invalidCount;
};

int assert_equal_u32(int nb, uint32_t *pa, uint32_t *pb)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}

	int invalidCount = 0;

	for (int i = 0; i < nb; i++)
	{
		uint32_t a = pa[i];
		uint32_t b = pb[i];
		if (a != b)
		{
			printf("invalid value SN = %d , reference 0x%08X diff with value 0x%08X, \n", i, a, b);
			invalidCount++;
		}
	}
	return invalidCount;
};

int assert_equal_u16(int nb, uint16_t *pa, uint16_t *pb)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}


	int invalidCount = 0;

	for (int i = 0; i < nb; i++)
	{
		uint16_t a = pa[i];
		uint16_t b = pb[i];
		if (a != b)
		{
			printf("invalid value SN = %d , reference 0x%04X diff with value 0x%04X, \n", i, a, b);
			invalidCount++;
		}
	}
	return invalidCount;
};

int assert_equal_u8(int nb, uint8_t *pa, uint8_t *pb)
{
	if (nb == 0)
	{
		printf("No data to check !\n");
		return -2;
	}


	int invalidCount = 0;

	for (int i = 0; i < nb; i++)
	{
		uint8_t a = pa[i];
		uint8_t b = pb[i];
		if (a != b)
		{
			printf("invalid value SN = %d , reference 0x%02X diff with value 0x%02X, \n", i, a, b);
			invalidCount++;
		}
	}
	return invalidCount;
};

// =================================================================
/* relative check. use it instead of use assert directly */

int rel_check_f32(char *referFileName, float *resultToCheck, int paramCount, float threshold)
{
	int relError = 0;
	float refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_f32(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		relError = -1;
	}
	else
		relError = assert_relative_error_f32(paramCount, refrenceData, resultToCheck, threshold);

	if (relError == 0)
		printf("relError count = 0, REL Test PASSED! \n");
	else
		printf("relError count = %d, Please check your data or function \n", relError);

	return 0;
}

int rel_check_f64(char *referFileName, double *resultToCheck, int paramCount, double threshold)
{
	int relError = 0;
	double refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_f64(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		relError = -1;
	}
	else
		relError = assert_relative_error_f64(paramCount, refrenceData, resultToCheck, threshold);

	if (relError == 0)
		printf("relError count = 0, REL Test PASSED! \n");
	else
		printf("relError count = %d, Please check your data or function \n", relError);

	return 0;
}

// =================================================================
/* snr check. use it instead of use assert directly */

int snr_check_f64(char *referFileName, double *resultToCheck, int paramCount, double threshold)
{
	int snrError = 0;
	double refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_f64(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		snrError = -1;
	}
	else
		snrError = assert_snr_error_f64(paramCount, refrenceData, resultToCheck, threshold);

	if (snrError == 0)
		printf("snrError count = 0, SNR Test PASSED! \n");
	else
#if SNR_MULTI
		printf("SNR Test \033[1;31;40mFAILED \033[0m! , Please check your data or function \n");
#endif
#if SNR_SINGLE
	printf("snrError count = %d, Please check your data or function \n", snrError);
#endif
	return 0;
}

int snr_check_f32(char *referFileName, float *resultToCheck, int paramCount, float threshold)
{
	int snrError = 0;
	float refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_f32(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		snrError = -1;
	}
	else
		snrError = assert_snr_error_f32(paramCount, refrenceData, resultToCheck, threshold);

	if (snrError == 0)
		printf("snrError count = 0, SNR Test PASSED! \n");
	else
#if SNR_MULTI
		printf("SNR Test \033[1;31;40mFAILED \033[0m! , Please check your data or function \n");
#endif
#if SNR_SINGLE
	printf("snrError count = %d, Please check your data or function \n", snrError);
#endif
	return 0;
}

int snr_check_q63(char *referFileName, q63 *resultToCheck, int paramCount, float threshold)
{
	int snrError = 0;
	q63 refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_q63(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		snrError = -1;
	}
	else
		snrError = assert_snr_error_q63(paramCount, refrenceData, resultToCheck, threshold);

	if (snrError == 0)
		printf("snrError count = 0, SNR Test PASSED! \n");
	else
#if SNR_MULTI
		printf("SNR Test \033[1;31;40mFAILED \033[0m! , Please check your data or function \n");
#endif
#if SNR_SINGLE
	printf("snrError count = %d, Please check your data or function \n", snrError);
#endif
	return 0;
}

int snr_check_q31(char *referFileName, q31 *resultToCheck, int paramCount, float threshold)
{
	int snrError = 0;
	q31 refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_q31(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		snrError = -1;
	}
	else
		snrError = assert_snr_error_q31(paramCount, refrenceData, resultToCheck, threshold);

	if (snrError == 0)
		printf("snrError count = 0, SNR Test PASSED! \n");
	else
#if SNR_MULTI
		printf("SNR Test \033[1;31;40mFAILED \033[0m! , Please check your data or function \n");
#endif
#if SNR_SINGLE
	printf("snrError count = %d, Please check your data or function \n", snrError);
#endif
	return 0;
}

int snr_check_q15(char *referFileName, q15 *resultToCheck, int paramCount, float threshold)
{
	int snrError = 0;
	q15 refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_q15(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		snrError = -1;
	}
	else
		snrError = assert_snr_error_q15(paramCount, refrenceData, resultToCheck, threshold);

	if (snrError == 0)
		printf("snrError count = 0, SNR Test PASSED! \n");
	else
#if SNR_MULTI
		printf("SNR Test \033[1;31;40mFAILED \033[0m! , Please check your data or function \n");
#endif
#if SNR_SINGLE
	printf("snrError count = %d, Please check your data or function \n", snrError);
#endif
	return 0;
}

int snr_check_q7(char *referFileName, q7 *resultToCheck, int paramCount, float threshold)
{
	int snrError = 0;
	q7 refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_q7(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		snrError = -1;
	}
	else
		snrError = assert_snr_error_q7(paramCount, refrenceData, resultToCheck, threshold);

	if (snrError == 0)
		printf("snrError count = 0, SNR Test PASSED! \n");
	else
#if SNR_MULTI
		printf("SNR Test \033[1;31;40mFAILED \033[0m! , Please check your data or function \n");
#endif
#if SNR_SINGLE
	printf("snrError count = %d, Please check your data or function \n", snrError);
#endif
	return 0;
}

// =================================================================
/* near equal check. use it instead of use assert directly */

int near_check_f64(char *referFileName, double *resultToCheck, int paramCount, double threshold)
{
	int nearError = 0;
	double refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_f64(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		nearError = -1;
	}
	else
		nearError = assert_near_equal_f64(paramCount, refrenceData, resultToCheck, threshold);

	if (nearError == 0)
		printf("nearError count = 0, NEAR_EQ Test PASSED! \n");
	else
		printf("nearError count = %d, Please check your data or function \n", nearError);

	return 0;
}

int near_check_f32(char *referFileName, float *resultToCheck, int paramCount, float threshold)
{
	int nearError = 0;
	float refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_f32(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		nearError = -1;
	}
	else
		nearError = assert_near_equal_f32(paramCount, refrenceData, resultToCheck, threshold);

	if (nearError == 0)
		printf("nearError count = 0, NEAR_EQ Test PASSED! \n");
	else
		printf("nearError count = %d, Please check your data or function \n", nearError);

	return 0;
}

int near_check_q63(char *referFileName, q63 *resultToCheck, int paramCount, q63 threshold)
{
	int nearError = 0;
	q63 refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_q63(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		nearError = -1;
	}
	else
		nearError = assert_near_equal_q63(paramCount, refrenceData, resultToCheck, threshold);

	if (nearError == 0)
		printf("nearError count = 0, NEAR_EQ Test PASSED! \n");
	else
		printf("nearError count = %d, Please check your data or function \n", nearError);

	return 0;
}

int near_check_q31(char *referFileName, q31 *resultToCheck, int paramCount, q31 threshold)
{
	int nearError = 0;
	q31 refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_q31(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		nearError = -1;
	}
	else
		nearError = assert_near_equal_q31(paramCount, refrenceData, resultToCheck, threshold);

	if (nearError == 0)
		printf("nearError count = 0, NEAR_EQ Test PASSED! \n");
	else
		printf("nearError count = %d, Please check your data or function \n", nearError);

	return 0;
}

int near_check_q15(char *referFileName, q15 *resultToCheck, int paramCount, q15 threshold)
{
	int nearError = 0;
	q15 refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_q15(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		nearError = -1;
	}
	else
		nearError = assert_near_equal_q15(paramCount, refrenceData, resultToCheck, threshold);

	if (nearError == 0)
		printf("nearError count = 0, NEAR_EQ Test PASSED! \n");
	else
		printf("nearError count = %d, Please check your data or function \n", nearError);

	return 0;
}

int near_check_q7(char *referFileName, q7 *resultToCheck, int paramCount, q7 threshold)
{
	int nearError = 0;
	q7 refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_q7(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		nearError = -1;
	}
	else
		nearError = assert_near_equal_q7(paramCount, refrenceData, resultToCheck, threshold);

	if (nearError == 0)
		printf("nearError count = 0, NEAR_EQ Test PASSED! \n");
	else
		printf("nearError count = %d, Please check your data or function \n", nearError);

	return 0;
}

// =================================================================
/* eq equal check. use it instead of use assert directly */

int eq_check_f64(char *referFileName, double *resultToCheck, int paramCount)
{
	int eqError = 0;
	double refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_f64(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		eqError = -1;
	}
	else
		eqError = assert_equal_f64(paramCount, refrenceData, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_f32(char *referFileName, float *resultToCheck, int paramCount)
{
	int eqError = 0;
	float refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_f32(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		eqError = -1;
	}
	else
		eqError = assert_equal_f32(paramCount, refrenceData, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_q63(char *referFileName, q63 *resultToCheck, int paramCount)
{
	int eqError = 0;
	q63 refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_q63(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		eqError = -1;
	}
	else
		eqError = assert_equal_q63(paramCount, refrenceData, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_q31(char *referFileName, q31 *resultToCheck, int paramCount)
{
	int eqError = 0;
	q31 refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_q31(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		eqError = -1;
	}
	else
		eqError = assert_equal_q31(paramCount, refrenceData, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_q15(char *referFileName, q15 *resultToCheck, int paramCount)
{
	int eqError = 0;
	q15 refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_q15(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		eqError = -1;
	}
	else
		eqError = assert_equal_q15(paramCount, refrenceData, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_q7(char *referFileName, q7 *resultToCheck, int paramCount)
{
	int eqError = 0;
	q7 refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_q7(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		eqError = -1;
	}
	else
		eqError = assert_equal_q7(paramCount, refrenceData, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_u32(char *referFileName, uint32_t *resultToCheck, int paramCount)
{
	int eqError = 0;
	uint32_t refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_u32(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		eqError = -1;
	}
	else
		eqError = assert_equal_u32(paramCount, refrenceData, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_u16(char *referFileName, uint16_t *resultToCheck, int paramCount)
{
	int eqError = 0;
	uint16_t refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_u16(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		eqError = -1;
	}
	else
		eqError = assert_equal_u16(paramCount, refrenceData, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_u8(char *referFileName, uint8_t *resultToCheck, int paramCount)
{
	int eqError = 0;
	uint8_t refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_u8(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		eqError = -1;
	}
	else
		eqError = assert_equal_u8(paramCount, refrenceData, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

// =================================================================
/* close check. use it instead of use assert directly */

int close_check_f32(char *referFileName, float *resultToCheck, int paramCount, double absthreshold, double relthreshold)
{
	int closeError = 0;
	float refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_f32(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		closeError = -1;
	}
	else
		closeError = assert_close_error_f32(paramCount, refrenceData, resultToCheck, absthreshold, relthreshold);

	if (closeError == 0)
		printf("closeError count = 0, CLOSE Test PASSED! \n");
	else
		printf("closeError count = %d, Please check your data or function \n", closeError);

	return 0;
}

int close_check_f64(char *referFileName, double *resultToCheck, int paramCount, double absthreshold, double relthreshold)
{
	int closeError = 0;
	double refrenceData[MAX_SIZE] = {0};
	int readCount = 0;

	load_data_f64(referFileName, &readCount, refrenceData);

	if (paramCount == 0)
		paramCount = readCount;

	if (max_paramCount_check(readCount, paramCount))
	{
		closeError = -1;
	}
	else
		closeError = assert_close_error_f64(paramCount, refrenceData, resultToCheck, absthreshold, relthreshold);

	if (closeError == 0)
		printf("closeError count = 0, CLOSE Test PASSED! \n");
	else
		printf("closeError count = %d, Please check your data or function \n", closeError);

	return 0;
}

int close_check_special_f32(float * referdata, float *resultToCheck, int paramCount, double absthreshold, double relthreshold)
{
	int closeError = 0;

	closeError = assert_close_error_f32(paramCount, referdata, resultToCheck, absthreshold, relthreshold);

	if (closeError == 0)
		printf("closeError count = 0, CLOSE Test PASSED! \n");
	else
		printf("closeError count = %d, Please check your data or function \n", closeError);

	return 0;
}

int close_check_special_f64(double * referdata, double *resultToCheck, int paramCount, double absthreshold, double relthreshold)
{
	int closeError = 0;

	closeError = assert_close_error_f64(paramCount, referdata, resultToCheck, absthreshold, relthreshold);

	if (closeError == 0)
		printf("closeError count = 0, CLOSE Test PASSED! \n");
	else
		printf("closeError count = %d, Please check your data or function \n", closeError);

	return 0;
}

void assert_true(unsigned long nb,bool cond)
{
   if (!cond)
   {
     printf("\033[1;31;40mInvalid \033[0m if judged true! Line: %d\n", nb);
   }
}

void assert_false(unsigned long nb,bool cond)
{
   if (cond)
   {
      printf("\033[1;31;40mInvalid \033[0m if judged false! Line: %d\n", nb);
   }
}

int rel_check_special_f32(float *referdata, float *resultToCheck, int paramCount, float threshold)
{
	int relError = 0;

	relError = assert_relative_error_f32(paramCount, referdata, resultToCheck, threshold);

	if (relError == 0)
		printf("relError count = 0, REL Test PASSED! \n");
	else
		printf("relError count = %d, Please check your data or function \n", relError);

	return 0;
}


int rel_check_special_f64(double *referdata, double *resultToCheck, int paramCount, double threshold)
{
	int relError = 0;

	relError = assert_relative_error_f64(paramCount, referdata, resultToCheck, threshold);

	if (relError == 0)
		printf("relError count = 0, REL Test PASSED! \n");
	else
		printf("relError count = %d, Please check your data or function \n", relError);

	return 0;
}

int snr_check_special_f32(float *referdata, float *resultToCheck, int paramCount, float threshold)
{
	int snrError = 0;
		snrError = assert_snr_error_f32(paramCount, referdata, resultToCheck, threshold);

	if (snrError == 0)
		printf("snrError count = 0, SNR Test PASSED! \n");
	else
		printf("snrError count = %d, Please check your data or function \n", snrError);

	return 0;
}

int snr_check_special_f64(f64 *referdata, f64 *resultToCheck, int paramCount, f64 threshold)
{
	int snrError = 0;
		snrError = assert_snr_error_f64(paramCount, referdata, resultToCheck, threshold);

	if (snrError == 0)
		printf("snrError count = 0, SNR Test PASSED! \n");
	else
		printf("snrError count = %d, Please check your data or function \n", snrError);

	return 0;
}

int snr_check_special_q7(q7 *referdata, q7 *resultToCheck, int paramCount, f32 threshold)
{
	int snrError = 0;
		snrError = assert_snr_error_q7(paramCount, referdata, resultToCheck, threshold);

	if (snrError == 0)
		printf("snrError count = 0, SNR Test PASSED! \n");
	else
		printf("snrError count = %d, Please check your data or function \n", snrError);

	return 0;
}

int snr_check_special_q15(q15 *referdata, q15 *resultToCheck, int paramCount, f32 threshold)
{
	int snrError = 0;
		snrError = assert_snr_error_q15(paramCount, referdata, resultToCheck, threshold);

	if (snrError == 0)
		printf("snrError count = 0, SNR Test PASSED! \n");
	else
		printf("snrError count = %d, Please check your data or function \n", snrError);

	return 0;
}

int snr_check_special_q31(q31 *referdata, q31 *resultToCheck, int paramCount, f32 threshold)
{
	int snrError = 0;
		snrError = assert_snr_error_q31(paramCount, referdata, resultToCheck, threshold);

	if (snrError == 0)
		printf("snrError count = 0, SNR Test PASSED! \n");
	else
		printf("snrError count = %d, Please check your data or function \n", snrError);

	return 0;
}

int snr_check_special_q63(q63 *referdata, q63 *resultToCheck, int paramCount, f32 threshold)
{
	int snrError = 0;
		snrError = assert_snr_error_q63(paramCount, referdata, resultToCheck, threshold);

	if (snrError == 0)
		printf("snrError count = 0, SNR Test PASSED! \n");
	else
		printf("snrError count = %d, Please check your data or function \n", snrError);

	return 0;
}

int near_check_special_f32(f32 *referdata, f32 *resultToCheck, int paramCount, f32 threshold)
{
	int snrError = 0;
		snrError = assert_near_equal_f32(paramCount, referdata, resultToCheck, threshold);

	if (snrError == 0)
		printf("nearError count = 0, NEAR Test PASSED! \n");
	else
		printf("nearError count = %d, Please check your data or function \n", snrError);

	return 0;
}

int near_check_special_f64(f64 *referdata, f64 *resultToCheck, int paramCount, f64 threshold)
{
	int snrError = 0;
		snrError = assert_near_equal_f64(paramCount, referdata, resultToCheck, threshold);

	if (snrError == 0)
		printf("nearError count = 0, NEAR Test PASSED! \n");
	else
		printf("nearError count = %d, Please check your data or function \n", snrError);

	return 0;
}

int near_check_special_q7(q7 *referdata, q7 *resultToCheck, int paramCount, q7 threshold)
{
	int snrError = 0;
		snrError = assert_near_equal_q7(paramCount, referdata, resultToCheck, threshold);

	if (snrError == 0)
		printf("nearError count = 0, NEAR Test PASSED! \n");
	else
		printf("nearError count = %d, Please check your data or function \n", snrError);

	return 0;
}

int near_check_special_q15(q15 *referdata, q15 *resultToCheck, int paramCount, q15 threshold)
{
	int snrError = 0;
		snrError = assert_near_equal_q15(paramCount, referdata, resultToCheck, threshold);

	if (snrError == 0)
		printf("nearError count = 0, NEAR Test PASSED! \n");
	else
		printf("nearError count = %d, Please check your data or function \n", snrError);

	return 0;
}

int near_check_special_q31(q31 *referdata, q31 *resultToCheck, int paramCount, q31 threshold)
{
	int snrError = 0;
		snrError = assert_near_equal_q31(paramCount, referdata, resultToCheck, threshold);

	if (snrError == 0)
		printf("nearError count = 0, NEAR Test PASSED! \n");
	else
		printf("nearError count = %d, Please check your data or function \n", snrError);

	return 0;
}

int near_check_special_q63(q63 *referdata, q63 *resultToCheck, int paramCount, q63 threshold)
{
	int snrError = 0;
		snrError = assert_near_equal_q63(paramCount, referdata, resultToCheck, threshold);

	if (snrError == 0)
		printf("nearError count = 0, NEAR Test PASSED! \n");
	else
		printf("nearError count = %d, Please check your data or function \n", snrError);

	return 0;
}

int eq_check_special_f32(float * referdata, float *resultToCheck, int paramCount)
{
	int eqError = 0;
	eqError = assert_equal_f32(paramCount, referdata, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_special_f64(f64 * referdata, f64 *resultToCheck, int paramCount)
{
	int eqError = 0;
	eqError = assert_equal_f64(paramCount, referdata, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_special_q7(q7 * referdata, q7 *resultToCheck, int paramCount)
{
	int eqError = 0;
	eqError = assert_equal_q7(paramCount, referdata, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_special_q15(q15 * referdata, q15 *resultToCheck, int paramCount)
{
	int eqError = 0;
	eqError = assert_equal_q15(paramCount, referdata, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_special_q31(q31 * referdata, q31 *resultToCheck, int paramCount)
{
	int eqError = 0;
	eqError = assert_equal_q31(paramCount, referdata, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_special_q63(q63 * referdata, q63 *resultToCheck, int paramCount)
{
	int eqError = 0;
	eqError = assert_equal_q63(paramCount, referdata, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}


int eq_check_special_u8(uint8_t * referdata, uint8_t *resultToCheck, int paramCount)
{
	int eqError = 0;
	eqError = assert_equal_u8(paramCount, referdata, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_special_u32(uint32_t * referdata, uint32_t *resultToCheck, int paramCount)
{
	int eqError = 0;
	eqError = assert_equal_u32(paramCount, referdata, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

int eq_check_special_u16(uint16_t * referdata, uint16_t *resultToCheck, int paramCount)
{
	int eqError = 0;
	eqError = assert_equal_u16(paramCount, referdata, resultToCheck);

	if (eqError == 0)
		printf("eqError count = 0, EQ Test PASSED! \n");
	else
		printf("eqError count = %d, Please check your data or function \n", eqError);

	return 0;
}

