/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:02:49 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 22:04:51 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	unset_valid_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	check_env_var(char *env_var)
{
	int		i;
	int		l;

	i = 0;
	l = ft_strlen(env_var);
	while (g_msh.env[i])
	{
		if (!ft_strncmp(g_msh.env[i], env_var, l) && g_msh.env[i][l] == '=')
		{
			free(g_msh.env[i]);
			while (g_msh.env[i + 1])
			{
				g_msh.env[i] = g_msh.env[i + 1];
				i++;
			}
			g_msh.env[i] = NULL;
		}
		i++;
	}
	return ;
}

void		ft_unset(t_cmd *cmd, t_exec *exec)
{
	int		arg;

	g_msh.force_ret_buildin = true;
	g_msh.last_ret_cmd = EXIT_SUCCESS;
	if (exec->child_pid == 0)
	{
		free_after_fork();
		exit(g_msh.last_ret_cmd);
	}
	arg = 1;
	while (cmd->args[arg])
	{
		if (unset_valid_chars(cmd->args[arg]))
			check_env_var(cmd->args[arg]);
		else
		{
			ft_printf("bash: unset: %s: not a valid identifier\n",
														cmd->args[arg]);
			g_msh.last_ret_cmd = EXIT_FAILURE;
		}
		arg++;
	}
	return ;
}
