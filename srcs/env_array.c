/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 21:38:03 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/13 19:10:14 by vscabell         ###   ########.fr       */
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

char	**duplicate_array(char **buffer, int len_arr)
{
	char	**new_buffer;
	int		i;

	if (!buffer || !(*buffer))
		return (NULL);
	new_buffer = ft_calloc(len_arr + 1, sizeof(char *));
	i = 0;
	while (i < len_arr)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	return (new_buffer);
}

char	**reallocate_array(char **buffer, char *new_string)
{
	char	**new_buffer;
	int		len_arr;

	len_arr = 0;
	while (buffer[len_arr])
		len_arr++;
	new_buffer = duplicate_array(buffer, len_arr + 1);
	new_buffer[len_arr] = new_string;
	free(buffer);
	return (new_buffer);
}
