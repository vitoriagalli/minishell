/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:58:58 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/27 17:00:52 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	activate_quoted_state(t_tokens *tk, t_lexer *lx, int type_quote)
{
	lx->state = type_quote;
	lx->i++;
	tk->type = WORD;
}

void	get_from_stdin(t_lexer *lx, char to_check)
{
	char	*line;
	int		ret;

	ret = 1;
	lx->line = ft_strjoin(lx->line, "\n");
	while (ret == 1)
	{
		ft_printf("> ");
		if ((ret = get_next_line(STDIN_FILENO, &line)) == -1)
			exit(EXIT_SUCCESS); // To do: a function Clean exit.
		line = ft_strjoin(line, "\n");
		lx->line = ft_strjoin(lx->line, line);
		if (lx->line[ft_strlen(lx->line) - 2] == to_check)
			ret = 0;
		free(line);
	}
	lx->line[ft_strlen(lx->line) - 1] = '\0';
}


void	quoted_state(t_tokens *tk, t_lexer *lx)
{
	bool end_quote;
	
	end_quote = false;
	if (lx->line[lx->i] == SINGLE_QUOTE)
		end_quote = true;
	else
		tk->data[ft_strlen(tk->data)] = lx->line[lx->i++];
	if (end_quote == true)
	{
		lx->state = STATE_GENERAL;
		lx->i++;
	}
	else if (lx->line[lx->i] == '\0')
	{
		get_from_stdin(lx, SINGLE_QUOTE);
		lx->i--;
	}	
}

void	double_quoted_state(t_tokens *tk, t_lexer *lx, t_minishell *msh)
{
	bool end_quote;
	
	end_quote = false;
	if (lx->line[lx->i] == DOUBLE_QUOTE)
		end_quote = true;
	else if (lx->line[lx->i] == ESCAPE)
		escape_in_double_quote(tk, lx);
	else if (lx->line[lx->i] == DOLLAR)
		evaluate_dollar(tk, lx, msh);
	else
		tk->data[ft_strlen(tk->data)] = lx->line[lx->i++];
	if (end_quote == true)
	{
		lx->state = STATE_GENERAL;
		lx->i++;
	}
	else if (lx->line[lx->i] == '\0')
	{
		get_from_stdin(lx, DOUBLE_QUOTE);
		lx->i--;
	}	
}
