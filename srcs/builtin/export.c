/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:45:23 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/18 13:12:03 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sort_string_arr(char **arr)
{
	int		i;
	int		j;
	char	*aux;

	if (!arr || !(*arr))
		return ;
	i = 0;
	while (arr[i + 1])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) > 0)
			{
				aux = arr[i];
				arr[i] = arr[j];
				arr[j] = aux;
			}
			j++;
		}
		i++;
	}
}

char	**duplicate_array(char **buffer, int len_arr)
{
	char	**new_buffer;
	int		i;

	if (!buffer || !(*buffer))
		return (NULL);
	new_buffer = ft_calloc(len_arr + 1, sizeof(char *));
	i = 0;
	while (i < len_arr)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	return (new_buffer);
}

char	**reallocate_array(char **buffer, char *new_string)
{
	char	**new_buffer;
	int		len_arr;

	len_arr = 0;
	while (buffer[len_arr])
		len_arr++;
	new_buffer = duplicate_array(buffer, len_arr + 1);
	new_buffer[len_arr] = new_string;
	free(buffer);
	return (new_buffer);
}

void		print_env_declare_mode(void)
{
	char	**sorted_env;
	int		i;

	i = 0;
	while (g_msh.env[i])
		i++;
	sorted_env = duplicate_array(g_msh.env, i);
	ft_sort_string_arr(sorted_env);
	i = 0;
	while (sorted_env[i])
		ft_printf("declare -x %s\n", sorted_env[i++]);
}

void	ft_export(t_cmd *cmd, t_exec *exec)
{
	bool	exist;
	int		len;
	int		i;

	if (exec->child_pid == 0)
		exit(EXIT_SUCCESS);
	if (!cmd->args[1])
		print_env_declare_mode();
	else
	{
		if ((len = ft_strrchr(cmd->args[1], '=') - cmd->args[1]) < 0)
			return ;
		i = 0;
		exist = false;
		while (g_msh.env[i])
		{
			if (!ft_strncmp(g_msh.env[i], cmd->args[1], len + 1))
			{
				free(g_msh.env[i]);
				g_msh.env[i] = ft_strdup(cmd->args[1]);
				exist = true;
			}
			i++;
		}
		if (exist == false)
			g_msh.env = reallocate_array(g_msh.env, cmd->args[1]);
	}

}
