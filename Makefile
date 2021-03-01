NAME = minishell

SRCS_DIR =	srcs
OBJS_DIR =	.objs
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_FILES =	main.c \
			token.c \
			token_lst.c \
			token_utils.c \
			lexer.c

SRCS = $(addprefix $(SRCS_DIR)/,$(SRC_FILES))
OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

HEAD = -I./$(LIBFT_DIR) -I./include
CC = clang
CFLAGS = -Wall -Werror -Wextra -g -w
LFLAGS = -L ./$(LIBFT_DIR) -lft
RM = /bin/rm -rf

all: $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(HEAD) $(CFLAG) $(LFLAGS) -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		mkdir -p $(OBJS_DIR)
		$(CC) $(CFLAGS) $(HEAD) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all


