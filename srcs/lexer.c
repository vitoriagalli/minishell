/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 22:48:01 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/01 22:30:39 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer(t_shell *sh)
{
	sh->tk = put_input_into_tkn_struct(sh);
	// check_syntax(sh);			// to implement
	// ft_tkn_print(sh->tk);
	return (0);
}
