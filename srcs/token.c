/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 22:12:38 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/26 22:33:21 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_tk_state(char c, int *state)
{
	if (!state)
		return (0);
	if (c == '\'' || c == '\"')
	{
		if (*state == 1)
			*state = 0;
		else
			*state = 1;
	}
	return (0);
}

void	handle_escape(char *data, int type)
{
	int		i;

	i = 0;
	if (type == DOUBLE_QUOTE)
	{
		while (data[i])
		{
			if (data[i] == ESCAPE && data[i + 1] == ESCAPE)
				ft_memmove(&data[i], &data[i + 1], ft_strlen(&data[i]));
			i++;
		}
	}
	else if (type == GENERAL)
	{
		while (data[i])
		{
			if (data[i] == ESCAPE)
			{
				ft_memmove(&data[i], &data[i + 1], ft_strlen(&data[i]));
				if (data[i + 1] == ESCAPE)
					i++;
			}
			i++;
		}
	}
}

void	atribute_new_token(t_token **tk, char *input, int i, int len)
{
	char	*data;
	t_token	*new_tk;
	int		type;

	if (len > 0)
	{
		data = ft_substr(input, i, len);
		if (is_tk_char(data[0]))
			type = data[0];
		else
			type = GENERAL;
		handle_escape(data, type);
		new_tk = ft_tkn_new(data, type);
		tkn_add_back(tk, new_tk);
	}
}

t_token	*put_input_into_tkn_lst(char *input)
{
	t_token	*tk;
	int		i;
	int		init_tkn;
	int		quote_state;

	tk = NULL;
	i = 0;
	init_tkn = 0;
	quote_state = false;
	while (input[i])
	{
		get_tk_state(input[i], &quote_state);
		if ((is_job_char(input[i]) || is_space_char(input[i])) && !quote_state)
		{
			atribute_new_token(&tk, input, init_tkn, i - init_tkn);
			if (is_job_char(input[i]))
				atribute_new_token(&tk, input, i, 1);
			init_tkn = i + 1;
		}
		i++;
	}
	atribute_new_token(&tk, input, init_tkn, i - init_tkn);
	return (tk);
}
