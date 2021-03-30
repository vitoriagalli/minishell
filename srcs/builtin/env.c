/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:45:59 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 11:55:39 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_msh *msh, t_cmd *cmd)
{
	int	i;

	(void)cmd;
	i = 0;
	g_stream.exit_status = EXIT_SUCCESS;
	while (msh->env[i])
		ft_putendl_fd(msh->env[i++], STDOUT_FILENO);
}
