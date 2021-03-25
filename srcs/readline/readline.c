/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:34:42 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/25 15:00:44 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int			get_input_user(void)
{
	char	buffer[3];
	int		send_line;

	if (!(g_msh.line = ft_calloc(sizeof(char), 2)))
		exit_msh("tcsetattr", strerror(errno));
	send_line = 0;
	while (send_line == 0)
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

static void	init_terminal(void)
{
	struct termios	term;
	char			**termtype;

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

int			read_line(bool from_main)
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
	else
		ft_printf("> ");
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
