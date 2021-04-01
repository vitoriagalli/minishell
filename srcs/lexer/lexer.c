/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:55:29 by romanbtt          #+#    #+#             */
/*   Updated: 2021/03/30 15:42:43 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_strjoin_realloc(t_msh *msh, char *s1, char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!(str = ft_calloc(lens1 + lens2 + ft_strlen(g_stream.line),
	sizeof(char))))
		exit_msh(msh, "ft_calloc: ", strerror(errno));
	ft_memcpy(str, s1, lens1);
	free(s1);
	ft_memcpy(&str[lens1], s2, lens2);
	str[lens1 + lens2] = '\0';
	return (str);
}

static void	replace_exit_status(t_msh *msh, t_tokens *tk, t_lexer *lx)
{
	char	*temp1;
	char	*temp2;

	if (!(temp1 = ft_itoa(g_stream.exit_status)))
		exit_msh(msh, "ft_itoa: ", strerror(errno));
	if (!(temp2 = ft_strjoin(tk->data, temp1)))
		exit_msh(msh, "ft_strjoin: ", strerror(errno));
	free(tk->data);
	free(temp1);
	tk->data = temp2;
	lx->i += 2;
}

static void	replace_env_var(t_msh *msh, t_tokens *tk, t_lexer *lx, int k)
{
	char	*temp1;
	char	**temp2;

	while (lx->line[k] != DOLLAR && lx->line[k] != SPACE &&
	lx->line[k] != '\0' && lx->line[k] != ESCAPE && lx->line[k] != '/' &&
	lx->line[k] != DOUBLE_QUOTE && lx->line[k] != '=' &&
	lx->line[k] != SEMICOLON && lx->line[k] != SINGLE_QUOTE)
		k++;
	if (!(temp1 = ft_substr(lx->line, lx->i, k - lx->i)))
		exit_msh(msh, "ft_substr: ", strerror(errno));
	temp2 = get_env_value(msh, temp1 + 1);
	free(temp1);
	temp1 = tk->data;
	if (!(tk->data = ft_strjoin_realloc(msh, temp1, temp2[0])))
		exit_msh(msh, "ft_strjoin: ", strerror(errno));
	lx->i = k;
	ft_array_clear(temp2, ft_free);
}

void		evaluate_dollar(t_msh *msh, t_tokens *tk, t_lexer *lx)
{
	int		k;

	k = lx->i + 1;
	if (lx->line[lx->i + 1] == '?')
		replace_exit_status(msh, tk, lx);
	else if (ft_isdigit(lx->line[lx->i + 1]))
		lx->i = k + 1;
	else
		replace_env_var(msh, tk, lx, k);
}

void		lexer(t_msh *msh)
{
	t_tokens	*tk;
	t_lexer		lx;

	if (!(msh->head_tk = malloc(sizeof(t_tokens))))
		exit_msh(msh, "malloc: ", strerror(errno));
	lx = (t_lexer) {0, ft_strlen(g_stream.line), 0, NULL, STATE_GEN};
	if (!(lx.line = ft_strdup(g_stream.line)))
		exit_msh(msh, "ft_strdup: ", strerror(errno));
	tk = msh->head_tk;
	init_token(msh, tk, &lx);
	while (lx.i < lx.size || lx.state != STATE_GEN)
	{
		if (lx.state == STATE_GEN)
			tk = general_state(msh, tk, &lx);
		if (lx.state == STATE_SINGLE_QUOTED)
			quoted_state(msh, tk, &lx);
		else if (lx.state == STATE_DOUBLE_QUOTED)
			double_quoted_state(msh, tk, &lx);
	}
	msh->head_tk = remove_last_empty_node(msh->head_tk);
	add_end_token(msh, msh->head_tk, &lx);
	ft_strdel(&lx.line);
}
