/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:51:34 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/10 14:31:38 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void insert_cmd_history(t_minishell *msh)
{
	t_history *hist;

	if (msh->rd_line[0] == '\0' || msh->rd_line[0] == ' ')
		return ;
	hist = malloc(sizeof(t_history));
	if (msh->head_hist == NULL)
	{
		hist->cmd_line = ft_strdup(msh->rd_line);
		hist->next = NULL;
		hist->prev = NULL;
		msh->head_hist = hist;
	}
	else
	{
		hist->cmd_line = ft_strdup(msh->rd_line);
		hist->next = msh->head_hist;
		msh->head_hist->prev = hist;
		hist->prev = NULL;
		msh->head_hist = hist;
	}
	msh->curr_hist = msh->head_hist;
}

void init_cmd_history(t_minishell *msh)
{
	msh->head_hist = malloc(sizeof(t_history));
	msh->head_hist->next = NULL;
	msh->head_hist->prev = NULL;
	
}