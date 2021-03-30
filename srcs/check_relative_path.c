/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_relative_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:21:08 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 15:48:21 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_path(t_msh *msh, char *env, char *path)
{
	char	*tmp1;
	char	*tmp2;

	if (!(tmp1 = ft_strjoin(env, "/")))
		exit_msh(msh, "strjoin: ", strerror(errno));
	if (!(tmp2 = ft_strjoin(tmp1, path)))
		exit_msh(msh, "strjoin: ", strerror(errno));
	free(tmp1);
	return (tmp2);
}

static void	print_error(t_msh *msh, char *cmd, t_exec *exec)
{
	if (dup2(exec->save_stdout, 1) < 0)
		exit_msh(msh, "dup2: ", strerror(errno));
	ft_printf("minishell: %s: command not found\n", cmd);
	g_stream.exit_status = 127;
}

char		*relative_path(t_msh *msh, char *cmd, t_exec *exec)
{
	char	**env_path;
	char	*tmp;
	int		i;

	i = 0;
	env_path = get_env_value(msh, "PATH");
	if (env_path)
	{
		while (env_path[i])
		{
			tmp = join_path(msh, env_path[i++], cmd);
			if (file_exists(tmp))
			{
				ft_array_clear(env_path, ft_free);
				return (tmp);
			}
			free(tmp);
		}
	}
	if (env_path)
		ft_array_clear(env_path, ft_free);
	print_error(msh, cmd, exec);
	ft_strdel(&cmd);
	return (NULL);
}
