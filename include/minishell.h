#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>

# define TRUE 1
# define FALSE 0

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
	CHAR_GENERAL = 0,
};



typedef struct	s_token {
	int			type;
	char 		*data;
	struct		s_token *next;
}				t_token;

// typedef struct	s_lexer {
// 	int			i;
// }				t_lexer;

typedef struct	s_minishell {
	char		*input;
	t_token		*head;
	char		all_tk_types[11];
	int			n_tokens;
}				t_minishell;


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

int		lexer(t_minishell *sh);

void	ft_tkn_print(t_token *head);



#endif
