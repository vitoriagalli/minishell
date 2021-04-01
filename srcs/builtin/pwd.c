/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:44:23 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 11:55:07 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_msh *msh, t_cmd *cmd)
{
	char buf[PATH_MAX];

	(void)cmd;
	(void)msh;
	g_stream.exit_status = EXIT_SUCCESS;
	if ((getcwd(buf, PATH_MAX)) == NULL)
	{
		ft_printf("minishell: pwd: %s\n", strerror(errno));
		g_stream.exit_status = EXIT_FAILURE;
		return ;
	}
	ft_putendl_fd(buf, STDOUT_FILENO);
}
