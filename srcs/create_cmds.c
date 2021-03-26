/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:55:53 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/26 10:58:37 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		init_command(t_cmd *cmd)
{
	int nb_tk;

	ft_bzero(cmd, sizeof(t_cmd));
	nb_tk = size_token_list(g_msh.head_tk);
	if (!(cmd->args = malloc(sizeof(char*) * (nb_tk - g_msh.cmds.curr_tk) + 1)))
		exit_msh("malloc: ", strerror(errno));
	ft_bzero(cmd->args, sizeof(char*) * (nb_tk - g_msh.cmds.curr_tk) + 1);
	cmd->next = NULL;
	g_msh.cmds.got_cmd_name = false;
	g_msh.cmds.curr_arg = 0;
}

static t_cmd	*handle_cmd_separator(t_cmd *cmd, t_tokens *tk)
{
	cmd->separator = tk->type;
	tk = tk->next;
	if (!(cmd->next = malloc(sizeof(t_cmd))))
		exit_msh("malloc: ", strerror(errno));
	cmd->args[g_msh.cmds.curr_arg] = NULL;
	cmd = cmd->next;
	init_command(cmd);
	return (cmd);
}

static t_tokens	*handle_redir(t_cmd *cmd, t_tokens *tk)
{
	if (tk->type == OUT_APPEND)
		return (handle_out_append(cmd, tk));
	else if (tk->type == OUT_OVERWRITE)
		return (handle_out_overwrite(cmd, tk));
	else if (tk->type == INPUT)
		return (handle_out_input(cmd, tk));
	return (NULL);
}

static void		handle_word(t_cmd *cmd, t_tokens *tk, t_cmds *cmds)
{
	char *tmp; //LAST CHANGE
	
	tmp = NULL;
	if (cmds->got_cmd_name == false)
	{
		tmp = ft_strtrim(tk->data, " "); //LAST CHANGE
		if (!(cmd->cmd_name = ft_strdup(tmp))) //LAST CHANGE
			exit_msh("ft_strdup: ", strerror(errno));
		if (!(cmd->args[cmds->curr_arg] = ft_strdup(cmd->cmd_name)))
			exit_msh("ft_strdup: ", strerror(errno));
		cmds->curr_arg++;
		cmds->got_cmd_name = true;
		free(tmp); //LAST CHANGE
	}
	else
	{
		if (ft_strncmp(cmd->cmd_name, "echo", 5))
			tmp = ft_strtrim(tk->data, " ");
		else
			tmp = ft_strdup(tk->data);
		if (!(cmd->args[cmds->curr_arg] = ft_strdup(tmp)))
			exit_msh("ft_strdup: ", strerror(errno));
		cmds->curr_arg++;
		free(tmp);
	}
}

void			create_cmds(void)
{
	t_tokens	*tk;
	t_cmd		*cmd;

	if (!(g_msh.cmds.head_cmd = malloc(sizeof(t_cmd))))
		exit_msh("malloc: ", strerror(errno));
	tk = g_msh.head_tk;
	cmd = g_msh.cmds.head_cmd;
	init_command(cmd);
	while (tk->next)
	{
		if (tk->type == OUT_APPEND || tk->type == OUT_OVERWRITE ||
		tk->type == INPUT)
			tk = handle_redir(cmd, tk);
		else if (tk->type == PIPE || tk->type == SEPARATOR)
			cmd = handle_cmd_separator(cmd, tk);
		else
			handle_word(cmd, tk, &g_msh.cmds);
		g_msh.cmds.curr_tk++;
		tk = tk->next;
	}
	cmd->args[g_msh.cmds.curr_arg] = NULL;
	ft_tknclear(&g_msh.head_tk, ft_free);
}
