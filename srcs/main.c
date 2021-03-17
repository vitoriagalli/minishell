/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:03:35 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/11 13:11:38 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_envp(t_minishell *msh)
{
	int i;
	t_env *node;

	i = 0;
	node = msh->head_env;
	while (msh->path_cmd[i])
		free(msh->path_cmd[i++]);
	free(msh->path_cmd);
	msh->path_cmd = NULL;
	free(msh->path_home);
	while (node)
	{
		if (!ft_strncmp(node->name, "PATH", 5))
			msh->path_cmd = ft_split(node->value, ':');
		if (!ft_strncmp(node->name, "HOME", 5))
			msh->path_home = ft_strdup(node->value);
		node = node->next;
	}
	if (msh->path_cmd == NULL)
		msh->path_cmd = ft_split(" :", ':');
}

void update_minishell(t_minishell *msh)
{
	update_envp(msh);
	msh->line = ft_strdup(msh->rd_line);
	free(msh->rd_line);
}

int main(int argc, char *argv[], char *envp[])
{
	t_minishell msh;

	ft_bzero(&msh, sizeof(t_minishell));
	init_terminal(&msh, envp);
	print_prompt();
	while ((read_line(&msh)) != 0)
	{
		update_minishell(&msh);
		lexer(&msh);
		if (!syntax_parser(&msh))
			continue;
		create_commands(&msh);
		execution_commands(&msh);
		free(msh.line);
		print_prompt();
	}
	// free everything before quit.
	return (msh.last_ret_cmd);
}