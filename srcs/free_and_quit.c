/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_quit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:39:03 by user42            #+#    #+#             */
/*   Updated: 2021/03/30 13:56:21 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_msh(t_msh *msh, char *function, char *str_err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(function, STDERR_FILENO);
	ft_putstr_fd(str_err, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit_program(msh);
}

void	exit_program(t_msh *msh)
{
	ft_tknclear(&msh->head_tk, ft_free);
	ft_cmdclear(&msh->cmds.head_cmd, ft_free);
	if (g_stream.line)
		ft_strdel(&g_stream.line);
	ft_array_clear(msh->env, ft_free);
	msh->env = NULL;
	free_history(msh);
	restore_terminal(msh, true);
	free(msh->save);
	msh->save = NULL;
	exit(g_stream.exit_status);
}
