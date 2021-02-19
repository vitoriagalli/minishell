#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>

# define TRUE 1
# define FALSE 0

typedef struct	s_token {
	int			type;
	char 		*data;
	struct		s_token *next;
}				t_token;

typedef struct	s_lexer {
	int			i;
}				t_lexer;

typedef struct	s_minishell {
	t_token		*head;
	char		*input;

}				t_minishell;


t_token	*ft_tkn_new(char *data);
void	tkn_add_front(t_token **head, t_token *new);
void	tkn_add_back(t_token **head, t_token *new);
int		ft_tkn_size(t_token *head);

void	ft_tkn_print(t_token *head);


#endif
