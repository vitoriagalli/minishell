/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:40:58 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/22 23:46:58 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds()
{
	t_cmd *node;

	while (g_msh.cmds.head_cmd != NULL)
	{
		node = g_msh.cmds.head_cmd;
		g_msh.cmds.head_cmd = g_msh.cmds.head_cmd->next;
		free(node);
	}
	ft_bzero(&g_msh.cmds, sizeof(t_cmds));
}

int	exit_status()
{
	if (errno == EACCES)
		return(126);
	if (errno == ENOENT)
		return (127);
	else
		return (EXIT_FAILURE);
}

void	set_redirection(t_cmd *cmd, t_exec *exec)
{
	t_list	*tmp;
	int fd;

	tmp = cmd->redirection;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp(tmp->content, "<"))
		{
			if ((fd = open(tmp->next->content, O_RDONLY)) < 0)
				exit_msh("open : ", strerror(errno));
			if (dup2(fd, STDIN_FILENO) < 0)
				exit_msh("dup2 : ", strerror(errno));
		}
		if (!ft_strcmp(tmp->content, ">"))
		{
			if ((fd = open(tmp->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0)
				exit_msh("open : ", strerror(errno));
			if (dup2(fd, STDOUT_FILENO) < 0)
				exit_msh("dup2 : ", strerror(errno));
		}
		if (!ft_strcmp(tmp->content, ">>"))
		{
			if ((fd = open(tmp->next->content, O_WRONLY | O_CREAT | O_APPEND, 0664)) < 0)
				exit_msh("open : ", strerror(errno));
			if (dup2(fd, STDOUT_FILENO) < 0)
				exit_msh("dup2 : ", strerror(errno));
		}
		if (fd < 0)
		{
			if (!ft_strcmp(tmp->content, "<"))
				ft_printf("minishell: %s: %s\n", tmp->next->content, "No such file or directory");
			else
				ft_printf("minishell: %s: %s\n", tmp->next->content, strerror(errno));
			exit(exit_status());
		}
		tmp = tmp->next->next;
	}

}

void call_exec(t_cmd *cmd, t_exec *exec, int fd_dup)
{
	int i;

	i = 0;
	if ((exec->child_pid = fork()) < 0)
		exit_msh("fork : ", strerror(errno));
	handle_signals(FORK, exec->child_pid);
	if (exec->child_pid == 0)
	{
		if (dup2(exec->pipefds[fd_dup], fd_dup) < 0)
			exit_msh("dup2 : ", strerror(errno));
		if (cmd->redirection)
			set_redirection(cmd, exec);
		else if (cmd->separator == PIPE)
		{
			if (close(exec->pipefds[0]) < 0)
				exit_msh("close : ", strerror(errno));
		}
		if (is_buildin_cmd(cmd->cmd_name))
			call_exec_buildin(cmd, exec);
		else
			execve(cmd->cmd_name, cmd->args, g_msh.env);
		ft_printf("minishell: %s: %s\n", cmd->cmd_name, strerror(errno));
		if (dup2(exec->save_stdout, STDOUT_FILENO) < 0)
			exit_msh("dup2 : ", strerror(errno));
		exit(exit_status());
	}
}

void	execute_command_pipe(t_cmd *cmd, t_exec *exec)
{
	int i;
	char *tmp;

	i = 0;
	if (exec->pipe == true)
	{
		if (close(exec->pipefds[1]) < 0)
			exit_msh("close : ", strerror(errno));
		if (dup2(exec->pipefds[0], STDIN_FILENO) < 0)
			exit_msh("dup2 : ", strerror(errno));
	}
	if (pipe(exec->pipefds) < 0)
		exit_msh("pipe : ", strerror(errno));
	exec->pipe = true;
	call_exec(cmd, exec, 1);
	if (is_buildin_cmd(cmd->cmd_name))
		call_exec_buildin(cmd, exec);
}

void 	execute_command(t_cmd *cmd, t_exec *exec)
{
		int i;
		char *tmp;

		i = 0;
		if (exec->pipe == true)
		{
			if (dup2(exec->save_stdout, exec->pipefds[1]) < 0)
				exit_msh("dup2 : ", strerror(errno));
		}
		exec->pipe = false;
		call_exec(cmd, exec, 0);
		if (is_buildin_cmd(cmd->cmd_name))
			call_exec_buildin(cmd, exec);
}

void 	execution_commands()
{
	t_cmd *cmd;
	t_exec		exec;
	int			status;

	ft_bzero(&exec, sizeof(t_exec));
	if (exec.save_stdin = dup(STDIN_FILENO) < 0)
		exit_msh("dup : ", strerror(errno));
	if (exec.save_stdout = dup(STDOUT_FILENO) < 0)
		exit_msh("dup : ", strerror(errno));
	cmd = g_msh.cmds.head_cmd;
	while (cmd)
	{
		if (cmd->separator == PIPE)
			execute_command_pipe(cmd, &exec);
		else
			execute_command(cmd, &exec);
		if (waitpid(exec.child_pid, &status, 0) < 0)
			exit_msh("waitpid : ", strerror(errno));
		if (g_msh.force_ret_buildin == true)
			g_msh.force_ret_buildin = false;
		else if (WIFEXITED(status))
			g_msh.last_ret_cmd = WEXITSTATUS(status);
		cmd = cmd->next;
	}
	if (dup2(exec.save_stdin, 0) < 0)
		exit_msh("dup2 : ", strerror(errno));
	if (dup2(exec.save_stdout, 1) < 0)
		exit_msh("dup2 : ", strerror(errno));
}
