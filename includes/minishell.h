/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:05:16 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 16:15:47 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <linux/limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>
# include <signal.h>

# include "libft.h"
# include "ft_printf.h"

# define LF '\n'
# define DEL 127
# define ESC 27
# define SQ_BR '['
# define UP 'A'
# define DOWN 'B'

# define CHAR_GENERAL 1
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define ESCAPE 92
# define VERTICAL_BAR 124
# define SPACE 32
# define SEMICOLON 59
# define TAB 9
# define NEW_LINE 10
# define GREAT 62
# define LESS 60
# define DOLLAR 36
# define EOT 4

# define WORD 100
# define PIPE 200
# define OUT_OVERWRITE 300
# define OUT_APPEND 400
# define INPUT 500
# define SEPARATOR 600
# define END 700

# define TYPE_GENERAL 1000
# define TYPE_SINGLE_QUOTE 2000
# define TYPE_DOUBLE_QUOTE 3000
# define TYPE_OPERATOR 4000
# define TYPE_SPACE 5000
# define TYPE_ESCAPE 6000
# define TYPE_DOLLAR 7000

# define STATE_GEN 10000
# define STATE_SINGLE_QUOTED 20000
# define STATE_DOUBLE_QUOTED 30000
# define STATE_BACKSLASHED 40000

# define ROOT 100000
# define FORK 200000

# define BLUE "\033[1;34m"
# define YELLOW "\033[1;33m"
# define END_COLOR "\033[0m"

typedef struct			s_lexer
{
	int					i;
	int					size;
	int					type;
	char				*line;
	int					state;
}						t_lexer;

typedef struct			s_tokens
{
	char				*data;
	int					type;
	struct s_tokens		*next;
}						t_tokens;

typedef struct			s_cmd
{
	char				*cmd_name;
	char				**args;
	t_list				*redirection;
	int					separator;
	struct s_cmd		*next;
}						t_cmd;

typedef struct			s_cmds
{
	t_cmd				*head_cmd;
	int					curr_tk;
	int					curr_arg;
	bool				got_cmd_name;
}						t_cmds;

typedef struct			s_exec
{
	bool				pipe;
	int					save_stdout;
	int					save_stdin;
	int					pipefds[2];
	pid_t				child_pid;
}						t_exec;

typedef struct			s_history
{
	char				*cmd_line;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

typedef struct			s_minishell
{
	char				**env;
	t_tokens			*head_tk;
	t_history			*head_hist;
	t_history			*curr_hist;
	t_cmds				cmds;
	struct termios		*save;
	char				*line;
	char				*tmp_line;
	int					last_ret_cmd;
	bool				force_ret_buildin;
}						t_minishell;

t_minishell				g_msh;

typedef void			(*t_inbuild)(t_cmd *, t_exec *);

/*
** parser.c
*/

bool					parser();

/*
** signal.c
*/

void					handle_signals(int caller, int pid);
void					signal_handler_parent(int signal);
void					signal_handler_do_nothing(int sig);
void					signal_handler_prompt(int sig);

/*
** main.c
*/

void					restore_terminal(bool from_exit);

/*
** get_env.c
*/

void					init_env(char **envp);
char					**get_env_value(char *key);
void					store_key_and_value(char **value, char **key,
							char *str);

/*
** free_and_quit.c
*/

void					exit_program();
void					ft_cmdclear(t_cmd **lst, void (*del)(void*));
void					ft_tknclear(t_tokens **lst, void (*del)(void*));
void					free_history();
void					free_after_fork();

/*
** find_path.c
*/

bool					find_path();
void					ft_array_clear(char **arr, void (*del)(void*));
void					ft_free(void *elem);

/*
** check_relative_path.c
*/

char					*relative_path(char *cmd);

/*
** check_absolute_path.c
*/

char					*absolute_path(char *cmd);
bool					file_exists(char *filepath);

/*
** execution_utils.c
*/

void					execution_cmds();
int						exit_status(void);

/*
** execution.c
*/

void					set_redirection(t_cmd *cmd);

/*
** error_handling.c
*/

void					exit_msh(char *function, char *str_err);

/*
** create_cmds.c
*/

void					create_cmds();

/*
** create_cmds_utils.c
*/

t_tokens				*handle_out_append(t_cmd *cmd, t_tokens *tk);
t_tokens				*handle_out_overwrite(t_cmd *cmd, t_tokens *tk);
t_tokens				*handle_out_input(t_cmd *cmd, t_tokens *tk);

/*
** readline.c
*/

int						read_line(bool from_main);
int						get_input_user();
void					print_prompt();

/*
** readline_utils.c
*/

int						ft_putchar(int c);
int						process_newline(void);
void					delete_char_left(int size);
void					add_char_to_line(int size, char c);

/*
** history.c
*/

void					init_cmd_history();
void					insert_cmd_history();
void					history_up(int size);
void					history_down(int size);

/*
** lexer.c
*/

void					lexer();
void					evaluate_dollar(t_tokens *tk, t_lexer *lx);

/*
** lexer_env.c
*/

char					*substitution_env(char *str);

/*
** tk_escape.c
*/

void					escape_in_double_quote(t_tokens *tk, t_lexer *lx);
void					handle_escape_in_general(t_tokens *tk, t_lexer *lx);

/*
** tk_general.c
*/

t_tokens				*general_state(t_tokens *tk, t_lexer *lx);

/*
** tk_operator.c
*/

t_tokens				*put_in_token_operator(t_tokens *tk, t_lexer *lx);

/*
** tk_quotes.c
*/

void					double_quoted_state(t_tokens *tk, t_lexer *lx);
void					quoted_state(t_tokens *tk, t_lexer *lx);
void					activate_quoted_state(t_tokens *tk, t_lexer *lx,
							int type_quote);

/*
** tk_utils.c
*/

t_tokens				*create_new_token(t_tokens *tk, t_lexer *lx);
t_tokens				*remove_last_empty_node(t_tokens *head_tk);
void					add_end_token(t_tokens *head_tk, t_lexer *lx);
int						size_token_list(t_tokens *lst);
void					init_token(t_tokens *tk, t_lexer *lx);

/*
** builtin.c
*/

bool					is_buildin_cmd(char *cmd);
void					call_exec_buildin(t_cmd *cmd, t_exec *exec);

/*
** cd.c
*/

void					ft_cd(t_cmd *cmd, t_exec *exec);
char					*replace_tild(char *arg);
void					replace_pwd(int i, bool is_pwd, char *pwd,
							char *oldpwd);

/*
** echo.c
*/

void					ft_echo(t_cmd *cmd, t_exec *exec);

/*
** env.c
*/

void					ft_env(t_cmd *cmd, t_exec *exec);

/*
** exit.c
*/

void					ft_exit(t_cmd *cmd, t_exec *exec);

/*
** export.c
*/

void					ft_export(t_cmd *cmd, t_exec *exec);
char					**reallocate_array(char **buffer, char *new_string);
char					**duplicate_array(char **buffer, int len_arr);

/*
** pwd.c
*/

void					ft_pwd(t_cmd *cmd, t_exec *exec);

/*
** unset.c
*/

void					ft_unset(t_cmd *cmd, t_exec *exec);

#endif
