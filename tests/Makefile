
# ===============================
#             Color
# ===============================
GREEN   = \033[0;32m
RED     = \033[0;31m
YELLOW  = \033[0;33m
RESET   = \033[0m

# ===============================
#        Install ReadLine
# ===============================
READLINE_PATH := $(shell brew --prefix readline 2>/dev/null)

ifeq ($(READLINE_PATH),)
$(warning $(YELLOW)>> readline が見つかりません。Homebrewでインストールしてください$(RESET))
$(warning $(YELLOW)>> brew install readline$(RESET))
endif

CFLAGS += -I$(READLINE_PATH)/include
CXXFLAGS += -I$(READLINE_PATH)/include
LDFLAGS += -L$(READLINE_PATH)/lib -lreadline

# ===============================
#        CONFIGURATION
# ===============================

CFLAGS  += -Wall -Wextra -Werror -I../includes -g
CXXFLAGS += -std=c++17 -Wall -Wextra -I../includes -I../libs/googletest/googletest/include -I../libs/googletest/googlemock/include -g

GTEST_DIR = ../libs/googletest
GTEST_BUILD = $(GTEST_DIR)/build
GTEST_LIB = $(GTEST_BUILD)/lib/libgtest.a
GTEST_MAIN = $(GTEST_BUILD)/lib/libgtest_main.a

LDFLAGS += -pthread

SRC_DIR = ../src
SRC  = $(shell find $(SRC_DIR) -name "*.c")
OBJ  = $(SRC:../src/%.c=build/%.o)

LIBFT = ../libs/libft/libft.a

TEST_DIR = .
TEST_SRC = $(shell find $(TEST_DIR) -name "*.cpp")
TEST_OBJ = $(TEST_SRC:.cpp=.o)

TARGET = run_tests

# ===============================
#             TARGETS
# ===============================

all: run

# ===========================
# 		GoogleTest
# ===========================

$(GTEST_LIB) $(GTEST_MAIN):|$(GTEST_DIR)
	mkdir -p $(GTEST_BUILD)
	cd $(GTEST_BUILD) && cmake .. && make

$(GTEST_DIR):
	@git clone git@github.com:google/googletest.git $(GTEST_DIR)


$(TARGET): $(OBJ) $(TEST_OBJ) $(LIBFT) $(GTEST_LIB) $(GTEST_MAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


build/%.o: ../src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


# ===========================
# 			Run
# ===========================

run: $(TARGET)
	./$(TARGET)

run_verbose: $(TARGET)
	./$(TARGET) --gtest_color=yes --gtest_print_time=1


# ===========================
# 			Clean
# ===========================

clean:
	rm -rf build
	rm -f $(TEST_OBJ)
	rm -f $(TARGET)
	@echo "$(GREEN)🧹 Cleaned object files.$(RESET)"

fclean: clean
	rm -rf $(GTEST_BUILD)
	@echo "$(GREEN)🧼 Cleaned executable and libft.$(RESET)"

re: fclean all

# ===============================
#             PHONY
# ===============================

.PHONY: all clean fclean re run run_verbose
