/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:45:12 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/07 17:54:55 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

builtin_funct	*is_builldin(char *cmd)
{
	static char				*rel_path[7] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit"};
	static char				*abs_path[7] = {"/bin/echo", "/bin/cd", "/bin/pwd",
		"/bin/export", "/bin/unset", "/bin/env", "/bin/exit"};
	static builtin_funct	f_call[7] = {ft_echo, ft_cd, ft_pwd, ft_export,
		ft_unset, ft_env, ft_exit};
	int						i;

	i = 0;
	while (i < 7)
	{
		if (!(ft_strcmp(cmd, rel_path[i])) || !(ft_strcmp(cmd, abs_path[i])))
			return (&f_call[i]);
		i++;
	}
	return (NULL);
}

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
	int	fd;

	if (cmd->redirection == LESSER)
	{
		fd = open(cmd->file_in, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	else if (cmd->redirection == GREATER)
	{
		fd = open(cmd->file_out, O_WRONLY | O_CREAT, 0664);
		dup2(fd, STDOUT_FILENO);
	}
	else if (cmd->redirection == GGREATER)
	{
		fd = open(cmd->file_out, O_WRONLY | O_CREAT | O_APPEND, 0664);
		dup2(fd, STDOUT_FILENO);
	}
}

int	launch_path(t_cmd *cmd, int *pid)
{
	char	**env_path;
	char	*tmp;
	int		i;

	i = 0;
	*pid = fork();
	if (*pid == 0)
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
	// else
	// 	wait(0);
	return (0);
}

int	launch_full_path(t_cmd *cmd, int *pid)
{
	char	**home_path;

	home_path = NULL;
	*pid = fork();
	if (*pid == 0)
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
	// else
	// 	wait(0);
	return (0);
}

int		execute_single_command(t_cmd *cmd)
{
	// t_exec			exec;
	builtin_funct	*f_buildin;
	int				fd[2];
	int				child_status;
	int				pid;

	pid = 0;
	child_status = 0;
	f_buildin = NULL;
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (cmd->redirection)
		set_redirection(cmd);
	if (f_buildin = is_builldin(cmd->cmd))
		(*f_buildin)(cmd);
	else if (ft_strchr("./~", cmd->cmd[0]))
		launch_full_path(cmd, &pid);		// to improve
	else
		launch_path(cmd, &pid);
	dup2(fd[0], 0);
	dup2(fd[1], 1);


	waitpid(pid, &child_status, 0);
	if (WIFEXITED(child_status))
		sh->status = WEXITSTATUS(child_status);
	// else if (WIFSIGNALED(status))
	// 	sh->status =  WTERMSIG(status);



	return (0);
}

int		execute(void)
{
	t_cmd		*tmp;
	// int			fd[2];


	// fd[0] = dup(STDIN_FILENO);
	// fd[1] = dup(STDOUT_FILENO);
	tmp = sh->cmd;
	while (tmp)
	{
		execute_single_command(tmp);
		tmp = tmp->next;
	}
	// dup2(fd[0], 0);
	// dup2(fd[1], 1);


	// free_shell(); // se usar da segfault, VER!
}
