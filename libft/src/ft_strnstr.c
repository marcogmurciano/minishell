/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:35:49 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 19:16:37 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Locates the first occurrence of the null-terminated string needle in the string haystack,
 *        where not more than len characters are searched. Characters that appear after a '\0' character
 *        are not searched.
 * @param haystack The string to be searched.
 * @param needle The substring to search for.
 * @param len The maximum number of characters to search.
 * @return A pointer to the first occurrence of needle in haystack, or NULL if needle is not found.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	if (needle == NULL || haystack == NULL)
		return (NULL);
	if (*needle == '\0')
        return ((char *)haystack);
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
        return (char *)haystack;
	while (*haystack && len >= needle_len)
	{
		if (!ft_strncmp(haystack, needle, needle_len))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
