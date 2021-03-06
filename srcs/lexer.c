/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 22:48:01 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/06 01:55:14 by vscabell         ###   ########.fr       */
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
	if (type == GREATER || type == GGREATER)
		(*cmd)->file_out = ft_strdup(file);
	else
		(*cmd)->file_in = ft_strdup(file);
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
			return (store_redirection_info(cmd, GGREATER,
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
	cmd->cmd = tk->tk_cmd;
	handle_redirection(&cmd, tk->args_lst);
	cmd->args = args_list_into_array_pointers(tk->args_lst);
	return (cmd);
}

t_cmd	*transform_tkn_into_cmds(t_shell *sh)
{
	t_cmd	*head_cmd;
	t_cmd	*new_cmd;
	t_token	*tmp;

	head_cmd = NULL;
	new_cmd = NULL;
	tmp = sh->tk;
	while (tmp)
	{
		new_cmd = build_cmd(tmp);
		cmd_add_back(&head_cmd, new_cmd);
		tmp = tmp->next;
	}
	return (head_cmd);
}

int		lexer(t_shell *sh)
{
	sh->tk = put_input_into_tkn_struct(sh);
	// check_syntax(sh);			// to implement
	sh->cmd = transform_tkn_into_cmds(sh);

	// ft_tkn_print(sh->tk);
	// ft_cmd_print(sh->cmd);
	return (0);
}
