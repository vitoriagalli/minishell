/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:54:34 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/24 21:46:51 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_separator(int type_left)
{
	if (type_left == 0 || type_left == OUT_OVERWRITE || type_left == PIPE ||
	type_left == OUT_APPEND || type_left == INPUT || type_left == SEPARATOR)
		return (false);
	return (true);
}

int	check_from_end(int type_left)
{
	if (type_left == OUT_OVERWRITE || type_left == OUT_APPEND ||
	type_left == INPUT || type_left == PIPE)
		return (false);
	return (true);
}

int check_redirection(int type_left)
{
	if (type_left == OUT_OVERWRITE || type_left == OUT_APPEND ||
	type_left == INPUT)
		return (false);
	return (true);
}

bool	syntax_parser(t_tokens *tk)
{
	int		type_left;
	int		syntax_ok;

	type_left = 0;
	syntax_ok = true;
	while (tk)
	{
		if (tk->type == PIPE || tk->type == SEPARATOR)
			syntax_ok = check_separator(type_left);
		else if (tk->type == OUT_APPEND || tk->type == OUT_OVERWRITE ||
		tk->type == INPUT)
			syntax_ok = check_redirection(type_left);
		else if (tk->type == END)
			syntax_ok = check_from_end(type_left);
		if (syntax_ok == false)
		{
			ft_printf("minishell: syntax error near unexpected token `%s'\n", tk->data);
			return (0);
		}	
		type_left = tk->type;
		tk = tk->next;
	}
	return (true);
}