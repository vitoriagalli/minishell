/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:51:34 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/23 00:12:06 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool jump_cmd_line()
{
	char *cmd_line;
	int len_cmd;

	if (g_msh.line[0] == '\0' || g_msh.line[0] == ' ')
	{
		g_msh.curr_hist = g_msh.head_hist;
		return (true);
	}
	if (g_msh.head_hist)
	{
		cmd_line = ft_strdup(g_msh.head_hist->cmd_line);
		len_cmd = ft_strlen(g_msh.line) + 1;
		if (!ft_strncmp(cmd_line, g_msh.line, len_cmd + 1))
		{
			g_msh.curr_hist = g_msh.head_hist;
			free(cmd_line);
			return (true);
		}
		free(cmd_line);
	}
	return (false);
}

void insert_cmd_history()
{
	t_history *hist;

	if (jump_cmd_line() == true)
		return ;
	hist = malloc(sizeof(t_history));
	if (g_msh.head_hist == NULL)
	{
		hist->cmd_line = ft_strdup(g_msh.line);
		hist->next = NULL;
		hist->prev = NULL;
		g_msh.head_hist = hist;
	}
	else
	{
		hist->cmd_line = ft_strdup(g_msh.line);
		hist->next = g_msh.head_hist;
		g_msh.head_hist->prev = hist;
		hist->prev = NULL;
		g_msh.head_hist = hist;
	}
	g_msh.curr_hist = g_msh.head_hist;
}

void init_cmd_history(t_minishell *msh)
{
	msh->head_hist = malloc(sizeof(t_history));
	msh->head_hist->next = NULL;
	msh->head_hist->prev = NULL;
}
