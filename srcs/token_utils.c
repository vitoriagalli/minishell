/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:20:53 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/02 20:55:04 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_tk_char(int c)
{
	if (c == PIPE ||
		c == SEMICOLON ||
		c == GREATER ||
		c == LESSER ||
		c == SPACE ||
		c == TAB )
		return (true);
	return (false);
}

int		is_quote_char(int c)
{
	if (c == SIMPLE_QUOTE ||
		c == DOUBLE_QUOTE)
		return (true);
	return (false);
}

// int		is_space_char(int c)
// {
// 	if (c == SPACE ||
// 		c == TAB)
// 		return (true);
// 	return (false);
// }

// int		is_job_char(int c)
// {
// 	if (c == PIPE ||
// 		c == SEMICOLON ||
// 		c == GREATER ||
// 		c == LESSER)
// 		return (true);
// 	return (false);
// }
