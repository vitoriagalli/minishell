/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:58:58 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 11:59:30 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		activate_quoted_state(t_tokens *tk, t_lexer *lx, int type_quote)
{
	lx->state = type_quote;
	lx->i++;
	tk->type = WORD;
}

static void	get_from_stdin(t_msh *msh, t_lexer *lx, t_tokens *tk, char to_check)
{
	char *tmp;
	char *tmp2;

	if (!(tmp = ft_strjoin(tk->data, "\n")))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	ft_strdel(&lx->line);
	while ((read_line(msh, false)) != 0)
	{
		if (!(tmp2 = ft_strjoin(g_stream.line, "\n")))
			exit_msh(msh, "ft_strjoin: ", strerror(errno));
		if (!(lx->line = ft_strjoin(tmp, tmp2)))
			exit_msh(msh, "ft_strjoin: ", strerror(errno));
		free(tmp);
		free(tmp2);
		if (!(tmp = ft_strdup(lx->line)))
			exit_msh(msh, "ft_strdup: ", strerror(errno));
		if (lx->line[ft_strlen(lx->line) - 2] == to_check)
			break ;
		ft_strdel(&lx->line);
	}
	ft_strdel(&g_stream.line);
	lx->line[ft_strlen(lx->line) - 1] = '\0';
	lx->size = ft_strlen(lx->line);
	free(tmp);
}

void		quoted_state(t_msh *msh, t_tokens *tk, t_lexer *lx)
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
		get_from_stdin(msh, lx, tk, SINGLE_QUOTE);
		free(tk->data);
		if (!(tk->data = malloc(sizeof(char) * lx->size + 1)))
			exit_msh(msh, "malloc: ", strerror(errno));
		ft_bzero(tk->data, lx->size + 1);
		lx->i = 0;
	}
}

void		double_quoted_state(t_msh *msh, t_tokens *tk, t_lexer *lx)
{
	bool end_quote;

	end_quote = false;
	if (lx->line[lx->i] == DOUBLE_QUOTE)
		end_quote = true;
	else if (lx->line[lx->i] == ESCAPE)
		escape_in_double_quote(tk, lx);
	else if (lx->line[lx->i] == DOLLAR)
		evaluate_dollar(msh, tk, lx);
	else
		tk->data[ft_strlen(tk->data)] = lx->line[lx->i++];
	if (end_quote == true)
	{
		lx->state = STATE_GEN;
		lx->i++;
	}
	else if (lx->line[lx->i - 1] == '\0')
	{
		get_from_stdin(msh, lx, tk, DOUBLE_QUOTE);
		free(tk->data);
		if (!(tk->data = malloc(sizeof(char) * lx->size + 1)))
			exit_msh(msh, "malloc: ", strerror(errno));
		ft_bzero(tk->data, lx->size + 1);
		lx->i = 0;
	}
}
