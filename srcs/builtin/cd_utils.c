/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:42:12 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 15:43:20 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_tild(char *arg)
{
	char	**path_home;
	char	*tmp;
	char	*tmp2;

	path_home = get_env_value("HOME");
	if (!(tmp2 = ft_substr(arg, 1, ft_strlen(arg))))
		exit_msh("ft_substr: ", strerror(errno));
	if (!(tmp = ft_strjoin(path_home[0], tmp2)))
		exit_msh("ft_strjoin: ", strerror(errno));
	free(tmp2);
	ft_array_clear(path_home, ft_free);
	return (tmp);
}

void	replace_pwd(int i, bool is_pwd, char *pwd, char *oldpwd)
{
	char	*tmp;

	ft_strdel(&g_msh.env[i]);
	if (is_pwd == true)
	{
		if (!(tmp = ft_strjoin("PWD=", pwd)))
			exit_msh("ft_strjoin: ", strerror(errno));
	}
	else
	{
		if (!(tmp = ft_strjoin("OLDPWD=", oldpwd)))
			exit_msh("ft_strjoin: ", strerror(errno));
	}
	if (!(g_msh.env[i] = ft_strdup(tmp)))
		exit_msh("ft_strdup: ", strerror(errno));
	ft_strdel(&tmp);
}
