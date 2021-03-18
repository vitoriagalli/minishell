/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:05:16 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/18 13:13:11 by vscabell         ###   ########.fr       */
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
#include <curses.h>
#include <term.h>

# include "libft.h"
# include "ft_printf.h"

# define LF '\n'
# define DEL 127
# define ESC 27
# define SQ_BR '['
# define UP 'A'
# define DOWN 'B'






# define BUFF_READ 512
# define OPEN_MAX 1024
# define BUFFER_SIZE 32

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

# define STATE_GENERAL 10000
# define STATE_SINGLE_QUOTED 20000
# define STATE_DOUBLE_QUOTED 30000
# define STATE_BACKSLASHED 40000

# define BLUE "\033[1;34m"
# define YELLOW "\033[1;33m"
# define END_COLOR "\033[0m"



typedef struct s_lexer
{
	int 		i;
	int			size;
	int			type;
	char		*line;
	int 		state;
}				t_lexer;

typedef struct	s_tokens
{
	char			*data;
	int				type;
	struct s_tokens	*next;
}				t_tokens;

typedef struct s_cmd
{
	char				*cmd_name;
	char				**args;
	char				*file_in;
	char				*file_out;
	int					red_in;
	int					red_out;
	int					separator;
	struct s_cmd		*next;
}				t_cmd;

typedef struct s_cmds
{
	t_cmd			*head_cmd;
	int				nb_tk;
	int				curr_tk;
	int				curr_arg;
	bool			got_cmd_name;
}				t_cmds;

typedef struct s_exec
{
	bool	pipe;
	int		save_stdout;
	int		save_stdin;
	int		pipefds[2];
	pid_t	child_pid;
	char	**path_cmd;
	char	*path_home;
}				t_exec;

typedef struct	s_history
{
	char 				*cmd_line;
	struct s_history	*next;
	struct s_history	*prev;
}				t_history;


typedef struct	s_minishell
{
	char			**env;
	t_tokens		*head_tk;
	t_history		*head_hist;
	t_history		*curr_hist;
	t_lexer			lx;
	t_cmds			*cmds;
	t_exec			exec;
	struct termios 	*term;
	char			**path_cmd;
	char			*path_home;
	char			*termtype;
	char			*rd_line;
	char 			*line;
	char			*tmp_line;
	int				last_ret_cmd;
	bool			force_ret_buildin;
}				t_minishell;

t_minishell g_msh;

typedef void	(*t_inbuild)(t_cmd *, t_exec *);

void	ft_echo(t_cmd *cmd, t_exec *exec);
void	ft_cd(t_cmd *cmd, t_exec *exec);
void 	ft_pwd(t_cmd *cmd, t_exec *exec);
void	ft_export(t_cmd *cmd, t_exec *exec);
void	ft_unset(t_cmd *cmd, t_exec *exec);
void	ft_env(t_cmd *cmd, t_exec *exec);
void	ft_exit(t_cmd *cmd, t_exec *exec);
int		get_next_line(int fd, char **line);

void	lexer();
void		init_token(t_tokens *tk, t_lexer *lx);
t_tokens	*next_token(t_tokens *tk, t_lexer *lx);
t_tokens	*token_special(t_tokens *tk, t_lexer *lx);
void 		token_in_quotes(t_tokens *tk, t_lexer *lx);
void		get_next_char(t_tokens *tk, t_lexer *lx);
void	token_dollar(t_tokens *tk, t_lexer *lx);

void	get_envp(char *envp[]);
void	tokens_substitution();
int		get_char_type(char c);
void	evaluate_dollar(t_tokens *tk, t_lexer *lx);

bool	syntax_parser();
void	create_commands();

void 	execution_commands();

bool	is_buildin_cmd(char *cmd);
void	call_exec_buildin(t_cmd *cmd, t_exec *exec);


void	store_key_and_value(char **value, char **key, char *str);

#endif
