/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:55:29 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/17 19:40:27 by romanbtt         ###   ########.fr       */
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

void	evaluate_dollar(t_tokens *tk, t_lexer *lx)
{	
	int		k;
	char	*temp;
	char	*ret_cmd;
	
	k = lx->i + 1;
	if (lx->line[lx->i + 1] == '?')
	{
		ret_cmd = ft_itoa(g_msh.last_ret_cmd);
		tk->data = ft_strjoin(tk->data, ret_cmd);
		lx->i += 2;
	}	
	else
	{
		while (lx->line[k] != DOLLAR && lx->line[k] != SPACE &&
		lx->line[k] != '\0' && lx->line[k] != ESCAPE &&
		lx->line[k] != DOUBLE_QUOTE && lx->line[k] != ESCAPE &&
		lx->line[k] != SEMICOLON && lx->line[k] != SINGLE_QUOTE &&
		lx->line[k] != '/')
			k++;
		temp = ft_substr(lx->line, lx->i, k - lx->i);
		temp = substitution_env(g_msh.head_env, temp);
		tk->data = ft_strjoin(tk->data, temp);
		lx->i = k;
		free(temp);
	}
}

void	lexer()
{
	t_tokens *tk;

	g_msh.head_tk = malloc(sizeof(t_tokens));
	g_msh.lx = (t_lexer) {0, ft_strlen(g_msh.line), 0, g_msh.line, 10000};
	tk = g_msh.head_tk;
	init_token(tk, &g_msh.lx);
	while (g_msh.lx.line[g_msh.lx.i])
	{
		if (g_msh.lx.state == STATE_GENERAL)
			tk = general_state(tk, &g_msh.lx);
		if (g_msh.lx.state == STATE_SINGLE_QUOTED)
			quoted_state(tk, &g_msh.lx);
		else if (g_msh.lx.state == STATE_DOUBLE_QUOTED)
			double_quoted_state(tk, &g_msh.lx);
	}
	g_msh.head_tk = remove_last_empty_node(g_msh.head_tk);
	add_end_token(g_msh.head_tk, &g_msh.lx);
}
