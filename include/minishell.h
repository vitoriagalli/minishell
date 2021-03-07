#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

// -exec set follow-fork-mode-child

typedef struct		s_token
{
	char			*tk_cmd;
	t_list			*args_lst;
	int				sep;
	struct s_token	*next;
}					t_token;

typedef struct		s_cmd {
	char			*cmd;
	char			**args;
	char			*file_in;
	char			*file_out;
	int				redirection;
	int				separator;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_exec {
	char			*path;
	char			**argv;
	// int				fd[2];
	int				pid;
}					t_exec;

typedef struct		s_shell {
	t_token			*tk;
	t_cmd			*cmd;
	char			*input;
	int				status;
}					t_shell;

typedef int		(*builtin_funct)(t_cmd *);

enum			token_type {
				PIPE = '|',
				SEMICOLON = ';',
				ESCAPE = '\\',
				LESSER = '<',
				GREATER = '>',
				GGREATER = 'G',
				SPACE = ' ',
				TAB = '\t',
				SIMPLE_QUOTE = '\'',
				DOUBLE_QUOTE = '\"',
				NULL_CHAR = 0,
				GENERAL = -1,
};

char	**g_env;
t_shell	sh;


// TOKENS

t_token	*ft_tkn_new(t_list *args, int sep);
void	tkn_add_back(t_token **head, t_token *new);
int		ft_tkn_size(t_token *head);
void	ft_free(char *elem);
void	ft_tkn_clear(t_token **lst, void (*del)(char*));
void	ft_tkn_print(t_token *head);

int		is_tk_char(int c);
int		is_quote_char(int c);
int		is_space_char(int c);
int		is_job_char(int c);

int		lexer(t_shell *sh);



t_token	*put_input_into_tkn_struct(t_shell *sh);
void	ft_lst_print(t_list *lst);


// ENV
void	initialize_global_env(void);
char	**reallocate(char **buffer, int len_arr);
void	store_value_and_name(char **value, char **name, int i);

// COMMANDS - BUILDINS

void	cmd_add_back(t_cmd **lst, t_cmd *new);
t_cmd	*ft_cmd_new(void);
void	ft_cmd_print(t_cmd *lst);
void	ft_cmd_clear(t_cmd **lst, void (*del)(char*));

int		execute(t_shell *sh);


int		ft_echo(t_cmd *cmd);
int		ft_cd(t_cmd *cmd);
int		ft_pwd(t_cmd *cmd);
int		ft_export(t_cmd *cmd);
int		ft_unset(t_cmd *cmd);
int		ft_env(t_cmd *cmd);
int		ft_exit(t_cmd *cmd);



void	ft_array_clear(char **arr, void (*del)(char *));
void	free_shell(t_shell *sh);
void	ft_free(char *elem);

#endif
