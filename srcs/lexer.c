/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 22:48:01 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/07 16:35:54 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*put_input_into_tkn_struct(void)
{
	t_token	*head_tk;
	int		i;
	int		init_tkn;
	int		sep;

	head_tk = NULL;
	i = 0;
	init_tkn = 0;
	sep = 0;
	while (sh->input[i])
		tkn_add_back(&head_tk, ft_tkn_new(args_lst(&i, &init_tkn, &sep), sep));
	return (head_tk);
}

t_cmd	*transform_tkn_into_cmds(void)
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

int		lexer(void)
{
	sh->tk = put_input_into_tkn_struct();
	sh->cmd = transform_tkn_into_cmds();
	// ft_tkn_print(sh->tk);
	// ft_cmd_print(sh->cmd);
	return (0);
}
