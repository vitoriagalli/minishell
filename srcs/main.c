/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:03:35 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/23 01:58:37 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_terminal(bool from_exit)
{
	if (from_exit == true)
	{
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, g_msh.save) == -1)
		{
			free(g_msh.save);
			g_msh.save = NULL;
			exit(g_msh.last_ret_cmd);
		}
	}
	else
	{
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, g_msh.save) == -1)
			exit_msh("tcsetattr", strerror(errno));
	}
}

int main(void)
{
	init_env(__environ);
	while ((read_line()) != 0)
	{
		restore_terminal(false);
		lexer();
		if (!syntax_parser())
			continue;
		create_commands();
		if (!find_path())
			continue;
		execution_commands();
		free(g_msh.save);
		g_msh.save = NULL;
	}
	// free everything before quit.
	// return (msh.last_ret_cmd);
	// exit_program();
}







// void	ft_lst_print(t_list *lst)
// {
// 	int count;

// 	count = 0;
// 	while (lst)
// 	{
// 		ft_printf("lst %i: %s\n", count, lst->content);
// 		lst = lst->next;
// 		count++;
// 	}
// }

// void	ft_cmd_print(t_cmd *lst)
// {
// 	int	count;
// 	int	i;

// 	i = 0;
// 	count = 0;
// 	while (lst)
// 	{
// 		ft_printf("-------- command %i ---------\n", count);
// 		ft_printf("cmd: %s\n", lst->cmd_name);
// 		ft_printf("sep: %i\n", lst->separator);
// 		while (lst->args[i])
// 		{
// 			ft_printf("arg %i: %s\n", i, lst->args[i]);
// 			i++;
// 		}
// 		ft_lst_print(lst->redirection);
// 		i = 0;
// 		lst = lst->next;
// 		count++;
// 	}
// }
