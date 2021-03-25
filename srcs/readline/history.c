/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:51:34 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 13:47:49 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_cmd_line(int size)
{
	while (size > 0)
	{
		tputs(tgetstr("le", NULL), 1, &ft_putchar);
		tputs(tgetstr("dc", NULL), 1, &ft_putchar);
		size--;
	}
}

void		history_up(int size)
{
	if (g_msh.head_hist == NULL)
		return ;
	if (g_msh.tmp_line == NULL)
	{
		if (!(g_msh.tmp_line = ft_strdup(g_msh.line)))
			exit_msh("strdup", strerror(errno));
	}
	else if (g_msh.curr_hist->next != NULL)
		g_msh.curr_hist = g_msh.curr_hist->next;
	else
		return ;
	delete_cmd_line(size);
	ft_printf("%s", g_msh.curr_hist->cmd_line);
	ft_strdel(&g_msh.line);
	if (!(g_msh.line = ft_strdup(g_msh.curr_hist->cmd_line)))
		exit_msh("strdup", strerror(errno));
}

void		history_down(int size)
{
	if (g_msh.head_hist == NULL || g_msh.tmp_line == NULL)
		return ;
	else
	{
		delete_cmd_line(size);
		g_msh.curr_hist = g_msh.curr_hist->prev;
		if (g_msh.curr_hist != NULL)
		{
			ft_printf(g_msh.curr_hist->cmd_line);
			ft_strdel(&g_msh.line);
			if (!(g_msh.line = ft_strdup(g_msh.curr_hist->cmd_line)))
				exit_msh("strdup", strerror(errno));
		}
		else
		{
			ft_printf(g_msh.tmp_line);
			ft_strdel(&g_msh.line);
			if (!(g_msh.line = ft_strdup(g_msh.tmp_line)))
				exit_msh("strdup", strerror(errno));
			g_msh.curr_hist = g_msh.head_hist;
			ft_strdel(&g_msh.tmp_line);
		}
	}
}

static bool	jump_cmd_line(void)
{
	char	*cmd_line;
	int		len_cmd;

	if (g_msh.line[0] == '\0' || g_msh.line[0] == ' ')
	{
		g_msh.curr_hist = g_msh.head_hist;
		return (true);
	}
	if (g_msh.head_hist)
	{
		if (!(cmd_line = ft_strdup(g_msh.head_hist->cmd_line)))
			exit_msh("ft_strdup: ", strerror(errno));
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

void		insert_cmd_history(void)
{
	t_history *hist;

	if (jump_cmd_line() == true)
		return ;
	if (!(hist = malloc(sizeof(t_history))))
		exit_msh("malloc: ", strerror(errno));
	if (g_msh.head_hist == NULL)
	{
		if (!(hist->cmd_line = ft_strdup(g_msh.line)))
			exit_msh("ft_strdup: ", strerror(errno));
		hist->next = NULL;
		hist->prev = NULL;
		g_msh.head_hist = hist;
	}
	else
	{
		if (!(hist->cmd_line = ft_strdup(g_msh.line)))
			exit_msh("ft_strdup: ", strerror(errno));
		hist->next = g_msh.head_hist;
		g_msh.head_hist->prev = hist;
		hist->prev = NULL;
		g_msh.head_hist = hist;
	}
	g_msh.curr_hist = g_msh.head_hist;
}
