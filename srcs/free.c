/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:23:57 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/07 16:49:50 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char *elem)
{
	if (elem)
	{
		free(elem);
		elem = NULL;
	}
}

void	ft_array_clear(char **arr, void (*del)(char *))
{
	int		len;
	int		i;

	len = 0;
	while (arr[len])
		len++;
	i = 0;
	while (i < len)
		del(arr[i++]);
}

void	free_shell(void)
{
	if (sh->cmd)
		ft_cmd_clear(&sh->cmd, ft_free);
	if (sh->tk)
		ft_tkn_clear(&sh->tk, ft_free);
}
