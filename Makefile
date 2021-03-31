NAME =		minishell

CC =		clang
CFLAGS =	-Wall -Wextra -Werror -g

INCLUDES =	-I ./includes -I ./libft/includes -I ./ft_printf/includes
LIBFT = -L ./libft -lft
FT_PRINTF = -L ./ft_printf -lftprintf

SRC_FILES =	main.c \
			readline/readline.c \
			readline/readline_utils.c \
			readline/history.c \
			lexer/lexer.c \
			lexer/tk_utils.c \
			lexer/tk_escape.c \
			lexer/tk_operator.c \
			lexer/tk_general.c \
			lexer/tk_quotes.c \
			builtin/builtin.c \
			builtin/cd.c \
			builtin/cd_utils.c \
			builtin/echo.c \
			builtin/env.c \
			builtin/exit.c \
			builtin/export.c \
			builtin/export_utils.c \
			builtin/pwd.c \
			builtin/unset.c \
			get_env.c \
			parser.c \
			create_cmds.c \
			create_cmds_utils.c \
			execution.c \
			execution_utils.c \
			find_path.c \
			signal.c \
			free_and_quit.c \
			free_utils.c \
			check_absolute_path.c \
			check_relative_path.c

SRCS = $(addprefix srcs/,$(SRC_FILES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo ' '
	@make --no-print-directory -C libft
	@make --no-print-directory -C ft_printf
	@clang $(OBJS) $(INCLUDES) $(CFLAGS) $(LIBFT) $(FT_PRINTF) -ltermcap -o $@
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
