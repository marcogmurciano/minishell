/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:23:19 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 18:09:14 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Sets n bytes of memory to zero starting from *s.
 * 
 * @param s Pointer to the starting point from which to set the memory.
 * @param n Number of bytes to set to 0.
 */
void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	if (!s)
		return ;
	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i++] = 0;
	}
	return ;
}
