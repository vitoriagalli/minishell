/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:45:59 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/24 15:56:03 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(UNUSED t_cmd *cmd, t_exec *exec)
{
	int		i;

	i = 0;
	if (exec->child_pid == 0)
	{
		while (g_msh.env[i])
			ft_putendl_fd(g_msh.env[i++], STDOUT_FILENO);
		free_after_fork();
		exit(EXIT_SUCCESS);
	}
}
