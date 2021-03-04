/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:45:12 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/04 01:16:40 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// funcao repetida em dois lugares no código
// REFATORAR
char	**get_env_path()
{
	t_env	*env;
	t_env	*tmp;

	env = put_env_into_lst(__environ);
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp("PATH", tmp->name))
		{
			return(ft_split(tmp->value, ':'));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*join_path(char *env, char *path)
{
	char	*tmp;

	tmp = ft_strjoin(env, "/");
	tmp = ft_strjoin(tmp, path);

	return (tmp);
}

int	launch_relative_path(t_exec *exec)
{
	char	**env_path;
	char	*tmp;
	int		pid;
	int		i;

	i = 0;
	env_path = get_env_path();
	pid = fork();
	if (pid == 0)
	{
		while (env_path[i])
		{
			tmp = join_path(env_path[i], exec->path);
			execve(tmp, exec->argv, __environ);
			i++;
		}
	}
	else
		wait(0);
	return (0);
}

int	launch_absolute_path(t_exec *exec)
{
	char	*tmp;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		execve(exec->path, exec->argv, __environ);
	}
	else
		wait(0);
	return (0);
}


builtin_funct	*is_builldin(char *cmd)
{
	static char				*f_name[7] = {"echo",
										"cd",
										"pwd",
										"export",
										"unset",
										"env",
										"exit"};
	static builtin_funct	f_call[7] = {ft_echo,
										ft_cd,
										ft_pwd,
										ft_export,
										ft_unset,
										ft_env,
										ft_exit};
	int						i;

	i = 0;
	while (i < 7)
	{
		if (!(ft_strcmp(cmd, f_name[i])))
			return (&f_call[i]);
		i++;
	}
	return (NULL);
}

int		execute_single_command(t_shell *sh, t_cmd *cmd)
{
	t_exec	exec;
	builtin_funct *f_buildin;

	f_buildin = NULL;

	exec.argv = cmd->args;
	exec.path = cmd->cmd;

	if (f_buildin = is_builldin(cmd->cmd))
		(*f_buildin)(cmd);
	else if (ft_strchr("./~", cmd->cmd[0]))
		launch_absolute_path(&exec);
	else
		launch_relative_path(&exec);
	return (0);
}

// implementar tipos de separadores
int		execute(t_shell *sh)
{
	t_cmd *tmp;

	tmp = sh->cmd;
	while (tmp)
	{
		execute_single_command(sh, tmp);
		tmp = tmp->next;
	}
}
