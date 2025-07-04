/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:36:26 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 19:18:31 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Finds the last occurrence of a character in a string.
 * @param str The string to search.
 * @param c The character to find (converted to unsigned char).
 * @return Pointer to the last occurrence of c in str, or NULL if not found.
 */
char	*ft_strrchr(const char *str, int c)
{
	const char	*found;

	if (str == NULL)
        return NULL;
	found = NULL;
	while (1)
	{
		if (*str == (unsigned char)c)
			found = str;
		if (*str == '\0')
			break ;
		str++;
	}
	return ((char *)found);
}
