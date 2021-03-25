/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:04:04 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 12:09:52 by romanbtt         ###   ########.fr       */
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

static void	print_error_redirection(t_list *tmp)
{
	if (!ft_strcmp(tmp->content, "<"))
		ft_printf("minishell: %s: %s\n", tmp->next->content,
			"No such file or directory");
	else
		ft_printf("minishell: %s: %s\n", tmp->next->content, strerror(errno));
	exit(exit_status());
}

void		set_redirection(t_cmd *cmd)
{
	t_list	*tmp;
	int		fd;

	tmp = cmd->redirection;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp(tmp->content, "<"))
		{
			fd = open(tmp->next->content, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		if (!ft_strcmp(tmp->content, ">"))
		{
			fd = open(tmp->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			dup2(fd, STDOUT_FILENO);
		}
		if (!ft_strcmp(tmp->content, ">>"))
		{
			fd = open(tmp->next->content, O_WRONLY | O_CREAT | O_APPEND, 0664);
			dup2(fd, STDOUT_FILENO);
		}
		if (fd < 0)
			print_error_redirection(tmp);
		tmp = tmp->next->next;
	}
}
