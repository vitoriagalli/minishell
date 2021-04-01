/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:46:30 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 16:04:26 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_with_arg(t_msh *msh, t_cmd *cmd)
{
	int ret;

	ret = ft_atoi(cmd->args[1]);
	ft_printf("exit\n");
	if (ret >= 0 && ret <= 255)
	{
		g_stream.exit_status = ret;
		exit_program(msh);
	}
	else
	{
		g_stream.exit_status = ret % 256;
		exit_program(msh);
	}
}

static int	too_many_args(t_cmd *cmd)
{
	if (cmd->args[2] != NULL)
	{
		ft_printf("exit\nminishell: exit: too many arguments\n");
		g_stream.exit_status = EXIT_FAILURE;
		return (1);
	}
	return (0);
}

static void	non_numerical_arg(t_msh *msh, t_cmd *cmd)
{
	int i;

	i = 0;
	if ((cmd->args[1][0] == '-' && !ft_isdigit(cmd->args[1][1])) ||
	(cmd->args[1][0] == '+' && !ft_isdigit(cmd->args[1][1])))
	{
		ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
		cmd->args[1]);
		g_stream.exit_status = 2;
		exit_program(msh);
	}
	while (cmd->args[1][i] != '\0')
	{
		if (!ft_isdigit(cmd->args[1][i++]) &&
		(cmd->args[1][0] != '-' && cmd->args[1][0] != '+'))
		{
			ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
			cmd->args[1]);
			g_stream.exit_status = 2;
			exit_program(msh);
		}
	}
}

void		ft_exit(t_msh *msh, t_cmd *cmd)
{
	if (cmd->separator == 0 || cmd->separator == SEPARATOR)
	{
		if (cmd->args[1] == NULL)
		{
			ft_printf("exit\n");
			exit_program(msh);
		}
		non_numerical_arg(msh, cmd);
		if (too_many_args(cmd) == 1)
			return ;
		exit_with_arg(msh, cmd);
	}
}
