/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:44:02 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/17 19:50:37 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_cmd *cmd, t_exec *exec)
{
	char *tmp;

	if (exec->child_pid == 0)
		exit(EXIT_SUCCESS);
	if (cmd->separator == 0 || cmd->separator == SEPARATOR)
	{
		if (cmd->args[1][0] == '~')
		{
			tmp = ft_substr(cmd->args[1], 1, ft_strlen(cmd->args[1]));
			tmp = ft_strjoin(g_msh.path_home, tmp);
		}
		else if (cmd->args[1][0] != '.' && cmd->args[1][0] != '/')
			tmp = ft_strjoin("./", cmd->args[1]);
		else
			tmp = ft_strdup(cmd->args[1]);
		if ((chdir(tmp)) < 0)
		{
			if (cmd->args[1][0] == '~')
				ft_printf("minishell: cd: %s: %s\n",tmp, strerror(errno));
			else
				ft_printf("minishell: cd: %s: %s\n",cmd->args[1], strerror(errno));
			g_msh.force_ret_buildin = true;
			g_msh.last_ret_cmd = 1;
		}
		free(tmp);
	}	
}