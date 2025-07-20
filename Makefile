CC = gcc

# Debugger used when running tests or in debug mode.
DEBUGGER = gdb

# Project folder configuration.
TARGET = target
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = $(TARGET)/build

# Source files in src/ and tests/ folders (recursively).
SRCS = $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS = $(wildcard $(TEST_DIR)/**/*.c) $(wildcard $(TEST_DIR)/*.c)

# Compilation flags for release (CFLAGS) and debug/tests (TFLAGS).
CFLAGS=-O2 -Wall -Werror -std=c99
TFLAGS=-O0 -g3 -Wall -std=c99 -D_DEBUG


# From here on, things get a little spicy - object file rules ahead.
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEBUG_OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.debug.o)

# Compiles the release build.
$(TARGET)/release build: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET)/release
	@echo "Path to the release binary: $(TARGET)/release"

# Compiles the program in debug mode.
$(TARGET)/debug build_debug: $(DEBUG_OBJS)
	$(CC) $(TFLAGS) $^ -o $(TARGET)/debug
	@echo "Path to the debug binary: $(TARGET)/debug"

# Builds a single test binary in debug mode.
build_test_%: $(DEBUG_OBJS)
	$(CC) $(TFLAGS) $(filter-out $(OBJ_DIR)/main.debug.o, $^)\
		$(TEST_DIR)/$(patsubst build_test_%,%, $@).c -o\
		$(TARGET)/$(patsubst build_%,%, $@)
	@echo "Path to the test binary: $(TARGET)/$(patsubst build_%,%, $@)"


# Compiles source files into object files (release mode).
$(OBJS): $(SRCS) | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(patsubst $(OBJ_DIR)/%.o,$(SRC_DIR)/%.c, $@)\
		-o $@

# Compiles source files into object files for debug/tests.
$(DEBUG_OBJS): $(SRCS) | $(OBJ_DIR)
	$(CC) -c $(TFLAGS) $(patsubst $(OBJ_DIR)/%.debug.o,$(SRC_DIR)/%.c, $@)\
		-o $@

$(TARGET):
	mkdir -p $(TARGET)

$(OBJ_DIR): | $(TARGET)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(dir $(OBJS))


run: $(TARGET)/release
	$(TARGET)/release

debug: $(TARGET)/debug
	$(DEBUGGER) $(TARGET)/debug

test_%: build_test_% FORCE
	$(DEBUGGER) $(TARGET)/$@


clean:
	rm -rf $(TARGET)

.PHONY: build_debug clean debug run FORCE
# Used to force execution of dependent rules.
FORCE: ;
