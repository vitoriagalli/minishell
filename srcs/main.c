/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:03:35 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/18 03:04:46 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_envp()
{
	int i;
	t_env *node;

	i = 0;
	node = g_msh.head_env;
	while (g_msh.path_cmd[i])
		free(g_msh.path_cmd[i++]);
	free(g_msh.path_cmd);
	g_msh.path_cmd = NULL;
	free(g_msh.path_home);
	while (node)
	{
		if (!ft_strncmp(node->name, "PATH", 5))
			g_msh.path_cmd = ft_split(node->value, ':');
		if (!ft_strncmp(node->name, "HOME", 5))
			g_msh.path_home = ft_strdup(node->value);
		node = node->next;
	}
	if (g_msh.path_cmd == NULL)
		g_msh.path_cmd = ft_split(" :", ':');
}

void update_minishell()
{
	update_envp();
	g_msh.line = ft_strdup(g_msh.rd_line);
	free(g_msh.rd_line);
}

void	init_env(char **envp)
{
	int		len_arr;
	int		i;

	len_arr = 0;
	while (envp[len_arr])
		len_arr++;
	g_msh.env = ft_calloc(len_arr + 1, sizeof(char *));
	i = 0;
	while (i < len_arr)
	{
		g_msh.env[i] = ft_strdup(envp[i]);
		i++;
	}
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
