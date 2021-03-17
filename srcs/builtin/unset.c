/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:02:49 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/10 17:19:39 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	seek_node(t_minishell *msh, t_cmd *cmd, int i)
{
	t_env *node;
	t_env *next_node;

	node = msh->head_env;
	while (node)
	{
		if (!ft_strncmp(node->name, cmd->args[i], ft_strlen(cmd->args[i])))
		{
			next_node = node->next;
			free(node);
			msh->head_env = next_node;
			break ;
		}
		if (!ft_strncmp(node->next->name, cmd->args[i], ft_strlen(cmd->args[i])))
		{
			next_node = node->next->next;
			free(node->next);
			node->next = next_node;
			break ;
		}
		node = node->next;
	}
}

int	check_identifier(t_minishell *msh, char *arg)
{
	int i;

	i = 0;
	if (arg[0] == '=')
	{
		msh->force_ret_buildin = true;
		msh->last_ret_cmd = 1;
		ft_printf("minishell: unset: `%s': not a valid identifier\n", arg);
		return (1);
	}
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			msh->force_ret_buildin = true;
			msh->last_ret_cmd = 1;
			ft_printf("minishell: unset: `%s': not a valid identifier\n", arg);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_unset(t_cmd *cmd, t_exec *exec, t_minishell *msh)
{
	int i;

	i = 1;
	if (exec->child_pid == 0)
		exit(EXIT_SUCCESS);
	if (cmd->separator == 0 || cmd->separator == SEPARATOR)
	{
		while (cmd->args[i])
		{
			if (check_identifier(msh, cmd->args[i]) == 1)
			{
				i++;
				continue ;
			}
			seek_node(msh, cmd, i);
			i++;
		}
	}
}