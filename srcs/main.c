/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:54:39 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/19 02:36:16 by vscabell         ###   ########.fr       */
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

t_token create_and_atribute_tkn(t_minishell *sh, int i)
{
	char *tkn_data;
	static int init_tkn = 0;		// bugado, arrumar


	tkn_data = ft_substr(sh->input, init_tkn, i - init_tkn);
	tkn_add_back(&sh->head, ft_tkn_new(tkn_data));
	init_tkn = i + 1;
}

int lexer(t_minishell *sh) {

	t_token	tk;
	int i = 0;
	int next_token;

	next_token = TRUE;
	while (sh->input[i])
	{
		if (sh->input[i] == '\'' || sh->input[i] == '\"' )
			next_token = TRUE ? FALSE : TRUE;
		else if (sh->input[i] == ' ' && next_token)
			create_and_atribute_tkn(sh, i);
		i++;
	}
	create_and_atribute_tkn(sh, i);


	ft_tkn_print(sh->head);
}


int	main(int argc, char **argv, char **envp) {

	t_minishell	sh;

	while (1)
	{
		ft_printf(">");
		sh.input = read_line();
		lexer(&sh);
		printf("%s\n", sh.input);

	}

}
