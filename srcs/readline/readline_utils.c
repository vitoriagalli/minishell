/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:35:28 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 15:45:41 by romanbtt         ###   ########.fr       */
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
	write(1, &c, 1);
	return (1);
}

void	delete_char_left(t_msh *msh, int size)
{
	int		col;
	char	cwd[PATH_MAX];
	int		len_prompt;

	getcwd(cwd, PATH_MAX);
	len_prompt = ft_strlen(cwd) + 3;
	col = tgetnum("col");
	if (size > 0)
	{
		if ((size + len_prompt + msh->remainder_line) % (col - 1) == 0)
		{
			tputs(tgetstr("up", NULL), 1, &ft_putchar);
			tputs(tgoto(tgetstr("ch", NULL), 0, col), 0, &ft_putchar);
			tputs(tgetstr("dc", NULL), 1, &ft_putchar);
		}
		g_stream.line[size - 1] = '\0';
		if (!(g_stream.line = ft_realloc(g_stream.line, sizeof(char) * size)))
			exit_msh(msh, "ft_realloc: ", strerror(errno));
		tputs(tgetstr("le", NULL), 1, &ft_putchar);
		tputs(tgetstr("dc", NULL), 1, &ft_putchar);
	}
}

void	add_char_to_line(t_msh *msh, int size, char c)
{
	char *temp;

	if (!ft_isprint(c))
		return ;
	if (!(temp = ft_strdup(g_stream.line)))
		exit_msh(msh, "strdup: ", strerror(errno));
	free(g_stream.line);
	if (!(g_stream.line = malloc(sizeof(char) * size + 2)))
		exit_msh(msh, "malloc: ", strerror(errno));
	ft_bzero(g_stream.line, size + 2);
	ft_strlcpy(g_stream.line, temp, size + 1);
	g_stream.line[ft_strlen(g_stream.line)] = c;
	ft_printf("%c", c);
	free(temp);
}

int		process_newline(t_msh *msh)
{
	ft_printf("\n");
	insert_cmd_history(msh);
	ft_strdel(&msh->tmp_line);
	return (1);
}
