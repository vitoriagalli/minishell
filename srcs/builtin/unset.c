/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vs-Rb <marvin@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:02:49 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/23 22:30:37 by Vs-Rb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_cmd *cmd, t_exec *exec)
{
	int		i;
	int		l;

	if (exec->child_pid == 0)
	{
		free_after_fork();
		exit(EXIT_SUCCESS);
	}	
	if (!cmd->args[1])
		return ;
	if (ft_strrchr(cmd->args[1], '='))
	{
		ft_printf("bash: unset: %s: not a valid identifier\n", cmd->args[1]);
		return ;
	}
	i = 0;
	l = ft_strlen(cmd->args[1]);
	while (g_msh.env[i])
	{
		if (!ft_strncmp(g_msh.env[i], cmd->args[1], l) && g_msh.env[i][l] == '=')
		{
			free(g_msh.env[i]);
			while (g_msh.env[i + 1])
			{
				g_msh.env[i] = g_msh.env[i + 1];
				i++;
			}
			g_msh.env[i] = NULL;
		}
		i++;
	}
	return ;
}
