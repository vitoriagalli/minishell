/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_general.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:02:49 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/21 20:38:44 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		escape_in_general(t_tokens *tk, t_lexer *lx)
{
	while (lx->line[lx->i] == ESCAPE)
	{
		if (lx->line[lx->i + 1] == ESCAPE ||
		lx->line[lx->i + 1] == DOUBLE_QUOTE)
			tk->data[lx->j++] = lx->line[++lx->i];
		else if (lx->line[lx->i + 1] == DOLLAR)
		{
			tk->data[lx->j++] = lx->line[++lx->i];
			tk->eval = false;
		}
		else
			tk->data[lx->j++] = lx->line[++lx->i];
		lx->i++;
	}
}

void		put_in_token_word(t_tokens *tk, t_lexer *lx)
{
	tk->data[lx->j++] = lx->line[lx->i];
	tk->type = WORD;
}

t_tokens	*general_state(t_tokens *tk, t_lexer *lx)
{
	if (lx->type == TYPE_SINGLE_QUOTE)
		tk = activate_quoted_state(tk, lx, STATE_SINGLE_QUOTED);
	else if (lx->type == TYPE_DOUBLE_QUOTE)
		tk = activate_quoted_state(tk, lx, STATE_DOUBLE_QUOTED);
	else if (lx->type == TYPE_OPERATOR)
		tk = put_in_token_operator(tk, lx);
	else if (lx->type == TYPE_SPACE || lx->type == TYPE_DOLLAR && lx->j > 0)
		tk = create_new_token(tk, lx);
	else if (lx->type == TYPE_ESCAPE)
		tk = activate_backslashed(tk, lx);
	else
		put_in_token_word(tk, lx);
	return (tk);
}
