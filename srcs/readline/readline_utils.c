/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:35:28 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 13:40:45 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	char cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	ft_printf("%s%s %s>%s ", BLUE, cwd, YELLOW, END_COLOR);
}

int		ft_putchar(int c)
{
	if (write(1, &c, 1) < 0)
		exit_msh("write", strerror(errno));
	return (1);
}

void	delete_char_left(int size)
{
	if (size > 0)
	{
		g_msh.line[size - 1] = '\0';
		if (!(g_msh.line = ft_realloc(g_msh.line, sizeof(char) * size)))
			exit_msh("ft_realloc: ", strerror(errno));
		tputs(tgetstr("le", NULL), 1, &ft_putchar);
		tputs(tgetstr("dc", NULL), 1, &ft_putchar);
	}
}

void	add_char_to_line(int size, char c)
{
	char *temp;

	if (!ft_isprint(c))
		return ;
	if (!(temp = ft_strdup(g_msh.line)))
		exit_msh("strdup: ", strerror(errno));
	free(g_msh.line);
	if (!(g_msh.line = malloc(sizeof(char) * size + 2)))
		exit_msh("malloc: ", strerror(errno));
	ft_bzero(g_msh.line, size + 2);
	ft_strlcpy(g_msh.line, temp, size + 1);
	g_msh.line[ft_strlen(g_msh.line)] = c;
	ft_printf("%c", c);
	free(temp);
}

int		process_newline(void)
{
	ft_printf("\n");
	insert_cmd_history();
	ft_strdel(&g_msh.tmp_line);
	return (1);
}
