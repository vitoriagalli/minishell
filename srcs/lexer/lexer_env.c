/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:17:51 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 22:37:55 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_and_free(char *s1, char *s2)
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

static char	*before_envp(char *before_env, char *value)
{
	char	*new_tk_value;
	char	*temp;

	new_tk_value = NULL;
	if (before_env)
	{
		if (!(temp = ft_strdup(value)))
			exit_msh("ft_strdup: ", strerror(errno));
		new_tk_value = ft_strjoin_and_free(before_env, temp);
		free(temp);
	}
	else if (!before_env)
		if (!(new_tk_value = ft_strdup(value)))
			exit_msh("ft_strdup: ", strerror(errno));
	return (new_tk_value);
}

static char	*subst_value(char *data, char *env_var, char *name, char *value)
{
	char	*new_tk_value;
	char	*before_env;
	char	*after_env;

	new_tk_value = NULL;
	before_env = NULL;
	after_env = NULL;
	if ((env_var - data - 1) > 0)
		if (!(before_env = ft_substr(data, 0, (env_var - data - 1))))
			exit_msh("ft_substr: ", strerror(errno));
	if ((ft_strlen(env_var) - ft_strlen(name)) > 0)
		if (!(after_env = ft_substr(env_var, ft_strlen(name),
		ft_strlen(env_var) - ft_strlen(name))))
			exit_msh("ft_strdup: ", strerror(errno));
	new_tk_value = before_envp(before_env, value);
	if (after_env)
		new_tk_value = ft_strjoin_and_free(new_tk_value, after_env);
	return (new_tk_value);
}

static char	*return_dollar_or_nothing(bool dollar)
{
	char *temp;

	if (dollar == true)
	{
		if (!(temp = ft_strdup("$")))
			exit_msh("ft_strdup: ", strerror(errno));
		return (temp);
	}
	else
	{
		if (!(temp = ft_strdup("")))
			exit_msh("ft_strdup: ", strerror(errno));
		return (temp);
	}
}

char		*substitution_env(char *str)
{
	char	*temp;
	char	*env_var;
	char	*value;
	char	*key;
	int		i;

	i = 0;
	if (str[1] == '\0')
		return (return_dollar_or_nothing(true));
	while (g_msh.env[i])
	{
		store_key_and_value(&value, &key, g_msh.env[i++]);
		env_var = ft_strnstr(str, key, ft_strlen(str));
		if (env_var && *(env_var - 1) == '$')
		{
			temp = subst_value(str, env_var, key, value);
			ft_strdel(&value);
			ft_strdel(&key);
			return (temp);
		}
		ft_strdel(&value);
		ft_strdel(&key);
	}
	return (return_dollar_or_nothing(false));
}
