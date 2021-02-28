/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 20:41:59 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/28 00:56:59 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_bin_path(t_env *env, char *command)
{
	(void)env;
	return (ft_strjoin("/bin/", command)); // gambiarra
}
