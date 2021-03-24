/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_general.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:02:49 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/24 15:55:51 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		put_in_token_word(t_tokens *tk, t_lexer *lx)
{
	if (lx->line[lx->i] == DOLLAR)
		evaluate_dollar(tk, lx);
	else
		tk->data[ft_strlen(tk->data)] = lx->line[lx->i++];
	tk->type = WORD;
}

t_tokens	*general_state(t_tokens *tk, t_lexer *lx)
{
	lx->type = get_char_type(lx->line[lx->i]);
	if (lx->type == TYPE_SINGLE_QUOTE)
		activate_quoted_state(tk, lx, STATE_SINGLE_QUOTED);
	else if (lx->type == TYPE_DOUBLE_QUOTE)
		activate_quoted_state(tk, lx, STATE_DOUBLE_QUOTED);
	else if (lx->type == TYPE_OPERATOR)
		tk = put_in_token_operator(tk, lx);
	else if (lx->type == TYPE_SPACE)
		tk = create_new_token(tk, lx);
	else if (lx->type == TYPE_ESCAPE)
		handle_escape_in_general(tk, lx);
	else
		put_in_token_word(tk, lx);
	return (tk);
}