/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 22:12:38 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/02 21:10:37 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_for_env(t_env *env, char *data)
{
	char	*new_tk_value;
	char	*env_var;
	char	*before_env;
	char	*after_env;

	new_tk_value = NULL;
	env_var = NULL;
	before_env = NULL;
	after_env = NULL;
	while (env)
	{
		env_var = ft_strnstr(data, env->name, ft_strlen(data));
		if (env_var && *(env_var - 1) == '$')
		{
			before_env = ft_substr(data, 0, (env_var - data - 1));
			after_env = ft_substr(env_var, ft_strlen(env->name),
				ft_strlen(env_var) - ft_strlen(env->name));
			new_tk_value = ft_strjoin_n_free(before_env,
				ft_strjoin_n_free(ft_strdup(env->value), after_env));
			return (new_tk_value);
		}
		env = env->next;
	}
	return (NULL);
}

char	*handle_env(char *data, t_env *env)
{
	char	*is_env;

	is_env = check_for_env(env, data);
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
			data = handle_env(data, sh->env);
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
	while (sh->input[*i])
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
