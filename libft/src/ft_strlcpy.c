/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:49:52 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 19:11:33 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Copies up to size - 1 characters from the string src to dst, null-terminating the result.
 * @param dst Destination buffer; must have enough space.
 * @param src Source string to copy from.
 * @param size Size of the destination buffer.
 * @return The total length of src. This allows the caller to detect truncation.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t i;

	i = 0;
	src_len = ft_strlen(src);
	if (size != 0) {
        while (i + 1 < size && src[i] != '\0') {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    }
    return (src_len);
}
