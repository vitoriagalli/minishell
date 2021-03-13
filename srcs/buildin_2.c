/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:23:09 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/13 19:08:33 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_env_declare_mode(void)
{
	char	**sorted_env;
	int		i;

	i = 0;
	while (g_env[i])
		i++;
	sorted_env = duplicate_array(g_env, i);
	ft_sort_string_tab(sorted_env);
	i = 0;
	while (sorted_env[i])
		ft_printf("declare -x %s\n", sorted_env[i++]);
	return (EXIT_SUCCESS);
}

int		ft_export(t_cmd *cmd)
{
	int		i;
	int		len;
	bool	exist;

	if (!cmd->args[1])
		return (print_env_declare_mode());
	if ((len = ft_strrchr(cmd->args[1], '=') - cmd->args[1]) < 0)
		return (EXIT_SUCCESS);
	i = 0;
	exist = false;
	while (g_env[i])
	{
		if (!ft_strncmp(g_env[i], cmd->args[1], len + 1))
		{
			free(g_env[i]);
			g_env[i] = ft_strdup(cmd->args[1]);
			exist = true;
		}
		i++;
	}
	if (exist == false)
		g_env = reallocate_array(g_env, cmd->args[1]);
	return (EXIT_SUCCESS);
}

int		ft_unset(t_cmd *cmd)
{
	int		i;
	int		l;

	if (!cmd->args[1])
		return (EXIT_SUCCESS);
	if (ft_strrchr(cmd->args[1], '='))
	{
		ft_printf("bash: unset: %s: not a valid identifier\n", cmd->args[1]);
		return (EXIT_FAILURE);
	}
	i = 0;
	l = ft_strlen(cmd->args[1]);
	while (g_env[i])
	{
		if (!ft_strncmp(g_env[i], cmd->args[1], l) && g_env[i][l] == '=')
		{
			free(g_env[i]);
			while (g_env[i + 1])
			{
				g_env[i] = g_env[i + 1];
				i++;
			}
			g_env[i] = NULL;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int		ft_env(t_cmd *cmd)
{
	int i;

	i = 0;
	while (g_env[i])
		ft_putendl_fd(g_env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
