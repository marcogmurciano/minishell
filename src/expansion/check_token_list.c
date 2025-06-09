/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:30:14 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:37:29 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Checks if the provided token's value needs expansion of variables
 */
int	needs_expansion(t_token *tokens_list)
{
	t_token	*current;

	current = tokens_list;
	while (current->token_type != TOKEN_EOF)
	{
		if (current->token_type == TOKEN_WORD
			&& (current->quote_type == NON_QUOTE
				|| current->quote_type == DOUBLE_QUOTE)
			&& (ft_strchr(current->value, '$')
				&& !ft_isoperator(ft_strchr(current->value, '$') + 1, 0)
				&& !ft_isspace(*(ft_strchr(current->value, '$') + 1))
				&& *(ft_strchr(current->value, '$') + 1) != '\0'))
		{
			return (1);
		}
		else
			current = current->next;
	}
	return (0);
}
