/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:37:31 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 19:08:58 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Appends the NUL-terminated string src to the end of dst, copying at most dst_memsize - strlen(dst) - 1 bytes.
 * @param dst The destination buffer.
 * @param src The source string.
 * @param dst_memsize Total size of the destination buffer.
 * @return The total length of the string it tried to create: initial length of dst plus length of src.
 *         If return value >= dst_memsize, truncation occurred.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dst_memsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dst_memsize <= dst_len)
		return (dst_memsize + src_len);
	while (src[i] && (dst_len + i) < (dst_memsize - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = 0;
	return (dst_len + src_len);
}
