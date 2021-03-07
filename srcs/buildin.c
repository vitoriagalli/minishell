/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:16:54 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/07 00:19:27 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(t_cmd *cmd)
{
	bool	flag;
	int		i;

	flag = false;
	i = 1;
	if (cmd->args[i] && !ft_strcmp(cmd->args[i], "-n"))
	{
		flag = true;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int		ft_cd(t_cmd *cmd)
{
	if (chdir(cmd->args[1]) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		ft_pwd(t_cmd *cmd)
{
	char	cwd[1024 + 1];

	(void)cmd;
	if (!(getcwd(cwd, 1024)))
		return (EXIT_FAILURE);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}


// sem argumentos, printa as variaveis do shell presente
// com argumentos, seta a variavel no shell presente
int		ft_export(t_cmd *cmd)
{
	int		i;
	int		len;
	int		exist;
	char	**new_add_env;

	i = 0;
	len = 0;
	exist = false;
	if (cmd->args[1])
	{
		len = ft_strrchr(cmd->args[1], '=') - cmd->args[1];
		while (g_env[i])
		{
			if (cmd->args[1] && !ft_strncmp(g_env[i], cmd->args[1], len + 1))
			{
				g_env[i] = cmd->args[1];
				exist = true;
			}
			i++;
		}
		if (exist == false)
		{
			len = 0;
			while (g_env[len])
				len++;
			new_add_env = reallocate(g_env, len);
			new_add_env[len] = cmd->args[1];
			g_env = new_add_env;
		}
	}
	else
	{
		while (g_env[i])
		{
			// verificar formato -declare
			ft_putendl_fd(g_env[i++], STDOUT_FILENO);
		}
	}

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
		// arrumar! comprar ate o final
		if (cmd->args[1] && !ft_strncmp(g_env[i], cmd->args[1], len))
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

// int		ft_exit(t_cmd *cmd)
int		ft_exit(t_shell *sh)
{
	// free_shell(sh);
	ft_array_clear(g_env, ft_free);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
