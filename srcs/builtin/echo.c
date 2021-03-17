/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:44:48 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/07 13:48:06 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool handle_flag_no_newline(char *args)
{
	int i;

	i = 1;
	while (args[i] != '\0')
	{
		if (args[i++] != 'n')
			return (false);
	}
	return (true);
}

void	ft_echo(t_cmd *cmd, t_exec *exec, t_minishell *msh)
{
	int i;
	bool no_newline;

	no_newline = false;
	if (exec->child_pid == 0)
	{
		i = 1;
		while (cmd->args[i] && cmd->args[i][0] == '-')
			no_newline = handle_flag_no_newline(cmd->args[i++]);
		if (no_newline == false && cmd->args[i - 1][0] == '-')
			i--;
		while (cmd->args[i + 1])
			ft_printf("%s ", cmd->args[i++]);
		if (cmd->args[i] && no_newline == true)
			ft_printf("%s", cmd->args[i]);
		else if (!cmd->args[i] && no_newline == true)
			ft_printf("");
		else if (cmd->args[i] && no_newline == false)
			ft_printf("%s\n", cmd->args[i]);
		else if (!cmd->args[i] && no_newline == false)
			ft_printf("\n");
		exit(EXIT_SUCCESS);
	}
}