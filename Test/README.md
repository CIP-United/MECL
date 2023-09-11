# Summary

Here's a quick summary of how to get started with the framework when cloning the repository for the first time.

First, you must use a MIPS-based LINUX kernel. Otherwise, the cloned source may contain functional tests that are not yet available in the official package.

After cloning the correct version, you need to generate some files. Please confirm that there is a successfully compiled static library in the test file, so that the function can be successfully linked. The command must be run from the test folder, using the reserved `buildTest.sh` script to compile the target program and generate a binary file.

# TEST FRAMEWORK

In the `BasicFramework.c` file, we define the data type, reference value size, file acquisition path, loading function, and test function.

## Available loading functions: 

Adapt to the required data types, providing a total of 10 functions of F32, F64, Q7, Q15, Q31, Q63, U8, U16, U32, and U64.
## Test method: 

According to the characteristics and reliability of the function, select six deviation judgment methods such as signal-to-noise ratio, approximate value, and relative value.

In the `BasicFramework.h` file, there are mainly declarations and definitions of related functions such as data loading, data detection, and assertion. It provides tools and functions for testing and validating mathematical functions, filters, statistics, and more.

# DATA

Two forms of data formats are provided, including text file format and C file format containing arrays. It is specifically divided into samples, input data, reference data, and auxiliary calculation parameters. The functions of each data are as follows.
## input data: 
As input to the function.
## Reference data: 
Compare with the output result of the function, and give a preliminary reference for correctness and error through specific judgment methods such as signal-to-noise ratio.

## Auxiliary calculation parameters: 
Used by some special functions to assist in processing, which can be reflected in shifting, mapping, etc. 

# TEST CODE

Groups are divided by function type and data type. For example, the basic functions Basicfunctions have q7, q15, q31, f32, f64 and other files according to the data type. The basic function Basicfunctionsq7 test code contains all basic functions such as add, sub, mult and other functions. q7 data type test.

Each function in the file is independently judged and processed, and the input data corresponds to its respective reference file and is adapted to its judgment method. Usually, the signal-to-noise ratio is selected as the preliminary basis.

# Building and Running

## Compile and generate static library

We compile in Source folder.

Use the command:

`make`

After running this command, the library will be generated under the current folder:`builddir`.

The generated static library `libMECL.a` is in the builddir folder, and the `libMECL.a` static library will be used in `Test`, so here we need to copy this file to the test folder for us to test.

## Copy static library to Test source folder

`cp ./builddir/libMECL.a ../Test`

## After completing the above steps, we need to enter the test folder:

Open Test source folder, compile and generate test program.

`cd ../Test`

In this folder is the script file buildTest.sh that we need to use.
For example: if we test `SupportTestsQ15.c`, then we need to use the following command:

`./buildTest.sh SupportTestsQ15.c`

## Execute Test program

`./SupportTestsQ15`

Then we can see the test results of `SupportTestsQ15.c`,if all of them are "PASSED", it means the test is passed.
