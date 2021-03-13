/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:23:09 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/13 16:37:58 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_declare_mode(void)
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
}

int		ft_export(t_cmd *cmd)
{
	int		i;
	int		len;
	bool	exist;
	char	**new_add_env;

	i = 0;
	len = 0;
	exist = false;
	if (cmd->args[1])
	{
		len = ft_strrchr(cmd->args[1], '=') - cmd->args[1];
		if (len > 0)
		{
			while (g_env[i])
			{
				if (cmd->args[1] && !ft_strncmp(g_env[i], cmd->args[1], len + 1))
				{
					free(g_env[i]);
					g_env[i] = ft_strdup(cmd->args[1]);
					exist = true;
				}
				i++;
			}
			if (exist == false)
			{
				len = 0;
				while (g_env[len])
					len++;
				new_add_env = reallocate_array(g_env, len);
				new_add_env[len] = cmd->args[1];
				g_env = new_add_env;
			}
		}
	}
	else
		print_env_declare_mode();
	return (EXIT_SUCCESS);
}

int		ft_unset(t_cmd *cmd)
{
	int		i;
	int		len;

	i = 0;
	if (cmd->args[1])
		len = ft_strlen(cmd->args[1]);
	while (g_env[i])
	{
		if (cmd->args[1] && !ft_strncmp(g_env[i], cmd->args[1], len) && g_env[i][len] == '=')
		{
			ft_printf("%c\n", g_env[i][len]);
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
