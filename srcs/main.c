/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:54:39 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/19 15:10:42 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_minishell(int exit_status) {
	exit(exit_status);
}

char *read_line(void) {

	char *line;

	if (get_next_line(STDIN_FILENO, &line) < 0) {
		free(line);
		exit_minishell(EXIT_FAILURE);
	}
	return(line);
}

t_token create_and_atribute_tkn(t_minishell *sh, int i, int *init_tkn)
{
	char *tkn_data;

	tkn_data = ft_substr(sh->input, *init_tkn, i - *init_tkn);
	tkn_add_back(&sh->head, ft_tkn_new(tkn_data));
	*init_tkn = i + 1;
}

int lexer(t_minishell *sh) {

	t_token	tk;
	int i = 0;
	int next_token;
	int init_tkn;

	init_tkn = 0;
	next_token = TRUE;
	while (sh->input[i])
	{
		if (sh->input[i] == '\'' || sh->input[i] == '\"' )
			next_token = TRUE ? FALSE : TRUE;
		else if (sh->input[i] == ' ' && next_token)
			create_and_atribute_tkn(sh, i, &init_tkn);
		i++;
	}
	create_and_atribute_tkn(sh, i, &init_tkn);

	ft_tkn_print(sh->head);
	ft_tkn_clear(&sh->head, ft_free);
}


int	main(int argc, char **argv, char **envp) {

	t_minishell	sh;

	while (1)
	{
		ft_printf(">");
		sh.input = read_line();
		lexer(&sh);
		// printf("%s\n", sh.input);
		free(sh.input);
	}
}
