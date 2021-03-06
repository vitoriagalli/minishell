/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 22:12:38 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/06 03:44:59 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_value_and_name(char **value, char **name, int i)
{
	char *addr;

	addr = ft_strrchr(g_env[i], '=');
	*name = ft_substr(g_env[i], 0, addr - g_env[i]);
	*value = ft_substr(g_env[i], addr - g_env[i] + 1,
	ft_strlen(g_env[i]) - (addr - g_env[i]));
}

char	*substitute_value(char *data, char *env_var, char *name, char *value)
{
	char	*new_tk_value;
	char	*before_env;
	char	*after_env;

	new_tk_value = NULL;
	before_env = ft_substr(data, 0, (env_var - data - 1));
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

char	*check_for_env(char *data)
{
	char	*env_var;
	char	*name;
	char	*value;
	int		i;

	env_var = NULL;
	name = NULL;
	value = NULL;
	i = 0;
	while (g_env[i])
	{
		store_value_and_name(&value, &name, i);
		env_var = ft_strnstr(data, name, ft_strlen(data));
		if (env_var && *(env_var - 1) == '$')
			return (substitute_value(data, env_var, name, value));
		i++;
	}
	return (NULL);
}

char	*handle_env(char *data)
{
	char	*is_env;

	is_env = check_for_env(data);
	if (is_env != NULL)
	{
		free(data);
		return (is_env);
	}
	return (data);
}

void	get_tk_state(char c, int *state)
{
	if (!state)
		return ;
	if (is_quote_char(c))
	{
		if (*state == 1)
			*state = 0;
		else
			*state = 1;
	}
}

void	handle_escape(char *data, int type)
{
	int		i;

	i = 0;
	if (type == DOUBLE_QUOTE)
	{
		while (data[i])
		{
			if (data[i] == ESCAPE && data[i + 1] == ESCAPE)
				ft_memmove(&data[i], &data[i + 1], ft_strlen(&data[i]));
			i++;
		}
	}
	else if (type == GENERAL)
	{
		while (data[i])
		{
			if (data[i] == ESCAPE)
			{
				ft_memmove(&data[i], &data[i + 1], ft_strlen(&data[i]));
				if (data[i + 1] == ESCAPE)
					i++;
			}
			i++;
		}
	}
}

void	atribute_new_list(t_shell *sh, t_list **tk, int i, int len)
{
	char	*data;
	t_list	*new_tk;
	int		type;

	data = NULL;
	new_tk = NULL;
	if (len > 0)
	{
		if (is_tk_char(sh->input[i]))
			type = sh->input[i];
		else
			type = GENERAL;
		if (type == SIMPLE_QUOTE || type == DOUBLE_QUOTE)
			data = ft_substr(sh->input, i + 1, len - 2);
		else
			data = ft_substr(sh->input, i, len);
		handle_escape(data, type);
		if (type != SIMPLE_QUOTE)
			data = handle_env(data);
		new_tk = ft_lstnew(data);
		ft_lstadd_back(tk, new_tk);
	}
}

t_list	*args_lst(t_shell *sh, int *i, int *init_tkn, int *sep)
{
	t_list	*tk;
	int		quote_state;

	tk = NULL;
	quote_state = false;
	while (sh->input[(*i)])
	{
		get_tk_state(sh->input[*i], &quote_state);
		if (is_tk_char(sh->input[*i]) && !quote_state)
		{
			if (*init_tkn != *i)
				atribute_new_list(sh, &tk, *init_tkn, *i - *init_tkn);
			if (sh->input[*i] == GREATER || sh->input[*i] == LESSER)
				atribute_new_list(sh, &tk, *i, 1);
			if (sh->input[*i] == PIPE || sh->input[*i] == SEMICOLON)
			{
				*sep = sh->input[*i];
				*init_tkn = *i + 1;
				(*i)++;
				return (tk);
			}
			*init_tkn = *i + 1;
		}
		(*i)++;
	}
	atribute_new_list(sh, &tk, *init_tkn, *i - *init_tkn);
	*sep = sh->input[*i];
	return (tk);
}

t_token	*put_input_into_tkn_struct(t_shell *sh)
{
	t_token	*tk;
	int		i;
	int		init_tkn;
	int		sep;

	tk = NULL;
	i = 0;
	init_tkn = 0;
	sep = 0;
	while (sh->input[i])
		tkn_add_back(&tk, ft_tkn_new(args_lst(sh, &i, &init_tkn, &sep), sep));
	return (tk);
}
