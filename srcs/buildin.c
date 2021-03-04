/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:16:54 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/03 21:50:29 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(t_cmd *cmd)
{
	bool	flag;
	int		i;

	flag = false;
	i = 1;
	if (cmd->args[i] && !ft_strcmp(cmd->args[i], "-n"))
	{
		flag = true;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int		ft_cd(t_cmd *cmd)
{
	if (chdir(cmd->args[1]) != 0)
		return (0);
	return (0);
}

int		ft_pwd(t_cmd *cmd)
{
	char	cwd[1024 + 1];

	(void)cmd;
	if (!(getcwd(cwd, 1024)))
		return (0);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}

int		ft_export(t_cmd *cmd)
{
	(void)cmd;
	return (0);
}

int		ft_unset(t_cmd *cmd)
{
	(void)cmd;
	return (0);
}

int		ft_env(t_cmd *cmd)
{
	(void)cmd;
	return (0);
}

int		ft_exit(t_cmd *cmd)
{
	(void)cmd;
	return (0);
}




// void	call_exec_path(t_cmd *cmd, t_exec *exec, t_minishell *msh, int fd_dup)
// {
// 	int i;
// 	char *tmp;

// 	i = 0;
// 	exec->child_pid = fork();
// 	if (exec->child_pid == 0)
// 	{
// 		dup2(exec->pipefds[fd_dup], fd_dup);
// 		if (cmd->redirection != 0)
// 			set_redirection(cmd, exec);
// 		else if (cmd->separator == PIPE)
// 			close(exec->pipefds[0]);
// 		if (is_buildin_cmd(cmd->cmd_name))
// 			call_exec_buildin(cmd, exec, msh);
//     	while (exec->path_cmd[i])
// 		{
// 			tmp = add_path_command(exec->path_cmd[i++], cmd->cmd_name);
// 			execve(tmp, cmd->args, __environ);
// 		}
// 		free(tmp);
// 		dup2(exec->save_stdout, STDOUT_FILENO);
// 		ft_printf("%s: command not found\n", cmd->cmd_name);
// 		exit(exit_status());
// 	}
// }
