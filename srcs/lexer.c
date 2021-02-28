/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:29:35 by vscabell          #+#    #+#             */
/*   Updated: 2021/02/28 00:52:50 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*put_env_into_lst(char **env_content)
{
	t_env	*env;
	char	*name;
	char	*value;
	char	*addr;

	env = NULL;
	name = NULL;
	value = NULL;
	addr = NULL;
	while (*env_content)
	{
		addr = ft_strrchr(*env_content, '=');
		name = ft_substr(*env_content, 0, addr - *env_content);
		value = ft_substr(*env_content, addr - *env_content + 1,
			ft_strlen(*env_content) - (addr - *env_content));
		env_add_back(&env, ft_env_new(name, value));
		env_content++;
	}
	return (env);
}

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

void	substitute_tokens(t_shell *sh)
{
	char	*is_env;
	t_token	*tmp;

	is_env = NULL;
	tmp = sh->tks;
	while (tmp)
	{
		is_env = check_for_env(sh->env, tmp->data);
		if (tmp->type != SIMPLE_QUOTE && is_env != NULL)
		{
			free(tmp->data);
			tmp->data = is_env;
			is_env = NULL;
		}
		else
			tmp = tmp->next;
	}
}

void	check_syntax(t_shell *sh)
{
	if (is_job_char(sh->tks->type))
	{
		ft_printf("bash: syntax error near unexpected token");
		exit(EXIT_FAILURE);
	}
}

int		lexer(t_shell *sh)
{
	sh->tks = put_input_into_tkn_lst(sh->input);
	substitute_tokens(sh);
	check_syntax(sh);			// to implement
	// ft_env_print(sh->env);
	// ft_tkn_print(sh->tks);
	return (0);
}
