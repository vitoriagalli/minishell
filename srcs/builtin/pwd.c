/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:44:23 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/21 19:25:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	ft_pwd(t_cmd *cmd, t_exec *exec)
{
	char buf[1024 + 1];

	if (exec->child_pid == 0)
	{
		if ((getcwd(buf, 1024)) == NULL)
		{
			ft_printf("minishell: pwd: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		ft_putendl_fd(buf, STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}
