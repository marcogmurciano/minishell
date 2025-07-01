/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:40:16 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/01 14:49:11 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Handles NULL input cases for ft_strjoin.
 *
 * If both s1 and s2 are NULL, returns NULL.
 * If one is NULL, returns a duplicate of the other.
 *
 * @param s1 First input string (may be NULL)
 * @param s2 Second input string (may be NULL)
 * @return Newly allocated string or NULL if both are NULL or allocation fails.
 */
static char *ft_strjoin_handle_null(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	return (NULL);
}

/**
 * @brief Allocates memory for the joined string.
 *
 * Allocates enough memory to hold both s1 and s2 and the null terminator.
 *
 * @param s1 First input string
 * @param s2 Second input string
 * @return Pointer to newly allocated memory, or NULL on failure.
 */
static char *ft_strjoin_alloc(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*newstr;

	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	newstr = malloc(len1 + len2 + 1);
	return (newstr);
}

/**
 * @brief Copies s1 and s2 into dst, concatenating them.
 *
 * @param dst Destination buffer (must be large enough)
 * @param s1 First input string
 * @param s2 Second input string
 */
static void ft_strjoin_copy(char *dst, const char *s1, const char *s2)
{
	size_t i = 0;
	size_t j = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
}

/**
 * @brief Concatenates two strings into a newly allocated string.
 *
 * If either s1 or s2 is NULL, returns a duplicate of the other.
 * If both are NULL, returns NULL.
 *
 * @param s1 First input string (may be NULL)
 * @param s2 Second input string (may be NULL)
 * @return Newly allocated concatenated string, or NULL on failure.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*null_case;
	char	*newstr;

	null_case = ft_strjoin_handle_null(s1, s2);
	if (null_case)
		return (null_case);
	newstr = ft_strjoin_alloc(s1, s2);
	if (!newstr)
		return (NULL);
	ft_strjoin_copy(newstr, s1, s2);
	return (newstr);
}
