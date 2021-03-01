#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdbool.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct		s_token
{
	char			*cmd;
	t_list			*args;
	int				sep;
	struct s_token	*next;
}					t_token;

typedef struct		s_shell {
	t_token			*cmd;
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
t_list	*args_lst(char *input, int *i, int *init_tkn, int *sep);



t_token	*put_input_into_tkn_lst(t_shell *sh);
void	ft_lst_print(t_list *lst);

#endif
