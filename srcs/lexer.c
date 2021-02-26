/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:29:35 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/26 20:31:15 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*put_env_into_lst(char **env_content)
{
	t_env	*env = NULL;
	char	**split;

	while (*env_content)
	{
		split = ft_split(*env_content, '=');
		env_add_back(&env, ft_env_new(split[0], split[1]));
		*env_content++;
	}
	return env;
}

char		*check_for_env(t_env *env, char *data)
{
	char	*new_tk_value = NULL;
	char	*env_var = NULL;
	char	*before_env = NULL;
	char	*after_env = NULL;

	while (env)
	{
		env_var = ft_strnstr(data, env->name, ft_strlen(data));
		if (env_var && *(env_var-1) == '$')
		{
			before_env = ft_substr(data, 0, (env_var - data - 1));
			after_env = ft_substr(env_var, ft_strlen(env->name), ft_strlen(env_var) - ft_strlen(env->name));
			new_tk_value = ft_strjoin_n_free(before_env, ft_strjoin_n_free(ft_strdup(env->value), after_env));
			free(data);
			return (new_tk_value);
		}
		env = env->next;
	}
	return (NULL);
}

void	substitute_tokens(t_shell *sh)
{
	char	*is_env;
	t_token	*tmp;

	tmp = sh->tks;
	while (tmp)
	{
		if (is_env = check_for_env(sh->env, tmp->data))
			tmp->data = is_env;
		else
			tmp = tmp->next;
	}
}

int		lexer(t_shell *sh, char **envp)
{
	sh->env = put_env_into_lst(envp);
	sh->tks = put_input_into_tkn_lst(sh->input);
	substitute_tokens(sh);

	// ft_env_print(sh->env);
	// ft_env_clear(&sh->env, ft_free);
	ft_tkn_print(sh->tks);
	// ft_tkn_clear(&sh->tks, ft_free);
}
