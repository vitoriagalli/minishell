/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vs-Rb <marvin@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:58:58 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/22 11:26:59 by Vs-Rb            ###   ########.fr       */
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
	lx->line = ft_strjoin(lx->line, "\n");
	ft_printf("> ");
	while ((read_line()) != 0)
	{
		g_msh.line = ft_strjoin(g_msh.line, "\n");
		lx->line = ft_strjoin(lx->line, g_msh.line);
		if (lx->line[ft_strlen(lx->line) - 2] == to_check)
			break ;
		free(g_msh.line);
		ft_printf("> ");
	}
	free (g_msh.line);
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

void	double_quoted_state(t_tokens *tk, t_lexer *lx)
{
	bool end_quote;
	
	end_quote = false;
	if (lx->line[lx->i] == DOUBLE_QUOTE)
		end_quote = true;
	else if (lx->line[lx->i] == ESCAPE)
		escape_in_double_quote(tk, lx);
	else if (lx->line[lx->i] == DOLLAR)
		evaluate_dollar(tk, lx);
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
		if (lx->line[lx->i] != NEW_LINE)
			lx->i--;
	}	
}
