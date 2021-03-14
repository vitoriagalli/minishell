/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 22:12:38 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/14 19:02:31 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_for_env(char *data)
{
	char	*new;
	char	*env_var;
	char	*key;
	char	*value;
	int		i;

	env_var = NULL;
	key = NULL;
	value = NULL;
	i = 0;
	while (g_env[i])
	{
		store_key_and_value(&value, &key, g_env[i]);
		env_var = ft_strnstr(data, key, ft_strlen(data));
		if (env_var && *(env_var - 1) == '$')
		{
			new = subst_value(data, env_var, key, value);
			free(key);
			free(value);
			return (new);
		}
		i++;
	}
	return (NULL);
}

char	*handle_dollar_sign(char *data, int exit_status)
{
	char	*new;
	char	*addr;

	addr = ft_strnstr(data, "$?", ft_strlen(data));
	if (addr)
	{
		new = subst_value(data, addr, ft_strdup("$?"), ft_itoa(exit_status));
		free(data);
		data = new;
		new = NULL;
	}
	new = check_for_env(data);
	if (new != NULL)
	{
		free(data);
		return (new);
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

void	remove_quotes(char *str, int type)
{
	int	len;
	int	i;

	if (!is_quote_char(type))
		return ;
	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == type)
		{
			ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i + 1]));
			str[len - 1] = '\0';
			len--;
		}
		i++;
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
		data = ft_substr(sh->input, i, len);
		i = 0;
		type = GENERAL;
		while (data[i++])
		{
			if (is_quote_char(data[i]))
			{
				type = data[i];
				break;
			}
		}
		remove_quotes(data, type);
		handle_escape(data, type);
		if (type != SIMPLE_QUOTE)
			data = handle_dollar_sign(data, sh->status);
		new_tk = ft_lstnew(data);
		ft_lstadd_back(tk, new_tk);
	}
}

t_list	*args_lst(int *i, int *init_tkn, int *sep)
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
