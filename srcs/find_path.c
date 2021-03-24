/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:17:05 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/24 16:44:44 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dispatch_check_function(t_cmd *cmd)
{
	char *ret;

	if (is_buildin_cmd(cmd->cmd_name))
	{
		if (!(ret = ft_strdup(cmd->cmd_name)))
			exit_msh("strdup", strerror(errno));
	}
	else if (ft_strchr("./~", cmd->cmd_name[0]))
		ret = absolute_path(cmd->cmd_name);
	else
		ret = relative_path(cmd->cmd_name);
	return (ret);
}

bool		find_path(void)
{
	t_cmd	*cmd;
	char	*ret;

	cmd = g_msh.cmds.head_cmd;
	while (cmd)
	{
		ret = dispatch_check_function(cmd);
		if (ret == NULL)
		{
			free(ret);
			cmd->cmd_name = ft_strdup("NULL");
			return (false);
		}
		free(cmd->cmd_name);
		if (!(cmd->cmd_name = ft_strdup(ret)))
			exit_msh("strdup", strerror(errno));
		free(ret);
		cmd = cmd->next;
	}
	return (true);
}
