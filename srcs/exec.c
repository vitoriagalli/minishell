/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:45:12 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/17 03:02:08 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipe(t_cmd *cmd, t_exec *exec)
{
	if (cmd->separator == PIPE)
	{
		if (exec->pipe == true)
		{
			close(exec->pipefd[1]);
			dup2(exec->pipefd[0], STDIN_FILENO);
		}
		pipe(exec->pipefd);
		exec->pipe = true;
	}
	else
	{
		if (exec->pipe  == true)
		{
			dup2(exec->fdout, exec->pipefd[1]);
			exec->pipe = false;
		}
	}
}

int		execute_command(t_cmd *cmd, t_exec *exec)
{
	builtin_funct	*f_buildin;

	f_buildin = NULL;
	if (f_buildin = is_builldin(cmd->cmd))
		(*f_buildin)(cmd);
	else
	{
		exec->pid = fork();
		signal(SIGINT, handle_signal2);
		signal(SIGQUIT, handle_signal2);
		if (exec->pid == 0)
		{
			if (cmd->separator == PIPE)
			{
				dup2(exec->pipefd[1], 1);
				close(exec->pipefd[0]);
			}
			else
				dup2(exec->pipefd[0], 0);
			execve(cmd->cmd, cmd->args, g_env);
		}
	}
	return (0);
}

int		execute(void)
{
	t_exec		exec;
	t_cmd		*cmd;

	exec.fdin = dup(STDIN_FILENO);
	exec.fdout = dup(STDOUT_FILENO);
	cmd = sh->cmd;
	while (cmd)
	{
		if (cmd->cmd)
		{
			set_redirection(cmd);
			set_pipe(cmd, &exec);
			execute_command(cmd, &exec);
			waitpid(exec.pid, &exec.status, 0);
			if (WIFEXITED(exec.status))
				sh->status = WEXITSTATUS(exec.status);
		}
		cmd = cmd->next;
	}
	dup2(exec.fdin, STDIN_FILENO);
	dup2(exec.fdout, STDOUT_FILENO);
	close(exec.fdin);
	close(exec.fdout);
}
