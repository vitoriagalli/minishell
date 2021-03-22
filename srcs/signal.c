/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vs-Rb <marvin@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:12:01 by user42            #+#    #+#             */
/*   Updated: 2021/03/22 16:05:24 by Vs-Rb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Ctrl+C - SIGINT
// Ctrl+\ - SIGQUIT

void	signal_handler_prompt(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("^C\n");
		g_msh.last_ret_cmd = 130;
		ft_bzero(g_msh.line, ft_strlen(g_msh.line));
        print_prompt();
	}
}

void	signal_handler_do_nothing(int sig)
{
	if (sig == SIGQUIT)
		sleep(0); // See with Vitoria
}

void	signal_handler_parent(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		g_msh.last_ret_cmd = 130;
	}
	if (signal == SIGQUIT)
	{
		ft_printf("Quit (core dumped)\n");
		g_msh.last_ret_cmd = 131;
	}
}

void	handle_signals(int caller, int pid)
{
	if (caller == ROOT)
	{
		if (signal(SIGINT, signal_handler_prompt) == SIG_ERR)
			exit_msh("signal", strerror(errno));
		if (signal(SIGQUIT, signal_handler_do_nothing) == SIG_ERR)
			exit_msh("signal", strerror(errno));
	}		
	else if (caller == FORK)
	{
		if (pid != 0)
		{
			if (signal(SIGINT, signal_handler_parent) == SIG_ERR)
				exit_msh("signal", strerror(errno));
			if (signal(SIGQUIT, signal_handler_parent) == SIG_ERR)
				exit_msh("signal", strerror(errno));
		}
	}
}