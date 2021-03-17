/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 21:54:51 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/17 03:02:32 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		ft_printf("$ ");
		signal(SIGINT, handle_signal);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\n", 1);
		ft_printf("$ ");
		signal(SIGQUIT, handle_signal);
	}
}

void			handle_signal2(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, handle_signal2);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\n", 1);
		signal(SIGQUIT, handle_signal2);
	}
}
