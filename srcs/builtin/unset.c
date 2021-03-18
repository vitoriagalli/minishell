/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:02:49 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/18 13:12:15 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_cmd *cmd, t_exec *exec)
{
	int		i;
	int		l;

	if (exec->child_pid == 0)
		exit(EXIT_SUCCESS);
	if (!cmd->args[1])
		exit(EXIT_SUCCESS);
	if (ft_strrchr(cmd->args[1], '='))
	{
		ft_printf("bash: unset: %s: not a valid identifier\n", cmd->args[1]);
		exit(EXIT_FAILURE);
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
