/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 22:48:01 by vscabell          #+#    #+#             */
/*   Updated: 2021/03/01 19:41:06 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer(t_shell *sh)
{
	sh->cmd = put_input_into_tkn_struct(sh);
	ft_tkn_print(sh->cmd);
	return (0);
}
