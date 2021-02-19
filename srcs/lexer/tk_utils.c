/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:00:02 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/19 15:29:12 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token(t_tokens *tk, t_lexer *lx)
{
	tk->data = malloc(sizeof(char) * (lx->size - lx->i) + 1);
	ft_bzero(tk->data, lx->size - lx->i + 1);
	tk->type = 0;
	tk->next = NULL;
}

t_tokens	*create_new_token(t_tokens *tk, t_lexer *lx)
{
	if (tk->data[0] != '\0')
	{
		tk->data[ft_strlen(tk->data)] = '\0';
		tk->next = malloc(sizeof(t_tokens));
		tk = tk->next;
		init_token(tk, lx);
	}
	lx->j = 0;
	return (tk);
}