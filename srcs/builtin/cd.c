/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:44:02 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 13:58:09 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env(t_msh *msh, char *oldpwd)
{
	int		i;
	char	pwd[PATH_MAX];

	i = 0;
	getcwd(pwd, PATH_MAX);
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], "PWD", 3))
			replace_pwd(msh, i, pwd);
		else if (!ft_strncmp(msh->env[i], "OLDPWD", 6))
			replace_oldpwd(msh, i, oldpwd);
		i++;
	}
}

static char	*check_replace_path(t_msh *msh, char **args)
{
	char *tmp;

	tmp = NULL;
	if (!args[1])
		return (NULL);
	else if (args[1][0] != '.' && args[1][0] != '/' && args[1][0] != '~')
	{
		if (!(tmp = ft_strjoin("./", args[1])))
			exit_msh(msh, "ft_strjoin: ", strerror(errno));
	}
	else
	{
		if (!(tmp = ft_strdup(args[1])))
			exit_msh(msh, "ft_strdup: ", strerror(errno));
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
	g_stream.exit_status = EXIT_FAILURE;
}

void		ft_cd(t_msh *msh, t_cmd *cmd)
{
	char	**ptr;
	char	*tmp;
	char	oldpwd[PATH_MAX];

	g_stream.exit_status = EXIT_SUCCESS;
	if (cmd->separator == PIPE)
		return ;
	tmp = check_replace_path(msh, cmd->args);
	getcwd(oldpwd, PATH_MAX);
	if (!cmd->args[1])
	{
		ptr = get_env_value(msh, "HOME");
		if ((chdir(ptr[0])) < 0)
			chdir_fail(ptr[0], tmp);
		ft_array_clear(ptr, ft_free);
	}
	else if (cmd->args[1] && cmd->args[2])
	{
		ft_printf("minishell: cd: too many arguments\n");
		g_stream.exit_status = EXIT_FAILURE;
	}
	else if ((chdir(tmp)) < 0)
		chdir_fail(cmd->args[1], tmp);
	update_env(msh, oldpwd);
	free(tmp);
}
