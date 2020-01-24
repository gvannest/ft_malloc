# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvannest <gvannest@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/03 14:13:27 by gvannest          #+#    #+#              #
#    Updated: 2020/01/24 15:00:49 by gvannest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#ENV
ifeq ($(HOSTTYPE),)
	export HOSTTYPE=$(shell uname -m)_$(shell uname -s)
endif

# COMPILATION
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-Wpadded -Weverything
ADDFLAGS = -g
SYSFLAG =  -shared

# DEFAULT RULE
DEFRULE = all

# BINARY
NAME_2 = malloc_exec
NAME = libft_malloc_${HOSTTYPE}.so
SYMLINK = libft_malloc.so

# PATHS
SRC_PATH = ./src/
OBJ_PATH = ./objs/
LIBFT_PATH = ./libft/
INC_PATH = ./includes_malloc\
    ./libft/includes/ \

# SOURCES
SRC_NAME = \
    globals.c \
    ft_malloc.c \
	utils_mmap.c \
	free_list_mgmt.c \
	size_flags.c \
	ft_free.c \
	large_chunk.c \
	new_allocated_chunck.c \
	ft_show_alloc_mem.c \
	ft_realloc.c \
	headers.c \
	ft_defrag.c \
	ft_calloc.c
	

OBJ_NAME = $(SRC_NAME:.c=.o)

# PREFIXES
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

# FLAGS
CPPFLAGS = -I./includes_malloc/ -I./libft/includes
LDFLAGS = -L./libft/
LFT = -lft
LIBFT = $(LDFLAGS) $(LFT)

# **************************************************************************** #
# SPECIAL CHARS

LOG_CLEAR= \033[2K
LOG_UP= \033[A
LOG_NOCOLOR= \033[0m
LOG_BOLD= \033[1m
LOG_UNDERLINE= \033[4m
LOG_BLINKING= \033[5m
LOG_BLACK= \033[1;30m
LOG_RED= \033[1;31m
LOG_GREEN= \033[1;32m
LOG_YELLOW= \033[1;33m
LOG_BLUE= \033[1;34m
LOG_MAGENTA= \033[1;35m
LOG_CYAN= \033[1;36m
LOG_WHITE= \033[1;37m
LOG_ORANGE= \033[1;38;5;208m

# **************************************************************************** #

# RULES

# MAIN RULES
default:
	@make $(DEFRULE)

.PHONY: all
all: libftcomp $(OBJ_PATH) $(NAME) Makefile

libftcomp:
	@make all -C $(LIBFT_PATH)

$(NAME): $(OBJ)
	@echo -e "--$(LOG_CLEAR)$(LOG_MAGENTA)$(NAME)$(LOG_NOCOLOR)....................... $(LOG_ORANGE)assembling$(LOG_NOCOLOR)$(LOG_UP)"
	@$(CC) $(CFLAGS) $(SYSFLAG) $(ADD_FLAGS) $(LIBFT) $(OBJ) -o $@
	@echo -e "--$(LOG_CLEAR)$(LOG_CYAN)$(NAME)$(LOG_NOCOLOR) compiled................. $(LOG_GREEN)✓$(LOG_NOCOLOR)"
	ln -fs $(NAME) $(SYMLINK)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(ADDFLAGS) -c -o $@ $<

$(OBJ_PATH_CH)%.o: $(SRC_PATH_CH)%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(ADDFLAGS) -c -o $@ $<

$(OBJ_PATH):
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)build $(NAME)$(LOG_NOCOLOR)"
	@mkdir -p $(OBJ_PATH)

.PHONY: clean
clean:
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)clean $(NAME)$(LOG_NOCOLOR)"
	@echo -e "--$(LOG_CLEAR)$(LOG_YELLOW)Objects$(LOG_NOCOLOR) deleted.............. $(LOG_RED)×$(LOG_NOCOLOR)"
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIBFT_PATH)

.PHONY: fclean
fclean: clean
	@echo -e "$(LOG_CLEAR)$(LOG_BLUE)fclean $(NAME)$(LOG_NOCOLOR)"
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)
	@rm -f $(SYMLINK)

.PHONY: re
re: fclean all
