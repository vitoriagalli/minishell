/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:16:25 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 10:53:24 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_exec_buildin(t_msh *msh, t_cmd *cmd)
{
	int					i;
	int					len;
	const char			inbuild[8][7] = {"echo", "cd", "pwd", "export",
	"unset", "env", "exit", "\0"};
	const t_inbuild		func_inbuild[7] = {ft_echo, ft_cd, ft_pwd, ft_export,
		ft_unset, ft_env, ft_exit};

	i = 0;
	len = ft_strlen(cmd->cmd_name);
	while (ft_strncmp(cmd->cmd_name, inbuild[i], len + 1))
		i++;
	(*func_inbuild[i])(msh, cmd);
}

bool	is_buildin_cmd(char *cmd)
{
	int			i;
	int			len;
	const char	inbuild[8][7] = {"echo", "cd", "pwd", "export",
	"unset", "env", "exit", "\0"};

	i = 0;
	len = ft_strlen(cmd);
	while (inbuild[i][0] != '\0')
	{
		if (!(ft_strncmp(inbuild[i++], cmd, len + 1)))
			return (true);
	}
	return (false);
}
