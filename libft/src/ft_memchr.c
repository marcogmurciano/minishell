/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:23:11 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 18:44:10 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Locate the first occurrence of byte c in memory area s within n bytes.
 * @param s Memory area to search.
 * @param c Byte to find (converted to unsigned char).
 * @param n Maximum number of bytes to examine.
 * @return Pointer to the matching byte, or NULL if not found.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t i;
	const unsigned char	*ptr;
	unsigned char		search_char;

	i = 0;
	ptr = (const unsigned char *)s;
	search_char = (unsigned char)c;
	while (i < n)
	{
		if (ptr[i] == search_char)
			return ((void *)ptr + i);
		i++;
	}
	return (NULL);
}
