# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/29 10:14:46 by tshimizu          #+#    #+#              #
#    Updated: 2026/02/10 17:40:45 by nkojima          ###   ########.fr        #
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
LDFLAGS += -L$(READLINE_PATH)/lib -lreadline

# ===============================
#        CONFIGURATION
# ===============================
NAME        = minishell
SRC_DIR     = src
LIBFT_DIR   = libs/libft
TEST_DIR    = tests
OBJ_DIR     = objs
INC_DIR     = includes
INCFLAG     = -I$(INC_DIR) -I$(LIBFT_DIR)
CFLAGS      += -Wall -Wextra -Werror $(INCFLAG)
LIBFT       = $(LIBFT_DIR)/libft.a
RMDIR       = rm -rf

# ===============================
#               SRC
# ===============================
SRC_UTILS   = utils/free.c\
			utils/free_ast.c\
			utils/validate_ll.c

SRC_INPUT   = input/repl.c\
			  input/signal.c

SRC_PARSE   = \
			parse/lexical/word.c \
			parse/lexical/operator.c \
			parse/lexical/quote.c \
			parse/lexical/tokenizer.c \
			parse/lexical/expand.c \
			parse/lexical/expand_buf.c \
			parse/lexical/expand_var.c \
			parse/lexical/normalize_tokens.c \
			parse/parse.c\
			parse/syntax/ast_build.c\
			parse/syntax/ast_cmd.c\
			parse/syntax/ast_redirect.c\
			parse/syntax/ast_utils.c

SRC_EXEC    = \
				exec/executor.c \
				exec/command.c \
				exec/exec_heredoc.c \
				exec/exec_redirect.c \
				exec/exec_stdio.c \
				exec/execute_ast.c

SRC_BUILTIN = builtin/echo.c\
			        builtin/pwd.c\
			        builtin/env.c\
			        builtin/cd.c\
			        builtin/export.c\
			        builtin/export_print.c\
							builtin/exit.c

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

# ===============================
#             TARGETS
# ===============================
all:
	@echo ""
	@echo " ██████   ██████  ███              ███      █████████  █████               ████  ████ "
	@echo "░░██████ ██████  ░░░              ░░░      ███░░░░░███░░███               ░░███ ░░███ "
	@echo " ░███░█████░███  ████  ████████   ████    ░███    ░░░  ░███████    ██████  ░███  ░███ "
	@echo " ░███░░███ ░███ ░░███ ░░███░░███ ░░███    ░░█████████  ░███░░███  ███░░███ ░███  ░███ "
	@echo " ░███ ░░░  ░███  ░███  ░███ ░███  ░███     ░░░░░░░░███ ░███ ░███ ░███████  ░███  ░███ "
	@echo " ░███      ░███  ░███  ░███ ░███  ░███     ███    ░███ ░███ ░███ ░███░░░   ░███  ░███ "
	@echo " █████     █████ █████ ████ █████ █████   ░░█████████  ████ █████░░██████  █████ █████"
	@echo "░░░░░     ░░░░░ ░░░░░ ░░░░ ░░░░░ ░░░░░     ░░░░░░░░░  ░░░░ ░░░░░  ░░░░░░  ░░░░░ ░░░░░ "
	@echo ""
	@$(MAKE) $(LIBFT)
	@$(MAKE) $(NAME)
	@echo "$(GREEN)Build Complete!$(RESET)"

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
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME)

# ===============================
#          RUN / TEST
# ===============================
run: all
	./$(NAME)

test: all
	@echo "$(YELLOW)Running GoogleTest...$(RESET)"
	@$(MAKE) -C $(TEST_DIR) run

test_verbose: all
	@echo "$(YELLOW)Running GoogleTest (verbose)...$(RESET)"
	@$(MAKE) -C $(TEST_DIR) run_verbose

# ===============================
#             CLEAN
# ===============================
clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(TEST_DIR) clean
	@echo "$(GREEN)🧹 Cleaned object files, libft, and tests.$(RESET)"

fclean:
	@$(RMDIR) $(OBJ_DIR)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(TEST_DIR) fclean
	@echo "$(GREEN)🧼 Cleaned executable, libft, and tests.$(RESET)"

re: fclean all

# ===============================
#             PHONY
# ===============================
.PHONY: all clean fclean re asan debug valgrind run test test_verbose
