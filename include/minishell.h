#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdbool.h>
# include <unistd.h>
# include <sys/wait.h>

// -exec set follow-fork-mode-child


typedef struct		s_env {
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_token
{
	char			*tk_cmd;
	t_list			*args_lst;
	int				sep;
	struct s_token	*next;
}					t_token;

typedef struct		s_exec {
	char			*path;
	char			**argv;
	int				status;
}					t_exec;

typedef struct		s_cmd {
	char			*cmd;
	char			**args;
	char			*file_in;
	char			*file_out;
	// int				redirection;
	int				separator;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_shell {
	t_token			*tk;
	t_env			*env;
	t_cmd			*cmd;
	char			*input;
}					t_shell;

typedef int		(*builtin_funct)(t_shell *);

enum token_type {
	PIPE = '|',
	SEMICOLON = ';',
	ESCAPE = '\\',
	GREATER = '>',
	LESSER = '<',
	SPACE = ' ',
	TAB = '\t',
	SIMPLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	NULL_CHAR = 0,
	GENERAL = -1,
};



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

t_env	*ft_env_new(char *name, char *value);
void	env_add_back(t_env **head, t_env *new);
int		ft_env_size(t_env *head);
void	ft_free(char *elem);
void	ft_env_clear(t_env **lst, void (*del)(char*));
void	ft_env_print(t_env *lst);
t_env	*put_env_into_lst(char **env_content);


// COMMANDS - BUILDINS

void	cmd_add_back(t_cmd **lst, t_cmd *new);
t_cmd	*ft_cmd_new(void);
void	ft_cmd_print(t_cmd *lst);


int	execute(t_shell *sh);


int		ft_echo(t_token  *tk);
int		ft_cd(t_token  *tk);
int		ft_pwd(t_token  *tk);
int		ft_export(t_token  *tk);
int		ft_unset(t_token  *tk);
int		ft_env(t_token  *tk);
int		ft_exit(t_token  *tk);

#endif
