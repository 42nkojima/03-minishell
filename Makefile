# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/22 17:42:12 by nkojima           #+#    #+#              #
#    Updated: 2025/11/22 20:30:00 by tshimizu         ###   ########.fr        #
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
#        OS Detection
# ===============================
UNAME_S := $(shell uname -s)
READLINE_PATH := $(shell brew --prefix readline 2>/dev/null)

ifeq ($(READLINE_PATH),)
	$(warning $(YELLOW)>> readline が見つかりません。Homebrewでインストールしてください$(RESET))
	$(warning $(YELLOW)>> brew install readline$(RESET))
endif

CFLAGS += -I$(READLINE_PATH)/include
LDFLAGS += -L$(READLINE_PATH)/lib -lreadline

# ===============================
#        CONFIGURATION
# ===============================
NAME        = minishell
CC          = cc
SRC_DIR     = src
LIBFT_DIR   = libs/libft
TEST_DIR    = tests
OBJ_DIR     = objs
INC_DIR     = includes
INCFLAG     = -I$(INC_DIR) -I$(LIBFT_DIR)
CFLAGS      += -Wall -Wextra -Werror $(INCFLAG)
LDFLAGS     += -L$(READLINE_PATH)/lib -lreadline
LIBFT       = $(LIBFT_DIR)/libft.a

# ===============================
#               SRC
# ===============================
SRC_UTILS   = 

SRC_INPUT   =

SRC_PARSE   = 

SRC_EXEC    = 

SRC_BUILTIN = 

SRC_MAIN    = main.c

ALL_SRC = \
    $(SRC_UTILS) \
    $(SRC_INPUT) \
    $(SRC_PARSE) \
    $(SRC_EXEC) \
    $(SRC_BUILTIN) \
    $(SRC_MAIN)

SRCS        = $(addprefix $(SRC_DIR)/, $(ALL_SRC))
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

RM          = rm -f
RMDIR       = rm -rf

# ===============================
#             TARGETS
# ===============================
all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(YELLOW)[LIBFT] Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@echo "$(YELLOW)[LD] Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅ Compiled: $(NAME)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)🔧 Compiled: $<$(RESET)"

# ===============================
#       SANITIZER / DEBUG
# ===============================
asan: CFLAGS += -g -fsanitize=address
asan: re
	@echo "$(GREEN)🚀 AddressSanitizer Enabled$(RESET)"
	./$(NAME)

debug: CFLAGS += -g -DDEBUG
debug: re
	@echo "$(GREEN)🚀 Debug build ready$(RESET)"

valgrind: re
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

# ===============================
#          RUN / TEST
# ===============================
run: all
	./$(NAME)

test:
	@echo "$(YELLOW)Running GoogleTest...$(RESET)"
	@$(MAKE) -C tests run

test_verbose:
	@echo "$(YELLOW)Running GoogleTest (verbose)...$(RESET)"
	@$(MAKE) -C tests run_verbose
# ===============================
#             CLEAN
# ===============================
clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(GREEN)🧹 Cleaned object files.$(RESET)"

fclean: clean
	@$(RMDIR) $(OBJ_DIR)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)🧼 Cleaned executable and libft.$(RESET)"

re: fclean all

# ===============================
#             PHONY
# ===============================
.PHONY: all clean fclean re asan debug valgrind run test $(LIBFT)
