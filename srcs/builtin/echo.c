/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:44:48 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 15:40:39 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_last(char *arg, int no_newline, int remainder)
{
	if (arg && no_newline == 1)
	{
		remainder += ft_strlen(arg);
		ft_printf("%s", arg);
	}
	else if (!arg && no_newline == 1)
		ft_printf("");
	else if (arg && (no_newline == 0 || no_newline == 2))
	{
		remainder = 0;
		ft_printf("%s\n", arg);
	}
	else if (!arg && (no_newline == 0 || no_newline == 2))
	{
		remainder = 0;
		ft_printf("\n");
	}
	return (remainder);
}

static int	handle_flag_no_newline(char *args)
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

void		ft_echo(t_msh *msh, t_cmd *cmd)
{
	int i;
	int no_newline;

	msh->remainder_line = 0;
	no_newline = 2;
	i = 1;
	g_stream.exit_status = EXIT_SUCCESS;
	while (cmd->args[i] && cmd->args[i][0] == '-')
		no_newline = handle_flag_no_newline(cmd->args[i++]);
	if (no_newline == 0)
		i--;
	while (cmd->args[i])
	{
		msh->remainder_line += ft_strlen(cmd->args[i]);
		if (!cmd->args[i + 1])
			ft_printf("%s", cmd->args[i++]);
		else
			ft_printf("%s ", cmd->args[i++]);
	}
	msh->remainder_line = print_last(cmd->args[i], no_newline,
		msh->remainder_line);
}
