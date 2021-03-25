/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:44:02 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/24 20:30:23 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	update_env(char *oldpwd)
{
	int i;
	char pwd[PATH_MAX];
	char *tmp;

	i = 0;
	getcwd(pwd, PATH_MAX);
	while (g_msh.env[i])
	{
		if (!ft_strncmp(g_msh.env[i], "PWD", 3))
		{
			free(g_msh.env[i]);
			if (!(tmp = ft_strjoin("PWD=", pwd)))
				exit_msh("ft_strjoin: ", strerror(errno));
			if (!(g_msh.env[i] = ft_strdup(tmp)))
				exit_msh("ft_strdup: ", strerror(errno));
			ft_strdel(&tmp);
		}
		else if (!ft_strncmp(g_msh.env[i], "OLDPWD", 6))
		{
			ft_strdel(&g_msh.env[i]);
			if (!(tmp = ft_strjoin("OLDPWD=", oldpwd)))
				exit_msh("ft_strjoin: ", strerror(errno));
			if (!(g_msh.env[i] = ft_strdup(tmp)))
				exit_msh("ft_strdup: ", strerror(errno));
			ft_strdel(&tmp);
		}
		i++;
	}
}

static char	*check_replace_path(char **args)
{
	char *tmp;
	char *tmp2;
	char **path_home;

	tmp = NULL;
	path_home = get_env_value("HOME");
	if (!args[1])
		return (NULL);
	if (args[1][0] == '~')
	{
		if (!(tmp2 = ft_substr(args[1], 1, ft_strlen(args[1]))))
			exit_msh("ft_substr: ", strerror(errno));
		if (!(tmp = ft_strjoin(path_home[0], tmp2)))
			exit_msh("ft_strjoin: ", strerror(errno));
		free(tmp2);
	}
	else if (args[1][0] != '.' && args[1][0] != '/')
	{
		if (!(tmp = ft_strjoin("./", args[1])))
			exit_msh("ft_strjoin: ", strerror(errno));
	}	
	else
		if (!(tmp = ft_strdup(args[1])))
			exit_msh("ft_strdup: ", strerror(errno));
	ft_array_clear(path_home, ft_free);
	return (tmp);
}

void	ft_cd(t_cmd *cmd, t_exec *exec)
{
	char *tmp;
	char oldpwd[PATH_MAX];

	if (exec->child_pid == 0)
	{
		free_after_fork();
		exit(EXIT_SUCCESS);
	}
	if (cmd->separator == 0 || cmd->separator == SEPARATOR)
	{
		if (!cmd->args[1])
			return ;
		tmp = check_replace_path(cmd->args);
		getcwd(oldpwd, PATH_MAX);
		if (cmd->args[2])
		{
			ft_printf("minishell: cd: too many arguments\n");
			g_msh.force_ret_buildin = true;
			g_msh.last_ret_cmd = 1;
		}
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
