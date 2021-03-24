/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:44:23 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/24 15:55:55 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	ft_pwd(UNUSED t_cmd *cmd, t_exec *exec)
{
	char buf[PATH_MAX];

	if (exec->child_pid == 0)
	{
		if ((getcwd(buf, PATH_MAX)) == NULL)
		{
			ft_printf("minishell: pwd: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		ft_putendl_fd(buf, STDOUT_FILENO);
		free_after_fork();
		exit(EXIT_SUCCESS);
	}
}
