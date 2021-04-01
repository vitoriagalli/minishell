/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:12:01 by user42            #+#    #+#             */
/*   Updated: 2021/03/30 14:52:39 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_prompt(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("^C\n");
		g_stream.exit_status = 130;
		ft_bzero(g_stream.line, ft_strlen(g_stream.line));
		print_prompt();
	}
}

void	signal_handler_do_nothing(int sig)
{
	(void)sig;
	return ;
}

void	signal_handler_parent(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		g_stream.exit_status = 130;
	}
	if (signal == SIGQUIT)
	{
		ft_printf("Quit (core dumped)\n");
		g_stream.exit_status = 131;
	}
}

void	handle_signals(t_msh *msh, int caller, int pid)
{
	if (caller == ROOT)
	{
		if (signal(SIGINT, signal_handler_prompt) == SIG_ERR)
			exit_msh(msh, "signal: ", strerror(errno));
		if (signal(SIGQUIT, signal_handler_do_nothing) == SIG_ERR)
			exit_msh(msh, "signal: ", strerror(errno));
	}
	else if (caller == FORK)
	{
		if (pid != 0)
		{
			if (signal(SIGINT, signal_handler_parent) == SIG_ERR)
				exit_msh(msh, "signal: ", strerror(errno));
			if (signal(SIGQUIT, signal_handler_parent) == SIG_ERR)
				exit_msh(msh, "signal: ", strerror(errno));
		}
	}
}
