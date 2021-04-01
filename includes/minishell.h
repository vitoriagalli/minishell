/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:05:16 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/31 11:00:33 by romanbtt         ###   ########.fr       */
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
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'
# define ESCAPE '\\'
# define VERTICAL_BAR '|'
# define SPACE ' '
# define SEMICOLON ';'
# define TAB '	'
# define NEW_LINE '\n'
# define GREAT '>'
# define LESS '<'
# define DOLLAR '$'
# define EOT 4
# define TILD '~'

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
	t_list				*red_in;
	t_list				*red_out;
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
	int					fdin;
	int					fdout;
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

typedef struct			s_stream
{
	char				*line;
	int					exit_status;
}						t_stream;

typedef struct			s_msh
{
	char				**env;
	t_tokens			*head_tk;
	t_history			*head_hist;
	t_history			*curr_hist;
	t_cmds				cmds;
	t_stream			line;
	struct termios		*save;
	char				*tmp_line;
	int					len_prompt;
	int					remainder_line;
}						t_msh;

t_stream				g_stream;

typedef void			(*t_inbuild)(t_msh *, t_cmd *);

/*
** parser.c
*/

bool					parser(t_msh *msh);

/*
** signal.c
*/

void					handle_signals(t_msh *msh, int caller, int pid);
void					signal_handler_parent(int signal);
void					signal_handler_do_nothing(int sig);
void					signal_handler_prompt(int sig);

/*
** main.c
*/

void					restore_terminal(t_msh *msh, bool from_exit);

/*
** get_env.c
*/

void					init_env(t_msh *msh, char **envp);
char					**get_env_value(t_msh *msh, char *key);

/*
** free_and_quit.c
*/

void					exit_program(t_msh *msh);
void					ft_cmdclear(t_cmd **lst, void (*del)(void*));
void					ft_tknclear(t_tokens **lst, void (*del)(void*));
void					free_history(t_msh *msh);

/*
** find_path.c
*/

bool					find_path(t_msh *msh, t_cmd *cmd, t_exec *exec);
void					ft_array_clear(char **arr, void (*del)(void*));
void					ft_free(void *elem);

/*
** check_relative_path.c
*/

char					*relative_path(t_msh *msh, char *cmd, t_exec *exec);

/*
** check_absolute_path.c
*/

char					*absolute_path(t_msh *msh, char *cmd, t_exec *exec);
bool					file_exists(char *filepath);

/*
** execution_utils.c
*/

void					execution_cmds(t_msh *msh);
int						exit_status(void);

/*
** execution.c
*/

int						set_input_red(t_msh *msh, t_cmd *cmd, t_exec *exec);
int						set_output_red(t_msh *msh, t_cmd *cmd, t_exec *exec);

/*
** error_handling.c
*/

void					exit_msh(t_msh *msh, char *function, char *str_err);

/*
** create_cmds.c
*/

void					create_cmds(t_msh *msh);

/*
** create_cmds_utils.c
*/

t_tokens				*handle_out_append(t_msh *msh, t_cmd *cmd,
							t_tokens *tk);
t_tokens				*handle_out_overwrite(t_msh *msh, t_cmd *cmd,
							t_tokens *tk);
t_tokens				*handle_out_input(t_msh *msh, t_cmd *cmd, t_tokens *tk);
void					del_last_empty_node(t_msh *msh);

/*
** readline.c
*/

int						read_line(t_msh *msh, bool from_main);
void					print_prompt(void);

/*
** readline_utils.c
*/

int						ft_putchar(int c);
int						process_newline(t_msh *msh);
void					delete_char_left(t_msh *msh, int size);
void					add_char_to_line(t_msh *msh, int size, char c);

/*
** history.c
*/

void					insert_cmd_history(t_msh *msh);
void					history_up(t_msh *msh, int size);
void					history_down(t_msh *msh, int size);

/*
** lexer.c
*/

void					lexer(t_msh *msh);
void					evaluate_dollar(t_msh *msh, t_tokens *tk, t_lexer *lx);
char					*ft_strjoin_realloc(t_msh *msh, char *s1, char *s2);

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

t_tokens				*general_state(t_msh *msh, t_tokens *tk, t_lexer *lx);

/*
** tk_operator.c
*/

t_tokens				*put_in_token_operator(t_msh *msh, t_tokens *tk,
							t_lexer *lx);

/*
** tk_quotes.c
*/

void					double_quoted_state(t_msh *msh, t_tokens *tk,
							t_lexer *lx);
void					quoted_state(t_msh *msh, t_tokens *tk, t_lexer *lx);
void					activate_quoted_state(t_tokens *tk, t_lexer *lx,
							int type_quote);

/*
** tk_utils.c
*/

t_tokens				*create_new_token(t_msh *msh, t_tokens *tk,
							t_lexer *lx);
t_tokens				*remove_last_empty_node(t_tokens *head_tk);
void					add_end_token(t_msh *msh, t_tokens *head_tk,
							t_lexer *lx);
int						size_token_list(t_tokens *lst);
void					init_token(t_msh *msh, t_tokens *tk, t_lexer *lx);

/*
** builtin.c
*/

bool					is_buildin_cmd(char *cmd);
void					call_exec_buildin(t_msh *msh, t_cmd *cmd);

/*
** cd.c
*/

void					ft_cd(t_msh *msh, t_cmd *cmd);
void					replace_pwd(t_msh *msh, int i, char *pwd);
void					replace_oldpwd(t_msh *msh, int i, char *oldpwd);

/*
** echo.c
*/

void					ft_echo(t_msh *msh, t_cmd *cmd);

/*
** env.c
*/

void					ft_env(t_msh *msh, t_cmd *cmd);

/*
** exit.c
*/

void					ft_exit(t_msh *msh, t_cmd *cmd);

/*
** export.c
*/

void					ft_export(t_msh *msh, t_cmd *cmd);
char					**reallocate_array(t_msh *msh, char **buffer,
							char *new_string);
char					**duplicate_array(t_msh *msh, char **buffer,
							int len_arr);

/*
** pwd.c
*/

void					ft_pwd(t_msh *msh, t_cmd *cmd);

/*
** unset.c
*/

void					ft_unset(t_msh *msh, t_cmd *cmd);

#endif
