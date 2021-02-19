/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:03:35 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/19 15:47:07 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd_inbuild(char **args)
{
	int i;
	static t_inbuild func_inbuild[7] = {ft_echo, ft_cd, ft_pwd, ft_export,
		ft_unset, ft_env, ft_exit};
	char **inbuild;

	inbuild = ft_split("echo cd pwd export unset env exit", ' ');
	i = 0;
	if (!args[0])
		return ;
	while (i < 7 && ft_strncmp(args[0], inbuild[i], ft_strlen(inbuild[i])))
		i++;
	if (i < 7)
		(*func_inbuild[i])(args);
	else
		ft_printf("minishell: command not found: %s\n", args[0]);
}

char *read_line(void)
{
	char *line;
	if (get_next_line(STDIN_FILENO, &line) == -1)
	{
		ft_printf("Error\nCouldn't read the input.");
		free(line);
		exit(EXIT_FAILURE);
	}
//	line = ft_strjoin(line, "\n");
	return (line);
}

void print(t_tokens *tokens)  // ONLY TO DEBUG
{
	//char *echo = tokens->content;

	while (tokens && tokens->data[0] != '\0')
	{
			ft_printf("%s+", tokens->data);
			tokens = tokens->next;
	}
}

void print2(t_tokens *tokens)  // ONLY TO DEBUG
{
	//char *echo = tokens->content;

	while (tokens && tokens->data[0] != '\0')
	{
			
			if (tokens->type == 10)
				ft_printf(" word");
			if (tokens->type == 20)
				ft_printf(" operator");
			if (tokens->type == 100)
				ft_printf(" pipe");	
			if (tokens->type == 200)
				ft_printf(" output_overwrite");	
			if (tokens->type == 300)
				ft_printf(" output_append");	
			if (tokens->type == 400)
				ft_printf(" input");	
			if (tokens->type == 500)
				ft_printf(" separator");		
			if (tokens->type == 30)
				ft_printf(" single quote");
			if (tokens->type == 40)
				ft_printf(" double quote");
			if (tokens->type == 50)
				ft_printf(" backslash");
			tokens = tokens->next;
			
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
		tokens_substitution(msh);
		print(msh->head_tk);
		print2(msh->head_tk); // ONLY TO DEBUG
	}
}

//static void print_env(t_env *env)
//{
//	while (env->next != NULL)
//	{
//		printf("%s - %s\n", env->name, env->value);
//		env = env->next;
//	}
//}

int main(int argc, char *argv[], char *envp[])
{
	t_minishell msh;
	
	msh = (t_minishell) {0};
	argc = 0;
	argv = NULL;
	put_envp_struct(envp, &msh); // Function to put the env in struct
	//print_env(msh.head_env); // ONLY TO DEBUG
	shell_loop(&msh);
	return (0);
}
