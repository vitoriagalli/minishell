/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:16:54 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/03 13:05:47 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(t_cmd  *cmd)
{
	// bool	flag;
	// t_list	*tmp;

	// flag = false;
	// tmp = cmd->args_lst->next;
	// if (tmp && !ft_strcmp(tmp->content, "-n"))
	// {
	// 	flag = true;
	// 	tmp = tmp->next;
	// }
	// while (tmp)
	// {
	// 	ft_putstr_fd(tmp->content, STDOUT_FILENO);
	// 	if (tmp->next)
	// 		ft_putstr_fd(" ", STDOUT_FILENO);
	// 	tmp = tmp->next;
	// }
	// if (!flag)
	// 	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int		ft_cd(t_cmd  *cmd)
{
	if (chdir(cmd->args[1]) != 0)
		return (0);
	return (0);
}

int		ft_pwd(t_cmd  *cmd)
{
	char	cwd[1024 + 1];

	(void)cmd;
	if (!(getcwd(cwd, 1024)))
		return (0);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}

int		ft_export(t_cmd  *cmd)
{
	(void)cmd;
	return (0);
}

int		ft_unset(t_cmd  *cmd)
{
	(void)cmd;
	return (0);
}

int		ft_env(t_cmd  *cmd)
{
	(void)cmd;
	return (0);
}

int		ft_exit(t_cmd  *cmd)
{
	(void)cmd;
	return (0);
}
