/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:51:34 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 15:44:16 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_cmd_line(t_msh *msh, int size)
{
	int		col;
	char	cwd[PATH_MAX];
	int		len_prompt;

	getcwd(cwd, PATH_MAX);
	len_prompt = ft_strlen(cwd) + 3;
	col = tgetnum("col");
	while (size > 0)
	{
		if ((size + len_prompt + msh->remainder_line) % (col - 1) == 0)
		{
			tputs(tgetstr("up", NULL), 1, &ft_putchar);
			tputs(tgoto(tgetstr("ch", NULL), 0, col), 0, &ft_putchar);
			tputs(tgetstr("dc", NULL), 1, &ft_putchar);
		}
		tputs(tgetstr("le", NULL), 1, &ft_putchar);
		tputs(tgetstr("dc", NULL), 1, &ft_putchar);
		size--;
	}
}

void		history_up(t_msh *msh, int size)
{
	if (msh->head_hist == NULL)
		return ;
	if (msh->tmp_line == NULL)
	{
		if (!(msh->tmp_line = ft_strdup(g_stream.line)))
			exit_msh(msh, "strdup", strerror(errno));
	}
	else if (msh->curr_hist->next != NULL)
		msh->curr_hist = msh->curr_hist->next;
	else
		return ;
	delete_cmd_line(msh, size);
	ft_printf("%s", msh->curr_hist->cmd_line);
	ft_strdel(&g_stream.line);
	if (!(g_stream.line = ft_strdup(msh->curr_hist->cmd_line)))
		exit_msh(msh, "strdup", strerror(errno));
}

void		history_down(t_msh *msh, int size)
{
	if (msh->head_hist == NULL || msh->tmp_line == NULL)
		return ;
	else
	{
		delete_cmd_line(msh, size);
		msh->curr_hist = msh->curr_hist->prev;
		if (msh->curr_hist != NULL)
		{
			ft_printf(msh->curr_hist->cmd_line);
			ft_strdel(&g_stream.line);
			if (!(g_stream.line = ft_strdup(msh->curr_hist->cmd_line)))
				exit_msh(msh, "strdup", strerror(errno));
		}
		else
		{
			ft_printf(msh->tmp_line);
			ft_strdel(&g_stream.line);
			if (!(g_stream.line = ft_strdup(msh->tmp_line)))
				exit_msh(msh, "strdup", strerror(errno));
			msh->curr_hist = msh->head_hist;
			ft_strdel(&msh->tmp_line);
		}
	}
}

static bool	jump_cmd_line(t_msh *msh)
{
	char	*cmd_line;
	int		len_cmd;

	if (g_stream.line[0] == '\0' || g_stream.line[0] == ' ')
	{
		msh->curr_hist = msh->head_hist;
		return (true);
	}
	if (msh->head_hist)
	{
		if (!(cmd_line = ft_strdup(msh->head_hist->cmd_line)))
			exit_msh(msh, "ft_strdup: ", strerror(errno));
		len_cmd = ft_strlen(g_stream.line) + 1;
		if (!ft_strncmp(cmd_line, g_stream.line, len_cmd + 1))
		{
			msh->curr_hist = msh->head_hist;
			free(cmd_line);
			return (true);
		}
		free(cmd_line);
	}
	return (false);
}

void		insert_cmd_history(t_msh *msh)
{
	t_history *hist;

	if (jump_cmd_line(msh) == true)
		return ;
	if (!(hist = malloc(sizeof(t_history))))
		exit_msh(msh, "malloc: ", strerror(errno));
	if (msh->head_hist == NULL)
	{
		if (!(hist->cmd_line = ft_strdup(g_stream.line)))
			exit_msh(msh, "ft_strdup: ", strerror(errno));
		hist->next = NULL;
		hist->prev = NULL;
		msh->head_hist = hist;
	}
	else
	{
		if (!(hist->cmd_line = ft_strdup(g_stream.line)))
			exit_msh(msh, "ft_strdup: ", strerror(errno));
		hist->next = msh->head_hist;
		msh->head_hist->prev = hist;
		hist->prev = NULL;
		msh->head_hist = hist;
	}
	msh->curr_hist = msh->head_hist;
}
