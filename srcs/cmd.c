/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:33:50 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/12 02:29:32 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**args_list_into_array_pointers(t_list *args_lst)
{
	char	**args;
	int		len;
	int		i;

	len = ft_lstsize(args_lst);
	args = (char **)calloc(len + 1, sizeof(char *));
	i = 0;
	while (i < len)
	{
		args[i] = ft_strdup(args_lst->content);
		args_lst = args_lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

int		store_redirection_info(t_cmd **cmd, int type, char *file, t_list **tmp)
{
	(*cmd)->redirection = type;
	(*cmd)->file = ft_strdup(file);
	// if (type == GREATER)
	// 	(*cmd)->fdout = open(file, O_WRONLY | O_CREAT, 0664);
	// else if (type == DGREATER)
	// 	(*cmd)->fdout = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	// else
	// 	(*cmd)->fdin = open(file, O_RDONLY);
	ft_lstclear(tmp, ft_free);
	return (0);
}

int		handle_redirection(t_cmd **cmd, t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp && tmp->next && tmp->next->next)
	{
		if (!ft_strcmp(tmp->next->content, ">") &&
			!ft_strcmp(tmp->next->next->content, ">"))
			return (store_redirection_info(cmd, DGREATER,
			tmp->next->next->next->content, &tmp->next));
		else if (!ft_strcmp(tmp->next->content, ">"))
			return (store_redirection_info(cmd, GREATER,
			tmp->next->next->content, &tmp->next));
		else if (!ft_strcmp(tmp->next->content, "<"))
			return (store_redirection_info(cmd, LESSER,
			tmp->next->next->content, &tmp->next));
		tmp = tmp->next;
	}
	return (0);
}

t_cmd	*build_cmd(t_token *tk)
{
	t_cmd	*cmd;
	t_list	*args;

	args = NULL;
	cmd = ft_cmd_new();
	cmd->cmd = find_path(tk->tk_cmd);
	cmd->separator = tk->sep;
	handle_redirection(&cmd, tk->args_lst);
	cmd->args = args_list_into_array_pointers(tk->args_lst);
	return (cmd);
}
