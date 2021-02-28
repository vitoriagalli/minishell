/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:03:35 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/28 00:03:04 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char *read_line(void)
{
	char *line;

	if (get_next_line(STDIN_FILENO, &line) == -1)
	{
		ft_printf("Error\nCouldn't read the input.");
		free(line);
		exit(EXIT_FAILURE);
	}
	return (line);
}

void print3(t_tokens *tokens)  // ONLY TO DEBUG
{

	ft_printf("\nOutput :\n");
	while (tokens)
	{
		ft_printf("%s", tokens->data);
		tokens = tokens->next;
	}
	ft_printf("\n");
}

void print(t_tokens *tokens)  // ONLY TO DEBUG
{
	int token = 1;
	while (tokens)
	{
		ft_printf("Token #%d : >%s<", token, tokens->data);
		if (tokens->type == WORD)
			ft_printf("	: Word\n");
		else if (tokens->type == PIPE)
			ft_printf("	: Pipe\n");
		else if (tokens->type == SEPARATOR)
			ft_printf("	: Separator\n");
		else if (tokens->type == INPUT)
			ft_printf("	: Input\n");
		else if (tokens->type == OUT_OVERWRITE)
			ft_printf("	: Output Overwrite\n");
		else if (tokens->type == OUT_APPEND)
			ft_printf("	: Output Append\n");
		else if (tokens->type == END)
			ft_printf("	: End\n");
		token++;
		tokens = tokens->next;
	}
}

void print_cmd(t_minishell *msh)
{
	t_cmd *cmd;
	int i;
	int j;
	
	j = 1;
	cmd = msh->cmds->head_cmd;
	while (cmd)
	{
		i = 0;
		ft_printf("Command #%d\n", j++);
		ft_printf("Command name	: %s\n", cmd->cmd_name);
		while (cmd->args[i])
			ft_printf("Argument %d	: %s\n",i , cmd->args[i++]);
		if (cmd->redirection == OUT_OVERWRITE)
			ft_printf("Redirection	: > %s\n", cmd->file_out);
		else if (cmd->redirection == OUT_APPEND)
			ft_printf("Redirection	: >> %s\n", cmd->file_out);
		if (cmd->redirection == INPUT)
			ft_printf("Redirection	: < %s\n", cmd->file_in);
		if (cmd->separator == PIPE)
			ft_printf("\nPipe\n");
		else if (cmd->separator == SEPARATOR)
			ft_printf("\nSemicolon\n");
		ft_printf("\n");
		cmd = cmd->next;
	}
}

void shell_loop(t_minishell *msh)
{
	char cwd[1024];
	
	while (1)
	{
		ft_printf("\033[1;34m%s \033[1;33m>\033[0m ", getcwd(cwd, 1024));
		msh->line = read_line();
		lexer(msh);
		if (!syntax_parser(msh->head_tk))
			continue;
		create_command(msh);
		exec_cmd_v2(msh, msh->cmds->head_cmd);
		//execute_command(msh, msh->cmds->head_cmd);
		//print_cmd(msh); DEBUG
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_minishell msh;
	
	msh = (t_minishell) {0};
	argc = 0;
	msh.cmds = malloc(sizeof(t_cmds));
	get_envp(envp, &msh);
	shell_loop(&msh);
	return (0);
}
