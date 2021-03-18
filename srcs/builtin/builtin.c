/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:16:25 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/17 19:50:22 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_exec_buildin(t_cmd *cmd, t_exec *exec)
{
	int i;
	int len;
	static t_inbuild func_inbuild[7] = {ft_echo, ft_cd, ft_pwd, ft_export,
		ft_unset, ft_env, ft_exit};
	char **inbuild;

	i = 0;
	len = ft_strlen(cmd->cmd_name);
	inbuild = ft_split("echo:cd:pwd:export:unset:env:exit", ':');
	while (ft_strncmp(cmd->cmd_name, inbuild[i], len + 1))
		i++;
	(*func_inbuild[i])(cmd, exec);
}

bool	is_buildin_cmd(char *cmd)
{
	char **inbuild;
	int i;
	int len;

	i = 0;
	len = ft_strlen(cmd);
	inbuild = ft_split("echo:cd:pwd:export:unset:env:exit", ':');
	while (inbuild[i])
	{
		if (!(ft_strncmp(inbuild[i++], cmd, len + 1)))
			return (true);
	}
	return (false);
}