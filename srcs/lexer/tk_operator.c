/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:01:16 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 10:31:27 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	precise_type_operator(t_tokens *tk)
{
	if (tk->data[0] == VERTICAL_BAR)
		tk->type = PIPE;
	else if (tk->data[0] == SEMICOLON)
		tk->type = SEPARATOR;
	else if (tk->data[0] == LESS)
		tk->type = INPUT;
	else if (tk->data[0] == GREAT)
		tk->type = OUT_OVERWRITE;
}

t_tokens	*put_in_token_operator(t_msh *msh, t_tokens *tk, t_lexer *lx)
{
	if (tk->data[0] != '\0')
	{
		tk = create_new_token(msh, tk, lx);
		lx->i--;
	}
	if (lx->line[lx->i] == GREAT && lx->line[lx->i + 1] == GREAT)
	{
		tk->data[ft_strlen(tk->data)] = lx->line[lx->i++];
		tk->data[ft_strlen(tk->data)] = lx->line[lx->i];
		tk->type = OUT_APPEND;
	}
	else
	{
		tk->data[ft_strlen(tk->data)] = lx->line[lx->i];
		precise_type_operator(tk);
	}
	tk = create_new_token(msh, tk, lx);
	return (tk);
}
