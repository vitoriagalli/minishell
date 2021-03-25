/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:17:05 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 02:33:21 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dispatch_check_function(t_cmd *cmd)
{
	char *ret;

	if (is_buildin_cmd(cmd->cmd_name))
	{
		if (!(ret = ft_strdup(cmd->cmd_name)))
			exit_msh("ft_strdup: ", strerror(errno));
	}
	else if (ft_strchr("./~", cmd->cmd_name[0]))
		ret = absolute_path(cmd->cmd_name);
	else
		ret = relative_path(cmd->cmd_name);
	return (ret);
}

bool		find_path(t_cmd *cmd)
{
	char	*ret;

	ret = dispatch_check_function(cmd);
	if (ret == NULL)
	{
		free(ret);
		if (!(cmd->cmd_name = ft_strdup("NULL")))
			exit_msh("ft_strdup: ", strerror(errno));
		return (false);
	}
	free(cmd->cmd_name);
	if (!(cmd->cmd_name = ft_strdup(ret)))
		exit_msh("ft_strdup: ", strerror(errno));
	free(ret);
	return (true);
}
