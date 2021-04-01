/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:49:03 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 15:42:14 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		del_last_empty_node(t_msh *msh)
{
	t_cmd *previous;

	if (!msh->cmds.head_cmd)
		return ;
	if (!msh->cmds.head_cmd->next)
		return ;
	previous = msh->cmds.head_cmd;
	while (previous->next->next)
		previous = previous->next;
	if (!previous->next->cmd_name)
	{
		ft_array_clear(previous->next->args, ft_free);
		free(previous->next);
		previous->next = NULL;
	}
}

t_tokens	*handle_out_append(t_msh *msh, t_cmd *cmd, t_tokens *tk)
{
	char	*id;
	char	*content;
	t_list	*lst_id;
	t_list	*lst_content;

	if (!(id = ft_strdup(">>")))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	if (!(lst_id = ft_lstnew(id)))
		exit_msh(msh, "ft_lstnew: ", strerror(errno));
	ft_lstadd_back(&cmd->red_out, lst_id);
	tk = tk->next;
	if (!(content = ft_strdup(tk->data)))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	if (!(lst_content = ft_lstnew(content)))
		exit_msh(msh, "ft_lstnew: ", strerror(errno));
	ft_lstadd_back(&cmd->red_out, lst_content);
	return (tk);
}

t_tokens	*handle_out_overwrite(t_msh *msh, t_cmd *cmd, t_tokens *tk)
{
	char	*id;
	char	*content;
	t_list	*lst_id;
	t_list	*lst_content;

	if (!(id = ft_strdup(">")))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	if (!(lst_id = ft_lstnew(id)))
		exit_msh(msh, "ft_lstnew: ", strerror(errno));
	ft_lstadd_back(&cmd->red_out, lst_id);
	tk = tk->next;
	if (!(content = ft_strdup(tk->data)))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	if (!(lst_content = ft_lstnew(content)))
		exit_msh(msh, "ft_lstnew: ", strerror(errno));
	ft_lstadd_back(&cmd->red_out, lst_content);
	return (tk);
}

t_tokens	*handle_out_input(t_msh *msh, t_cmd *cmd, t_tokens *tk)
{
	char	*id;
	char	*content;
	t_list	*lst_id;
	t_list	*lst_content;

	if (!(id = ft_strdup("<")))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	if (!(lst_id = ft_lstnew(id)))
		exit_msh(msh, "ft_lstnew: ", strerror(errno));
	ft_lstadd_back(&cmd->red_in, lst_id);
	tk = tk->next;
	if (!(content = ft_strdup(tk->data)))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	if (!(lst_content = ft_lstnew(content)))
		exit_msh(msh, "ft_lstnew: ", strerror(errno));
	ft_lstadd_back(&cmd->red_in, lst_content);
	return (tk);
}
