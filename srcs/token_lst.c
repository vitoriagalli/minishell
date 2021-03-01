/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 22:21:50 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/02 00:49:14 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_tkn_new(t_list *args, int sep)
{
	t_token	*elem;

	elem = malloc(sizeof(t_token));
	if (!elem)
		return (NULL);
	if (args)
		elem->cmd = ft_strdup(args->content);
	elem->args_lst = args;
	elem->sep = sep;
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
		del(to_free->cmd);
		free(to_free);
		to_free = *lst;
	}
	*lst = NULL;
}


/*
** temporary function
*/

void	ft_lst_print(t_list *lst)
{
	int count;

	count = 0;
	while (lst)
	{
		ft_printf("--- args %i ----\n", count);
		ft_printf("content: %s\n", lst->content);
		lst = lst->next;
		count++;
	}
}

void	ft_tkn_print(t_token *lst)
{
	int count;

	count = 0;
	while (lst)
	{
		ft_printf("-------- element %i ---------\n", count);
		ft_printf("cmd: %s\n", lst->cmd);
		ft_printf("type: %i\n", lst->sep);
		ft_printf("next: %p\n", lst->next);
			ft_printf("args: %p\n", lst->args_lst);
		ft_lst_print(lst->args_lst);
		lst = lst->next;
		count++;
	}
}


