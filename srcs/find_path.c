/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:17:05 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 12:30:27 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dispatch_check_function(t_msh *msh, t_cmd *cmd, t_exec *exec)
{
	char *ret;

	if (is_buildin_cmd(cmd->cmd_name))
	{
		if (!(ret = ft_strdup(cmd->cmd_name)))
			exit_msh(msh, "ft_strdup: ", strerror(errno));
	}
	else if (ft_strchr("./~", cmd->cmd_name[0]))
		ret = absolute_path(msh, cmd->cmd_name, exec);
	else
		ret = relative_path(msh, cmd->cmd_name, exec);
	return (ret);
}

bool		find_path(t_msh *msh, t_cmd *cmd, t_exec *exec)
{
	char	*ret;

	ret = dispatch_check_function(msh, cmd, exec);
	if (ret == NULL)
	{
		free(ret);
		if (!(cmd->cmd_name = ft_strdup("NULL")))
			exit_msh(msh, "ft_strdup: ", strerror(errno));
		return (false);
	}
	ft_strdel(&cmd->cmd_name);
	if (!(cmd->cmd_name = ft_strdup(ret)))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	ft_strdel(&ret);
	return (true);
}
