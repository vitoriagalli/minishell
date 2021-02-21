/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:29:35 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/21 20:45:47 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_quote_char(int c)
{
	if (c == CHAR_SIMPLE_QUOTE ||
		c == CHAR_DOUBLE_QUOTE)
		return TRUE;
	return FALSE;
}

int		is_space_char(int c)
{
	if (c == CHAR_SPACE ||
		c == CHAR_SPACE)
		return TRUE;
	return FALSE;
}

int		is_job_char(int c)
{
	if (c == CHAR_PIPE ||
		c == CHAR_SEMICOLON ||
		c == CHAR_ESCAPE ||
		c == CHAR_GREATER ||
		c == CHAR_LESSER)
		return TRUE;
	return FALSE;
}

int		is_next_token(int c)
{
	int i;
	int all_tk_type[11] = {CHAR_PIPE, CHAR_SEMICOLON, CHAR_ESCAPE, CHAR_GREATER,
	CHAR_LESSER, CHAR_SPACE, CHAR_TAB};

	i = 0;
	while (i < 11)
	{
		if (c == all_tk_type[i])
			return TRUE;
		i++;
	}
	return FALSE;
}

void	create_tk_atribute_data(int i, int init_tkn, char *input, t_token *tk)
{
	char *data;

	data = ft_substr(input, init_tkn, i - init_tkn);
	if (i > init_tkn)
		tkn_add_back(&tk, ft_tkn_new(data));
}

t_token	*put_input_into_tkn_lst(char *input)
{
	t_token	*tk = NULL;
	int i = 0;
	int init_tkn = 0;
	int quote_state = FALSE;
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
			if (quote_state == TRUE)
				quote_state = FALSE;
			else
				quote_state = TRUE;
		}
		else if (is_next_token(input[i]) && quote_state == FALSE)
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

int lexer(t_minishell *sh)
{

	sh->head = put_input_into_tkn_lst(sh->input);
	// classify_type_of_token();

	ft_tkn_print(sh->head);
	ft_tkn_clear(&sh->head, ft_free);
}
