/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:20:53 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/14 17:17:17 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_tk_char(int c)
{
	if (c == PIPE ||
		c == SEMICOLON ||
		c == GREATER ||
		c == LESSER ||
		c == SPACE ||
		c == TAB)
		return (true);
	return (false);
}

int		is_quote_char(int c)
{
	if (c == SIMPLE_QUOTE ||
		c == DOUBLE_QUOTE)
		return (true);
	return (false);
}

void	store_key_and_value(char **value, char **key, char *str)
{
	char *addr;

	addr = ft_strrchr(str, '=');
	*key = ft_substr(str, 0, addr - str);
	*value = ft_substr(str, addr - str + 1,
	ft_strlen(str) - (addr - str));
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
		new_tk_value = ft_strjoin_n_free(before_env, ft_strdup(value));
	else
		new_tk_value = ft_strdup(value);
	if (after_env)
		new_tk_value = ft_strjoin_n_free(new_tk_value, after_env);
	return (new_tk_value);
}
