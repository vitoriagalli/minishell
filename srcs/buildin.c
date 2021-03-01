/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:16:54 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/02 00:43:29 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(t_token  *tk)
{
	bool	flag;
	t_list	*tmp;

	flag = false;
	tmp = tk->args_lst->next;
	if (tmp && !ft_strcmp(tmp->content, "-n"))
	{
		flag = true;
		tmp = tmp->next;
	}
	while (tmp)
	{
		ft_putstr_fd(tmp->content, STDOUT_FILENO);
		if (tmp->next)
			ft_putstr_fd(" ", STDOUT_FILENO);
		tmp = tmp->next;
	}
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int		ft_cd(t_token  *tk)
{
	if (chdir(tk->args_lst->next->content) != 0)
		return (0);
	return (0);
}

int		ft_pwd(t_token  *tk)
{
	char	cwd[1024 + 1];

	(void)tk;
	if (!(getcwd(cwd, 1024)))
		return (0);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}

int		ft_export(t_token  *tk)
{
	(void)tk;
	return (0);
}

int		ft_unset(t_token  *tk)
{
	(void)tk;
	return (0);
}

int		ft_env(t_token  *tk)
{
	(void)tk;
	return (0);
}

int		ft_exit(t_token  *tk)
{
	(void)tk;
	return (0);
}
