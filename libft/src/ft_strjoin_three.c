/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:17:08 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 19:08:02 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Joins three strings into a new dynamically allocated string.
 * @param s1 First string to join.
 * @param s2 Second string to join.
 * @param s3 Third string to join.
 * @return Pointer to the newly allocated joined string, or NULL on failure.
 */
char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*joined;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	joined = ft_strjoin(temp, s3);
	free(temp);
	if (!joined)
		return (NULL);
	return (joined);
}
