# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/22 17:42:12 by nkojima           #+#    #+#              #
#    Updated: 2025/11/22 19:37:52 by tshimizu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ===============================
#             Color              #
# ===============================
GREEN   = \033[0;32m
RED     = \033[0;31m
YELLOW  = \033[0;33m
RESET   = \033[0m

# ========================
#        CONFIGURATION
# ========================
NAME        = minishell

CC          = cc
SRC_DIR		= src
LIBFT_DIR   = libs/libft
OBJ_DIR     = objs
INC_DIR     = includes

INCFLAG     = -I$(INC_DIR) -I$(LIBFT_DIR)
CFLAGS      = -Wall -Wextra -Werror $(INCFLAG)
LIBFT       = $(LIBFT_DIR)/libft.a
LIBS        = -lreadline

# ========================
#        SOURCES
# ========================
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

SRCS 		= $(addprefix $(SRC_DIR)/, $(ALL_SRC))
OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

RM          = rm -f
RMDIR       = rm -rf

# ========================
#        TARGETS
# ========================
all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(YELLOW)[LIBFT] Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $@
	@echo "$(GREEN)✅ Compiled: $(NAME)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)🔧 Compiled: $<$(RESET)"

# ========================
#     DEBUG/SANITIZER
# ========================
asan: CFLAGS += -g -fsanitize=address
asan: re
	@echo "$(YELLOW)🚀 Running with AddressSanitizer$(RESET)"
	./$(NAME)

debug: CFLAGS += -g
debug: re
	@echo "$(YELLOW)🚀 Debug build ready (use gdb/lldb)$(RESET)"

valgrind: re
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

# ========================
#        TEST/RUN
# ========================
run: all
	./$(NAME)
# TODO
test: all
	./test/test

# ========================
#        CLEANING
# ========================
clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(YELLOW)🧹 Cleaned object files.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(RED)🧼 Cleaned executable and libft.$(RESET)"

re: fclean all

# ========================
#        PHONY
# ========================
.PHONY: all clean fclean re asan debug run test valgrind $(LIBFT)
