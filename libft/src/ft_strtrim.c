/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:18:54 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 19:20:08 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Checks if a character is present in a given set.
 * @param c Character to check.
 * @param set Set of characters.
 * @return 1 if c is in set, 0 otherwise.
 */
static int	is_in_set(unsigned char c, char const *set)
{
	while (*set != '\0')
	{
		if (c == (unsigned char)*set)
			return (1);
		set++;
	}
	return (0);
}

/**
 * @brief Trims characters in set from the start and end of s1.
 * @param s1 The string to trim.
 * @param set The set of characters to trim from s1.
 * @return A new trimmed string, or NULL on failure.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*result;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	if (end == 0)
		return (ft_strdup(""));
	while (start < end && is_in_set((unsigned char)s1[start], set))
		start++;
	while (end > start && is_in_set((unsigned char)s1[end - 1], set))
		end--;
	len = end - start;
	result = ft_substr(s1, start, len);
	return (result);
}
