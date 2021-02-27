/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:05:16 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/26 23:59:43 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "libft.h"
# include "ft_printf.h"

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

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_cmd
{
	char				*cmd_name;
	char				**args;
	char				*file_in;
	char				*file_out;
	int					redirection;
	int					separator;
	struct s_cmd		*next;	
}				t_cmd;

typedef struct s_cmds
{
	t_cmd	*head_cmd;
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


typedef struct	s_minishell
{
	t_tokens		*head_tk;
	t_lexer			lx;
	t_env 			*head_env;
	t_cmds			*cmds;
	t_exec			exec;
	char			**path_cmd;
	char			*path_home;
	char 			*line;
	int				last_ret_cmd;
}				t_minishell;

typedef void	(*t_inbuild)(char **);

void	ft_echo(char **args);
void	ft_cd(char **args);
void 	ft_pwd(char **args);
void	ft_export(char **args);
void	ft_unset(char **args);
void	ft_env(char **args);
void	ft_exit(char **args);
int		get_next_line(int fd, char **line);

void	lexer(t_minishell *msh);
void		init_token(t_tokens *tk, t_lexer *lx);
t_tokens	*next_token(t_tokens *tk, t_lexer *lx);
t_tokens	*token_special(t_tokens *tk, t_lexer *lx);
void 		token_in_quotes(t_tokens *tk, t_lexer *lx);
void		get_next_char(t_tokens *tk, t_lexer *lx);
void	token_dollar(t_tokens *tk, t_lexer *lx);

void	get_envp(char *envp[], t_minishell *msh);
void	tokens_substitution(t_minishell *msh);
int			get_char_type(char c);
void	evaluate_dollar(t_tokens *tk, t_lexer *lx, t_minishell *msh);

bool	syntax_parser(t_tokens *tk);
void	create_command(t_minishell *msh);
//void	execute_command(t_minishell *msh, t_cmd *head_cmd);

void 	exec_cmd_v2(t_minishell *msh, t_cmd *head_cmd);
#endif