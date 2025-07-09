/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:30:14 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/09 15:03:27 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Determines whether variable expansion is required in the given tokens list.
 *
 * This function iterates through an EOF-terminated doubly linked list of tokens and checks for the presence
 * of the '$' character in tokens of type TOKEN_WORD that are either unquoted or double-quoted. If such a token
 * is found, the function concludes that variable expansion is needed.
 *
 * @param tokens_list Pointer to the head of an EOF-terminated doubly linked list of tokens (t_token).
 * @return 1 if variable expansion is needed, 0 otherwise.
 */
int needs_expansion(t_token *tokens_list)
{
	t_token *current;

	current = tokens_list;
	while (current->token_type != TOKEN_EOF)
	{
		if (current->token_type == TOKEN_WORD &&
			(current->quote_type == NON_QUOTE || 
				current->quote_type == DOUBLE_QUOTE) &&
			(ft_strchr(current->value, '$') &&
			!ft_isoperator(ft_strchr(current->value, '$') + 1, 0) &&
			!ft_isspace(*(ft_strchr(current->value, '$') + 1)) &&
			*(ft_strchr(current->value, '$') + 1) != '\0'))
		{
			return(1);
		}
		else
			current = current->next;
	}
	return (0);
}
