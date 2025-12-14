# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/24 12:50:10 by tshimizu          #+#    #+#              #
#    Updated: 2025/11/29 11:39:41 by tshimizu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
$(error $(YELLOW)>> readline が見つかりません。Homebrewでインストールしてください$(RESET))
$(error $(YELLOW)>> brew install readline$(RESET))
endif

CFLAGS += -I$(READLINE_PATH)/include
CXXFLAGS += -I$(READLINE_PATH)/include
LDFLAGS += -L$(READLINE_PATH)/lib -lreadline

# ===============================
#        CONFIGURATION
# ===============================

CFLAGS  += -Wall -Wextra -Werror -I../includes -g
CXXFLAGS += -std=c++17 -Wall -Wextra -I../includes -I../libs/googletest/googletest/include -I../libs/googletest/googlemock/include -g -no-pie

GTEST_DIR = ../libs/googletest
GTEST_BUILD = $(GTEST_DIR)/build
GTEST_LIB = $(GTEST_BUILD)/lib/libgtest.a
GTEST_MAIN = $(GTEST_BUILD)/lib/libgtest_main.a

LDFLAGS += -pthread

SRC_DIR = ../src
SRC  = $(filter-out ../src/main.c, $(shell find $(SRC_DIR) -name "*.c"))
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

$(TARGET): $(GTEST_LIB) $(GTEST_MAIN) $(OBJ) $(TEST_OBJ) $(LIBFT)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(TEST_OBJ) $(GTEST_LIB) $(GTEST_MAIN) $(LIBFT) $(LDFLAGS)

$(GTEST_LIB) $(GTEST_MAIN):|$(GTEST_DIR)
	mkdir -p $(GTEST_BUILD)
	cd $(GTEST_BUILD) && cmake -DCMAKE_POSITION_INDEPENDENT_CODE=ON .. && make

$(GTEST_DIR):
	@git clone https://github.com/google/googletest.git $(GTEST_DIR)

build/%.o: ../src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


# ===========================
# 			Run
# ===========================

run: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(TARGET)

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
	@echo "$(GREEN)🧼 Cleaned executable.$(RESET)"

re: fclean all

# ===============================
#             PHONY
# ===============================

.PHONY: all clean fclean re run run_verbose
