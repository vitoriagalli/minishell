/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:45:12 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/08 00:33:27 by vscabell         ###   ########.fr       */
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

char	*join_path(char *env, char *path)
{
	char	*tmp;

	tmp = ft_strjoin(env, "/");
	tmp = ft_strjoin(tmp, path);
	return (tmp);
}

void	set_redirection(t_cmd *cmd)
{
	if (cmd->redirection == LESSER)
		dup2(cmd->fd_in, STDIN_FILENO);
	else
		dup2(cmd->fd_out, STDOUT_FILENO);
}

// void	set_pipe(t_cmd *cmd)
// {
// 	int	fd;

// 	pipe(cmd->pfd);

// }

int	launch_path(t_cmd *cmd)
{
	char	**env_path;
	char	*tmp;
	int		i;

	i = 0;
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		env_path = get_env_value("PATH");
		while (env_path[i])
		{
			tmp = join_path(env_path[i], cmd->cmd);
			execve(tmp, cmd->args, g_env);
			i++;
		}
		free(tmp);
		ft_putstr_fd(cmd->cmd, STDOUT_FILENO);
		ft_putendl_fd(": command not found", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	launch_full_path(t_cmd *cmd)
{
	char	**home_path;

	home_path = NULL;
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (*cmd->cmd == '~')
		{
			ft_memmove(&cmd->cmd[0], &cmd->cmd[1], ft_strlen(cmd->cmd));
			home_path = get_env_value("HOME");
			cmd->cmd = ft_strjoin_n_free(*home_path, cmd->cmd);
		}
		execve(cmd->cmd, cmd->args, g_env);
		ft_putstr_fd(cmd->cmd, STDOUT_FILENO);
		ft_putendl_fd(": command not found", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int		execute_single_command(t_cmd *cmd)
{
	builtin_funct	*f_buildin;
	int				child_status;

	cmd->pid = 0;
	child_status = 0;
	f_buildin = NULL;

	if (cmd->redirection)
		set_redirection(cmd);
	if (f_buildin = is_builldin(cmd->cmd))
		(*f_buildin)(cmd);
	else if (ft_strchr("./~", cmd->cmd[0]))
		launch_full_path(cmd);		// to improve
	else
		launch_path(cmd);

	waitpid(cmd->pid, &child_status, 0);
	if (WIFEXITED(child_status))


	// 	sh->status = WEXITSTATUS(child_status);
	// else if (WIFSIGNALED(status))
	// 	sh->status =  WTERMSIG(status);



	return (0);
}

int		execute(void)
{
	t_cmd		*tmp;
	int			fd[2];


	tmp = sh->cmd;
	while (tmp)
	{
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);

		execute_single_command(tmp);

		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);

		tmp = tmp->next;
	}


	// free_shell(); // segfault, VER!
}
