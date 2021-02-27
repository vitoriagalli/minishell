# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 21:34:55 by romanbtt          #+#    #+#              #
#    Updated: 2021/02/17 16:41:50 by romanbtt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC =		clang
CFLAGS =	-Wall -Wextra -Werror

INC_DIR = includes
INC_LIBFT_DIR = ../libft/includes
SRC_DIR = sources
LIBFT_DIR = ../libft


LIBFT = $(LIBFT_DIR)/libft.a

SRC_FILES =	ft_printf.c \
			ft_printf_utils.c \
			flags.c \
			format_char.c \
			format_string.c \
			format_pointer.c \
			format_int.c \
			format_unsigned_int.c \
			format_percent.c \
			format_hex.c

SRCS = $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo ' '
	@make --no-print-directory -C $(LIBFT_DIR)
	@cp $(LIBFT) ./$(NAME)
	@ar rcs $(NAME) $(OBJS)
	@echo "\033[1;32m\n[OK]\033[0m    \033[1;33mCreating \033[0m $@"

%.o: %.c
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(INC_LIBFT_DIR) -c $< -o $@
	@echo "\033[1;32m[OK]\033[0m    \033[1;33mCompiling\033[0m $(<F)"

clean:
	@rm -f $(OBJS)
	@echo "\033[1;32m[OK]\033[0m    \033[1;33mDeleting \033[0m object files of ft_printf\n"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;32m[OK]\033[0m    \033[1;33mDeleting \033[0m $(NAME)\n"

re: fclean all
