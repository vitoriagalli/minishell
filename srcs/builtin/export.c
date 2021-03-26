/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:45:23 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/26 15:51:40 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool		export_valid_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
			return (false);
		i++;
	}
	return (true);
}

static void		ft_sort_string_arr(char **arr)
{
	int		i;
	int		j;
	char	*aux;

	if (!arr || !(*arr))
		return ;
	i = 0;
	while (arr[i + 1])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) > 0)
			{
				aux = arr[i];
				arr[i] = arr[j];
				arr[j] = aux;
			}
			j++;
		}
		i++;
	}
}

static void		print_env_declare_mode(void)
{
	char	**sorted_env;
	int		i;

	i = 0;
	while (g_msh.env[i])
		i++;
	sorted_env = duplicate_array(g_msh.env, i);
	ft_sort_string_arr(sorted_env);
	i = 0;
	while (sorted_env[i])
		ft_printf("declare -x %s\n", sorted_env[i++]);
	free(sorted_env);
}

void			look_for_env(char *env_str)
{
	bool	exist;
	int		len;
	int		i;

	if ((len = ft_strrchr(env_str, '=') - env_str) < 0)
		return ;
	i = 0;
	exist = false;
	while (g_msh.env[i])
	{
		if (!ft_strncmp(g_msh.env[i], env_str, len + 1))
		{
			free(g_msh.env[i]);
			if (!(g_msh.env[i] = ft_strdup(env_str)))
				exit_msh("ft_strdup: ", strerror(errno));
			exist = true;
		}
		i++;
	}
	if (exist == false)
		g_msh.env = reallocate_array(g_msh.env, env_str);
}

void			ft_export(t_cmd *cmd, t_exec *exec)
{
	int		i;

	i = 1;
	g_msh.force_ret_buildin = true;
	g_msh.last_ret_cmd = EXIT_SUCCESS;
	//if (exec->child_pid == 0)
	//{
	//	free_after_fork();
	//	exit(g_msh.last_ret_cmd);
	//}
	if (!cmd->args[i])
		return (print_env_declare_mode());
	while (cmd->args[i])
	{
		if (export_valid_chars(cmd->args[i]))
			look_for_env(cmd->args[i]);
		else
		{
			ft_printf("bash: unset: %s: not a valid identifier\n",
														cmd->args[i]);
			g_msh.last_ret_cmd = EXIT_FAILURE;
		}
		i++;
	}
}
