/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:45:12 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/14 03:56:35 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ZONA! organizar esse paranauê
void	set_redirection(t_cmd *cmd)
{
	t_list	*tmp;
	int		fd;

	tmp = cmd->red;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->next &&
			!ft_strcmp(tmp->content, ">") && !ft_strcmp(tmp->next->content, ">"))
		{
			if (!tmp->next->next)
			{
				ft_printf("bash: syntax error near unexpected token `newline'\n");
				return ;
			}
			fd = open(tmp->next->next->content, O_WRONLY | O_CREAT | O_APPEND, 0664);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			tmp = tmp->next->next->next;
		}
		else if (!ft_strcmp(tmp->content, ">"))
		{
			if (!tmp->next)
			{
				ft_printf("bash: syntax error near unexpected token `newline'\n");
				return ;
			}
			fd = open(tmp->next->content, O_WRONLY | O_CREAT, 0664);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			tmp = tmp->next->next;
		}
		else if (!ft_strcmp(tmp->content, "<"))
		{
			if (!tmp->next)
			{
				ft_printf("bash: syntax error near unexpected token `newline'\n");
				return ;
			}
			fd = open(tmp->next->content, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
			tmp = tmp->next->next;
		}
	}

}
