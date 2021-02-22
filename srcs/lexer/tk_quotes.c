/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:58:58 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/21 20:37:09 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*activate_quoted_state(t_tokens *tk, t_lexer *lx, int type_quote)
{
	tk = create_new_token(tk, lx);
	lx->state = type_quote;
	tk->data[lx->j++] = lx->line[lx->i++];
	tk->type = DOUBLE_QUOTED;
	if (type_quote == STATE_SINGLE_QUOTED)
	{
		tk->eval = false;
		tk->type = SINGLE_QUOTED;
	}
	return (tk);
}

void		get_from_stdin(t_tokens *tk, char to_check)
{
	char	*line;
	int		ret;
	char	quote[2];

	quote[0] = to_check;
	quote[1] = '\0';
	ret = 1;
	while (ret == 1)
	{
		ft_printf("> ");
		if ((ret = get_next_line(STDIN_FILENO, &line)) == -1)
			exit(EXIT_SUCCESS); // To do: a function Clean exit.
		tk->data = ft_strjoin(tk->data, line);
		if (tk->data[ft_strlen(tk->data) - 1] == to_check)
		{
			tk->data = ft_strtrim(tk->data, quote);
			tk->data = ft_strjoin(tk->data, "\n");
			ret = 0;
		}
		free(line);
	}
}

void		escape_in_double_quote(t_tokens *tk, t_lexer *lx)
{
	if (lx->line[lx->i + 1] == DOUBLE_QUOTE)
		tk->data[lx->j++] = lx->line[++lx->i];
	else
		tk->data[lx->j++] = lx->line[lx->i];
	lx->i++;
}

t_tokens	*quoted_state(t_tokens *tk, t_lexer *lx)
{
	int type;

	type = get_char_type(lx->line[lx->i]);
	tk->data[lx->j++] = lx->line[lx->i++];
	tk->type = SINGLE_QUOTED;
	if (type == TYPE_SINGLE_QUOTE)
	{
		tk->data = ft_strtrim(tk->data, "\'");
		if (lx->line[lx->i] == NEW_LINE || lx->line[lx->i] == SPACE)
			tk->data[ft_strlen(tk->data)] = lx->line[lx->i++];
		else
			tk->data[lx->j++] = lx->line[lx->i++];
		tk = create_new_token(tk, lx);
		lx->i--;
	}
	else if (lx->line[lx->i] == '\0')
	{
		get_from_stdin(tk, SINGLE_QUOTE);
		tk->type = SINGLE_QUOTED;
	}
	return (tk);
}

t_tokens	*double_quoted_state(t_tokens *tk, t_lexer *lx, t_env *env)
{
	int type;

	type = get_char_type(lx->line[lx->i]);
	if (lx->line[lx->i] == ESCAPE)
		escape_in_double_quote(tk, lx);
	else
		tk->data[lx->j++] = lx->line[lx->i++];
	tk->type = DOUBLE_QUOTED;
	if (type == TYPE_DOUBLE_QUOTE)
	{
		tk->data = ft_strtrim(tk->data, "\"");
		if (lx->line[lx->i] == NEW_LINE || lx->line[lx->i] == SPACE)
			tk->data[ft_strlen(tk->data)] = lx->line[lx->i++];
		else
			tk->data[lx->j++] = lx->line[lx->i++];
		tk = create_new_token(tk, lx);
		lx->i--;
	}
	else if (lx->line[lx->i] == '\0')
	{
		get_from_stdin(tk, DOUBLE_QUOTE);
		tk->type = DOUBLE_QUOTED;
	}
	return (tk);
}
