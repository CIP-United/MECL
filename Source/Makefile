# This is an example Makefile to show how to build the library

# Please get cross-compile toolchains from:
# https://repo.oss.cipunited.com/mips-toolchain-cip/

# Cross compile
NATIVE = false
toolchains := 

ifeq	($(NATIVE), true)
else ifeq ($(NATIVE), false)
	toolchains := mips-mti-elf-
else
	$(error Invalid NATIVE value)
endif

# Compilation tools
CC := $(toolchains)cc
AR := $(toolchains)ar
LD := $(toolchains)ld

# Compilation flags
CFLAGS := -Wsign-compare \
 -Wdouble-promotion \
 -Ofast -ffast-math \
 -Wall -Wextra  -Werror \
 -Wno-unused \
 -mabi=32

LDFLAGS := -mabi=32

# Build type
BUILD = DSP

ifeq      ($(BUILD), C)
	LD_BUILD := debug
else ifeq ($(BUILD), DSP)
	CFLAGS += -mdsp -mdspr2
	MACRO_FLAGS = -DMIPS_MATH_DSP=1
else
	$(error Invalid BUILD value)
endif

# Debug
DEBUG = false

ifeq      ($(DEBUG), true)
	CFLAGS += -g
else ifeq      ($(DEBUG), false)
else
	$(error Invalid DEBUG value)
endif

# Sources
SRCS := BasicMathFunctions/BasicMathFunctions.c \
 CommonTables/CommonTables.c \
 InterpolationFunctions/InterpolationFunctions.c \
 BayesFunctions/BayesFunctions.c \
 MatrixFunctions/MatrixFunctions.c \
 ComplexMathFunctions/ComplexMathFunctions.c \
 QuaternionMathFunctions/QuaternionMathFunctions.c \
 ControllerFunctions/ControllerFunctions.c \
 SVMFunctions/SVMFunctions.c \
 DistanceFunctions/DistanceFunctions.c \
 StatisticsFunctions/StatisticsFunctions.c \
 FastMathFunctions/FastMathFunctions.c \
 SupportFunctions/SupportFunctions.c \
 FilteringFunctions/FilteringFunctions.c \
 TransformFunctions/TransformFunctions.c \
 WindowFunctions/WindowFunctions.c

# Includes
DSP_INCLUDES := ../Include \
  ../PrivateInclude 

# Compilation flags for include folders
INC_FLAGS := $(addprefix -I,$(DSP_INCLUDES))
CFLAGS += $(INC_FLAGS)

# Output folder for build products
BUILDDIR := builddir
OBJECTS := $(SRCS:%=$(BUILDDIR)/%.o)
OBJS := $(patsubst %.c,$(OBJECTS),$(notdir $(SRCS)))
STATIC_LIB = $(BUILDDIR)/libMECL.a

all: static
.PHONY : all

-include $(OBJECTS:.o=.d)

static: $(STATIC_LIB)

$(STATIC_LIB): $(OBJS)
	$(AR) rcv $(STATIC_LIB) $(OBJECTS)

$(BUILDDIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(MACRO_FLAGS) -c -MMD $< -o $@

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MMD $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean :
	rm -rf $(BUILDDIR) $(STATIC_LIB)