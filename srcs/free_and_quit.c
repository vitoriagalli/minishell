/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_quit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:39:03 by user42            #+#    #+#             */
/*   Updated: 2021/03/23 01:03:04 by vscabell         ###   ########.fr       */
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

void	ft_tknclear(t_tokens **lst, void (*del)(void*))
{
	t_tokens	*to_free;

	to_free = *lst;
	if (!*lst || !lst || !del)
		return ;
	while (to_free)
	{
		*lst = to_free->next;
		del(to_free->data);
		free(to_free);
		to_free = *lst;
	}
	*lst = NULL;
}

void	ft_cmdclear(t_cmd **lst, void (*del)(void*))
{
	t_cmd	*to_free;

	to_free = *lst;
	if (!*lst || !lst || !del)
		return ;
	while (to_free)
	{
		*lst = to_free->next;
		ft_array_clear(to_free->args, ft_free);
		if (to_free->redirection)
			ft_lstclear(&to_free->redirection, ft_free);
		del(to_free->cmd_name);
		free(to_free);
		to_free = *lst;
	}
	*lst = NULL;
}

void	free_loop_stuff(void)
{
	ft_tknclear(&g_msh.head_tk, ft_free);
	ft_cmdclear(&g_msh.cmds.head_cmd, ft_free);

	free(g_msh.save);
	g_msh.save = NULL;
}

void	exit_program()
{
	ft_tknclear(&g_msh.head_tk, ft_free);
	ft_cmdclear(&g_msh.cmds.head_cmd, ft_free);

	ft_array_clear(g_msh.env, ft_free);
	g_msh.env = NULL;
	free_history();
	// free_tokens();
	if (g_msh.line)
		ft_strdel(&g_msh.line);
	restore_terminal(true);
	free(g_msh.save);
	g_msh.save = NULL;
	exit(g_msh.last_ret_cmd);
}
