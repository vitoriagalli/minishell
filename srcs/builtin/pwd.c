/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:44:23 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/17 19:52:13 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	ft_pwd(t_cmd *cmd, t_exec *exec)
{
	char buf[1024 + 1];

	if (exec->child_pid == 0)
	{
		if ((getcwd(buf, 1024)) == NULL)
			ft_printf("minishell: pwd: %s\n", strerror(errno));
		else
			ft_putendl_fd(buf, STDOUT_FILENO);
		exit(exit_status());
	}
}
