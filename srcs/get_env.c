/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:25:59 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 23:55:53 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		store_key_and_value(char **value, char **key, char *str)
{
	char *addr;

	addr = ft_strrchr(str, '=');
	if (!(*key = ft_substr(str, 0, addr - str)))
		exit_msh("ft_substr: ", strerror(errno));
	if (!(*value = ft_substr(str, addr - str + 1,
	ft_strlen(str) - (addr - str))))
		exit_msh("ft_strdup: ", strerror(errno));
}

static void	free_name_and_value(char *name, char *value)
{
	free(name);
	name = NULL;
	free(value);
	value = NULL;
}

char		**get_env_value(char *key)
{
	char	**env_values;
	char	*name;
	char	*value;
	int		i;

	name = NULL;
	value = NULL;
	i = 0;
	while (g_msh.env[i])
	{
		store_key_and_value(&value, &name, g_msh.env[i]);
		if (!ft_strcmp(key, name))
		{
			if (!(env_values = ft_split(value, ':')))
				exit_msh("ft_split: ", strerror(errno));
			free_name_and_value(name, value);
			return (env_values);
		}
		free_name_and_value(name, value);
		i++;
	}
	env_values = ft_split(" -", '-');
	env_values[0][0] = '\0';
	return (env_values);
}

void		init_env(char **envp)
{
	int		len_arr;
	int		i;

	len_arr = 0;
	while (envp[len_arr])
		len_arr++;
	if (!(g_msh.env = ft_calloc(len_arr + 1, sizeof(char *))))
		exit_msh("ft_calloc: ", strerror(errno));
	i = 0;
	while (i < len_arr)
	{
		if (!(g_msh.env[i] = ft_strdup(envp[i])))
			exit_msh("ft_strdup: ", strerror(errno));
		i++;
	}
}
