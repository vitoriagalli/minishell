/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:54:39 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/07 21:23:40 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(int exit_status)
{
	exit(exit_status);
}

char	*read_line(void)
{
	char	*line;

	if (get_next_line(STDIN_FILENO, &line) < 0)
	{
		free(line);
		exit_minishell(EXIT_FAILURE);
	}
	return (line);
}

void	sh_loop(void)
{
	while (true)
	{
		ft_printf("$ ");
		sh->input = read_line();
		lexer();
		execute();
	}
}

int		main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	sh = ft_calloc(1, sizeof(t_shell));
	initialize_global_env();
	sh_loop();
	return (0);
}
