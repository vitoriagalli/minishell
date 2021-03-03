/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:45:12 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/03 13:01:22 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch(t_exec *exec)
{
	if (!fork())
	{
		execve(exec->path, exec->argv, __environ);
		exit(0);
	}
	else
		wait(0);
	return (0);
}

int	launch_process(t_cmd *cmd)
{
	t_exec	exec;

	exec.argv = cmd->args;
	exec.path = ft_strjoin("/bin/", cmd->cmd);

	return (launch(&exec));
}

int		execute_single_command(t_shell *sh, t_cmd *cmd)
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
		if (!(ft_strcmp(cmd->cmd, f_name[i])))
			return ((*f_call[i])(cmd));
		i++;
	}
	return (launch_process(cmd)); // to implement
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
