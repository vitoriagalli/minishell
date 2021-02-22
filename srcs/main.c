/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:54:39 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/22 02:20:56 by vscabell         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp) {

	t_shell	sh;
	char **args;

	while (1)
	{
		ft_printf("$ ");
		sh.input = read_line();
		// lexer(&sh);				// in progress

		args = ft_split(sh.input, ' ');
		execute(args);

		free(sh.input);
	}
}
