/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:00:02 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/21 20:35:13 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_char_type(char c)
{
	if (c == SINGLE_QUOTE)
		return (TYPE_SINGLE_QUOTE);
	else if (c == DOUBLE_QUOTE)
		return (TYPE_DOUBLE_QUOTE);
	else if (c == VERTICAL_BAR || c == SEMICOLON || c == GREAT || c == LESS)
		return (TYPE_OPERATOR);
	else if (c == SPACE || c == TAB || c == NEW_LINE)
		return (TYPE_SPACE);
	else if (c == DOLLAR)
		return (TYPE_DOLLAR);
	else if (c == ESCAPE)
		return (TYPE_ESCAPE);
	else
		return (TYPE_GENERAL);
}

void		init_token(t_tokens *tk, t_lexer *lx)
{
	tk->data = malloc(sizeof(char) * (lx->size - lx->i) + 1);
	ft_bzero(tk->data, lx->size - lx->i + 1);
	tk->eval = true;
	tk->type = 0;
	tk->next = NULL;
}

t_tokens	*create_new_token(t_tokens *tk, t_lexer *lx)
{
	int type;

	if (tk->data[0] != '\0')
	{
		type = get_char_type(lx->line[lx->i]);
		if (type == TYPE_SPACE)
		{
			if (lx->line[lx->i] == TAB)
				tk->data[lx->j] = SPACE;
			else
				tk->data[lx->j] = lx->line[lx->i];
		}
		tk->data[ft_strlen(tk->data)] = '\0';
		tk->next = malloc(sizeof(t_tokens));
		tk = tk->next;
		init_token(tk, lx);
	}
	lx->state = STATE_GENERAL;
	lx->j = 0;
	if (lx->line[lx->i] == DOLLAR)
		tk->data[lx->j++] = lx->line[lx->i];
	return (tk);
}
