/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:54:39 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/26 20:31:01 by vscabell         ###   ########.fr       */
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

	// sh = (t_shell) {0};

	while (1)
	{
		ft_printf("$ ");
		sh.input = read_line();
		lexer(&sh, envp);				// in progress
		// execute(&sh);
	}
}
