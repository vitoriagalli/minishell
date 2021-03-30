/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:34:42 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 13:23:32 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_event(t_msh *msh, char *buf)
{
	int size;

	size = ft_strlen(g_stream.line);
	if (buf[0] == LF)
		return (process_newline(msh));
	else if (buf[0] == DEL)
		delete_char_left(msh, size);
	else if (buf[0] == ESC && buf[1] == SQ_BR && buf[2] == UP)
		history_up(msh, size);
	else if (buf[0] == ESC && buf[1] == SQ_BR && buf[2] == DOWN)
		history_down(msh, size);
	else
		add_char_to_line(msh, size, buf[0]);
	return (0);
}

static int	get_input_user(t_msh *msh)
{
	char	buffer[3];
	int		send_line;

	if (!(g_stream.line = ft_calloc(sizeof(char), 2)))
		exit_msh(msh, "tcsetattr", strerror(errno));
	send_line = 0;
	while (send_line == 0)
	{
		ft_bzero(buffer, 3);
		if (read(STDIN_FILENO, &buffer, 3) < 0)
			exit_msh(msh, "read", strerror(errno));
		if (buffer[0] == EOT && g_stream.line[0] == '\0')
		{
			ft_printf("exit\n");
			exit_program(msh);
		}
		send_line = handle_event(msh, buffer);
	}
	return (1);
}

static void	init_terminal(t_msh *msh)
{
	struct termios	term;
	char			**termtype;

	ft_bzero(&term, sizeof(struct termios));
	if (!(msh->save = ft_calloc(1, sizeof(struct termios))))
		exit_msh(msh, "calloc", strerror(errno));
	termtype = get_env_value(msh, "TERM");
	if (tgetent(NULL, termtype[0]) < 0)
		exit_msh(msh, "tgetent: ", strerror(errno));
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit_msh(msh, "tcsetattr: ", strerror(errno));
	ft_memcpy(msh->save, &term, sizeof(term));
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1)
		exit_msh(msh, "tcsetattr: ", strerror(errno));
	ft_array_clear(termtype, ft_free);
}

int			read_line(t_msh *msh, bool from_main)
{
	if (msh->save)
	{
		free(msh->save);
		msh->save = NULL;
	}
	if (from_main == true)
	{
		ft_tknclear(&msh->head_tk, ft_free);
		print_prompt();
	}
	else
		ft_printf("> ");
	init_terminal(msh);
	ft_cmdclear(&msh->cmds.head_cmd, ft_free);
	ft_bzero(&msh->cmds, sizeof(t_cmds));
	handle_signals(msh, ROOT, 1);
	if (g_stream.line != NULL)
		free(g_stream.line);
	if (get_input_user(msh) == 0)
		return (0);
	return (1);
}
