CC="C:\Projects\nes_emulator\nes_emulator\mingw\mingw64\bin\gcc.exe"
CFLAGS=-I. -Isrc -Itests -Itests/unity -std=c11 -Wall -Wextra

# Source files
SRCS=src/cpu.c src/opcodes.c
TEST_SRCS=tests/test_cpu.c tests/unity/unity.c

# Object files
OBJS=$(SRCS:.c=.o)
TEST_OBJS=$(TEST_SRCS:.c=.o)

# Executables
TEST_EXE=test_cpu.exe

# Default target
all: test

# Build and run tests
test: $(TEST_EXE)
	./$(TEST_EXE)

# Build test executable
$(TEST_EXE): $(TEST_OBJS) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	del /Q $(TEST_EXE) $(OBJS) $(TEST_OBJS) 2>nul || true

.PHONY: all test clean
