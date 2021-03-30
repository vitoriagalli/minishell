/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:04:04 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 15:45:06 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exit_status(void)
{
	if (errno == EACCES)
		return (126);
	if (errno == ENOENT)
		return (127);
	else
		return (EXIT_FAILURE);
}

int			set_input_red(t_cmd *cmd)
{
	t_list	*tmp;
	int		fd;

	tmp = cmd->red_in;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp(tmp->content, "<"))
			fd = open(tmp->next->content, O_RDONLY);
		if (fd < 0)
		{
			ft_printf("minishell: %s: %s\n", tmp->next->content,
				"No such file or directory");
			g_stream.exit_status = EXIT_FAILURE;
			return (-1);
		}
		tmp = tmp->next->next;
	}
	return (fd);
}

int			set_output_red(t_cmd *cmd)
{
	t_list	*tmp;
	int		fd;

	tmp = cmd->red_out;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp(tmp->content, ">"))
			fd = open(tmp->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (!ft_strcmp(tmp->content, ">>"))
			fd = open(tmp->next->content, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (fd < 0)
		{
			ft_printf("minishell: %s: %s\n",
										tmp->next->content, strerror(errno));
			g_stream.exit_status = 1;
			return (-1);
		}
		tmp = tmp->next->next;
	}
	return (fd);
}
