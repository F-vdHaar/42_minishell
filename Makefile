# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 18:49:28 by fvon-de           #+#    #+#              #
#    Updated: 2025/03/18 19:24:37 by fvon-de          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_RESET  = \033[0m
COLOR_YELLOW = \033[1;33m  # Compiling messages
COLOR_BLUE   = \033[1;34m  # Info
COLOR_GREEN  = \033[1;32m  # Success
COLOR_RED    = \033[1;31m  # Errors

# Project settings
NAME        = minishell
NAME_DEBUG  = minishell_debug
INCLUDE_DIR = include
LIB42_DIR   = lib/lib42
LIB42_REPO  = https://github.com/F-vdHaar/42_lib.git
SRC_DIR     = src
OBJ_DIR     = obj

# Compiler settings
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Wunused -I$(INCLUDE_DIR) \
              -I$(LIB42_DIR)/libft/include \
              -I$(LIB42_DIR)/ft_printf/include \
              -I$(LIB42_DIR)/gnl/include
DEBUG_FLAGS = $(CFLAGS) -g -O0 -fsanitize=undefined -fno-strict-aliasing \
              -fno-omit-frame-pointer -fstack-protector -DDEBUG -fno-inline
LDFLAGS     = -L$(LIB42_DIR) -l42 

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default rule
all: $(LIB42_DIR)/lib42.a $(NAME)
	@echo "$(COLOR_GREEN)$(NAME) build complete.$(COLOR_RESET)"

# Ensure object directory exists
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(COLOR_YELLOW)Created directory: $(OBJ_DIR)$(COLOR_RESET)"

# Clone or build external library
$(LIB42_DIR)/lib42.a:
	@if [ ! -d "$(LIB42_DIR)" ]; then \
		echo "$(COLOR_YELLOW)Cloning lib42...$(COLOR_RESET)"; \
		mkdir -p lib; \
		git clone $(LIB42_REPO) $(LIB42_DIR); \
	fi
	@$(MAKE) -C $(LIB42_DIR)

# Build project
$(NAME): $(OBJS) $(LIB42_DIR)/lib42.a
	@echo "$(COLOR_YELLOW)Linking  $(NAME)...$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "$(COLOR_GREEN)$(NAME) Linking successful!$(COLOR_RESET)"

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(COLOR_YELLOW)Compiling $< $(COLOR_RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Build debug version
$(NAME_DEBUG): $(OBJS) $(LIB42_DIR)/lib42.a
	@echo "$(COLOR_BLUE)Linking $(NAME_DEBUG)...$(COLOR_RESET)"
	$(CC) $(DEBUG_FLAGS) $(OBJS) -o $(NAME_DEBUG) $(LDFLAGS)
	@echo "$(COLOR_GREEN)$(NAME_DEBUG) built successfully.$(COLOR_RESET)"

# Cleaning rules
clean:
	@echo "$(COLOR_BLUE)Cleaning object files...$(COLOR_RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(COLOR_BLUE)Removing executables...$(COLOR_RESET)"
	@rm -f $(NAME) $(NAME_DEBUG)
	@echo "$(COLOR_BLUE)Cleaning libraries...$(COLOR_RESET)"
	@$(MAKE) -C $(LIB42_DIR) clean

re: fclean all

# Debug rules
debug: clean
	@echo "$(COLOR_RED)Compiling in debug mode...$(COLOR_RESET)"
	$(MAKE) $(NAME_DEBUG)

redebug: fclean debug

# Norminette check
norm:
	@echo "$(COLOR_BLUE)Running Norminette...$(COLOR_RESET)"
	@-norminette $(SRC_DIR) | grep -v "OK!" || true
	@-norminette $(INCLUDE_DIR) | grep -v "OK!" || true
	@echo "$(COLOR_BLUE)Norminette check complete!$(COLOR_RESET)"

.PHONY: all clean fclean re norm debug redebug