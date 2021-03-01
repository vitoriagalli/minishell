/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:54:39 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/01 17:34:38 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	clear_memory(t_shell *sh)
// {
// 	// ft_env_clear(&sh->env, ft_free);
// 	// free(sh->env);
// 	ft_tkn_clear(&sh->tks, ft_free);
// 	free(sh->tks);
// 	free(sh->input);
// }

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

void	loop(t_shell *sh)
{
	while (true)
	{
		ft_printf("$ ");
		sh->input = read_line();
		lexer(sh);
		// execute(sh);
		// clear_memory(sh);
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	(void)argc;
	(void)argv;
	sh = (t_shell) {0};
	sh.envp = envp;
	sh.env = put_env_into_lst(envp);
	loop(&sh);
	return (0);
}
