/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:16:54 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/27 15:46:07 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(t_shell *sh)
{
	bool	flag;
	t_token	*tmp;

	flag = false;
	tmp = sh->tks->next;
	if (tmp && !ft_strcmp(tmp->data, "-n"))
	{
		flag = true;
		tmp = tmp->next;
	}
	while (tmp)
	{
		ft_putstr_fd(tmp->data, STDOUT_FILENO);
		if (tmp->next)
			ft_putstr_fd(" ", STDOUT_FILENO);
		tmp = tmp->next;
	}
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int		ft_cd(t_shell *sh)
{
	if (chdir(sh->tks->next->data) != 0)
		return (0);
	return (0);
}

int		ft_pwd(t_shell *sh)
{
	char	cwd[1024 + 1];

	(void)sh;
	if (!(getcwd(cwd, 1024)))
		return (0);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}

int		ft_export(t_shell *sh)
{
	return (0);
}

int		ft_unset(t_shell *sh)
{
	return (0);
}

int		ft_env(t_shell *sh)
{
	return (0);
}

int		ft_exit(t_shell *sh)
{
	return (0);
}
