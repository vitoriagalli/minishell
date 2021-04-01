/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:42:12 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 13:58:17 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_oldpwd(t_msh *msh, int i, char *oldpwd)
{
	char	*tmp;

	ft_strdel(&msh->env[i]);
	if (!(tmp = ft_strjoin("OLDPWD=", oldpwd)))
		exit_msh(msh, "ft_strjoin: ", strerror(errno));
	if (!(msh->env[i] = ft_strdup(tmp)))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	ft_strdel(&tmp);
}

void	replace_pwd(t_msh *msh, int i, char *pwd)
{
	char	*tmp;

	ft_strdel(&msh->env[i]);
	if (!(tmp = ft_strjoin("PWD=", pwd)))
		exit_msh(msh, "ft_strjoin: ", strerror(errno));
	if (!(msh->env[i] = ft_strdup(tmp)))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	ft_strdel(&tmp);
}
