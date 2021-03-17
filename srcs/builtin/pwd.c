/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:44:23 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/04 09:44:32 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	ft_pwd(t_cmd *cmd, t_exec *exec, t_minishell *msh)
{
	char buf[1024];

	if (exec->child_pid == 0)
	{
		if ((getcwd(buf, 1024)) == NULL)
		{
			ft_printf("minishell: pwd: %s\n", strerror(errno));
			exit(exit_status());
		}
	}
}