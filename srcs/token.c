/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 22:12:38 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/25 22:13:29 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_next_token(int c)
{
	char	*tk_types[6] = {PIPE, SEMICOLON, GREATER,
	LESSER, SPACE, TAB};
	int i;

	i = 0;
	while (i < 6)
	{
		if (c == tk_types[i])
			return (true);
		i++;
	}
	return (false);
}

t_token	*put_input_into_tkn_lst(char *input)
{
	t_token	*tk = NULL;
	int i = 0;
	int init_tkn = 0;
	int quote_state = false;
	char *data;

	while (1)
	{
		if (!input[i])
		{
			if (i > init_tkn)
				tkn_add_back(&tk, ft_tkn_new(ft_substr(input, init_tkn, i - init_tkn)));
			return (tk);
		}
		else if (is_quote_char(input[i]))
		{
			if (quote_state == true)
				quote_state = false;
			else
				quote_state = true;
		}
		else if (is_next_token(input[i]) && quote_state == false)
		{
			if (i > init_tkn)
				tkn_add_back(&tk, ft_tkn_new(ft_substr(input, init_tkn, i - init_tkn)));
			if (is_job_char(input[i]))
				tkn_add_back(&tk, ft_tkn_new(ft_substr(input, i, 1)));
			init_tkn = i + 1;
		}
		i++;
	}
}
