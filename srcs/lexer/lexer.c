/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vs-Rb <marvin@student.42sp.org.br>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:55:29 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/21 20:48:35 by Vs-Rb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*strjoin;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!(strjoin = malloc(sizeof(char) * (lens1 + lens2 + 1))))
		return (NULL);
	ft_memcpy(strjoin, s1, lens1);
	ft_memcpy(&strjoin[lens1], s2, lens2);
	strjoin[lens1 + lens2] = '\0';
	free(s1);
	free(s2);
	return (strjoin);
}

char	*subst_value(char *data, char *env_var, char *name, char *value)
{
	char	*new_tk_value;
	char	*before_env;
	char	*after_env;

	new_tk_value = NULL;
	before_env = NULL;
	after_env = NULL;
	if ((env_var - data - 1) > 0)
		before_env = ft_substr(data, 0, (env_var - data - 1));
	if ((ft_strlen(env_var) - ft_strlen(name)) > 0)
		after_env = ft_substr(env_var, ft_strlen(name),
			ft_strlen(env_var) - ft_strlen(name));
	if (before_env)
		new_tk_value = ft_strjoin_and_free(before_env, ft_strdup(value));
	else
		new_tk_value = ft_strdup(value);
	if (after_env)
		new_tk_value = ft_strjoin_and_free(new_tk_value, after_env);
	return (new_tk_value);
}

static char *substitution_env(char *str)
{
	char	*temp;
	char	*env_var;
	char	*value;
	char	*key;
	int		i;

	if (str[1] == '\0')
	{
		temp = ft_strdup("$");
		return (temp);
	}
	while (g_msh.env[i])
	{
		store_key_and_value(&value, &key, g_msh.env[i]);
		env_var = ft_strnstr(str, key, ft_strlen(str));
		if (env_var && *(env_var - 1) == '$')
		{
			temp = subst_value(str, env_var, key, value);
			free(key);
			free(value);
			return (temp);
		}
		i++;
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
		temp = substitution_env(temp);
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
