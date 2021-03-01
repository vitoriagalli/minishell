/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 22:12:38 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/01 03:39:10 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_tk_state(char c, int *state)
{
	if (!state)
		return ;
	if (is_quote_char(c))
	{
		if (*state == 1)
			*state = 0;
		else
			*state = 1;
	}
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

void	atribute_new_list(t_list **tk, char *input, int i, int len)
{
	char	*data;
	t_list	*new_tk;
	int		type;

	data = NULL;
	new_tk = NULL;
	if (len > 0)
	{
		if (is_tk_char(input[i]))
			type = input[i];
		else
			type = GENERAL;
		if (type == SIMPLE_QUOTE || type == DOUBLE_QUOTE)
			data = ft_substr(input, i + 1, len - 2);
		else
			data = ft_substr(input, i, len);
		handle_escape(data, type);
		new_tk = ft_lstnew(data);
		ft_lstadd_back(tk, new_tk);
	}
}

t_list	*args_lst(char *input, int *i, int *init_tkn, int *sep)
{
	t_list	*tk;
	int		quote_state;

	tk = NULL;
	quote_state = false;
	while (input[*i])
	{
		get_tk_state(input[*i], &quote_state);
		if ((is_job_char(input[*i]) || is_space_char(input[*i])) && !quote_state)
		{
			atribute_new_list(&tk, input, *init_tkn, *i - *init_tkn);
			*init_tkn = *i + 1;
			if (is_job_char(input[*i]))
			{
				(*i)++;
				*sep = input[*i];
				return(tk);
			}
		}
		(*i)++;
	}
	atribute_new_list(&tk, input, *init_tkn, *i - *init_tkn);
	return (tk);
}

t_token	*put_input_into_tkn_lst(t_shell *sh)
{
	t_token	*tk = NULL;
	t_list	*args = NULL;
	int		i = 0;
	int		init_tkn = 0;
	int		sep = 0;

	while (sh->input[i])
	{
		args = ft_tkn_new(args_lst(sh->input, &i, &init_tkn, &sep), sep);
		tkn_add_back(&tk, args);
	}
	return(tk);
}
