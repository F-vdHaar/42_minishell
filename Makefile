# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvon-de <fvon-der@student.42heilbronn.d    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 20:24:03 by fvon-de           #+#    #+#              #
#    Updated: 2025/03/20 21:37:50 by fvon-de          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_RESET     = \033[0m
COLOR_INFO      = \033[36m  # Info messages (light cyan)
COLOR_WARN      = \033[33m  # Warnings or compiling steps (yellow)
COLOR_SUCCESS   = \033[32m  # Success messages (green)
COLOR_ERROR     = \033[31m  # Error messages (red)
COLOR_HEADER    = \033[1;34m # Header or category titles (blue)

# Project settings
NAME            = minishell
NAME_DEBUG      = minishell_debug
INCLUDE_DIR     = include
LIB42_DIR       = lib/lib42
LIB42_REPO      = https://github.com/F-vdHaar/42_lib.git
SRC_DIR         = src
OBJ_DIR         = obj

# Compiler settings
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -Wunused -I$(INCLUDE_DIR) \
                  -I$(LIB42_DIR)/libft/include \
                  -I$(LIB42_DIR)/ft_printf/include \
                  -I$(LIB42_DIR)/gnl/include
DEBUG_FLAGS     = -I$(INCLUDE_DIR) \
                  -I$(LIB42_DIR)/libft/include \
                  -I$(LIB42_DIR)/ft_printf/include \
                  -I$(LIB42_DIR)/gnl/include \
				  -g -O0 -fsanitize=undefined \
                  -fno-omit-frame-pointer -fstack-protector -DDEBUG -fno-inline
LDFLAGS         = -L$(LIB42_DIR) -l42

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# For Debug
$(info Sources: $(SRCS))
$(info Objects: $(OBJS))

# Default rule
all: $(LIB42_DIR)/lib42.a $(NAME)
	@echo "$(COLOR_SUCCESS)Build complete: $(NAME)$(COLOR_RESET)"

# Ensure object directory exists before compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/$(dir $*)
	@echo "$(COLOR_WARN)Compiling $<$(COLOR_RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Ensure object directory for debug exists before compiling
$(OBJ_DIR)/debug/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/debug/$(dir $*)
	@echo "$(COLOR_WARN)Compiling $< with DEBUG_FLAGS$(COLOR_RESET)"
	@$(CC) $(DEBUG_FLAGS) -c $< -o $@

# Ensure main object directory exists
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(COLOR_WARN)Created directory: $(OBJ_DIR)$(COLOR_RESET)"

# Clone or build external library
$(LIB42_DIR)/lib42.a:
	@if [ ! -d "$(LIB42_DIR)" ]; then \
		echo "$(COLOR_WARN)Cloning lib42...$(COLOR_RESET)"; \
		mkdir -p lib; \
		git clone $(LIB42_REPO) $(LIB42_DIR); \
	fi
	@$(MAKE) -C $(LIB42_DIR)

# Build project
$(NAME): $(OBJS) $(LIB42_DIR)/lib42.a
	@echo "$(COLOR_WARN)Linking $(NAME)...$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "$(COLOR_SUCCESS)Linking successful: $(NAME)$(COLOR_RESET)"

# Build debug version
$(NAME_DEBUG): $(OBJS:$(OBJ_DIR)/%.o=$(OBJ_DIR)/debug/%.o) $(LIB42_DIR)/lib42.a
	@echo "$(COLOR_HEADER)Linking $(NAME_DEBUG)...$(COLOR_RESET)"
	$(CC) $(DEBUG_FLAGS) $(OBJS:$(OBJ_DIR)/%.o=$(OBJ_DIR)/debug/%.o) -o $(NAME_DEBUG) $(LDFLAGS)
	@echo "$(COLOR_SUCCESS)$(NAME_DEBUG) built successfully$(COLOR_RESET)"

# Cleaning rules
clean:
	@echo "$(COLOR_HEADER)Cleaning object files...$(COLOR_RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(COLOR_SUCCESS)Object files cleaned$(COLOR_RESET)"

fclean: clean
	@echo "$(COLOR_HEADER)Removing executables...$(COLOR_RESET)"
	@rm -f $(NAME) $(NAME_DEBUG)
	@echo "$(COLOR_HEADER)Cleaning libraries...$(COLOR_RESET)"
	@$(MAKE) -C $(LIB42_DIR) clean
	@echo "$(COLOR_SUCCESS)All cleaned up$(COLOR_RESET)"

re: fclean all

# Debug rules
debug:  $(NAME_DEBUG)
	@echo "$(COLOR_ERROR)Compiling in debug mode...$(COLOR_RESET)"

redebug: fclean debug

# Norminette check
norm:
	@echo "$(COLOR_HEADER)Running Norminette...$(COLOR_RESET)"
	@-norminette $(SRC_DIR) | grep -v "OK!" || true
	@-norminette $(INCLUDE_DIR) | grep -v "OK!" || true
	@echo "$(COLOR_SUCCESS)Norminette check complete$(COLOR_RESET)"

.PHONY: all clean fclean re norm debug redebug
