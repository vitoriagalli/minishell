/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:45:23 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 22:37:51 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool		export_valid_chars(char *str)
{
	int	i;

	if (ft_isdigit(str[0]) || str[0] == '=')
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
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

static void		print_env_declare_mode(t_msh *msh)
{
	char	**sorted_env;
	int		i;

	i = 0;
	while (msh->env[i])
		i++;
	sorted_env = duplicate_array(msh, msh->env, i);
	ft_sort_string_arr(sorted_env);
	i = 0;
	while (sorted_env[i])
		ft_printf("declare -x %s\n", sorted_env[i++]);
	free(sorted_env);
}

void			look_for_env(t_msh *msh, char *env_str)
{
	bool	exist;
	int		len;
	int		i;

	if ((len = ft_strrchr(env_str, '=') - env_str) < 0)
		return ;
	i = 0;
	exist = false;
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], env_str, len + 1))
		{
			free(msh->env[i]);
			if (!(msh->env[i] = ft_strdup(env_str)))
				exit_msh(msh, "ft_strdup: ", strerror(errno));
			exist = true;
		}
		i++;
	}
	if (exist == false)
		msh->env = reallocate_array(msh, msh->env, env_str);
}

void			ft_export(t_msh *msh, t_cmd *cmd)
{
	int		i;

	i = 1;
	g_stream.exit_status = EXIT_SUCCESS;
	if (!cmd->args[i])
		return (print_env_declare_mode(msh));
	while (cmd->args[i])
	{
		if (export_valid_chars(cmd->args[i]))
			look_for_env(msh, cmd->args[i]);
		else
		{
			ft_printf("bash: export: `%s': not a valid identifier\n",
														cmd->args[i]);
			g_stream.exit_status = EXIT_FAILURE;
		}
		i++;
	}
}
