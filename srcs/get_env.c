/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:25:59 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/18 13:13:50 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	store_key_and_value(char **value, char **key, char *str)
{
	char *addr;

	addr = ft_strrchr(str, '=');
	*key = ft_substr(str, 0, addr - str);
	*value = ft_substr(str, addr - str + 1,
	ft_strlen(str) - (addr - str));
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

void	store_important_values(void)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (g_msh.env[i])
	{
		store_key_and_value(&value, &key, g_msh.env[i]);
		if (!ft_strncmp(key, "PATH", ft_strlen(key)))
			g_msh.path_cmd = ft_split(value, ':');
		if (!ft_strncmp(key, "HOME", ft_strlen(key)))
			g_msh.path_cmd = ft_strdup(value);
		if (!ft_strncmp(key, "TERM", ft_strlen(key)))
			g_msh.termtype = ft_strdup(value);
		free(key);
		free(value);
		i++;
	}
}

void	init_env(char **envp)
{
	allocate_and_atribute(envp);
	store_important_values();
}


