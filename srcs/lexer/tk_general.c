/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_general.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:02:49 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 13:57:26 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_tild_lexer(t_msh *msh, t_tokens *tk, t_lexer *lx)
{
	char **path_home;

	if ((lx->line[lx->i + 1] == ' ' || lx->line[lx->i + 1] == '/' ||
	lx->line[lx->i + 1] == 0) && (lx->i == 0 || lx->line[lx->i - 1] == ' '))
	{
		path_home = get_env_value(msh, "HOME");
		if (!path_home[0])
			return ;
		tk->data = ft_strjoin_realloc(msh, tk->data, path_home[0]);
		ft_array_clear(path_home, ft_free);
	}
	else
		tk->data[ft_strlen(tk->data)] = lx->line[lx->i];
	lx->i++;
}

static int	get_char_type(char c)
{
	if (c == SINGLE_QUOTE)
		return (TYPE_SINGLE_QUOTE);
	else if (c == DOUBLE_QUOTE)
		return (TYPE_DOUBLE_QUOTE);
	else if (c == VERTICAL_BAR || c == SEMICOLON || c == GREAT || c == LESS)
		return (TYPE_OPERATOR);
	else if (c == SPACE || c == TAB || c == '\0')
		return (TYPE_SPACE);
	else if (c == DOLLAR)
		return (TYPE_DOLLAR);
	else if (c == ESCAPE)
		return (TYPE_ESCAPE);
	else
		return (TYPE_GENERAL);
}

static void	put_in_token_word(t_msh *msh, t_tokens *tk, t_lexer *lx)
{
	if (lx->line[lx->i] == DOLLAR)
		evaluate_dollar(msh, tk, lx);
	else if (lx->line[lx->i] == TILD)
		replace_tild_lexer(msh, tk, lx);
	else
		tk->data[ft_strlen(tk->data)] = lx->line[lx->i++];
	tk->type = WORD;
}

t_tokens	*general_state(t_msh *msh, t_tokens *tk, t_lexer *lx)
{
	lx->type = get_char_type(lx->line[lx->i]);
	if (lx->type == TYPE_SINGLE_QUOTE)
		activate_quoted_state(tk, lx, STATE_SINGLE_QUOTED);
	else if (lx->type == TYPE_DOUBLE_QUOTE)
		activate_quoted_state(tk, lx, STATE_DOUBLE_QUOTED);
	else if (lx->type == TYPE_OPERATOR)
		tk = put_in_token_operator(msh, tk, lx);
	else if (lx->type == TYPE_SPACE)
		tk = create_new_token(msh, tk, lx);
	else if (lx->type == TYPE_ESCAPE)
		handle_escape_in_general(tk, lx);
	else
		put_in_token_word(msh, tk, lx);
	return (tk);
}
