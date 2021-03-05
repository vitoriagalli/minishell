/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 21:19:21 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/06 00:19:29 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_env_new(char *name, char *value)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->name = name;
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env *tmp;

	tmp = *lst;
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int		ft_env_size(t_env *lst)
{
	int		count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void	ft_env_clear(t_env **lst, void (*del)(char*))
{
	t_env	*to_free;

	to_free = *lst;
	if (!*lst || !lst || !del)
		return ;
	while (to_free)
	{
		*lst = to_free->next;
		del(to_free->name);
		del(to_free->value);
		free(to_free);
		to_free = *lst;
	}
	*lst = NULL;
}


// nao precisa de parametro MUDAR
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

/*
** temporary function
*/

void	ft_env_print(t_env *lst)
{
	int count;

	count = 0;
	while (lst)
	{
		ft_printf("--- element %i ----\n", count);
		ft_printf("data: %s\n", lst->name);
		ft_printf("type: %s\n", lst->value);
		ft_printf("next: %p\n", lst->next);
		lst = lst->next;
		count++;
	}
}
