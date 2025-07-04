/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:04:23 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 18:50:41 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Copies n bytes from memory area src to memory area dest. The memory areas may overlap.
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to copy.
 * @return Pointer to the destination memory area.
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*target;
	const unsigned char	*source;

	if (dest == NULL && src == NULL)
		return (dest);
	target = (unsigned char *)dest;
	source = (const unsigned char *)src;
	if (source < target && (target < source + n))
	{
		source += n;
		target += n;
		while (n--)
			*(--target) = *(--source);
	}
	else
	{
		while (n--)
			*target++ = *source++;
	}
	return (dest);
}
