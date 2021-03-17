NAME = minishell

SRCS_DIR =	srcs
OBJS_DIR =	.objs
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
SRC_FILES =	main.c \
			lexer.c \
			token.c \
			token_lst.c \
			token_utils.c \
			cmd.c \
			cmd_lst.c \
			path.c \
			redirection.c \
			exec.c \
			buildin_1.c \
			buildin_2.c \
			env_array.c \
			signal.c \
			free.c \
			read_line.c

SRCS = $(addprefix $(SRCS_DIR)/,$(SRC_FILES))
OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

HEAD = -I./$(LIBFT_DIR) -I./include
CC = clang
CFLAGS = -Wall -Werror -Wextra -g -w
LFLAGS = -L ./$(LIBFT_DIR) -lft \
		-l ncurses
RM = /bin/rm -rf

all: $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(HEAD) $(CFLAG) $(LFLAGS) -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		mkdir -p $(OBJS_DIR)
		$(CC) $(CFLAGS) $(HEAD) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all


