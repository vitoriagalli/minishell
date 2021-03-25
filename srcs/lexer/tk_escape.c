/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:00:18 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 14:57:58 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_escape_in_general(t_tokens *tk, t_lexer *lx)
{
	tk->data[ft_strlen(tk->data)] = lx->line[++lx->i];
	lx->i++;
	tk->type = WORD;
}

void	escape_in_double_quote(t_tokens *tk, t_lexer *lx)
{
	if (lx->line[lx->i + 1] == ESCAPE || lx->line[lx->i + 1] == DOUBLE_QUOTE ||
	lx->line[lx->i + 1] == DOLLAR)
	{
		tk->data[ft_strlen(tk->data)] = lx->line[++lx->i];
		lx->i++;
	}
	else
		tk->data[ft_strlen(tk->data)] = lx->line[lx->i++];
}
