/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vs-Rb <marvin@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:03:35 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/22 11:53:21 by Vs-Rb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_terminal()
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, g_msh.save) == -1)
		exit (0); // Call exit function faillure
	free(g_msh.save);
}

int main(__attribute__((unused))int argc, __attribute__((unused))char *argv[],
	char *envp[])
{
	init_env(envp);
	while ((read_line()) != 0)
	{
		restore_terminal();
		lexer();
		if (!syntax_parser())
			continue;
		create_commands();
		if (!find_path())
			continue;
		execution_commands();
		free(g_msh.line);
	}
	// free everything before quit.
	// return (msh.last_ret_cmd);
	// exit_program();
}
