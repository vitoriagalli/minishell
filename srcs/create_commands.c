/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vs-Rb <marvin@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:55:53 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/22 15:42:15 by Vs-Rb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens()
{
	t_tokens *node;

	while (g_msh.head_tk != NULL)
	{
		node = g_msh.head_tk;
		g_msh.head_tk = g_msh.head_tk->next;
		free(node);
	}
}

void	init_command(t_cmd *cmd)
{
	int nb_tk;

	ft_bzero(cmd, sizeof(t_cmd));
	nb_tk = size_token_list(g_msh.head_tk);
	cmd->args = malloc(sizeof(char*) * (nb_tk - g_msh.cmds.curr_tk));
	ft_bzero(cmd->args, sizeof(char*) * (nb_tk - g_msh.cmds.curr_tk));
	cmd->next = NULL;
	g_msh.cmds.got_cmd_name = false;
	g_msh.cmds.curr_arg = 0;
}

t_cmd	*handle_cmd_separator(t_cmd *cmd, t_tokens *tk)
{
	cmd->separator = tk->type;
	tk = tk->next;
	cmd->next = malloc(sizeof(t_cmd));
	cmd->args[g_msh.cmds.curr_arg] = NULL;
	cmd = cmd->next;
	init_command(cmd);
	return (cmd);
}

t_tokens	*handle_out_append(t_cmd *cmd, t_tokens *tk, t_cmds *cmds)
{
	ft_lstadd_back(&cmd->redirection, ft_lstnew(ft_strdup(">>")));
	tk = tk->next;
	cmds->curr_tk++;
	ft_lstadd_back(&cmd->redirection, ft_lstnew(ft_strdup(tk->data)));
	return (tk);
}

t_tokens	*handle_out_overwrite(t_cmd *cmd, t_tokens *tk, t_cmds *cmds)
{
	ft_lstadd_back(&cmd->redirection, ft_lstnew(ft_strdup(">")));
	tk = tk->next;
	cmds->curr_tk++;
	ft_lstadd_back(&cmd->redirection, ft_lstnew(ft_strdup(tk->data)));
	return (tk);
}

t_tokens	*handle_out_input(t_cmd *cmd, t_tokens *tk, t_cmds *cmds)
{
	ft_lstadd_back(&cmd->redirection, ft_lstnew(ft_strdup("<")));
	tk = tk->next;
	ft_lstadd_back(&cmd->redirection, ft_lstnew(ft_strdup(tk->data)));
	return (tk);
}

t_tokens	*handle_redir(t_cmd *cmd, t_tokens *tk, t_cmds *cmds)
{
	if (tk->type == OUT_APPEND)
		return (handle_out_append(cmd, tk, cmds));
	else if (tk->type == OUT_OVERWRITE)
		return (handle_out_overwrite(cmd, tk, cmds));
	else if (tk->type == tk->type == INPUT)
		return (handle_out_input(cmd, tk, cmds));
}

void	handle_word(t_cmd *cmd, t_tokens *tk, t_cmds *cmds)
{
	if (cmds->got_cmd_name == false)
	{
		cmd->cmd_name = ft_strdup(tk->data);
		cmd->args[cmds->curr_arg] = ft_strdup(cmd->cmd_name);
		cmds->curr_arg++;
		cmds->got_cmd_name = true;
	}
	else
	{
		cmd->args[cmds->curr_arg] = ft_strdup(tk->data);
		cmds->curr_arg++;
	}
}

void	create_commands()
{
	t_tokens *tk;
	t_cmd *cmd;

	g_msh.cmds.head_cmd = malloc(sizeof(t_cmd));
	tk = g_msh.head_tk;
	cmd = g_msh.cmds.head_cmd;
	init_command(cmd);
	while (tk->next)
	{
		if (tk->type == OUT_APPEND || tk->type == OUT_OVERWRITE || tk->type == INPUT)
			tk = handle_redir(cmd, tk, &g_msh.cmds);
		else if (tk->type == PIPE || tk->type == SEPARATOR)
			cmd = handle_cmd_separator(cmd, tk);
		else
			handle_word(cmd, tk, &g_msh.cmds);
		g_msh.cmds.curr_tk++;
		tk = tk->next;
	}
	free_tokens();
}
