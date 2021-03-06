/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 21:38:03 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/06 03:52:44 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_global_env(void)
{
	int		len_arr;
	int		i;

	len_arr = 0;
	while (__environ[len_arr])
		len_arr++;
	g_env = ft_calloc(len_arr + 1, sizeof(char *));
	i = 0;
	while (i < len_arr)
	{
		g_env[i] = ft_strdup(__environ[i]);
		i++;
	}
}

char	**reallocate(char **buffer, int len_arr)
{
	char	**new_buffer;
	int		i;

	if (!buffer || !(*buffer))
		return NULL;
	new_buffer = ft_calloc(len_arr + 2, sizeof(char *));
	i = 0;
	while (i < len_arr)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (new_buffer);
}
