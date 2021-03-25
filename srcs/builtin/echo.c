/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:44:48 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/24 20:01:31 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int handle_flag_no_newline(char *args)
{
	int i;

	i = 1;
	while (args[i] != '\0')
	{
		if (args[i++] != 'n')
			return (0);
	}
	return (1);
}

void	ft_echo(t_cmd *cmd, t_exec *exec)
{
	int i;
	int no_newline;

	no_newline = 2;
	if (exec->child_pid == 0)
	{
		i = 1;
		while (cmd->args[i] && cmd->args[i][0] == '-')
			no_newline = handle_flag_no_newline(cmd->args[i++]);
		if (no_newline == 0)
			i--;
		while (cmd->args[i])
		{
			if (!cmd->args[i + 1])
				ft_printf("%s", cmd->args[i++]);
			else
				ft_printf("%s ", cmd->args[i++]);
		}	
		if (cmd->args[i] && no_newline == 1)
			ft_printf("%s", cmd->args[i]);
		else if (!cmd->args[i] && no_newline == 1)
			ft_printf("");
		else if (cmd->args[i] && (no_newline == 0 || no_newline == 2))
			ft_printf("%s\n", cmd->args[i]);
		else if (!cmd->args[i] && (no_newline == 0 || no_newline == 2))
			ft_printf("\n");
		free_after_fork();
		exit(EXIT_SUCCESS);
	}
}