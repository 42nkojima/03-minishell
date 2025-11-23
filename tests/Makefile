
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -g
LDFLAGS = -pthread

ROOT_DIR = ..
SRC_DIR = $(ROOT_DIR)/src
INCLUDES_DIR = $(ROOT_DIR)/includes
LIBFT_DIR = $(ROOT_DIR)/libs/libft
TEST_BASE_DIR = .
OBJS_DIR = $(ROOT_DIR)/objs
BUILD_DIR = ./build

GTEST_DIR = /usr/include
GTEST_LIB = -lgtest -lgtest_main

INCLUDES = -I$(INCLUDES_DIR) -I$(LIBFT_DIR) -I$(GTEST_DIR)

MODULES = utils input parse exec builtin

SOURCES = 
SOURCES += $(wildcard $(SRC_DIR)/utils/*.c)
SOURCES += $(wildcard $(SRC_DIR)/input/*.c)
SOURCES += $(wildcard $(SRC_DIR)/parse/*.c)
SOURCES += $(wildcard $(SRC_DIR)/exec/*.c)
SOURCES += $(wildcard $(SRC_DIR)/builtin/*.c)

SOURCES := $(filter-out $(SRC_DIR)/main.c, $(SOURCES))

TEST_DIRS = input parse exec builtin
TEST_SOURCES = $(foreach dir, $(TEST_DIRS), $(wildcard $(TEST_BASE_DIR)/$(dir)/*_test.c))

OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.c=.o)))
TEST_OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_SOURCES:.c=.o)))

DEPS = $(OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

TARGET = $(BUILD_DIR)/run_tests

.PHONY: all run run-verbose run-filter clean rebuild help debug

all: $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(OBJECTS) $(TEST_OBJECTS)
	@echo "Linking $@..."
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJECTS) $(TEST_OBJECTS) \
		-L$(LIBFT_DIR) -lft $(LDFLAGS) $(GTEST_LIB)
	@echo "✓ Build successful: $@"

$(BUILD_DIR)/%.o: $(SRC_DIR)/utils/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/input/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/parse/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/exec/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/builtin/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%_test.o: $(TEST_BASE_DIR)/input/%_test.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%_test.o: $(TEST_BASE_DIR)/parse/%_test.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%_test.o: $(TEST_BASE_DIR)/exec/%_test.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%_test.o: $(TEST_BASE_DIR)/builtin/%_test.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

run: $(TARGET)
	@echo "Running tests..."
	@./$(TARGET)

run-verbose: $(TARGET)
	@echo "Running tests (verbose)..."
	@./$(TARGET) --gtest_print_time=1 --gtest_color=yes

run-filter: $(TARGET)
	@if [ -z "$(FILTER)" ]; then \
		echo "Usage: make run-filter FILTER=TestSuite.TestName"; \
		exit 1; \
	fi
	@echo "Running tests matching: $(FILTER)"
	@./$(TARGET) --gtest_filter="$(FILTER)"

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
	@echo "✓ Cleaned"

rebuild: clean all

debug:
	@echo "=== PROJECT STRUCTURE ==="
	@echo "Root: $(ROOT_DIR)"
	@echo "Source files: $(SOURCES)"
	@echo "Test files: $(TEST_SOURCES)"
	@echo ""
	@echo "=== OBJECTS ==="
	@echo "Source objects: $(OBJECTS)"
	@echo ""
	@echo "=== BUILD ==="
	@echo "Build dir: $(BUILD_DIR)"
	@echo "Target: $(TARGET)"

help:
	@echo "minishell Test Makefile"
	@echo ""
	@echo "Targets:"
	@echo "  make all              - Build test executable (default)"
	@echo "  make run              - Build and run all tests"
	@echo "  make run-verbose      - Run tests with verbose output"
	@echo "  make run-filter       - Run specific tests (FILTER=Suite.Test)"
	@echo "  make clean            - Remove build directory"
	@echo "  make rebuild          - Clean and rebuild"
	@echo "  make debug            - Show build information"
	@echo "  make help             - Show this help"
	@echo ""
	@echo "Examples:"
	@echo "  make run"
	@echo "  make run-filter FILTER=ParseTests.TokenTest"
	@echo "  make run-verbose"

-include $(DEPS)
