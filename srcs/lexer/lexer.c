/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:55:29 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/28 00:04:46 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *substitution_env(t_env *env, char *str)
{
	char *temp;
	
	if (str[1] == '\0')
	{
		temp = ft_strdup("$");
		return (temp);
	}	
	while (env->next)
	{
		if (!ft_strncmp(env->name, str + 1, ft_strlen(str) + 1))
		{
			temp = ft_strdup(env->value);
			return (temp); //PROBABLE LEAK
		}	
		env = env->next;
	}
	temp = ft_strdup("");
	return (temp);
}

void	evaluate_dollar(t_tokens *tk, t_lexer *lx, t_minishell *msh)
{	
	int		k;
	char	*temp;
	char	*ret_cmd;
	
	k = lx->i + 1;
	if (lx->line[lx->i + 1] == '?')
	{
		ret_cmd = ft_itoa(msh->last_ret_cmd);
		tk->data = ft_strjoin(tk->data, ret_cmd);
		lx->i += 2;
	}	
	else
	{
		while (lx->line[k] != DOLLAR && lx->line[k] != SPACE &&
		lx->line[k] != '\0' && lx->line[k] != ESCAPE &&
		lx->line[k] != DOUBLE_QUOTE)
			k++;
		temp = ft_substr(lx->line, lx->i, k - lx->i);
		temp = substitution_env(msh->head_env, temp);
		tk->data = ft_strjoin(tk->data, temp);
		lx->i = k;
		free(temp);
	}
}

void	lexer(t_minishell *msh)
{
	t_tokens *tk;

	msh->head_tk = malloc(sizeof(t_tokens));
	msh->lx = (t_lexer) {0, ft_strlen(msh->line), 0, msh->line, 10000};
	tk = msh->head_tk;
	init_token(tk, &msh->lx);
	while (msh->lx.line[msh->lx.i])
	{
		if (msh->lx.state == STATE_GENERAL)
			tk = general_state(tk, &msh->lx, msh);
		if (msh->lx.state == STATE_SINGLE_QUOTED)
			quoted_state(tk, &msh->lx);
		else if (msh->lx.state == STATE_DOUBLE_QUOTED)
			double_quoted_state(tk, &msh->lx, msh);
	}
	msh->head_tk = remove_last_empty_node(msh->head_tk);
	add_end_token(msh->head_tk, &msh->lx);
}
