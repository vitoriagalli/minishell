#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdbool.h>
# include <unistd.h>

typedef struct	s_token {
	int			type;
	char		*data;
	struct		s_token *next;
}				t_token;

typedef struct	s_shell {
	t_token		*tks;
	char		*input;
	int			status;
}				t_shell;

typedef int		(*builtin_funct)(t_shell *);

enum token_type {
	CHAR_PIPE = '|',
	CHAR_SEMICOLON = ';',
	CHAR_ESCAPE = '\\',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_SPACE = ' ',
	CHAR_TAB = '\t',
	CHAR_SIMPLE_QUOTE = '\'',
	CHAR_DOUBLE_QUOTE = '\"',
	CHAR_NULL = 0,
	CHAR_GENERAL = -1,
};


// TOKENS


t_token	*ft_tkn_new(char *data);
void	tkn_add_front(t_token **head, t_token *new);
void	tkn_add_back(t_token **head, t_token *new);
int		ft_tkn_size(t_token *head);
void	ft_free(char *elem);
void	ft_tkn_clear(t_token **lst, void (*del)(char*));

int		is_tk_char(int c);
int		is_quote_char(int c);
int		is_space_char(int c);
int		is_job_char(int c);

int		lexer(t_shell *sh);

void	ft_tkn_print(t_token *head);



// COMMANDS - BUILDINS

int	execute(t_shell *sh);
int	ft_cd(t_shell *sh);
int	ft_echo(t_shell *sh);
int	ft_cd(t_shell *sh);
int	ft_pwd(t_shell *sh);
int	ft_export(t_shell *sh);
int	ft_unset(t_shell *sh);
int	ft_env(t_shell *sh);
int	ft_exit(t_shell *sh);


#endif
