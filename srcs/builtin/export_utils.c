/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:54:54 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 11:02:31 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**duplicate_array(t_msh *msh, char **buffer, int len_arr)
{
	char	**new_buffer;
	int		i;

	if (!buffer || !(*buffer))
		return (NULL);
	if (!(new_buffer = ft_calloc(len_arr + 1, sizeof(char *))))
		exit_msh(msh, "ft_calloc: ", strerror(errno));
	i = 0;
	while (i < len_arr)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	return (new_buffer);
}

char		**reallocate_array(t_msh *msh, char **buffer, char *new_string)
{
	char	**new_buffer;
	int		len_arr;

	len_arr = 0;
	while (buffer[len_arr])
		len_arr++;
	new_buffer = duplicate_array(msh, buffer, len_arr + 1);
	if (!(new_buffer[len_arr] = ft_strdup(new_string)))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	free(buffer);
	return (new_buffer);
}
