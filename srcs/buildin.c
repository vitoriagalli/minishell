/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:16:54 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/26 01:48:27 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(t_shell *sh)
{
	if (!(ft_strcmp(sh->tks->next->data, "-n")))
		ft_putstr_fd(sh->tks->next->next->data, STDOUT_FILENO);
	else
		ft_putendl_fd(sh->tks->next->data, STDOUT_FILENO);
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

int		execute(t_shell *sh)
{
	static int				*f_name[7] = {"echo",
										"cd",
										"pwd",
										"export",
										"unset",
										"env",
										"exit"};
	static builtin_funct	f_call[7] = {ft_echo,
									ft_cd,
									ft_pwd,
									ft_export,
									ft_unset,
									ft_env,
									ft_exit};
	int						i;

	i = 0;
	while (i < 7)
	{
		if (!(ft_strcmp(sh->tks->data, f_name[i])))
			return ((*f_call[i])(sh));
		i++;
	}
	// return fork_process() // to implement
	return (0);
}
