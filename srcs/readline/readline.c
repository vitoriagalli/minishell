/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:34:42 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/10 17:40:26 by romanbtt         ###   ########.fr       */
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

void	history_up(t_minishell *msh, int size)
{
	if (msh->head_hist == NULL)
		return ;
	if (msh->tmp_line == NULL)
		msh->tmp_line = ft_strdup(msh->rd_line);
	else if (msh->curr_hist->next != NULL)
		msh->curr_hist = msh->curr_hist->next;
	else
		return ;
	while (size > 0)
	{
		tputs(tgetstr("le", NULL), 1, &ft_putchar);
		tputs(tgetstr("dc", NULL), 1, &ft_putchar);
		size--;
	}
	ft_printf(msh->curr_hist->cmd_line);
	msh->rd_line = ft_strdup(msh->curr_hist->cmd_line);
}

void	history_down(t_minishell *msh, int size)
{
	if (msh->head_hist == NULL || msh->tmp_line == NULL)
		return ;
	else
	{
		while (size > 0)
		{
			tputs(tgetstr("le", NULL), 1, &ft_putchar);
			tputs(tgetstr("dc", NULL), 1, &ft_putchar);
			size--;
		}
		msh->curr_hist = msh->curr_hist->prev;
		if (msh->curr_hist != NULL)
		{
			ft_printf(msh->curr_hist->cmd_line);
			msh->rd_line = ft_strdup(msh->curr_hist->cmd_line);
		}
		else
		{
			ft_printf(msh->tmp_line);
			msh->rd_line = ft_strdup(msh->tmp_line);
			msh->curr_hist = msh->head_hist;
			free(msh->tmp_line);
			msh->tmp_line = NULL;
		}

	}
}

void	delete_char_left(t_minishell *msh, int size)
{
	if (size > 0)
	{
		msh->rd_line[size - 1] = '\0';
		msh->rd_line = ft_realloc(msh->rd_line, sizeof(char) * size);
		tputs(tgetstr("le", NULL), 1, &ft_putchar);
		tputs(tgetstr("dc", NULL), 1, &ft_putchar);
	}	
}

void	add_char_to_line(t_minishell *msh, int size, char c)
{
	char *temp;
	
	if (!ft_isprint(c))
		return ;
	temp = ft_strdup(msh->rd_line);
	free(msh->rd_line);
	msh->rd_line = malloc(sizeof(char) * size + 2);
	ft_bzero(msh->rd_line, size + 2);
	ft_strlcpy(msh->rd_line, temp, size + 1);
	msh->rd_line[ft_strlen(msh->rd_line)] = c;
	msh->rd_line[ft_strlen(msh->rd_line) + 1] = '\0';
	ft_printf("%c", c);
}

int	process_newline(t_minishell *msh, int size)
{
	ft_printf("\n");
	msh->curr_hist = NULL;
	insert_cmd_history(msh);
	msh->tmp_line = NULL;
	
	return (1);
}

int	handle_event(t_minishell *msh, char *buf)
{
	int size;

	size = ft_strlen(msh->rd_line);
	if (buf[0] == LF)
		return (process_newline(msh, size));
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

int	get_input_user(t_minishell *msh)
{
	char buffer[3];
	int send_line;

	msh->rd_line = ft_calloc(sizeof(char), 2);
	send_line = 0;
	while(send_line == 0)
	{
		ft_bzero(buffer, 3);
		read(STDIN_FILENO, &buffer, 3);
		if (buffer[0] == EOT)
			return (0);
		send_line = handle_event(msh, buffer);
	}
	return (1);
}

void init_terminal(t_minishell *msh, char *envp[])
{
	struct termios term;

	put_envp_in_list(envp, msh);
	msh->term = &term;
	if (tgetent(NULL, msh->termtype) < 0)
		exit (0);// Call exit function faillure
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit (0); // Call exit function faillure
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		exit (0); // Call exit function faillure
}

int read_line(t_minishell *msh)
{
	if (get_input_user(msh) == 0)
		return (0);
	return (1);
}