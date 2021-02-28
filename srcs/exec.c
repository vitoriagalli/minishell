/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:45:12 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/28 00:55:57 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch(t_exec *exec)
{
	if (!fork())
	{
		if (execve(exec->path, exec->argv, exec->envp))
			exit(0);
		exit(0);
	}
	else
		wait(0);
	return (0);
}

char	**put_tk_lst_into_array_pointers(t_token *tks)
{
	char	**args;
	int		len;
	int		i;

	len = ft_tkn_size(tks);
	args = (char **)calloc(len + 1, sizeof(char *));
	i = 0;
	while (i < len)
	{
		args[i] = tks->data;
		tks = tks->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	launch_process(t_shell *sh)
{
	sh->exec = ft_calloc(1, sizeof(t_exec));
	sh->exec->envp = sh->envp;
	sh->exec->argv = put_tk_lst_into_array_pointers(sh->tks);
	sh->exec->path = find_bin_path(sh->env, sh->exec->argv[0]);
	return (launch(sh->exec));
}

int		execute(t_shell *sh)
{
	static char				*f_name[7] = {"echo",
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
	return (launch_process(sh)); // to implement
}
