/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:55:29 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/21 20:40:03 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			tk = quoted_state(tk, &msh->lx);
		else if (msh->lx.state == STATE_DOUBLE_QUOTED)
			tk = double_quoted_state(tk, &msh->lx, msh->head_env);
		else if (msh->lx.state == STATE_GENERAL)
			msh->lx.i++;
	}
}
