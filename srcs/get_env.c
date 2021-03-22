/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vs-Rb <marvin@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:25:59 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/22 11:23:54 by Vs-Rb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	store_key_and_value(char **value, char **key, char *str)
{
	char *addr;

	addr = ft_strrchr(str, '=');
	*key = ft_substr(str, 0, addr - str);
	*value = ft_substr(str, addr - str + 1, ft_strlen(str) - (addr - str));
}

char	**get_env_value(char *key)
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
			env_values = ft_split(value, ':');
			free(name);
			free(value);
			return (env_values);
		}
		free(name);
		free(value);
		i++;
	}
	return (NULL);
}

void	allocate_and_atribute(char **envp)
{
	int		len_arr;
	int		i;

	len_arr = 0;
	while (envp[len_arr])
		len_arr++;
	g_msh.env = ft_calloc(len_arr + 1, sizeof(char *));
	i = 0;
	while (i < len_arr)
	{
		g_msh.env[i] = ft_strdup(envp[i]);
		i++;
	}
}

void	init_env(char **envp)
{
	allocate_and_atribute(envp);
}


