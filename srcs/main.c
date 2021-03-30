/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:03:35 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 15:42:30 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_terminal(t_msh *msh, bool from_exit)
{
	if (from_exit == true)
	{
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, msh->save) == -1)
		{
			free(msh->save);
			msh->save = NULL;
			exit(g_stream.exit_status);
		}
	}
	else
	{
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, msh->save) == -1)
			exit_msh(msh, "tcsetattr: ", strerror(errno));
	}
}

int		main(void)
{
	t_msh msh;

	ft_bzero(&msh, sizeof(t_msh));
	init_env(&msh, __environ);
	while ((read_line(&msh, true)) != 0)
	{
		restore_terminal(&msh, false);
		lexer(&msh);
		if (!parser(&msh))
			continue;
		create_cmds(&msh);
		execution_cmds(&msh);
	}
	exit_program(&msh);
}
