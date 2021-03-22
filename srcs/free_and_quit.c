/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_quit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vs-Rb <marvin@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:39:03 by user42            #+#    #+#             */
/*   Updated: 2021/03/22 16:10:15 by Vs-Rb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	free_history()
{
	t_history *node;

	while (g_msh.head_hist != NULL)
	{
		node = g_msh.head_hist;
		g_msh.head_hist = g_msh.head_hist->next;
		free(node);
	}
	g_msh.curr_hist = NULL;
}

void	exit_program()
{
	ft_array_clear(g_msh.env, ft_free);
	g_msh.env = NULL;
	free_history();
	free_tokens();
 	if (g_msh.line)
		ft_strdel(&g_msh.line);
	restore_terminal(true);
	exit(g_msh.last_ret_cmd);
}
