/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vs-Rb <marvin@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:47:08 by Vs / Rb           #+#    #+#             */
/*   Updated: 2021/03/22 16:28:24 by Vs-Rb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char *elem)
{
	if (elem)
	{
		free(elem);
		elem = NULL;
	}
}

void	ft_array_clear(char **arr, void (*del)(char *))
{
	int		len;
	int		i;

	len = 0;
	while (arr[len])
		len++;
	i = 0;
	while (i < len)
		del(arr[i++]);
	del(arr);
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

	if (!(tmp = ft_strjoin(env, "/")))
		exit_msh("strjoin", strerror(errno));
	if (!(tmp = ft_strjoin(tmp, path)))
		exit_msh("strjoin", strerror(errno));
	return (tmp);
}

char *relative_path(char *cmd)
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
	ft_printf("minishell: %s: command not found\n", cmd);
	g_msh.last_ret_cmd = 127;
	return (NULL);
}

char	*absolute_path(char *cmd)
{
	char	**home_path;
	char	*tmp;

	home_path = NULL;
	if (cmd[0] == '~')
	{
		home_path = get_env_value("HOME");
		if (!(tmp = ft_strjoin(home_path[0], cmd)))
			exit_msh("strjoin", strerror(errno));
		free (cmd);
		cmd = tmp;
		ft_array_clear(home_path, ft_free);
	}
	if (!file_exists(cmd))
	{
		ft_printf("minishell: %s: command not found\n", cmd);
		g_msh.last_ret_cmd = 127;
		return (NULL);
	}
	else if (is_directory(cmd))
	{
		ft_printf("minishell: %s: Is a directory\n", cmd);
		g_msh.last_ret_cmd = 126;
		return (NULL);
	}
	return (cmd);
}

bool	find_path()
{
	t_cmd *cmd;
	char *ret;

	cmd = g_msh.cmds.head_cmd;
	while (cmd)
	{
		if (is_buildin_cmd(cmd->cmd_name))
		{
			if (!(ret = ft_strdup(cmd->cmd_name)))
				exit_msh("strdup", strerror(errno));
		}
		else if (ft_strchr("./~", cmd->cmd_name[0]))
			ret = absolute_path(cmd->cmd_name);
		else
			ret = relative_path(cmd->cmd_name);
		if (ret == NULL)
			return (false);
		if (!(cmd->cmd_name = ft_strdup(ret)))
			exit_msh("strdup", strerror(errno));
		cmd = cmd->next;
	}
	return (true);
}
