#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdbool.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct		s_env {
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_token
{
	char			*cmd;
	t_list			*args;
	int				sep;
	struct s_token	*next;
}					t_token;

typedef struct		s_shell {
	t_token			*cmd;
	t_env			*env;
	char			**envp;
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
char	**put_tk_lst_into_array_pointers(t_token *tks);

void	handle_escape(char *data, int type);

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

#endif
