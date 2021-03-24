/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:34:42 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/24 15:55:41 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt()
{
	char cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	ft_printf("%s%s %s>%s ",BLUE ,cwd ,YELLOW, END_COLOR);
}

static int		ft_putchar(int c)
{
	if (write(1, &c, 1) < 0)
		exit_msh("write", strerror(errno));
	return (1);
}

static void	history_up(int size)
{
	if (g_msh.head_hist == NULL)
		return ;
	if (g_msh.tmp_line == NULL)
	{
		if (!(g_msh.tmp_line = ft_strdup(g_msh.line)))
			exit_msh("strdup", strerror(errno));
	}
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
	ft_strdel(&g_msh.line);
	if (!(g_msh.line = ft_strdup(g_msh.curr_hist->cmd_line)))
		exit_msh("strdup", strerror(errno));
}

static void	history_down(int size)
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
			ft_strdel(&g_msh.line);
			if (!(g_msh.line = ft_strdup(g_msh.curr_hist->cmd_line)))
				exit_msh("strdup", strerror(errno));
		}
		else
		{
			ft_printf(g_msh.tmp_line);
			ft_strdel(&g_msh.line);
			if (!(g_msh.line = ft_strdup(g_msh.tmp_line)))
				exit_msh("strdup", strerror(errno));
			g_msh.curr_hist = g_msh.head_hist;
			ft_strdel(&g_msh.tmp_line);
		}
	}
}

static void	delete_char_left(int size)
{
	if (size > 0)
	{
		g_msh.line[size - 1] = '\0';
		g_msh.line = ft_realloc(g_msh.line, sizeof(char) * size);
		tputs(tgetstr("le", NULL), 1, &ft_putchar);
		tputs(tgetstr("dc", NULL), 1, &ft_putchar);
	}
}

static void	add_char_to_line(int size, char c)
{
	char *temp;

	if (!ft_isprint(c))
		return ;
	if (!(temp = ft_strdup(g_msh.line)))
		exit_msh("strdup", strerror(errno));
	free(g_msh.line);
	g_msh.line = malloc(sizeof(char) * size + 2);
	ft_bzero(g_msh.line, size + 2);
	ft_strlcpy(g_msh.line, temp, size + 1);
	g_msh.line[ft_strlen(g_msh.line)] = c;
	ft_printf("%c", c);
	free(temp);
}

int	process_newline()
{
	ft_printf("\n");
	//g_msh.curr_hist = NULL;
	insert_cmd_history();
	ft_strdel(&g_msh.tmp_line);
	return (1);
}

static int	handle_event(char *buf)
{
	int size;

	size = ft_strlen(g_msh.line);
	if (buf[0] == LF)
		return (process_newline());
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

	if (!(g_msh.line = ft_calloc(sizeof(char), 2)))
		exit_msh("tcsetattr", strerror(errno));
	send_line = 0;
	while(send_line == 0)
	{
		ft_bzero(buffer, 3);
		if (read(STDIN_FILENO, &buffer, 3) < 0)
			exit_msh("read", strerror(errno));
		
		if (buffer[0] == EOT && g_msh.line[0] == '\0')
		{
			ft_printf("exit\n");
			exit_program();
		}	
		send_line = handle_event(buffer);
	}
	return (1);
}

static void init_terminal()
{
	struct termios term;
	char	**termtype;

	if (!(g_msh.save = ft_calloc(1, sizeof(struct termios))))
		exit_msh("calloc", strerror(errno));
	termtype = get_env_value("TERM");
	if (tgetent(NULL, termtype[0]) < 0)
		exit_msh("tgetent", strerror(errno));
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit_msh("tcsetattr", strerror(errno));
	ft_memcpy(g_msh.save, &term, sizeof(term));
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1)
		exit_msh("tcsetattr", strerror(errno));
	ft_array_clear(termtype, ft_free);
	
}

int read_line(bool from_main)
{
	if (g_msh.save)
	{
		free(g_msh.save);
		g_msh.save = NULL;
	}
	if (from_main == true)
	{
		ft_tknclear(&g_msh.head_tk, ft_free);
		print_prompt();
	}	
	init_terminal();
	ft_cmdclear(&g_msh.cmds.head_cmd, ft_free);
	ft_bzero(&g_msh.cmds, sizeof(t_cmds));
	handle_signals(ROOT, 1);
	if (g_msh.line != NULL)
		free(g_msh.line);
	if (get_input_user() == 0)
		return (0);
	return (1);
}
