/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_quit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:39:03 by user42            #+#    #+#             */
/*   Updated: 2021/03/22 00:59:36 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_program()
{
	ft_array_clear(g_msh.env, ft_free);

	// TO DO
	// if (g_msh.rd_line)
	// 	free(g_msh.rd_line);
	// free(g_msh.save);
	// ft_lstclear(&g_msh.head_tk, ft_free);


	exit(g_msh.last_ret_cmd);
}
