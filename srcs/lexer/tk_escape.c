/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:00:18 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/21 20:39:22 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*activate_backslashed(t_tokens *tk, t_lexer *lx)
{
	tk = create_new_token(tk, lx);
	lx->state = STATE_BACKSLASHED;
	return (tk);
}

void		backslashed_state(t_tokens *tk, t_lexer *lx)
{
	int type_plus_one;

	tk->type = BACKSLASHED;
	if (lx->line[lx->i] == ESCAPE)
		escape_in_general(tk, lx);
	else
		tk->data[lx->j++] = lx->line[lx->i++];
	if (lx->line[lx->i] == SINGLE_QUOTE || lx->line[lx->i] == DOUBLE_QUOTE)
	{
		if (lx->line[lx->i++] == SINGLE_QUOTE)
			lx->state = STATE_SINGLE_QUOTED;
		else
			lx->state = STATE_DOUBLE_QUOTED;
		return ;
	}
	type_plus_one = get_char_type(lx->line[lx->i + 1]);
	if (type_plus_one == TYPE_ESCAPE || type_plus_one == TYPE_SPACE ||
	type_plus_one == TYPE_DOLLAR || type_plus_one == TYPE_DOUBLE_QUOTE ||
	type_plus_one == TYPE_SINGLE_QUOTE)
	{
		if (type_plus_one != TYPE_DOLLAR)
			tk->data[lx->j++] = lx->line[lx->i];
		lx->state = STATE_GENERAL;
		return ;
	}
}
