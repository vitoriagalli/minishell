/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:01:16 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/21 20:37:25 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*put_in_token_operator(t_tokens *tk, t_lexer *lx)
{
	if (tk->data[0] != '\0')
		tk = create_new_token(tk, lx);
	if (lx->line[lx->i] == GREAT && lx->line[lx->i + 1] == GREAT)
	{
		tk->data[lx->j++] = lx->line[lx->i++];
		tk->data[lx->j] = lx->line[lx->i];
	}
	else
		tk->data[lx->j] = lx->line[lx->i];
	tk->type = OPERATOR;
	tk = create_new_token(tk, lx);
	return (tk);
}
