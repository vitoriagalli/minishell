/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:55:29 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/19 16:12:11 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_char_type(char c)
{
	if (c == SINGLE_QUOTE)
		return (TYPE_QUOTE);
	else if (c == DOUBLE_QUOTE)
		return (TYPE_DOUBLE_QUOTE);
	else if (c == VERTICAL_BAR || c == SEMICOLON || c == GREAT || c == LESS)
		return (TYPE_OPERATOR);
	else if (c == SPACE || c == TAB || c == NEW_LINE)
		return (TYPE_SPACE);
	else if (c == ESCAPE)
		return (TYPE_ESCAPE);
	else
		return (TYPE_GENERAL);
}

void	put_in_token_word(t_tokens *tk, t_lexer *lx)
{
	tk->data[lx->j++] = lx->line[lx->i];
	tk->type = WORD;
}

t_tokens	*put_in_token_operator(t_tokens *tk, t_lexer *lx)
{
	if (tk->data[0] != '\0')
		tk = create_new_token(tk, lx);
	if (lx->line[lx->i] == GREAT && lx->line[lx->i + 1] == GREAT)
	{
		tk->data[lx->j++] = lx->line[lx->i++];
		tk->data[lx->j++] = lx->line[lx->i];
	}
	else
		tk->data[lx->j++] = lx->line[lx->i];
	tk->type = OPERATOR;
	tk = create_new_token(tk, lx);
	return (tk);
}

void	activate_quoted_state(t_tokens *tk, t_lexer *lx, int type_quote)
{
	lx->state = type_quote;
//	tk->data[lx->j++] = lx->line[lx->i++];
}

t_tokens	*general_state(t_tokens *tk, t_lexer *lx)
{
	if (lx->type == TYPE_QUOTE)
		activate_quoted_state(tk, lx, STATE_SINGLE_QUOTED);
	else if (lx->type == TYPE_DOUBLE_QUOTE)
		activate_quoted_state(tk, lx, STATE_DOUBLE_QUOTED);
	else if (lx->type == TYPE_OPERATOR)
		tk = put_in_token_operator(tk, lx);
	else if (lx->type == TYPE_SPACE)
		tk = create_new_token(tk, lx);
	else if (lx->type == TYPE_ESCAPE)
		lx->state = STATE_BACKSLASHED;
	else
		put_in_token_word(tk, lx);
	return (tk);
}

void backslashed_state(t_tokens *tk, t_lexer *lx)
{
	int type_plus_one;

	type_plus_one = get_char_type(lx->line[lx->i + 1]);
	if (type_plus_one == TYPE_SPACE)
		lx->state = STATE_GENERAL;
	tk->data[lx->j++] = lx->line[lx->i];
	tk->type = BACKSLASHED;
}

void get_from_stdin(t_tokens *tk, char to_check)
{
	char *line;
	int ret;

	ret = 1;
	tk->data = ft_strjoin(tk->data, "\n");
	while (ret == 1)
	{
		ft_printf("> ");
		if ((ret = get_next_line(STDIN_FILENO, &line)) == -1)
			exit(EXIT_SUCCESS); // To do: a function Clean exit.
		line = ft_strjoin(line, "\n");
		tk->data = ft_strjoin(tk->data, line);
		if (tk->data[ft_strlen(tk->data) - 2] == to_check)
			ret = 0;
		free(line);
	}
}

void quoted_state(t_tokens *tk, t_lexer *lx)
{
	int type;

	tk->data[lx->j++] = lx->line[lx->i++];
	tk->type = SINGLE_QUOTED;
	type = get_char_type(lx->line[lx->i]);
	if (type == TYPE_QUOTE)
		lx->state = STATE_GENERAL;
	else if (type == TYPE_SPACE || lx->line[lx->i] == '\0')
	{
		get_from_stdin(tk, SINGLE_QUOTE);
		tk->type = SINGLE_QUOTED;
		return ;
	}	
	tk->data[lx->j++] = lx->line[lx->i];
	tk->type = SINGLE_QUOTED;


}

void double_quoted_state(t_tokens *tk, t_lexer *lx)
{
	int type;

	tk->data[lx->j++] = lx->line[lx->i++];
	tk->type = DOUBLE_QUOTED;
	type = get_char_type(lx->line[lx->i]);
	if (type == TYPE_DOUBLE_QUOTE)
		lx->state = STATE_GENERAL;
	else if (type == TYPE_SPACE || lx->line[lx->i] == '\0')
	{
		get_from_stdin(tk, DOUBLE_QUOTE);
		tk->type = DOUBLE_QUOTED;
		return ;
	}	
}

void	lexer(t_minishell *msh)
{	
	t_tokens *tk;
	
	msh->head_tk = malloc(sizeof(t_tokens));
	msh->lx = (t_lexer) {0, 0, ft_strlen(msh->line), 0, msh->line, 10000};
	tk = msh->head_tk;
	init_token(tk, &msh->lx);
	while (msh->line[msh->lx.i])
	{
		msh->lx.type = get_char_type(msh->lx.line[msh->lx.i]);
		if (msh->lx.state == STATE_GENERAL)
			tk = general_state(tk, &msh->lx);
		if (msh->lx.state == STATE_BACKSLASHED)
			backslashed_state(tk, &msh->lx);
		if (msh->lx.state == STATE_SINGLE_QUOTED)
			quoted_state(tk, &msh->lx);
		else if (msh->lx.state == STATE_DOUBLE_QUOTED)
			double_quoted_state(tk, &msh->lx);
		if (msh->lx.state == STATE_GENERAL)
			msh->lx.i++;
	}
}