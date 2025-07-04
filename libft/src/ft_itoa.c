/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:20:56 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 18:30:11 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Calculates the length (in digits) required to represent an integer 
 * as a string, including sign.
 * @param n The integer to measure.
 * @return The number of characters needed.
 */
static int	ft_int_length(int n)
{
	int		lenght;
	long	num;

	lenght = 0;
	num = n;
	if (num < 0)
	{
		lenght++;
		num = -num;
	}
	while (num >= 10)
	{
		num /= 10;
		lenght++;
	}
	return (lenght);
}

/**
 * @brief Converts an integer to a newly allocated string representation.
 * @param n The integer to convert.
 * @return Pointer to the string representation (must be freed by caller), or NULL on allocation failure.
 */
char	*ft_itoa(int n)
{
	long	num;
	char	*str;
	int		len;

	num = n;
	len = ft_int_length(num);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
        str[0] = '0';
	while (--len >= 0 && str[len] != '-')
	{
		str[len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
