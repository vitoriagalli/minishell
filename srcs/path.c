/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 00:41:48 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/11 23:41:40 by vscabell         ###   ########.fr       */
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
		store_value_and_name(&value, &name, i);
		if (!ft_strcmp(key, name))
			return (ft_split(value, ':'));
		i++;
	}
	return (NULL);
}

bool	file_exists(char *filepath)
 {
	struct stat		buffer;
	return (stat (filepath, &buffer) == 0);
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
	env_path = get_env_value("PATH");		// ver seg fault quando unset
	while (env_path[i])
	{
		tmp = join_path(env_path[i], cmd);
		if (file_exists(tmp))
			return (tmp);
		free(tmp);
		i++;
	}
	ft_putstr_fd(cmd, STDOUT_FILENO);
	ft_putendl_fd(": command not found", STDOUT_FILENO);
	return (NULL);
}
char	*absolute_path(char *cmd)
{
	char	**home_path;

	home_path = NULL;
	if (cmd[0] == '~')
	{
		ft_memmove(&cmd[0], &cmd[1], ft_strlen(cmd));
		home_path = get_env_value("HOME");
		cmd = ft_strjoin_n_free(*home_path, cmd);
		ft_array_clear(home_path, ft_free);
	}
	if (file_exists(cmd))
		return (cmd);
	ft_putstr_fd(cmd, STDOUT_FILENO);
	ft_putendl_fd(": command not found", STDOUT_FILENO);
	return (NULL);
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
