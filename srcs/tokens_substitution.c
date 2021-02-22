/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:11:36 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/21 19:12:25 by romanbtt         ###   ########.fr       */
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
		while (tk->data[sub->i + k] != DOLLAR && tk->data[sub->i + k] != NEW_LINE &&
		tk->data[sub->i + k] != SPACE && tk->data[sub->i + k] != '\0' && tk->data[sub->i + k] != ESCAPE)
			k++;
		sub->temp = ft_substr(tk->data, sub->i, k);
		sub->temp = substitution_env(tk, env, sub->temp);
		sub->buffer = ft_strjoin(sub->buffer, sub->temp);
		sub->i += k;
		sub->j += ft_strlen(sub->buffer);
	}
}

void	precise_type_operator(t_tokens *tk, t_sub *sub)
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
	sub->buffer = ft_strdup(tk->data);
}

void	substitution_type_word(t_tokens *tk, t_sub *sub, t_env *env)
{
	while (tk->data[sub->i] != NEW_LINE && tk->data[sub->i] != SPACE && tk->data[sub->i] != '\0')
	{
		if (tk->data[sub->i] == DOLLAR)
			substitution_dollar_sign(tk, sub, env);
		else
			sub->buffer[sub->j++] = tk->data[sub->i++];
	}
	sub->buffer[sub->j++] = tk->data[sub->i++];
	tk->type = WORD;
}

void	substitution_type_backslash(t_tokens *tk, t_sub *sub, t_env *env)
{
	while (tk->data[sub->i] != NEW_LINE && tk->data[sub->i] != SPACE && tk->data[sub->i] != '\0')
	{
		if (tk->eval == true)
		{
			if (tk->data[sub->i] == DOLLAR)
			{
				substitution_dollar_sign(tk, sub, env);
				sub->j = ft_strlen(sub->buffer);
			}	
			else
				sub->buffer[sub->j++] = tk->data[sub->i++];
		}
		else
			sub->buffer[sub->j++] = tk->data[sub->i++];
	}
	sub->buffer[sub->j++] = tk->data[sub->i++];
	tk->type = WORD;
}

void	substitution_type_single_quote(t_tokens *tk, t_sub *sub)
{
	sub->buffer = ft_strdup(tk->data);
	tk->type = WORD;
}

void	substitution_type_double_quote(t_tokens *tk, t_sub *sub, t_env *env)
{
	if (tk->data[0] == NEW_LINE || tk->data[0] == SPACE)
		sub->buffer[0] = tk->data[sub->i++];
	while (tk->data[sub->i] != NEW_LINE && tk->data[sub->i] != '\0')
	{
		if (tk->data[sub->i] == ESCAPE && tk->data[sub->i + 1] == ESCAPE)
		{
			sub->buffer[ft_strlen(sub->buffer)] = tk->data[++sub->i];
			sub->i++;
		}	
		else if (tk->data[sub->i] == ESCAPE && tk->data[sub->i + 1] == DOLLAR)
		{
			sub->buffer[ft_strlen(sub->buffer)] = tk->data[++sub->i];
			sub->i++;
		}
		else
		{
			if (tk->data[sub->i] == DOLLAR)
				substitution_dollar_sign(tk, sub, env);
			else
				sub->buffer[ft_strlen(sub->buffer)] = tk->data[sub->i++];
		}
		if (tk->data[sub->i] == NEW_LINE || tk->data[sub->i] == SPACE)
			sub->buffer[ft_strlen(sub->buffer)] = tk->data[sub->i++];
	}
	tk->type = WORD;
}

void	tokens_substitution(t_minishell *msh)
{
	t_tokens *tk;

	tk = msh->head_tk;
	while (tk != NULL)
	{
		msh->sub = (t_sub) {0};
		msh->sub.buffer = malloc(sizeof(char) * ft_strlen(tk->data));
		ft_bzero(msh->sub.buffer, ft_strlen(tk->data));
		if (tk->type == WORD)
			substitution_type_word(tk, &msh->sub, msh->head_env);
		else if (tk->type == OPERATOR)
			precise_type_operator(tk, &msh->sub);
		else if (tk->type == SINGLE_QUOTED)
			substitution_type_single_quote(tk, &msh->sub);
		else if (tk->type == DOUBLE_QUOTED)
			substitution_type_double_quote(tk, &msh->sub, msh->head_env);
		else if (tk->type == BACKSLASHED)
			substitution_type_backslash(tk, &msh->sub, msh->head_env);
		tk->data = ft_strdup(msh->sub.buffer);
		tk = tk->next;		
	}
}