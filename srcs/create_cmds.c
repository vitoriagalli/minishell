/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:55:53 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 13:56:37 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		init_command(t_msh *msh, t_cmd *cmd)
{
	int nb_tk;

	ft_bzero(cmd, sizeof(t_cmd));
	nb_tk = size_token_list(msh->head_tk);
	if (!(cmd->args = malloc(sizeof(char*) * (nb_tk - msh->cmds.curr_tk) + 1)))
		exit_msh(msh, "malloc: ", strerror(errno));
	ft_bzero(cmd->args, sizeof(char*) * (nb_tk - msh->cmds.curr_tk) + 1);
	cmd->next = NULL;
	msh->cmds.got_cmd_name = false;
	msh->cmds.curr_arg = 0;
}

static t_cmd	*handle_cmd_separator(t_msh *msh, t_cmd *cmd, t_tokens *tk)
{
	cmd->separator = tk->type;
	tk = tk->next;
	if (!(cmd->next = malloc(sizeof(t_cmd))))
		exit_msh(msh, "malloc: ", strerror(errno));
	cmd->args[msh->cmds.curr_arg] = NULL;
	cmd = cmd->next;
	init_command(msh, cmd);
	return (cmd);
}

static t_tokens	*handle_redir(t_msh *msh, t_cmd *cmd, t_tokens *tk)
{
	if (tk->type == OUT_APPEND)
		return (handle_out_append(msh, cmd, tk));
	else if (tk->type == OUT_OVERWRITE)
		return (handle_out_overwrite(msh, cmd, tk));
	else if (tk->type == INPUT)
		return (handle_out_input(msh, cmd, tk));
	return (NULL);
}

static void		handle_word(t_msh *msh, t_cmd *cmd, t_tokens *tk, t_cmds *cmds)
{
	if (cmds->got_cmd_name == false)
	{
		if (!(cmd->cmd_name = ft_strdup(tk->data)))
			exit_msh(msh, "ft_strdup: ", strerror(errno));
		if (!(cmd->args[cmds->curr_arg] = ft_strdup(cmd->cmd_name)))
			exit_msh(msh, "ft_strdup: ", strerror(errno));
		cmds->curr_arg++;
		cmds->got_cmd_name = true;
	}
	else
	{
		if (!(cmd->args[cmds->curr_arg] = ft_strdup(tk->data)))
			exit_msh(msh, "ft_strdup: ", strerror(errno));
		cmds->curr_arg++;
	}
}

void			create_cmds(t_msh *msh)
{
	t_tokens	*tk;
	t_cmd		*cmd;

	if (!(msh->cmds.head_cmd = ft_calloc(1, sizeof(t_cmd))))
		exit_msh(msh, "malloc: ", strerror(errno));
	tk = msh->head_tk;
	cmd = msh->cmds.head_cmd;
	init_command(msh, cmd);
	while (tk->next)
	{
		if (tk->type == OUT_APPEND || tk->type == OUT_OVERWRITE ||
		tk->type == INPUT)
			tk = handle_redir(msh, cmd, tk);
		else if (tk->type == PIPE || tk->type == SEPARATOR)
			cmd = handle_cmd_separator(msh, cmd, tk);
		else
			handle_word(msh, cmd, tk, &msh->cmds);
		msh->cmds.curr_tk++;
		tk = tk->next;
	}
	cmd->args[msh->cmds.curr_arg] = NULL;
	ft_tknclear(&msh->head_tk, ft_free);
	del_last_empty_node(msh);
}
