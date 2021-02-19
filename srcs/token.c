/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 22:21:50 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/19 01:53:13 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_tkn_new(char *data)
{
	t_token	*elem;

	elem = malloc(sizeof(t_token));
	if (!elem)
		return (NULL);
	elem->data = data;
	elem->type = 0;
	elem->next = NULL;
	return (elem);
}

void	tkn_add_front(t_token **head, t_token *new)
{
	if (!new)
		return ;
	if (*head)
		new->next = *head;
	*head = new;
}

void tkn_add_back(t_token **head, t_token *new)
{

	t_token *tmp;

	tmp = *head;
	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	ft_tkn_size(t_token *head)
{
	int		count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}


// TEMPORARY FUNCTION

void	ft_tkn_print(t_token *head)
{
	int count;

	count = 0;
	while (head)
	{
		ft_printf("--- element %i ----\n", count);
		ft_printf("data: %s\n", head->data);
		ft_printf("type: %i\n", head->type);
		ft_printf("next: %p\n", head->next);
		head = head->next;
		count++;
	}

}

