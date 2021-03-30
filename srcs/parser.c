/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:17:37 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 11:50:25 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_separator(int type_left)
{
	if (type_left == 0 || type_left == OUT_OVERWRITE || type_left == PIPE ||
	type_left == OUT_APPEND || type_left == INPUT || type_left == SEPARATOR)
		return (false);
	return (true);
}

static int	check_from_end(int type_left)
{
	if (type_left == OUT_OVERWRITE || type_left == OUT_APPEND ||
	type_left == INPUT || type_left == PIPE)
		return (false);
	return (true);
}

static int	check_redirection(int type_left)
{
	if (type_left == OUT_OVERWRITE || type_left == OUT_APPEND ||
	type_left == INPUT)
		return (false);
	return (true);
}

static bool	dispatch_checker_function(t_tokens *tk, int type_left)
{
	bool syntax_ok;

	syntax_ok = true;
	if (tk->type == PIPE || tk->type == SEPARATOR)
		syntax_ok = check_separator(type_left);
	else if (tk->type == OUT_APPEND || tk->type == OUT_OVERWRITE ||
	tk->type == INPUT)
		syntax_ok = check_redirection(type_left);
	else if (tk->type == END)
		syntax_ok = check_from_end(type_left);
	return (syntax_ok);
}

bool		parser(t_msh *msh)
{
	t_tokens	*tk;
	int			type_left;
	int			syntax_ok;

	tk = msh->head_tk;
	type_left = 0;
	while (tk)
	{
		if (tk->data[0] == '\0')
			return (false);
		syntax_ok = dispatch_checker_function(tk, type_left);
		if (syntax_ok == false)
		{
			ft_printf("minishell: syntax error near unexpected token `%s'\n",
				tk->data);
			g_stream.exit_status = 2;
			return (false);
		}
		type_left = tk->type;
		tk = tk->next;
	}
	return (true);
}
