/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:03:35 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/18 22:30:10 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void update_minishell()
{
	g_msh.line = ft_strdup(g_msh.rd_line);
	free(g_msh.rd_line);
}

int main(int argc, char *argv[], char *envp[])
{
	init_env(envp);
	init_terminal(envp);
	print_prompt();
	while ((read_line()) != 0)
	{
		update_minishell();
		lexer();
		if (!syntax_parser())
		{
			print_prompt();
			continue;
		}
		create_commands();
		execution_commands();
		free(g_msh.line);
		print_prompt();
	}
	// free everything before quit.
//	return (msh.last_ret_cmd);
}
