NAME = minishell

SRCS = main.c
OBJS = main.o

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

LIBFTPRINTF_DIR = ft_printf
LIBFTPRINTF = $(LIBFTPRINTF_DIR)/libftprintf.a

HEAD = -I./$(LIBFT_DIR) -I./$(LIBFTPRINTF_DIR) -I./include

CC = clang

CFLAGS = -Wall -Werror -Wextra -w

LFLAGS = -L ./$(LIBFT_DIR) -lft \
		-L ./$(LIBFTPRINTF_DIR) -lftprintf

all: $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(LIBFTPRINTF_DIR)
	$(CC) $(OBJS) $(HEAD) $(CFLAG) $(LFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(HEAD) -c $< -o $@

$(LIBFT):
	make -C libft

$(LIBFTPRINTF_DIR):
	make -C ft_printf


clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(LIBFTPRINTF_DIR)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(LIBFTPRINTF_DIR)
	rm -rf $(NAME)

re: fclean all


