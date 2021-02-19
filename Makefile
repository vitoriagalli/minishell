NAME =		minishell

CC =		clang
CFLAGS =	-w  -Wall -Wextra -Werror -g # -g to delete

INCLUDES =	-I ./includes -I ./libft/includes -I ./ft_printf/includes
LIBFT = -L ./libft -lft
FT_PRINTF = -L ./ft_printf -lftprintf

SRC_FILES =	main.c \
			get_next_line.c \
			inbuild.c \
			lexer/lexer.c \
			lexer/tk_utils.c \
			get_env.c \
			tokens_substitution.c

SRCS = $(addprefix srcs/,$(SRC_FILES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo ' '
	@make --no-print-directory -C libft
	@make --no-print-directory -C ft_printf
	@clang $(OBJS) $(INCLUDES) $(CFLAGS) $(LIBFT) $(FT_PRINTF) -o $@
	@echo "\033[1;32m\n[OK]\033[0m    \033[1;33mCreating \033[0m $@"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[1;32m[OK]\033[0m    \033[1;33mCompiling\033[0m $(<F)"

clean:
	@$(RM) $(OBJS)
	@echo "\033[1;32m[OK]\033[0m    \033[1;33mDeleting \033[0m object files of minishell\n"
	@make --no-print-directory clean -C libft
	@make --no-print-directory clean -C ft_printf
	

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[1;32m[OK]\033[0m    \033[1;33mDeleting \033[0m $(NAME)\n"
	@make --no-print-directory fclean -C libft
	@make --no-print-directory fclean -C ft_printf

re: fclean all
