/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vs-Rb <marvin@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:44:02 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/18 21:24:01 by Vs-Rb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(char *oldpwd)
{
	int i;
	char pwd[PATH_MAX];

	i = 0;
	getcwd(pwd, PATH_MAX);
	while (g_msh.env[i])
	{
		if (!ft_strncmp(g_msh.env[i], "PWD", 3))
		{
			free(g_msh.env[i]);
			g_msh.env[i] = ft_strdup(ft_strjoin("PWD=", pwd));
		}
		else if (!ft_strncmp(g_msh.env[i], "OLDPWD", 6))
		{
			free(g_msh.env[i]);
			g_msh.env[i] = ft_strdup(ft_strjoin("OLDPWD=", oldpwd));
		}
		i++;
	}
}

char	*check_replace_path(char **args)
{
	char *tmp;
	
	tmp = NULL;
	if (args[1][0] == '~')
	{
		tmp = ft_substr(args[1], 1, ft_strlen(args[1]));
		tmp = ft_strjoin(g_msh.path_home, tmp);
	}
	else if (args[1][0] != '.' && args[1][0] != '/')
		tmp = ft_strjoin("./", args[1]);
	else
		tmp = ft_strdup(args[1]);
	return (tmp);
}

void	ft_cd(t_cmd *cmd, t_exec *exec)
{
	char *tmp;
	char oldpwd[PATH_MAX];

	if (exec->child_pid == 0)
		exit(EXIT_SUCCESS);
	if (cmd->separator == 0 || cmd->separator == SEPARATOR)
	{
		tmp = check_replace_path(cmd->args);
		getcwd(oldpwd, PATH_MAX);
		if (cmd->args[2] != NULL)
			ft_printf("minishell: cd: too many arguments\n");
		else if ((chdir(tmp)) < 0)
		{
			if (cmd->args[1][0] == '~')
				ft_printf("minishell: cd: %s: %s\n",tmp, strerror(errno));
			else
				ft_printf("minishell: cd: %s: %s\n",cmd->args[1], strerror(errno));
			g_msh.force_ret_buildin = true;
			g_msh.last_ret_cmd = 1;
		}
		update_env(oldpwd);
		free(tmp);
	}	
}