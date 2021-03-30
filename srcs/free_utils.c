/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:15:34 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 11:26:57 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void *elem)
{
	if (elem)
	{
		free(elem);
		elem = NULL;
	}
}

void	ft_array_clear(char **arr, void (*del)(void*))
{
	int		len;
	int		i;

	len = 0;
	while (arr[len])
		len++;
	i = 0;
	while (i < len)
		del(arr[i++]);
	del(arr);
}

void	free_history(t_msh *msh)
{
	t_history *node;

	while (msh->head_hist != NULL)
	{
		node = msh->head_hist;
		msh->head_hist = msh->head_hist->next;
		free(node->cmd_line);
		free(node);
	}
	msh->curr_hist = NULL;
}

void	ft_tknclear(t_tokens **lst, void (*del)(void*))
{
	t_tokens	*to_free;

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

void	ft_cmdclear(t_cmd **lst, void (*del)(void*))
{
	t_cmd	*to_free;

	to_free = *lst;
	if (!*lst || !lst || !del)
		return ;
	while (to_free)
	{
		*lst = to_free->next;
		ft_array_clear(to_free->args, ft_free);
		if (to_free->red_in)
			ft_lstclear(&to_free->red_in, ft_free);
		if (to_free->red_out)
			ft_lstclear(&to_free->red_out, ft_free);
		del(to_free->cmd_name);
		free(to_free);
		to_free = *lst;
	}
	*lst = NULL;
}
