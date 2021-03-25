/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_absolute_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:20:14 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 13:26:39 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool		file_exists(char *filepath)
{
	struct stat		buffer;

	return (stat(filepath, &buffer) == 0);
}

static bool	is_directory(char *filepath)
{
	struct stat		buffer;

	if (stat(filepath, &buffer) != 0)
		return (false);
	return (S_ISDIR(buffer.st_mode));
}

static char	*check_tild(char *cmd)
{
	char	**home_path;
	char	*tmp;

	home_path = get_env_value("HOME");
	if (!(tmp = ft_strjoin(home_path[0], cmd + 1)))
		exit_msh("strjoin: ", strerror(errno));
	ft_strdel(&cmd);
	if (!(cmd = ft_strdup(tmp)))
		exit_msh("ft_strdup: ", strerror(errno));
	ft_strdel(&tmp);
	ft_array_clear(home_path, ft_free);
	return (cmd);
}

char		*absolute_path(char *cmd)
{
	char	*tmp;

	if (cmd[0] == '~')
		cmd = check_tild(cmd);
	if (!file_exists(cmd))
	{
		ft_printf("minishell: %s: command not found\n", cmd);
		g_msh.last_ret_cmd = 127;
		ft_strdel(&cmd);
		return (NULL);
	}
	else if (is_directory(cmd))
	{
		ft_printf("minishell: %s: Is a directory\n", cmd);
		g_msh.last_ret_cmd = 126;
		ft_strdel(&cmd);
		return (NULL);
	}
	if (!(tmp = ft_strdup(cmd)))
		exit_msh("ft_strdup: ", strerror(errno));
	return (tmp);
}
