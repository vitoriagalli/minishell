/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:02:49 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/18 03:16:02 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	seek_node(t_cmd *cmd, int i)
// {
// 	t_env *node;
// 	t_env *next_node;

// 	node = g_msh.head_env;
// 	while (node)
// 	{
// 		if (!ft_strncmp(node->name, cmd->args[i], ft_strlen(cmd->args[i])))
// 		{
// 			next_node = node->next;
// 			free(node);
// 			g_msh.head_env = next_node;
// 			break ;
// 		}
// 		if (!ft_strncmp(node->next->name, cmd->args[i], ft_strlen(cmd->args[i])))
// 		{
// 			next_node = node->next->next;
// 			free(node->next);
// 			node->next = next_node;
// 			break ;
// 		}
// 		node = node->next;
// 	}
// }

// int	check_identifier(char *arg)
// {
// 	int i;

// 	i = 0;
// 	if (arg[0] == '=')
// 	{
// 		g_msh.force_ret_buildin = true;
// 		g_msh.last_ret_cmd = 1;
// 		ft_printf("minishell: unset: `%s': not a valid identifier\n", arg);
// 		return (1);
// 	}
// 	while (arg[i] != '\0' && arg[i] != '=')
// 	{
// 		if (!ft_isalnum(arg[i]) && arg[i] != '_')
// 		{
// 			g_msh.force_ret_buildin = true;
// 			g_msh.last_ret_cmd = 1;
// 			ft_printf("minishell: unset: `%s': not a valid identifier\n", arg);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// void	ft_unset(t_cmd *cmd, t_exec *exec)
// {
// 	int i;

// 	i = 1;
// 	if (exec->child_pid == 0)
// 		exit(EXIT_SUCCESS);
// 	if (cmd->separator == 0 || cmd->separator == SEPARATOR)
// 	{
// 		while (cmd->args[i])
// 		{
// 			if (check_identifier(cmd->args[i]) == 1)
// 			{
// 				i++;
// 				continue ;
// 			}
// 			seek_node(cmd, i);
// 			i++;
// 		}
// 	}
// }


void	ft_unset(t_cmd *cmd, t_exec *exec)
{
	int		i;
	int		l;

	if (exec->child_pid == 0)
		exit(EXIT_SUCCESS);
	if (!cmd->args[1])
		exit(EXIT_SUCCESS);
	if (ft_strrchr(cmd->args[1], '='))
	{
		ft_printf("bash: unset: %s: not a valid identifier\n", cmd->args[1]);
		exit(EXIT_FAILURE);
	}
	i = 0;
	l = ft_strlen(cmd->args[1]);
	while (g_msh.env[i])
	{
		if (!ft_strncmp(g_msh.env[i], cmd->args[1], l) && g_msh.env[i][l] == '=')
		{
			free(g_msh.env[i]);
			while (g_msh.env[i + 1])
			{
				g_msh.env[i] = g_msh.env[i + 1];
				i++;
			}
			g_msh.env[i] = NULL;
		}
		i++;
	}
	return ;
}
