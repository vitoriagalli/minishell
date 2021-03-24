/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 23:39:56 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/24 16:50:54 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_msh(char *function, char *str_err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(function, STDERR_FILENO);
	ft_putstr_fd(str_err, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit_program();
}
