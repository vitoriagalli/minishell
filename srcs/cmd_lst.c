/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 02:21:34 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/08 00:15:07 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmd_new(void)
{
	t_cmd	*elem;

	elem = malloc(sizeof(t_cmd));
	if (!elem)
		return (NULL);
	elem->cmd = NULL;
	elem->args = NULL;
	// elem->file_in = NULL;
	// elem->file_out = NULL;
	elem->next = NULL;
	return (elem);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd *tmp;

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

void	ft_cmd_clear(t_cmd **lst, void (*del)(char*))
{
	t_cmd	*to_free;

	to_free = *lst;
	if (!*lst || !lst || !del)
		return ;
	while (to_free)
	{
		*lst = to_free->next;
		del(to_free->cmd);
		// del(to_free->file_in);
		// del(to_free->file_out);
		ft_array_clear(&to_free->args, ft_free);
		// del(to_free); // cmd é stack, ver se vai ser point
		to_free = *lst;
	}
	*lst = NULL;
}


/*
** temporary function
*/


void	ft_cmd_print(t_cmd *lst)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (lst)
	{
		ft_printf("-------- command %i ---------\n", count);
		ft_printf("cmd: %s\n", lst->cmd);
		// ft_printf("in: %s\n", lst->file_in);
		// ft_printf("out: %s\n", lst->file_out);
		ft_printf("red: %i\n", lst->redirection);
		ft_printf("sep: %i\n", lst->separator);
		while (lst->args[i])
		{
			ft_printf("arg %i: %s\n", i, lst->args[i]);
			i++;
		}
		i = 0;
		lst = lst->next;
		count++;
	}
}
