/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:45:59 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/18 02:57:53 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd *cmd, t_exec *exec)
{
	int		i;

	i = 0;
	if (exec->child_pid == 0)
	{
		while (g_msh.env[i])
			ft_putendl_fd(g_msh.env[i++], STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}
