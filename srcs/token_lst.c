/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 22:21:50 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/27 23:47:30 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_tkn_new(char *data, int type)
{
	t_token	*elem;

	elem = malloc(sizeof(t_token));
	if (!elem)
		return (NULL);
	elem->data = data;
	elem->type = type;
	elem->next = NULL;
	return (elem);
}

void	tkn_add_back(t_token **lst, t_token *new)
{
	t_token *tmp;

	tmp = *lst;
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int		ft_tkn_size(t_token *lst)
{
	int		count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void	ft_free(char *elem)
{
	if (elem)
		free(elem);
}

void	ft_tkn_clear(t_token **lst, void (*del)(char*))
{
	t_token	*to_free;

	to_free = *lst;
	if (!*lst || !lst || !del)
		return ;
	while (to_free)
	{
		*lst = to_free->next;
		del(to_free->data);
		free(to_free);
		to_free = *lst;
	}
	*lst = NULL;
}

/*
** temporary function
*/

void	ft_tkn_print(t_token *lst)
{
	int count;

	count = 0;
	while (lst)
	{
		ft_printf("--- element %i ----\n", count);
		ft_printf("data: %s\n", lst->data);
		ft_printf("type: %i\n", lst->type);
		ft_printf("next: %p\n", lst->next);
		lst = lst->next;
		count++;
	}
}
