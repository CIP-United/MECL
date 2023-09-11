# 编译器设置
CC := gcc
CFLAGS := -I../Include -I../../CMSIS_5/CMSIS/Core/Include/ -I FrameworkInclude/ -I Include/Benchmarks/ -I Include/Tests/

# 源文件列表
SOURCES := $(wildcard *.cpp) $(wildcard *.c) $(wildcard FrameworkSource/*.cpp) $(wildcard Source/Benchmarks/*.cpp) $(wildcard Source/Tests/*.cpp)

# 目标文件列表
OBJECTS := $(SOURCES:.cpp=.o)
OBJECTS := $(OBJECTS:.c=.o)

# 目标可执行文件
EXECUTABLE := myprogram

# 默认目标
all: $(EXECUTABLE)

# 生成可执行文件
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

# 编译源文件
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
