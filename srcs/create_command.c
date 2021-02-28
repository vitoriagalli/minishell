/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:55:53 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/27 23:57:14 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_command(t_cmd *cmd, t_minishell *msh)
{
	
	ft_bzero(cmd, sizeof(t_cmd));
	msh->cmds->nb_tk = size_token_list(msh->head_tk);
	cmd->args = malloc(sizeof(char*) * msh->cmds->nb_tk - msh->cmds->curr_tk);
	cmd->next = NULL;
	msh->cmds->got_cmd_name = false;
	msh->cmds->curr_arg = 0;
}

t_cmd	*handle_cmd_separator(t_cmd *cmd, t_tokens *tk, t_minishell *msh)
{
	cmd->separator = tk->type;
	tk = tk->next;
	msh->cmds->curr_tk++;
	cmd->next = malloc(sizeof(t_cmd));
	cmd->args[msh->cmds->curr_arg] = NULL;
	cmd = cmd->next;
	init_command(cmd, msh);
	return (cmd);
}

t_tokens	*handle_cmd_input(t_cmd *cmd, t_tokens *tk, t_cmds *cmds)
{
	cmd->redirection = tk->type;
	tk = tk->next;
	cmd->file_in = ft_strdup(tk->data);
	return (tk);
}

t_tokens	*handle_cmd_output(t_cmd *cmd, t_tokens *tk, t_cmds *cmds)
{
	cmd->redirection = tk->type;
	tk = tk->next;
	cmds->curr_tk++;
	cmd->file_out = ft_strdup(tk->data);
	return (tk);
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

void	create_command(t_minishell *msh)
{
	t_tokens *tk;
	t_cmd *cmd;

	*msh->cmds = (t_cmds) {0};
	msh->cmds->head_cmd = malloc(sizeof(t_cmd));
	tk = msh->head_tk;
	cmd = msh->cmds->head_cmd;
	init_command(cmd, msh);
	while (tk->next)
	{
		if (tk->type == PIPE || tk->type == SEPARATOR)
			cmd = handle_cmd_separator(cmd, tk, msh);
		else if (tk->type == OUT_APPEND || tk->type == OUT_OVERWRITE)
			tk = handle_cmd_output(cmd, tk, msh->cmds);
		else if (tk->type == INPUT)
			tk = handle_cmd_input(cmd, tk, msh->cmds);
		else
			handle_word(cmd, tk, msh->cmds);
		msh->cmds->curr_tk++;
		tk = tk->next;
	}
	cmd->args[msh->cmds->curr_arg] = NULL;
}