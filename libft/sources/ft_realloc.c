/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 09:27:49 by romanbtt          #+#    #+#             */
/*   Updated: 2021/02/13 19:14:58 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!(new_ptr = malloc(sizeof(char) * size)))
		return (NULL);
	ft_bzero(new_ptr, size);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	ptr = NULL;
	return (new_ptr);
}
