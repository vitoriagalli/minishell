/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:40:58 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/21 19:20:25 by user42           ###   ########.fr       */
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

//char	*add_path_command(char *path, char *cmd)
//{
//	char *tmp;
//
//	tmp = ft_strjoin("/", cmd);
//	tmp = ft_strjoin(path, tmp);
//	return (tmp);
//}

void	set_redirection(t_cmd *cmd, t_exec *exec)
{
	t_list	*tmp;
	int fd;

	tmp = cmd->redirection;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp(tmp->content, "<"))
		{
			fd = open(tmp->next->content, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		if (!ft_strcmp(tmp->content, ">"))
		{
			fd = open(tmp->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			dup2(fd, STDOUT_FILENO);
		}
		if (!ft_strcmp(tmp->content, ">>"))
		{
			fd = open(tmp->next->content, O_WRONLY | O_CREAT | O_APPEND, 0664);
			dup2(fd, STDOUT_FILENO);
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
	exec->child_pid = fork();
	handle_signals(FORK, exec->child_pid);
	if (exec->child_pid == 0)
	{
		dup2(exec->pipefds[fd_dup], fd_dup);
		// if (cmd->red_in != 0 || cmd->red_out != 0)
		if (cmd->redirection)
			set_redirection(cmd, exec);
		else if (cmd->separator == PIPE)
			close(exec->pipefds[0]);
		if (is_buildin_cmd(cmd->cmd_name))
			call_exec_buildin(cmd, exec);
		else
			execve(cmd->cmd_name, cmd->args, g_msh.env);
		ft_printf("minishell: %s: %s\n", cmd->cmd_name, strerror(errno));
		dup2(exec->save_stdout, STDOUT_FILENO);
		exit(exit_status());
	}
}

//void	call_exec_rel_abs(t_cmd *cmd, t_exec *exec, int fd_dup)
//{
//	int i;
//	char *tmp;
//
//	i = 0;
//	exec->child_pid = fork();
//	if (exec->child_pid == 0)
//	{
//		dup2(exec->pipefds[fd_dup], fd_dup);
//		if (cmd->red_in != 0 || cmd->red_out != 0)
//			set_redirection(cmd, exec);
//		else if (cmd->separator == PIPE)
//			close(exec->pipefds[0]);
//    	if (cmd->cmd_name[0] == '~')
//		{
//			tmp = ft_substr(cmd->cmd_name, 1, ft_strlen(cmd->cmd_name));
//			cmd->cmd_name = ft_strjoin(exec->path_home, tmp);
//			free(tmp);
//		}
//		execve(cmd->cmd_name, cmd->args, __environ);
//		dup2(exec->save_stdout, STDOUT_FILENO);
//		ft_printf("minishell: %s: %s\n",cmd->cmd_name, strerror(errno));
//		exit(exit_status());
//	}
//}

//void	call_exec_path(t_cmd *cmd, t_exec *exec, int fd_dup)
//{
//	int i;
//	char *tmp;
//
//	i = 0;
//	exec->child_pid = fork();
//	if (exec->child_pid == 0)
//	{
//		dup2(exec->pipefds[fd_dup], fd_dup);
//		if (cmd->red_in != 0 || cmd->red_out != 0)
//			set_redirection(cmd, exec);
//		else if (cmd->separator == PIPE)
//			close(exec->pipefds[0]);
//		if (is_buildin_cmd(cmd->cmd_name))
//			call_exec_buildin(cmd, exec);
//    	while (exec->path_cmd[i])
//		{
//			tmp = add_path_command(exec->path_cmd[i++], cmd->cmd_name);
//			execve(tmp, cmd->args, __environ);
//		}
//		free(tmp);
//		dup2(exec->save_stdout, STDOUT_FILENO);
//		ft_printf("%s: command not found\n", cmd->cmd_name);
//		// free all
//		exit(exit_status());
//	}
//}

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
	//if (strchr("./~", cmd->cmd_name[0]))
	//	call_exec_rel_abs(cmd, exec, 1);
	//else
	//
	call_exec(cmd, exec, 1);
	if (is_buildin_cmd(cmd->cmd_name))
		call_exec_buildin(cmd, exec);
	//}
}

void 	execute_command(t_cmd *cmd, t_exec *exec)
{
		int i;
		char *tmp;

		i = 0;
		if (exec->pipe == true)
			dup2(exec->save_stdout, exec->pipefds[1]);
		exec->pipe = false;
		//if (ft_strchr("./~", cmd->cmd_name[0]))
		//	call_exec_rel_abs(cmd, exec, 0);
		//else
		//{
		call_exec(cmd, exec, 0);
		if (is_buildin_cmd(cmd->cmd_name))
			call_exec_buildin(cmd, exec);
		//}
}

void 	execution_commands()
{
	t_cmd *cmd;
	t_exec		exec;
	int			status;

	exec = (t_exec) {0, 0, 0, 0, 0, 0, g_msh.path_cmd, g_msh.path_home};
	exec.save_stdin = dup(STDIN_FILENO);
	exec.save_stdout = dup(STDOUT_FILENO);
	cmd = g_msh.cmds->head_cmd;
	while (cmd)
	{
		if (cmd->separator == PIPE)
			execute_command_pipe(cmd, &exec);
		else
			execute_command(cmd, &exec);
		waitpid(exec.child_pid, &status, 0);
		if (g_msh.force_ret_buildin == true)
			g_msh.force_ret_buildin = false;
		else if (WIFEXITED(status))
			g_msh.last_ret_cmd = WEXITSTATUS(status);
		// else if (WIFSIGNALED(status))
		// 	g_msh.last_ret_cmd = WTERMSIG(status);		// nao esta retornando o status esperado
		cmd = cmd->next;
	}
	dup2(exec.save_stdin, 0);
	dup2(exec.save_stdout, 1);
}
