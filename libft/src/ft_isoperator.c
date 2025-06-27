/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isoperator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:52:06 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/27 15:54:26 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Checks if the character at a given position in the input is an operator.
 *
 * Operators are defined as '|', '<', or '>'.
 *
 * @param input The input string to check.
 * @param i The index in the string to check for an operator.
 * @return 1 if the character is an operator, 0 otherwise.
 */
int	ft_isoperator(char *input, int i)
{
	if(input[i] == '|' || input[i] == '<' || input[i] == '>')
		return (1);
	return (0);
}