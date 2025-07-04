/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:32:54 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 18:22:16 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Checks if a character is a sign ('+' or '-').
 * 
 * @param c The character to check (represented as an int).
 * @return 1 if the character is '+', 2 if '-', 0 otherwise.
 */
int	ft_issign(int c)
{
	if (c == '+')
		return (1);
	if (c == '-')
		return (2);
	return (0);
}
