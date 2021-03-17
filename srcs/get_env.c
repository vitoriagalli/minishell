/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:25:59 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/05 19:00:25 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_env	*create_node(t_env *env, char *envp, int name, int value)
{
	char *str_name;
	char *str_value;

	str_name = ft_substr(envp, 0, name);
	str_value = ft_substr(envp, name + 1, value);
	ft_strlcpy(env->name, str_name, name + 1);
	ft_strlcpy(env->value, str_value, value + 1);
	free(str_name);
	free(str_value);
	return (env);
}

static void	init_node(t_env *env, int name, int value)
{
	env->name = malloc(sizeof(char) * name + 1);
	ft_bzero(env->name, name + 1);
	env->value = malloc(sizeof(char) * value + 1);
	ft_bzero(env->value, value + 1);
	env->next = NULL;
}

static void	count_char_name_value(char *envp, int *name, int *value)
{
	int n;
	int v;

	n = 0;
	while (envp[++n] != '=')
		;
	v = n + 1;
	while (envp[++v] != '\0')
		;
	*name = n;
	*value = v - n - 1;
}

void	put_envp_in_list(char *envp[], t_minishell *msh)
{
	int line;
	int name;
	int value;
	t_env *env;

	line = 0;
	msh->head_env = malloc(sizeof(t_env));
	env = msh->head_env;
	while (1)
	{
		count_char_name_value(envp[line], &name, &value);
		init_node(env, name, value);
		env = create_node(env, envp[line++], name, value);
		if (!ft_strncmp(env->name, "PATH", name))
			msh->path_cmd = ft_split(env->value, ':');
		if (!ft_strncmp(env->name, "HOME", name))
			msh->path_home = ft_strdup(env->value);
		if (!ft_strncmp(env->name, "TERM", name))
			msh->termtype = ft_strdup(env->value);
		if (envp[line] == NULL)
			break;
		env->next = malloc(sizeof(t_env));
		env = env->next;
	}
	env->next = NULL;
}