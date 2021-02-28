/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:16:25 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/27 22:43:45 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*last_env_node(t_env *lst)
{
	while (lst)
	{
		if (!(*lst).next)
			return (lst);
		lst = (*lst).next;
	}
	return (NULL);
}

void	ft_echo(t_cmd *cmd, t_exec *exec, t_minishell *msh)
{
	int i;
	bool no_newline;

	if (exec->child_pid == 0)
	{
		no_newline = false;
		i = 0;
		if (cmd->args[++i] && !(ft_strncmp(cmd->args[i], "-n", 2)))
		{
			no_newline = true;
			i++;
		}	
		while (cmd->args[i + 1])
			ft_printf("%s ", cmd->args[i++]);
		if (no_newline == true)
			ft_printf("%s", cmd->args[i]);
		else
			ft_printf("%s\n", cmd->args[i]);
		exit(EXIT_SUCCESS);
	}
}

void	ft_cd(t_cmd *cmd, t_exec *exec, t_minishell *msh)
{
	char *tmp;

	if (exec->child_pid == 0)
		exit(EXIT_SUCCESS);
	if (cmd->separator == 0 || cmd->separator == SEPARATOR)
	{
		if (cmd->args[1][0] == '~')
		{
			tmp = ft_substr(cmd->args[1], 1, ft_strlen(cmd->args[1]));
			tmp = ft_strjoin(msh->path_home, tmp);
		}
		else if (cmd->args[1][0] != '.')
			tmp = ft_strjoin("./", cmd->args[1]);
		else
			tmp = ft_strdup(cmd->args[1]);
		if ((chdir(tmp)) < 0)
		{
			if (cmd->args[1][0] == '~')
				ft_printf("minishell: cd: %s: %s\n",tmp, strerror(errno));
			else
				ft_printf("minishell: cd: %s: %s\n",cmd->args[1], strerror(errno));
			msh->force_ret_buildin = true;
			msh->last_ret_cmd = 1;
		}	
		free(tmp);
	}	
}

void 	ft_pwd(t_cmd *cmd, t_exec *exec, t_minishell *msh)
{
	char buf[1024];

	if (exec->child_pid == 0)
	{
		if ((getcwd(buf, 1024)) == NULL)
		{
			ft_printf("minishell: pwd: %s\n", strerror(errno));
			exit(exit_status());
		}
	}
}

void	ft_export(t_cmd *cmd, t_exec *exec, t_minishell *msh)
{
	t_env *node;
	char *name;
	char *value;
	int i;

	i = 0;
	if (exec->child_pid == 0)
		exit(EXIT_SUCCESS);
	if (cmd->separator == 0 || cmd->separator == SEPARATOR)
	{
		node = last_env_node(msh->head_env);
		node->next = malloc(sizeof(t_env));
		node = node->next;
		while (cmd->args[1][i] != '\0')
		{
			while (cmd->args[1][i] != '=')
			{
				if (cmd->args[1][i] == ':')
					break;
			}
		}
	}
}

void	ft_unset(t_cmd *cmd, t_exec *exec, t_minishell *msh)
{
	ft_printf("unset\n");
	ft_printf("TO DO\n");
}

void	ft_env(t_cmd *cmd, t_exec *exec, t_minishell *msh)
{
	t_env *line;
	
	if (exec->child_pid == 0)
	{
		line = msh->head_env;
		while (line->next)
		{
			ft_printf("%s=%s\n", line->name, line->value);
			line = line->next;
		}
		exit(EXIT_SUCCESS);
	}
}

void	ft_exit(t_cmd *cmd, t_exec *exec, t_minishell *msh)
{
	if (exec->child_pid == 0)
		exit(EXIT_SUCCESS);
	if (cmd->separator == 0 || cmd->separator == SEPARATOR)
		exit(EXIT_SUCCESS);
}

void	call_exec_buildin(t_cmd *cmd, t_exec *exec, t_minishell *msh)
{
	int i;
	int len;
	static t_inbuild func_inbuild[7] = {ft_echo, ft_cd, ft_pwd, ft_export,
		ft_unset, ft_env, ft_exit};
	char **inbuild;

	i = 0;
	len = ft_strlen(cmd->cmd_name);
	inbuild = ft_split("echo:cd:pwd:export:unset:env:exit", ':');
	while (ft_strncmp(cmd->cmd_name, inbuild[i], len))
		i++;
	(*func_inbuild[i])(cmd, exec, msh);
}

bool	is_buildin_cmd(char *cmd)
{
	char **inbuild;
	int i;
	int len;

	i = 0;
	len = ft_strlen(cmd);
	inbuild = ft_split("echo:cd:pwd:export:unset:env:exit", ':');
	while (inbuild[i])
	{
		if (!(ft_strncmp(inbuild[i++], cmd, len)))
			return (true);
	}
	return (false);
}