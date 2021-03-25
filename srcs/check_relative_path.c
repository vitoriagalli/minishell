/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_relative_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:21:08 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/24 20:34:25 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_path(char *env, char *path)
{
	char	*tmp1;
	char	*tmp2;

	if (!(tmp1 = ft_strjoin(env, "/")))
		exit_msh("strjoin: ", strerror(errno));
	if (!(tmp2 = ft_strjoin(tmp1, path)))
		exit_msh("strjoin: ", strerror(errno));
	free(tmp1);
	return (tmp2);
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
			{
				ft_array_clear(env_path, ft_free);
				return (tmp);
			}
			free(tmp);
			i++;
		}
	}
	if (env_path)
		ft_array_clear(env_path, ft_free);
	ft_printf("minishell: %s: command not found\n", cmd);
	g_msh.last_ret_cmd = 127;
	ft_strdel(&cmd);
	return (NULL);
}