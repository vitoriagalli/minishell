/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:51:34 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/17 19:28:20 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void insert_cmd_history()
{
	t_history *hist;

	if (g_msh.rd_line[0] == '\0' || g_msh.rd_line[0] == ' ')
		return ;
	hist = malloc(sizeof(t_history));
	if (g_msh.head_hist == NULL)
	{
		hist->cmd_line = ft_strdup(g_msh.rd_line);
		hist->next = NULL;
		hist->prev = NULL;
		g_msh.head_hist = hist;
	}
	else
	{
		hist->cmd_line = ft_strdup(g_msh.rd_line);
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