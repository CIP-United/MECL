#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mips_math_types.h"


typedef int8_t q7;
typedef int16_t q15;
typedef int32_t q31;
typedef int64_t q63;

#define MAX_SIZE 80000
// #define NOT_EMBEDDED 0

// SNR for single elements or multi
#define SNR_MULTI 1
#define SNR_SINGLE 0

#define ASSERT_TRUE(A) assert_true(__LINE__,A)
#define ASSERT_FALSE(A) assert_false(__LINE__,A)
// =================================================================

/* Patterens static path */
#define Patterns_PATH "../Testing/Patterns/DSP"

#define BasicMathsF32 "/BasicMaths/BasicMathsF32/"
#define BasicMathsF64 "/BasicMaths/BasicMathsF64/"
#define BasicMathsQ15 "/BasicMaths/BasicMathsQ15/"
#define BasicMathsQ31 "/BasicMaths/BasicMathsQ31/"
#define BasicMathsQ7 "/BasicMaths/BasicMathsQ7/"
#define BayesF32 "/Bayes/BayesF32/"
#define BinaryF32 "/Matrix/Binary/BinaryF32/"
#define BinaryF64 "/Matrix/Binary/BinaryF64/"
#define BinaryQ15 "/Matrix/Binary/BinaryQ15/"
#define BinaryQ31 "/Matrix/Binary/BinaryQ31/"
#define BinaryQ7 "/Matrix/Binary/BinaryQ7/"
#define BIQUADF32 "/Filtering/BIQUAD/BIQUADF32/"
#define BIQUADF64 "/Filtering/BIQUAD/BIQUADF64/"
#define BIQUADQ15 "/Filtering/BIQUAD/BIQUADQ15/"
#define BIQUADQ31 "/Filtering/BIQUAD/BIQUADQ31/"
#define ComplexMathsF32 "/ComplexMaths/ComplexMathsF32/"
#define ComplexMathsF64 "/ComplexMaths/ComplexMathsF64/"
#define ComplexMathsQ15 "/ComplexMaths/ComplexMathsQ15/"
#define ComplexMathsQ31 "/ComplexMaths/ComplexMathsQ31/"
#define ControllerF32 "/Controller/ControllerF32/"
#define ControllerQ15 "/Controller/ControllerQ15/"
#define ControllerQ31 "/Controller/ControllerQ31/"
#define DECIMF32 "/Filtering/DECIM/DECIMF32/"
#define DECIMQ15 "/Filtering/DECIM/DECIMQ15/"
#define DECIMQ31 "/Filtering/DECIM/DECIMQ31/"
#define DistanceF32 "/Distance/DistanceF32/"
#define DistanceF64 "/Distance/DistanceF64/"
#define DistanceU32 "/Distance/DistanceU32/"
#define FastMathF32 "/FastMath/FastMathF32/"
#define FastMathF64 "/FastMath/FastMathF64/"
#define FastMathQ15 "/FastMath/FastMathQ15/"
#define FastMathQ31 "/FastMath/FastMathQ31/"
#define FastMathQ63 "/FastMath/FastMathQ63/"
#define FIRF32 "/Filtering/FIR/FIRF32/"
#define FIRF64 "/Filtering/FIR/FIRF64/"
#define FIRQ15 "/Filtering/FIR/FIRQ15/"
#define FIRQ31 "/Filtering/FIR/FIRQ31/"
#define FIRQ7 "/Filtering/FIR/FIRQ7/"
#define InterpolationF32 "/Interpolation/InterpolationF32/"
#define InterpolationQ15 "/Interpolation/InterpolationQ15/"
#define InterpolationQ31 "/Interpolation/InterpolationQ31/"
#define InterpolationQ7 "/Interpolation/InterpolationQ7/"
#define MFCCF32 "/Transform/MFCCF32/"
#define MFCCQ15 "/Transform/MFCCQ15/"
#define MFCCQ31 "/Transform/MFCCQ31/"
#define MISCF32 "/Filtering/MISC/MISCF32/"
#define MISCF64 "/Filtering/MISC/MISCF64/"
#define MISCQ15 "/Filtering/MISC/MISCQ15/"
#define MISCQ31 "/Filtering/MISC/MISCQ31/"
#define MISCQ7 "/Filtering/MISC/MISCQ7/"
#define QuaternionMathsF32 "/QuaternionMaths/QuaternionMathsF32/"
#define StatsF32 "/Stats/StatsF32/"
#define StatsF64 "/Stats/StatsF64/"
#define StatsQ15 "/Stats/StatsQ15/"
#define StatsQ31 "/Stats/StatsQ31/"
#define StatsQ7 "/Stats/StatsQ7/"
#define SupportF32 "/Support/SupportF32/"
#define SupportF64 "/Support/SupportF64/"
#define SupportQ15 "/Support/SupportQ15/"
#define SupportQ31 "/Support/SupportQ31/"
#define SupportQ7 "/Support/SupportQ7/"
#define SupportBarF32 "/SupportBarF32/"
#define SVMF32 "/SVM/SVMF32/"
#define TransformF32 "/Transform/TransformF32/"
#define TransformF64 "/Transform/TransformF64/"
#define TransformQ15 "/Transform/TransformQ15/"
#define TransformQ31 "/Transform/TransformQ31/"
#define UnaryF32 "/Matrix/Unary/UnaryF32/"
#define UnaryF64 "/Matrix/Unary/UnaryF64/"
#define UnaryQ15 "/Matrix/Unary/UnaryQ15/"
#define UnaryQ31 "/Matrix/Unary/UnaryQ31/"
#define UnaryQ7 "/Matrix/Unary/UnaryQ7/"
#define WindowF32 "/Window/WindowF32/"
#define WindowF64 "/Window/WindowF64/"

/* loading data */
#if defined(NOT_EMBEDDED)
int load_data_f32(char *fileName, int *paramCount, float *loadedData);
int load_data_f64(char *fileName, int *paramCount, double *loadedData);
int load_data_q63(char *fileName, int *paramCount, q63 *loadedData);
int load_data_q31(char *fileName, int *paramCount, q31 *loadedData);
int load_data_q15(char *fileName, int *paramCount, q15 *loadedData);
int load_data_q7(char *fileName, int *paramCount, q7 *loadedData);

int load_data_u64(char *fileName, int *paramCount, uint64_t *loadedData);
int load_data_u32(char *fileName, int *paramCount, uint32_t *loadedData);
int load_data_u16(char *fileName, int *paramCount, uint16_t *loadedData);
int load_data_u8(char *fileName, int *paramCount, uint8_t *loadedData);

#else

void load_data_f32(void *valuePointer, int dataSize, float *loadedData);
void load_data_f64(void *valuePointer, int dataSize, double *loadedData);
void load_data_q63(void *valuePointer, int dataSize, q63 *loadedData);
void load_data_q31(void *valuePointer, int dataSize, q31 *loadedData);
void load_data_q15(void *valuePointer, int dataSize, q15 *loadedData);
void load_data_q7(void *valuePointer, int dataSize, q7 *loadedData);

void load_data_u64(void *valuePointer, int dataSize, uint64_t *loadedData);
void load_data_u32(void *valuePointer, int dataSize, uint32_t *loadedData);
void load_data_u16(void *valuePointer, int dataSize, uint16_t *loadedData);
void load_data_u8(void *valuePointer, int dataSize, uint8_t *loadedData);

#endif

/* REL check */
#if defined(NOT_EMBEDDED)

int rel_check_f32(char *referFileName, float *resultToCheck, int paramCount, float threshold);
int rel_check_f64(char *referFileName, double *resultToCheck, int paramCount, double threshold);

#endif

int rel_check_special_f32(float *referdata, float *resultToCheck, int paramCount, float threshold);
int rel_check_special_f64(double *referdata, double *resultToCheck, int paramCount, double threshold);

/* SNR check */
#if defined(NOT_EMBEDDED)

int snr_check_q63(char *referFileName, q63 *resultToCheck, int paramCount, float threshold);
int snr_check_q31(char *referFileName, q31 *resultToCheck, int paramCount, float threshold);
int snr_check_q15(char *referFileName, q15 *resultToCheck, int paramCount, float threshold);
int snr_check_q7(char *referFileName, q7 *resultToCheck, int paramCount, float threshold);
int snr_check_f64(char *referFileName, double *resultToCheck, int paramCount, double threshold);
int snr_check_f32(char *referFileName, float *resultToCheck, int paramCount, float threshold);

#endif
int snr_check_special_f32(float *referdata, float *resultToCheck, int paramCount, float threshold);
int snr_check_special_f64(f64 *referdata, f64 *resultToCheck, int paramCount, f64 threshold);
int snr_check_special_q7(q7 *referdata, q7 *resultToCheck, int paramCount, f32 threshold);
int snr_check_special_q15(q15 *referdata, q15 *resultToCheck, int paramCount, f32 threshold);
int snr_check_special_q31(q31 *referdata, q31 *resultToCheck, int paramCount, f32 threshold);
int snr_check_special_q63(q63 *referdata, q63 *resultToCheck, int paramCount, f32 threshold);

/* NEAR EQ check */
#if defined(NOT_EMBEDDED)

int near_check_f64(char *referFileName, double *resultToCheck, int paramCount, double threshold);
int near_check_f32(char *referFileName, float *resultToCheck, int paramCount, float threshold);
int near_check_q63(char *referFileName, q63 *resultToCheck, int paramCount, q63 threshold);
int near_check_q31(char *referFileName, q31 *resultToCheck, int paramCount, q31 threshold);
int near_check_q15(char *referFileName, q15 *resultToCheck, int paramCount, q15 threshold);
int near_check_q7(char *referFileName, q7 *resultToCheck, int paramCount, q7 threshold);

#endif

int near_check_special_f64(f64 *referdata, double *resultToCheck, int paramCount, double threshold);
int near_check_special_f32(f32 *referdata, float *resultToCheck, int paramCount, float threshold);
int near_check_special_q7(q7 *referdata, q7 *resultToCheck, int paramCount, q7 threshold);
int near_check_special_q15(q15 *referdata, q15 *resultToCheck, int paramCount, q15 threshold);
int near_check_special_q31(q31 *referdata, q31 *resultToCheck, int paramCount, q31 threshold);
int near_check_special_q63(q63 *referdata, q63 *resultToCheck, int paramCount, q63 threshold);

/* EQ check */
#if defined(NOT_EMBEDDED)

int eq_check_f64(char *referFileName, double *resultToCheck, int paramCount);
int eq_check_f32(char *referFileName, float *resultToCheck, int paramCount);
int eq_check_q63(char *referFileName, q63 *resultToCheck, int paramCount);
int eq_check_q31(char *referFileName, q31 *resultToCheck, int paramCount);
int eq_check_q15(char *referFileName, q15 *resultToCheck, int paramCount);
int eq_check_q7(char *referFileName, q7 *resultToCheck, int paramCount);

int eq_check_u32(char *referFileName, uint32_t *resultToCheck, int paramCount);
int eq_check_u16(char *referFileName, uint16_t *resultToCheck, int paramCount);
int eq_check_u8(char *referFileName, uint8_t *resultToCheck, int paramCount);

#endif

int eq_check_special_f32(float * referdata, float *resultToCheck, int paramCount);
int eq_check_special_f64(f64 * referdata, f64 *resultToCheck, int paramCount);
int eq_check_special_q7(q7 * referdata, q7 *resultToCheck, int paramCount);
int eq_check_special_q15(q15 * referdata, q15 *resultToCheck, int paramCount);
int eq_check_special_q31(q31 * referdata, q31 *resultToCheck, int paramCount);
int eq_check_special_q63(q63 *referdata, q63 *resultToCheck, int paramCount);

int eq_check_special_u32(uint32_t *referdata, uint32_t *resultToCheck, int paramCount);
int eq_check_special_u16(uint16_t *referdata, uint16_t *resultToCheck, int paramCount);
int eq_check_special_u8(uint8_t *referdata, uint8_t *resultToCheck, int paramCount);

/* CLOSE check */
#if defined(NOT_EMBEDDED)

int close_check_f32(char *referFileName, float *resultToCheck, int paramCount, double absthreshold, double relthreshold);
int close_check_f64(char *referFileName, double *resultToCheck, int paramCount, double absthreshold, double relthreshold);

#endif

int close_check_special_f32(float * referdata, float *resultToCheck, int paramCount, double absthreshold, double relthreshold);
int close_check_special_f64(double * referdata, double *resultToCheck, int paramCount, double absthreshold, double relthreshold);

void assert_true(unsigned long nb,bool cond);
void assert_false(unsigned long nb,bool cond);

