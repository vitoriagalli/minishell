#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdbool.h>
# include <unistd.h>

#include <sys/wait.h>

typedef struct		s_token {
	char			*data;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct		s_env {
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

// typedef struct		s_exec {
// 	char			*path;
// 	char			**argv;
// 	char			**envp;
// }					t_exec;

typedef struct		s_shell {
	t_token			*tks;
	t_env			*env;
	char			*input;
	int				status;

	char			*path;
	char			**argv;
	char			**envp;
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

t_token	*ft_tkn_new(char *data, int type);
void	tkn_add_back(t_token **head, t_token *new);
int		ft_tkn_size(t_token *head);
void	ft_free(char *elem);
void	ft_tkn_clear(t_token **lst, void (*del)(char*));
void	ft_tkn_print(t_token *head);

int		is_tk_char(int c);
int		is_quote_char(int c);
int		is_space_char(int c);
int		is_job_char(int c);

int		lexer(t_shell *sh, char** envp);
t_token	*put_input_into_tkn_lst(char *input);
void	substitute_tokens(t_shell *sh);


// ENV

t_env	*ft_env_new(char *name, char *value);
void	env_add_back(t_env **head, t_env *new);
int		ft_env_size(t_env *head);
void	ft_free(char *elem);
void	ft_env_clear(t_env **lst, void (*del)(char*));
void	ft_env_print(t_env *lst);


// COMMANDS - BUILDINS

int	execute(t_shell *sh);

int		ft_cd(t_shell *sh);
int		ft_echo(t_shell *sh);
int		ft_cd(t_shell *sh);
int		ft_pwd(t_shell *sh);
int		ft_export(t_shell *sh);
int		ft_unset(t_shell *sh);
int		ft_env(t_shell *sh);
int		ft_exit(t_shell *sh);

// PATH

char	*find_bin_path(t_env *env, char *command);

#endif
