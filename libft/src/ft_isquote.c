/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:54:45 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/27 16:24:37 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Checks if the character at a given position in the input is a quote character.
 *
 * Quotes are defined as single quote (') or double quote (").
 *
 * @param trimmed_input The input string to check.
 * @param i The index in the string to check for a quote.
 * @return 1 if the character is a quote, 0 otherwise.
 */
int ft_isquote(char *input, int i)
{
	if(input[i] == '\'' || input[i] == '\"')
		return (1);
	return (0);
}