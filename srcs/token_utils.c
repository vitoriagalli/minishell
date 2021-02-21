/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:20:53 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/21 21:21:27 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_tk_char(int c)
{
	if (c == CHAR_PIPE ||
		c == CHAR_SEMICOLON ||
		c == CHAR_ESCAPE ||
		c == CHAR_GREATER ||
		c == CHAR_LESSER ||
		c == CHAR_SPACE ||
		c == CHAR_TAB ||
		c == CHAR_SIMPLE_QUOTE ||
		c == CHAR_DOUBLE_QUOTE)
		return TRUE;
	return FALSE;
}

int		is_quote_char(int c)
{
	if (c == CHAR_SIMPLE_QUOTE ||
		c == CHAR_DOUBLE_QUOTE)
		return TRUE;
	return FALSE;
}

int		is_space_char(int c)
{
	if (c == CHAR_SPACE ||
		c == CHAR_TAB)
		return TRUE;
	return FALSE;
}

int		is_job_char(int c)
{
	if (c == CHAR_PIPE ||
		c == CHAR_SEMICOLON ||
		c == CHAR_ESCAPE ||
		c == CHAR_GREATER ||
		c == CHAR_LESSER)
		return TRUE;
	return FALSE;
}
