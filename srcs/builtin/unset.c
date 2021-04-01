/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:02:49 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 11:59:50 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	unset_valid_chars(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) || str[0] == '=')
		return (false);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	check_env_var(t_msh *msh, char *env_var)
{
	int		i;
	int		l;

	i = 0;
	l = ft_strlen(env_var);
	while (msh->env[i])
	{
		if (!ft_strncmp(msh->env[i], env_var, l) && msh->env[i][l] == '=')
		{
			free(msh->env[i]);
			while (msh->env[i + 1])
			{
				msh->env[i] = msh->env[i + 1];
				i++;
			}
			msh->env[i] = NULL;
		}
		i++;
	}
	return ;
}

void		ft_unset(t_msh *msh, t_cmd *cmd)
{
	int		arg;

	g_stream.exit_status = EXIT_SUCCESS;
	arg = 1;
	while (cmd->args[arg])
	{
		if (unset_valid_chars(cmd->args[arg]))
			check_env_var(msh, cmd->args[arg]);
		else
		{
			ft_printf("bash: unset: `%s': not a valid identifier\n",
														cmd->args[arg]);
			g_stream.exit_status = EXIT_FAILURE;
		}
		arg++;
	}
	return ;
}
