/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:05:16 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/31 12:29:59 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		set_input(t_msh *msh, t_cmd *cmd, t_exec *exec)
{
	static bool	comes_from_pipe;

	if (cmd->red_in)
		if ((exec->fdin = set_input_red(msh, cmd, exec)) < 0)
			return (-1);
	if (comes_from_pipe == true || cmd->red_in)
	{
		if (dup2(exec->fdin, 0) < 0)
			exit_msh(msh, "dup2: ", strerror(errno));
		if (close(exec->fdin) < 0)
			exit_msh(msh, "close: ", strerror(errno));
	}
	if (cmd->separator == PIPE)
		comes_from_pipe = true;
	else
		comes_from_pipe = false;
	return (0);
}

int		set_output(t_msh *msh, t_cmd *cmd, t_exec *exec)
{
	if (cmd->separator == PIPE)
	{
		pipe(exec->pipefds);
		exec->fdout = exec->pipefds[1];
		exec->fdin = exec->pipefds[0];
	}
	if (cmd->red_out)
	{
		if ((exec->fdout = set_output_red(msh, cmd, exec)) < 0)
			return (-1);
	}
	if (cmd->separator != PIPE && !cmd->red_out)
	{
		if (dup2(exec->save_stdout, 1) < 0)
			exit_msh(msh, "dup2: ", strerror(errno));
	}
	else
	{
		if (dup2(exec->fdout, 1) < 0)
			exit_msh(msh, "dup2: ", strerror(errno));
		if (close(exec->fdout) < 0)
			exit_msh(msh, "close: ", strerror(errno));
	}
	return (0);
}

void	call_command(t_msh *msh, t_cmd *cmd, t_exec *exec)
{
	int		status;

	if (is_buildin_cmd(cmd->cmd_name))
		call_exec_buildin(msh, cmd);
	else
	{
		if ((exec->child_pid = fork()) < 0)
			exit_msh(msh, "fork: ", strerror(errno));
		handle_signals(msh, FORK, exec->child_pid);
		if (exec->child_pid == 0)
		{
			execve(cmd->cmd_name, cmd->args, msh->env);
			ft_printf("minishell: %s: %s\n", cmd->cmd_name, strerror(errno));
			exit(exit_status());
		}
		waitpid(exec->child_pid, &status, 0);
		if (WIFEXITED(status))
			g_stream.exit_status = WEXITSTATUS(status);
	}
}

void	exec_commands_loop(t_msh *msh, t_exec *exec)
{
	t_cmd	*cmd;

	cmd = msh->cmds.head_cmd;
	while (cmd)
	{
		if (set_input(msh, cmd, exec) < 0)
		{
			if ((exec->fdin = dup(exec->save_stdin)) < 0)
				exit_msh(msh, "dup: ", strerror(errno));
			while (cmd && cmd->separator == PIPE)
				cmd = cmd->next;
		}
		else
		{
			if (set_output(msh, cmd, exec) >= 0)
				if (cmd->cmd_name && find_path(msh, cmd, exec))
					call_command(msh, cmd, exec);
		}
		cmd = cmd->next;
	}
}

void	execution_cmds(t_msh *msh)
{
	t_exec	exec;

	ft_bzero(&exec, sizeof(t_exec));
	if ((exec.save_stdin = dup(STDIN_FILENO)) < 0)
		exit_msh(msh, "dup: ", strerror(errno));
	if ((exec.save_stdout = dup(STDOUT_FILENO)) < 0)
		exit_msh(msh, "dup: ", strerror(errno));
	exec.fdin = dup(STDIN_FILENO);
	exec_commands_loop(msh, &exec);
	if (dup2(exec.save_stdin, 0) < 0)
		exit_msh(msh, "dup2: ", strerror(errno));
	if (close(exec.save_stdin) < 0)
		exit_msh(msh, "close: ", strerror(errno));
	if (dup2(exec.save_stdout, 1) < 0)
		exit_msh(msh, "dup2: ", strerror(errno));
	if (close(exec.save_stdout) < 0)
		exit_msh(msh, "close: ", strerror(errno));
	ft_cmdclear(&msh->cmds.head_cmd, ft_free);
}
