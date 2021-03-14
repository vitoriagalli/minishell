/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 00:41:48 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/14 19:07:39 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env_value(char *key)
{
	char	*name;
	char	*value;
	int		i;

	name = NULL;
	value = NULL;
	i = 0;
	while (g_env[i])
	{
		store_key_and_value(&value, &name, g_env[i]);
		if (!ft_strcmp(key, name))
			return (ft_split(value, ':'));
		i++;
	}
	return (NULL);
}

bool	file_exists(char *filepath)
{
	struct stat		buffer;

	return (stat(filepath, &buffer) == 0);
}

bool	is_directory(char *filepath)
{
	struct stat		buffer;

	if (stat(filepath, &buffer) != 0)
		return (false);
	return (S_ISDIR(buffer.st_mode));
}

char	*join_path(char *env, char *path)
{
	char	*tmp;

	tmp = ft_strjoin(env, "/");
	tmp = ft_strjoin(tmp, path);
	return (tmp);
}

char	*relative_path(char *cmd)
{
	char	**env_path;
	char	*tmp;
	int		i;

	i = 0;
	env_path = get_env_value("PATH");
	if (env_path)
	{
		while (env_path[i])
		{
			tmp = join_path(env_path[i], cmd);
			if (file_exists(tmp))
				return (tmp);
			free(tmp);
			i++;
		}
	}
	ft_printf("bash: %s: command not found\n", cmd);
	return (NULL);
}

char	*absolute_path(char *cmd)
{
	char	**home_path;

	home_path = NULL;
	if (cmd[0] == '~')
	{
		home_path = get_env_value("HOME");
		cmd = ft_strjoin(home_path[0], &cmd[1]);
		ft_array_clear(home_path, ft_free);
	}
	if (!file_exists(cmd))
	{
		ft_printf("bash: %s: command not found\n", cmd);
		return (NULL);
	}
	else if (is_directory(cmd))
	{
		ft_printf("bash: %s: Is a directory\n", cmd);
		return (NULL);
	}
	return (cmd);
}

char	*find_path(char *cmd)
{
	builtin_funct	*f_buildin;

	f_buildin = NULL;
	if (f_buildin = is_builldin(cmd))
		return (cmd);
	if (ft_strchr("./~", cmd[0]))
		return (absolute_path(cmd));
	else
		return (relative_path(cmd));
}
