/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:03:35 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 02:26:20 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_terminal(bool from_exit)
{
	if (from_exit == true)
	{
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, g_msh.save) == -1)
		{
			free(g_msh.save);
			g_msh.save = NULL;
			exit(g_msh.last_ret_cmd);
		}
	}
	else
	{
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, g_msh.save) == -1)
			exit_msh("tcsetattr: ", strerror(errno));
	}
}

int		main(void)
{
	init_env(__environ);
	while ((read_line(true)) != 0)
	{
		restore_terminal(false);
		lexer();
		if (!syntax_parser())
			continue;
		create_commands();
		execution_commands();
	}
	exit_program();
}
