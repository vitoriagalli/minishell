/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:29:35 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/22 02:00:38 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		is_next_token(int c)
{
	char *tk_types[11] = {CHAR_PIPE, CHAR_SEMICOLON, CHAR_ESCAPE, CHAR_GREATER,
	CHAR_LESSER, CHAR_SPACE, CHAR_TAB};
	int i;

	i = 0;
	while (i < 11)
	{
		if (c == tk_types[i])
			return true;
		i++;
	}
	return false;
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

int lexer(t_shell *sh)
{

	sh->tks = put_input_into_tkn_lst(sh->input);
	ft_tkn_print(sh->tks);
	ft_tkn_clear(&sh->tks, ft_free);
}
