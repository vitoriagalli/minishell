/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:40:58 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/27 00:05:19 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status()
{
	if (errno == EACCES)
		return(126);
	if (errno == ENOENT)
		return (127);
	else
		return (EXIT_FAILURE);
}

//void	look_non_env_path(t_cmd *cmd, char *path_home)
//{
//	char *temp;
//	
//	if (cmd->cmd_name[0] == '~')
//	{
//		temp = ft_substr(cmd->cmd_name, 1, ft_strlen(cmd->cmd_name));
//		cmd->cmd_name = ft_strjoin(path_home, temp);
//		free(temp);
//	}	
//	execve(cmd->cmd_name, cmd->args, __environ);
//	ft_printf("minishell: %s: %s\n",cmd->cmd_name, strerror(errno));
//	exit(exit_status());
//}
//
//void	look_env_path(t_cmd *cmd, char **path_cmd)
//{
//	char *temp;
//	int i;
//
//	i = 0;
//	while (path_cmd[i])
//	{
//		temp = ft_strjoin("/", cmd->cmd_name);
//		temp = ft_strjoin(path_cmd[i], temp);
//		execve(temp, cmd->args, __environ);
//		free(temp);
//		i++;
//	}
//	ft_printf("%s: command not found\n", cmd->cmd_name);
//	exit(exit_status());
//}
//
//void	execute_command(t_minishell *msh, t_cmd *head_cmd)
//{
//	pid_t child_pid;
//	t_cmd *cmd;
//	int status;
//	
//	cmd = head_cmd;
//	if ((child_pid = fork()) < 0)
//	{
//		ft_printf("minishell: fork(): %s\n", strerror(errno));
//		return ;
//	}
//	if (child_pid == 0)
//	{
//		if (strchr("./~", head_cmd->cmd_name[0]))
//			look_non_env_path(cmd, msh->path_home);
//		else
//			look_env_path(cmd, msh->path_cmd);
//	}
//	else
//	{
//		if ((waitpid(child_pid, &status, 0)) < 0)
//		{
//			ft_printf("minishell: waitpid(): %s\n", strerror(errno));
//			return ;
//		}
//	}	 
//	if (WIFEXITED(status))
//  		msh->last_ret_cmd = WEXITSTATUS(status);
//	else if (WIFSIGNALED(status))
//  		msh->last_ret_cmd =  WTERMSIG(status);
//}


char	write_into_file()
{
	
}

char	*add_path_command(char *path, char *cmd)
{
	char *tmp;

	tmp = ft_strjoin("/", cmd);
	tmp = ft_strjoin(path, tmp);
	return (tmp);
}

void	set_redirection(t_cmd *cmd, t_exec *exec)
{
	if (cmd->redirection == INPUT)
	{
		exec->pipefds[0] = open(cmd->file_in, O_RDONLY);
		dup2(exec->pipefds[0], STDIN_FILENO);
	}
}

void	call_exec_rel_abs(t_cmd *cmd, t_exec *exec, int fd_dup)
{
	int i;
	char *tmp;

	i = 0;
	exec->child_pid = fork();
	if (exec->child_pid == 0)
	{	
		dup2(exec->pipefds[fd_dup], fd_dup);
		if (cmd->redirection != 0)
			set_redirection(cmd, exec);
		else if (cmd->separator == PIPE)
			close(exec->pipefds[0]);
    	if (cmd->cmd_name[0] == '~')
		{
			tmp = ft_substr(cmd->cmd_name, 1, ft_strlen(cmd->cmd_name));
			cmd->cmd_name = ft_strjoin(exec->path_home, tmp);
			free(tmp);
		}
		execve(cmd->cmd_name, cmd->args, __environ);
		ft_printf("minishell: %s: %s\n",cmd->cmd_name, strerror(errno));
		exit(exit_status());
	}
}

void	call_exec_path(t_cmd *cmd, t_exec *exec, int fd_dup)
{
	int i;
	char *tmp;

	i = 0;
	exec->child_pid = fork();
	if (exec->child_pid == 0)
	{
		dup2(exec->pipefds[fd_dup], fd_dup);
		if (cmd->redirection != 0)
			set_redirection(cmd, exec);
		else if (cmd->separator == PIPE)
			close(exec->pipefds[0]);
    	while (exec->path_cmd[i])
		{
			tmp = add_path_command(exec->path_cmd[i++], cmd->cmd_name);
			execve(tmp, cmd->args, __environ);
		}
		free(tmp);
		ft_printf("%s: command not found\n", cmd->cmd_name);
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
		close(exec->pipefds[1]);
		dup2(exec->pipefds[0], STDIN_FILENO);
	}
	pipe(exec->pipefds);
	exec->pipe = true;
	if (strchr("./~", cmd->cmd_name[0]))
		call_exec_rel_abs(cmd, exec, 1);
	else
		call_exec_path(cmd, exec, 1);
}

void 	execute_command(t_cmd *cmd, t_exec *exec)
{
		int i;
		char *tmp;

		i = 0;
		if (exec->pipe == true)
			dup2(exec->save_stdout, exec->pipefds[1]);
		exec->pipe = false;
		if (ft_strchr("./~", cmd->cmd_name[0]))
			call_exec_rel_abs(cmd, exec, 0);
		else
			call_exec_path(cmd, exec, 0);
}

void 	exec_cmd_v2(t_minishell *msh, t_cmd *head_cmd)
{
	t_cmd *cmd;
	t_exec		exec;
	int			status;

	exec = (t_exec) {0, 0, 0, 0, 0, 0, msh->path_cmd, msh->path_home};
	exec.save_stdin = dup(STDIN_FILENO);
	exec.save_stdout = dup(STDOUT_FILENO);
	cmd = msh->cmds->head_cmd;
	while (cmd)
	{
		if (cmd->separator == PIPE)
			execute_command_pipe(cmd, &exec);
		else
			execute_command(cmd, &exec);
		waitpid(exec.child_pid, &status, 0);
		if (WIFEXITED(status))
			msh->last_ret_cmd = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
  			msh->last_ret_cmd =  WTERMSIG(status);
		cmd = cmd->next;
	}
	dup2(exec.save_stdin, 0);
	dup2(exec.save_stdout, 1);
}