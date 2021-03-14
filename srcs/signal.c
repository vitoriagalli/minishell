/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 21:54:51 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/14 23:03:34 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("$ ", 1); // ver codicional que vai mostrar o prompt
		free_shell();
	}
	else if (sig == SIGQUIT)
	{
		ft_printf("exit\n");
		free_shell();
	}
}
