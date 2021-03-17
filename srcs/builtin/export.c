/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:45:23 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/10 17:04:12 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_node_tail(t_env *lst)
{
	while (lst)
	{
		if (!(*lst).next)
			break ;
		lst = (*lst).next;
	}
	lst->next = malloc(sizeof(t_env));
	lst = lst->next;
	lst->next = NULL;
	return (lst);
}

static char	*get_identifier_env(char *arg, t_minishell *msh)
{
	int i;

	i = 0;
	if (arg[0] == '=')
	{
		msh->last_ret_cmd = 1;
		ft_printf("minishell: export: `%s': not a valid identifier\n", arg);
		return (NULL);
	}
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			msh->last_ret_cmd = 1;
			ft_printf("minishell: export: `%s': not a valid identifier\n", arg);
			return (NULL);
		}	
		i++;
	}
	if (arg[i] == '=')
		return (ft_substr(arg, 0, i));
	else
		return (NULL);
}

static char	*get_value_env(char *arg, size_t len_id)
{
	int i;

	i = len_id + 1;
	while (arg[i] != '\0')
		i++;
	return (ft_substr(arg, len_id + 1, ft_strlen(arg) - len_id));
}

void	ft_export(t_cmd *cmd, t_exec *exec, t_minishell *msh)
{
	t_env *node;
	char *id;
	char *val;
	int i;

	i = 1;
	if (exec->child_pid == 0)
		exit(EXIT_SUCCESS);
	if (cmd->separator == 0 || cmd->separator == SEPARATOR)
	{
		while (cmd->args[i] != NULL)
		{
			if ((id = get_identifier_env(cmd->args[i], msh)) == NULL)
			{
				msh->force_ret_buildin = true;
				return ;
			}	
			val = get_value_env(cmd->args[i], ft_strlen(id));
			node = create_node_tail(msh->head_env);
			node->name = ft_strdup(id);
			node->value = ft_strdup(val);
			i++;
		}
	}
}