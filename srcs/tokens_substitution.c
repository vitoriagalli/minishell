/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:11:36 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/19 15:07:02 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *substitution_env(t_tokens *tk, t_env *env, char *str)
{
	if (str[1] == '\0')
		return ("$");
	while (env->name != NULL)
	{
		if (!ft_strncmp(env->name, str + 1, ft_strlen(str) + 1))
			return (env->value);
		env = env->next;
	}
	return ("");
}

void	substitution_dollar_sign(t_tokens *tk, t_sub *sub, t_env *env)
{	
	int k;
	
	k = 1;
	if (tk->data[sub->i + 1] == '?')
	{
		ft_printf("Should print the $? value\n"); // TO DO
		sub->i += 2;
	}	
	else
	{
		while (tk->data[sub->i + k] != DOLLAR && tk->data[sub->i + k] != '\0')
			k++;
		sub->temp = ft_substr(tk->data, sub->i, k);
		sub->temp = substitution_env(tk, env, sub->temp);
		sub->buffer = ft_strjoin(sub->buffer, sub->temp);
		sub->i += k;
	}
}

void	substitution_type_word(t_tokens *tk, t_sub *sub, t_env *env)
{
	sub->buffer = malloc(sizeof(char) * ft_strlen(tk->data));
	while (tk->data[sub->i] != '\0')
	{
		if(tk->data[sub->i] == DOLLAR)
			substitution_dollar_sign(tk, sub, env);
		else
			sub->buffer[sub->j++] = tk->data[sub->i++];
	}
	tk->data = ft_strdup(sub->buffer);
	free(sub->buffer);
//	if (sub->temp)
//		free(sub->temp);
}

void	precise_type_operator(t_tokens *tk)
{
	if (tk->data[0] == VERTICAL_BAR)
		tk->type = PIPE;
	else if (tk->data[0] == SEMICOLON)
		tk->type = SEPARATOR;
	else if (tk->data[0] == LESS)
		tk->type = INPUT;
	else if (tk->data[0] == GREAT && tk->data[1] == GREAT)
		tk->type = OUT_APPEND;
	else if (tk->data[0] == GREAT)
		tk->type = OUT_OVERWRITE;
}

void	tokens_substitution(t_minishell *msh)
{
	t_tokens *tk;

	tk = msh->head_tk;
	while (tk != NULL)
	{
		msh->sub = (t_sub) {0};
		if (tk->type == WORD)
			substitution_type_word(tk, &msh->sub, msh->head_env);
		else if (tk->type == OPERATOR)
			precise_type_operator(tk);
		//else if (tk->type == SINGLE_QUOTED)
		//	substitution_type_single_quote();
		//else if (tk->type == DOUBLE_QUOTED)
		//	substitution_type_double_quote();
		//else if (tk->type == BACKSLASHED)
		//	substitution_type_backslash();
		tk = tk->next;			
	}
}