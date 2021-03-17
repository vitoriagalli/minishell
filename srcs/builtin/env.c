/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:45:59 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/04 09:46:16 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd *cmd, t_exec *exec, t_minishell *msh)
{
	t_env *line;
	
	if (exec->child_pid == 0)
	{
		line = msh->head_env;
		while (line)
		{
			ft_printf("%s=%s\n", line->name, line->value);
			line = line->next;
		}
		exit(EXIT_SUCCESS);
	}
}