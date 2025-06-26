/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:30:14 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/26 16:44:37 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int needs_expansion(t_token *tokens_list)
{
	t_token *current;

	current = tokens_list;
	while (current->token_type != TOKEN_EOF)
	{
		if (current->token_type == TOKEN_WORD &&
			(current->quote_type == NON_QUOTE || 
				current->quote_type == DOUBLE_QUOTE)&&
			strchr(current->value, '$'))
		{
			return(1);
		}
		else
			current = current->next;
	}
	return (0);
}
