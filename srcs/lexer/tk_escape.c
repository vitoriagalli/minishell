/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vs-Rb <marvin@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:00:18 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/22 13:07:18 by Vs-Rb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_escape_in_general(t_tokens *tk, t_lexer *lx)
{
	tk->data[ft_strlen(tk->data)] = lx->line[++lx->i];
	lx->i++;
	tk->type = WORD;
}

void		escape_in_double_quote(t_tokens *tk, t_lexer *lx)
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