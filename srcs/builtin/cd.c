/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:44:02 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 15:43:06 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env(char *oldpwd)
{
	int		i;
	char	pwd[PATH_MAX];

	i = 0;
	getcwd(pwd, PATH_MAX);
	while (g_msh.env[i])
	{
		if (!ft_strncmp(g_msh.env[i], "PWD", 3))
			replace_pwd(i, true, pwd, oldpwd);
		else if (!ft_strncmp(g_msh.env[i], "OLDPWD", 6))
			replace_pwd(i, false, pwd, oldpwd);
		i++;
	}
}

static char	*check_replace_path(char **args)
{
	char *tmp;

	tmp = NULL;
	if (!args[1])
		return (NULL);
	if (args[1][0] == '~')
		tmp = replace_tild(args[1]);
	else if (args[1][0] != '.' && args[1][0] != '/')
	{
		if (!(tmp = ft_strjoin("./", args[1])))
			exit_msh("ft_strjoin: ", strerror(errno));
	}
	else
	{
		if (!(tmp = ft_strdup(args[1])))
			exit_msh("ft_strdup: ", strerror(errno));
	}
	return (tmp);
}

static void	chdir_fail(char *arg, char *tmp)
{
	if (arg[0] == '~')
		ft_printf("minishell: cd: %s: %s\n", tmp, strerror(errno));
	else
		ft_printf("minishell: cd: %s: %s\n", arg,
	strerror(errno));
	g_msh.force_ret_buildin = true;
	g_msh.last_ret_cmd = 1;
}

void		ft_cd(t_cmd *cmd, t_exec *exec)
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
			chdir_fail(cmd->args[1], tmp);
		update_env(oldpwd);
		free(tmp);
	}
}
