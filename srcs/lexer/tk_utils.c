/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:00:02 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 10:24:58 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			size_token_list(t_tokens *lst)
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

void		add_end_token(t_msh *msh, t_tokens *head_tk, t_lexer *lx)
{
	t_tokens *current;

	if (!head_tk)
		return ;
	current = head_tk;
	while (current->next)
		current = current->next;
	if (!(current->next = malloc(sizeof(t_tokens))))
		exit_msh(msh, "malloc: ", strerror(errno));
	lx->i = 0;
	if (!(current->next->data = ft_strdup("newline")))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	current->next->type = 700;
	current->next->next = NULL;
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
		free(previous->next->data);
		free(previous->next);
		previous->next = NULL;
	}
	return (head_tk);
}

void		init_token(t_msh *msh, t_tokens *tk, t_lexer *lx)
{
	if (!(tk->data = malloc(sizeof(char) * (lx->size - lx->i) + 1)))
		exit_msh(msh, "malloc: ", strerror(errno));
	ft_bzero(tk->data, lx->size - lx->i + 1);
	tk->type = 700;
	tk->next = NULL;
}

t_tokens	*create_new_token(t_msh *msh, t_tokens *tk, t_lexer *lx)
{
	if (tk->data[0] != '\0')
	{
		tk->data[ft_strlen(tk->data)] = '\0';
		if (!(tk->next = malloc(sizeof(t_tokens))))
			exit_msh(msh, "malloc: ", strerror(errno));
		tk = tk->next;
		init_token(msh, tk, lx);
	}
	lx->i++;
	lx->state = STATE_GEN;
	return (tk);
}
