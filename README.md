# MECL

## About

MIPS Embedded Compute Library (MECL) is an optimized compute library for MIPS embedded systems.

It provides optimized compute kernels for MIPS processors with MIPS DSP ASE on the current.

You don't need any of the other projects to build and use MECL. Cross-compile may require installation of mips-cross-toolchains.

### MECL Kernels

Kernels provided by MECL (list not exhaustive):

- Basic mathematics (real, complex, quaternion, linear algebra, fast math functions)
- DSP (filtering)
- Transforms (FFT, MFCC, DCT)
- Statistics 
- Classical ML (Support Vector Machine, Distance functions for clustering ...)

Kernels are provided with several datatypes : f64, f32, q31, q15, q7.

## Support / Contact

For any questions or to reach the MECL team, please create a new issue in https://github.com/CIP-United/MECL , or contact our support ipsupport@cipunited.com

## Building for speed

MECL is used when you need performance. As consequence MECL should be compiled with the options giving the best performance:

### Options to use

- make -j BUILD=DSP

Now Makefile uses hard-float as default. When hard-float are used, then the fpu should be selected to ensure that the compiler is not using a software float emulation.

Compilers are doing unrolling. So this option may not be needed but it is highly dependent on the compiler. With some compilers, this option is needed to get better performances.

Speed of memory is important. If you can map the data and the constant tables used by MECL in DTCM memory then it is better. If you have a cache, enable it.

## How to build

You can build MECL with Makefile under `Source` folder on the current.

### How to build with any other build system

You need the following folders:

- Source
- Include
- PrivateInclude

In Source subfolders, you may either build all of the source file with a datatype suffix (like _f32.c), or just compile the files without a datatype suffix. For instance for BasicMathFunctions, you can build all the C files except BasicMathFunctions.c, or you can just build these file (they are including all of the other C files of the folder).

f16 files are not mandatory. You can build with -DDISABLEFLOAT16
## Folders and files

The only folders required to build and use MECL Library are:

- Source
- Include
- PrivateInclude

Other folders are part of different projects, tests or examples.

### Folders
- Include:
  * Include files for MECL
- PrivateInclude:
  * Some include needed to build MECL
  
- Source:
  * MECL source
- Testing:
  * MECL Test framework for MIPS environment