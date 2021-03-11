/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:45:12 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/11 03:01:59 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			tmpfd[2];

void	set_redirection(t_cmd *cmd)
{
	if (cmd->redirection == LESSER)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	else
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

int		execute_single_command(t_cmd *cmd)
{
	builtin_funct	*f_buildin;

	f_buildin = NULL;
	if (f_buildin = is_builldin(cmd->cmd))
		(*f_buildin)(cmd);
	else
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
			execve(cmd->cmd, cmd->args, g_env);

	}
	return (0);
}

int		execute(void)
{
	int			child_status;
	t_cmd		*cmd;

	tmpfd[0] = dup(STDIN_FILENO);
	tmpfd[1] = dup(STDOUT_FILENO);

	child_status = 0;
	cmd = sh->cmd;

	while (cmd)
	{
		set_redirection(cmd);
		if (cmd->cmd)
		{
			execute_single_command(cmd);
			waitpid(cmd->pid, &child_status, 0);
			if (WIFEXITED(child_status))
				sh->status = WEXITSTATUS(child_status);
			else if (WIFSIGNALED(child_status))
				sh->status =  WTERMSIG(child_status);
		}
		cmd = cmd->next;
	}

	dup2(tmpfd[0], STDIN_FILENO);
	dup2(tmpfd[1], STDOUT_FILENO);
	close(tmpfd[0]);
	close(tmpfd[1]);

}
