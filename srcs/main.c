/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vs-Rb <marvin@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:03:35 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/18 21:31:31 by Vs-Rb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void update_minishell()
{
	g_msh.line = ft_strdup(g_msh.rd_line);
	free(g_msh.rd_line);
}

int main(__attribute__((unused))int argc, __attribute__((unused))char *argv[],
	char *envp[])
{
	init_env(envp);
	init_terminal(envp);
	print_prompt();
	while ((read_line()) != 0)
	{
		update_minishell();
		lexer();
		create_commands();
		if (!syntax_parser() || !find_path())
			continue;
		execution_commands();
		free(g_msh.line);
		print_prompt();
	}
	// free everything before quit.
//	return (msh.last_ret_cmd);
}
