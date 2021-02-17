#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>


typedef struct	s_token {
	int			type;
	char 		*data;
	struct		s_token *next;
}				t_token;


typedef struct	s_minishell {

	t_token		*token;
	char		*input;

}				t_minishell;


#endif
