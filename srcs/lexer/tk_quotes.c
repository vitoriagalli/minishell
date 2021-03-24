/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:58:58 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/24 15:55:48 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	activate_quoted_state(t_tokens *tk, t_lexer *lx, int type_quote)
{
	lx->state = type_quote;
	lx->i++;
	tk->type = WORD;
}

static void	get_from_stdin(t_lexer *lx, t_tokens *tk, char to_check)
{
	char *tmp;
	char *tmp2;
	
	//lx->line = ft_strjoin(lx->line, "\n");
	tmp = ft_strjoin(tk->data, "\n");
	ft_strdel(&lx->line);
	ft_printf("> ");
	while ((read_line(false)) != 0)
	{
		//g_msh.line = ft_strjoin(g_msh.line, "\n");
		tmp2 = ft_strjoin(g_msh.line, "\n");
		lx->line = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		tmp = ft_strdup(lx->line);
		if (lx->line[ft_strlen(lx->line) - 2] == to_check)
			break ;
		ft_strdel(&lx->line);
		//free(g_msh.line);
		ft_printf("> ");
	}
	ft_strdel(&g_msh.line);
	lx->line[ft_strlen(lx->line) - 1] = '\0';
	lx->size = ft_strlen(lx->line);
	free(tmp);
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
		lx->state = STATE_GEN;
		lx->i++;
	}
	else if (lx->line[lx->i] == '\0')
	{
		get_from_stdin(lx, tk, SINGLE_QUOTE);
		free(tk->data);
		tk->data = malloc(sizeof(char) * lx->size + 1);
		ft_bzero(tk->data, lx->size + 1);
		lx->i = 0;
		//lx->i--;
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
		lx->state = STATE_GEN;
		lx->i++;
	}
	else if (lx->line[lx->i - 1] == '\0')
	{
		get_from_stdin(lx, tk, DOUBLE_QUOTE);
		free(tk->data);
		tk->data = malloc(sizeof(char) * lx->size + 1);
		ft_bzero(tk->data, lx->size + 1);
		lx->i = 0;
		//if (lx->line[lx->i] != NEW_LINE)
		//	lx->i--;
	}	
}
