/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:45:12 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/03 03:52:13 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch(t_exec *exec)
{
	if (!fork())
	{
		execve(exec->path, exec->argv, __environ);
		exit(0);
	}
	else
		wait(0);
	return (0);
}

char	**put_lst_into_array_pointers(t_list *lst)
{
	char	**args;
	int		len;
	int		i;

	len = ft_lstsize(lst);
	args = (char **)calloc(len + 1, sizeof(char *));
	i = 0;
	while (i < len)
	{
		args[i] = lst->content;
		lst = lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	launch_process(t_token *tk)
{
	t_exec	exec;

	exec.argv = put_lst_into_array_pointers(tk->args_lst);
	exec.path = ft_strjoin("/bin/", tk->tk_cmd);

	return (launch(&exec));
}

int		execute_single_command(t_shell *sh, t_token *tk)
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
		if (!(ft_strcmp(tk->tk_cmd, f_name[i])))
			return ((*f_call[i])(tk));
		i++;
	}
	return (launch_process(tk)); // to implement
}

// implementar tipos de separadores
int		execute(t_shell *sh)
{
	t_token *tmp;

	tmp = sh->tk;
	while (tmp)
	{
		execute_single_command(sh, tmp);
		tmp = tmp->next;
	}
}
