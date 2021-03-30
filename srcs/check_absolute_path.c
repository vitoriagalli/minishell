/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_absolute_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:20:14 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 15:39:34 by romanbtt         ###   ########.fr       */
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

static char	*check_tild(t_msh *msh, char *cmd)
{
	char	**home_path;
	char	*tmp;

	home_path = get_env_value(msh, "HOME");
	if (!(tmp = ft_strjoin(home_path[0], cmd + 1)))
		exit_msh(msh, "strjoin: ", strerror(errno));
	ft_strdel(&cmd);
	if (!(cmd = ft_strdup(tmp)))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	ft_strdel(&tmp);
	ft_array_clear(home_path, ft_free);
	return (cmd);
}

char		*absolute_path(t_msh *msh, char *cmd, t_exec *exec)
{
	char	*tmp;

	if (cmd[0] == '~')
		cmd = check_tild(msh, cmd);
	if (!file_exists(cmd))
	{
		if (dup2(exec->save_stdout, 1) < 0)
			exit_msh(msh, "dup2: ", strerror(errno));
		ft_printf("minishell: %s: command not found\n", cmd);
		g_stream.exit_status = 127;
		ft_strdel(&cmd);
		return (NULL);
	}
	else if (is_directory(cmd))
	{
		if (dup2(exec->save_stdout, 1) < 0)
			exit_msh(msh, "dup2: ", strerror(errno));
		ft_printf("minishell: %s: Is a directory\n", cmd);
		g_stream.exit_status = 126;
		ft_strdel(&cmd);
		return (NULL);
	}
	if (!(tmp = ft_strdup(cmd)))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	return (tmp);
}
