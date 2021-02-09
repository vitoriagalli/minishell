# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/23 08:54:07 by vscabell          #+#    #+#              #
#    Updated: 2021/02/09 23:30:53 by vscabell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS_DIR = srcs

OBJS_DIR = .objs

INCL_DIR = include

SRCS = $(SRCS_DIR)/ft_itoa.c \
	$(SRCS_DIR)/ft_putstr_fd.c \
	$(SRCS_DIR)/ft_strnstr.c \
	$(SRCS_DIR)/ft_memccpy.c \
	$(SRCS_DIR)/ft_split.c	\
	$(SRCS_DIR)/ft_strrchr.c \
	$(SRCS_DIR)/ft_atoi.c \
	$(SRCS_DIR)/ft_memchr.c \
	$(SRCS_DIR)/ft_strchr.c \
	$(SRCS_DIR)/ft_strtrim.c \
	$(SRCS_DIR)/ft_bzero.c \
	$(SRCS_DIR)/ft_memcmp.c \
	$(SRCS_DIR)/ft_strdup.c \
	$(SRCS_DIR)/ft_substr.c \
	$(SRCS_DIR)/ft_calloc.c	\
	$(SRCS_DIR)/ft_memcpy.c	\
	$(SRCS_DIR)/ft_strjoin.c \
	$(SRCS_DIR)/ft_tolower.c \
	$(SRCS_DIR)/ft_isalnum.c \
	$(SRCS_DIR)/ft_memmove.c \
	$(SRCS_DIR)/ft_strlcat.c \
	$(SRCS_DIR)/ft_toupper.c \
	$(SRCS_DIR)/ft_isalpha.c \
	$(SRCS_DIR)/ft_memset.c \
	$(SRCS_DIR)/ft_strlcpy.c \
	$(SRCS_DIR)/ft_isascii.c \
	$(SRCS_DIR)/ft_putchar_fd.c \
	$(SRCS_DIR)/ft_strlen.c \
	$(SRCS_DIR)/ft_isdigit.c \
	$(SRCS_DIR)/ft_putendl_fd.c \
	$(SRCS_DIR)/ft_strmapi.c \
	$(SRCS_DIR)/ft_isprint.c \
	$(SRCS_DIR)/ft_putnbr_fd.c \
	$(SRCS_DIR)/ft_strncmp.c \
	$(SRCS_DIR)/ft_lstnew.c \
	$(SRCS_DIR)/ft_lstadd_front.c \
	$(SRCS_DIR)/ft_lstsize.c \
	$(SRCS_DIR)/ft_lstlast.c \
	$(SRCS_DIR)/ft_lstadd_back.c \
	$(SRCS_DIR)/ft_lstdelone.c \
	$(SRCS_DIR)/ft_lstclear.c \
	$(SRCS_DIR)/ft_lstiter.c \
	$(SRCS_DIR)/ft_lstmap.c \
	$(SRCS_DIR)/ft_isspace.c \
	$(SRCS_DIR)/ft_strjoin_n_free.c \
	$(SRCS_DIR)/ft_calloc_char.c \
	$(SRCS_DIR)/ft_itoa_base.c \
	$(SRCS_DIR)/ft_swap.c \
	$(SRCS_DIR)/get_next_line.c

OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

CC = clang

HEAD = -I./$(INCL_DIR)

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

RM = /bin/rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@ ar rc $(NAME) $(OBJS)
	@ ranlib $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(HEAD) -c $< -o $@

clean:
	@ $(RM) $(OBJS_DIR)

fclean: clean
	@ $(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
