/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:16:25 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/12 21:42:53 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
	int i;
	bool flag_n;

	i = 1;
	flag_n = 0;
	if (args[1][0] == '-')
	{
		while (args[1][i] == 'n')
			i++;
		if (args[1][i] == '\0')
			flag_n = 1;
	}
	if (flag_n)
	{
		*args = *(args) + 2;
		while (*args++)
			ft_putstr_fd(ft_strjoin(*args, " "), 1);
	}
	else
	{
		*args = *(args) + 1;
		while (*args++)
			ft_putstr_fd(ft_strjoin(*args, " "), 1);
		ft_putstr_fd("\n", 1);
	}
}

void	ft_cd(char **args)
{
	if (chdir(args[1]) == -1)
		printf("cd: %s: %s\n", strerror(errno), args[1]);
}

void 	ft_pwd(char **args)
{
	char path[1024];

	if (!getcwd(path, 1024))
		printf("%s: %s\n", args[0], strerror(errno));
	else
		printf("%s\n", path);
}

void	ft_export(char **args)
{
	printf("Hello from ft_export\n");
	printf("%s\n", args[0]);
}

void	ft_unset(char **args)
{
	printf("Hello from ft_unset\n");
	printf("%s\n", args[0]);
}

void	ft_env(char **args)
{
	printf("Hello from ft_env\n");
	printf("%s\n", args[0]);
}

void	ft_exit(char **args)
{
	exit(EXIT_SUCCESS);
	args[0][0] = '\0';
}