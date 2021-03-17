/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:46:30 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/10 16:50:10 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_arg(t_cmd *cmd)
{
	int ret;
	
	ret = ft_atoi(cmd->args[1]);
	ft_printf("exit\n");
	if (ret >= 0 && ret <= 255)
		exit(ret);
	else
		exit (ret % 256);
}

int		too_many_args(t_cmd *cmd, t_minishell *msh)
{
	if (cmd->args[2] != NULL)
	{
		ft_printf("minishell: exit: too many argument\n");
		msh->force_ret_buildin = true;
		msh->last_ret_cmd = 1;
		return (1);
	}
	return (0);
}

void	non_numerical_arg(t_cmd *cmd)
{
	int i;

	i = 0;
	if ((cmd->args[1][0] == '-' && !ft_isdigit(cmd->args[1][1])) ||
	(cmd->args[1][0] == '+' && !ft_isdigit(cmd->args[1][1])))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n",
		cmd->args[1]);
		exit(2);
	}
	while (cmd->args[1][i] != '\0')
	{
		if (!ft_isdigit(cmd->args[1][i++]) &&
		(cmd->args[1][0] != '-' && cmd->args[1][0] != '+'))
		{
			ft_printf("minishell: exit: %s: numeric argument required\n",
			cmd->args[1]);
			exit(2);
		}
	}
}

void	ft_exit(t_cmd *cmd, t_exec *exec, t_minishell *msh)
{
	if (exec->child_pid == 0)
		exit(EXIT_SUCCESS);
	if (cmd->separator == 0 || cmd->separator == SEPARATOR)
	{
		if (cmd->args[1] == NULL)
		{
			ft_printf("exit\n");
			exit(msh->last_ret_cmd);
		}
		non_numerical_arg(cmd);
		if (too_many_args(cmd, msh) == 1)
			return ;
		exit_with_arg(cmd);
	}
}