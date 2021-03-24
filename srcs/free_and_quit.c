/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_quit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:39:03 by user42            #+#    #+#             */
/*   Updated: 2021/03/24 16:29:41 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_after_fork(void)
{
	ft_cmdclear(&g_msh.cmds.head_cmd, ft_free);
	ft_tknclear(&g_msh.head_tk, ft_free);
	free_history();
	free(g_msh.tmp_line);
	free(g_msh.line);
	free(g_msh.save);
	ft_array_clear(g_msh.env, ft_free);
}

void	exit_program(void)
{
	ft_tknclear(&g_msh.head_tk, ft_free);
	ft_cmdclear(&g_msh.cmds.head_cmd, ft_free);
	if (g_msh.line)
		ft_strdel(&g_msh.line);
	ft_array_clear(g_msh.env, ft_free);
	g_msh.env = NULL;
	free_history();
	restore_terminal(true);
	free(g_msh.save);
	g_msh.save = NULL;
	exit(g_msh.last_ret_cmd);
}
