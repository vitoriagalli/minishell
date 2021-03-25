/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:49:03 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 12:56:02 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*handle_out_append(t_cmd *cmd, t_tokens *tk)
{
	ft_lstadd_back(&cmd->redirection, ft_lstnew(ft_strdup(">>")));
	tk = tk->next;
	ft_lstadd_back(&cmd->redirection, ft_lstnew(ft_strdup(tk->data)));
	return (tk);
}

t_tokens	*handle_out_overwrite(t_cmd *cmd, t_tokens *tk)
{
	ft_lstadd_back(&cmd->redirection, ft_lstnew(ft_strdup(">")));
	tk = tk->next;
	ft_lstadd_back(&cmd->redirection, ft_lstnew(ft_strdup(tk->data)));
	return (tk);
}

t_tokens	*handle_out_input(t_cmd *cmd, t_tokens *tk)
{
	ft_lstadd_back(&cmd->redirection, ft_lstnew(ft_strdup("<")));
	tk = tk->next;
	ft_lstadd_back(&cmd->redirection, ft_lstnew(ft_strdup(tk->data)));
	return (tk);
}
