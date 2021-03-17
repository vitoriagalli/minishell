/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:00:02 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/24 14:16:46 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		size_token_list(t_tokens *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = (*lst).next;
	}
	return (i);
}

void	add_end_token(t_tokens *head_tk, t_lexer *lx)
{
	t_tokens *current;

	if (!head_tk)
		return ;
	current = head_tk;
	while (current->next)
		current = current->next;
	current->next = malloc(sizeof(t_tokens));
	lx->i = 0;
	init_token(current->next, lx);
	current->next->data = ft_strdup("newline");
}

t_tokens	*remove_last_empty_node(t_tokens *head_tk)
{
	t_tokens *previous;
	
	if (!head_tk)
		return (NULL);
	if (!head_tk->next)
		return (head_tk);
	previous = head_tk;
	while (previous->next->next)
		previous = previous->next;
	if (!previous->next->data[0])
	{
		free(previous->next);
		previous->next = NULL;
	}
	return (head_tk);

}

int			get_char_type(char c)
{
	if (c == SINGLE_QUOTE)
		return (TYPE_SINGLE_QUOTE);
	else if (c == DOUBLE_QUOTE)
		return (TYPE_DOUBLE_QUOTE);
	else if (c == VERTICAL_BAR || c == SEMICOLON || c == GREAT || c == LESS)
		return (TYPE_OPERATOR);
	else if (c == SPACE || c == TAB || c == '\0')
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
	tk->type = 700;
	tk->next = NULL;
}

t_tokens	*create_new_token(t_tokens *tk, t_lexer *lx)
{
	int type;

	if (tk->data[0] != '\0')
	{
		tk->data[ft_strlen(tk->data)] = '\0';
		tk->next = malloc(sizeof(t_tokens));
		tk = tk->next;
		init_token(tk, lx);
	}
	lx->i++;
	lx->state = STATE_GENERAL;
	return (tk);
}
