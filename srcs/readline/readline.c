/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:34:42 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/18 22:23:07 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt()
{
	char cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	ft_printf("%s%s %s>%s ",BLUE ,cwd ,YELLOW, END_COLOR);
}

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	history_up(int size)
{
	if (g_msh.head_hist == NULL)
		return ;
	if (g_msh.tmp_line == NULL)
		g_msh.tmp_line = ft_strdup(g_msh.rd_line);
	else if (g_msh.curr_hist->next != NULL)
		g_msh.curr_hist = g_msh.curr_hist->next;
	else
		return ;
	while (size > 0)
	{
		tputs(tgetstr("le", NULL), 1, &ft_putchar);
		tputs(tgetstr("dc", NULL), 1, &ft_putchar);
		size--;
	}
	ft_printf("%s", g_msh.curr_hist->cmd_line);
	g_msh.rd_line = ft_strdup(g_msh.curr_hist->cmd_line);
}

void	history_down(int size)
{
	if (g_msh.head_hist == NULL || g_msh.tmp_line == NULL)
		return ;
	else
	{
		while (size > 0)
		{
			tputs(tgetstr("le", NULL), 1, &ft_putchar);
			tputs(tgetstr("dc", NULL), 1, &ft_putchar);
			size--;
		}
		g_msh.curr_hist = g_msh.curr_hist->prev;
		if (g_msh.curr_hist != NULL)
		{
			ft_printf(g_msh.curr_hist->cmd_line);
			g_msh.rd_line = ft_strdup(g_msh.curr_hist->cmd_line);
		}
		else
		{
			ft_printf(g_msh.tmp_line);
			g_msh.rd_line = ft_strdup(g_msh.tmp_line);
			g_msh.curr_hist = g_msh.head_hist;
			free(g_msh.tmp_line);
			g_msh.tmp_line = NULL;
		}

	}
}

void	delete_char_left(int size)
{
	if (size > 0)
	{
		g_msh.rd_line[size - 1] = '\0';
		g_msh.rd_line = ft_realloc(g_msh.rd_line, sizeof(char) * size);
		tputs(tgetstr("le", NULL), 1, &ft_putchar);
		tputs(tgetstr("dc", NULL), 1, &ft_putchar);
	}
}

void	add_char_to_line(int size, char c)
{
	char *temp;

	if (!ft_isprint(c))
		return ;
	temp = ft_strdup(g_msh.rd_line);
	free(g_msh.rd_line);
	g_msh.rd_line = malloc(sizeof(char) * size + 2);
	ft_bzero(g_msh.rd_line, size + 2);
	ft_strlcpy(g_msh.rd_line, temp, size + 1);
	g_msh.rd_line[ft_strlen(g_msh.rd_line)] = c;
	g_msh.rd_line[ft_strlen(g_msh.rd_line) + 1] = '\0';
	ft_printf("%c", c);
}

int	process_newline(int size)
{
	ft_printf("\n");
	g_msh.curr_hist = NULL;
	insert_cmd_history();
	g_msh.tmp_line = NULL;

	return (1);
}

int	handle_event(char *buf)
{
	int size;

	size = ft_strlen(g_msh.rd_line);
	if (buf[0] == LF)
		return (process_newline(size));
	else if (buf[0] == DEL)
		delete_char_left(size);
	else if (buf[0] == ESC && buf[1] == SQ_BR && buf[2] == UP)
		history_up(size);
	else if (buf[0] == ESC && buf[1] == SQ_BR && buf[2] == DOWN)
		history_down(size);
	else
		add_char_to_line(size, buf[0]);
	return (0);
}

int	get_input_user()
{
	char buffer[3];
	int send_line;

	g_msh.rd_line = ft_calloc(sizeof(char), 2);
	send_line = 0;
	while(send_line == 0)
	{
		ft_bzero(buffer, 3);
		read(STDIN_FILENO, &buffer, 3);
		if (buffer[0] == EOT)
			return (0);
		send_line = handle_event(buffer);
	}
	return (1);
}

void init_terminal(char *envp[])
{
	struct termios term;
	char	**termtype;

	termtype = get_env_value("TERM");
	g_msh.term = &term;
	if (tgetent(NULL, termtype[0]) < 0)
		exit (0);// Call exit function faillure
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit (0); // Call exit function faillure
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		exit (0); // Call exit function faillure
	ft_array_clear(termtype, ft_free);
}

int read_line()
{
	if (get_input_user() == 0)
		return (0);
	return (1);
}
