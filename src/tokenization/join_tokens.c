/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:45:00 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/30 13:20:53 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	join_tokens(t_token **tokens_head)
{
	t_token	*current;
	t_token	*next;
	char	*joined_token_values;

	current = *tokens_head;
	while (current && current->next && current->token_type != TOKEN_EOF)
	{
		next = current->next;
		if (current->token_type == TOKEN_WORD && next->token_type == TOKEN_WORD
			&& !next->spaced && next->token_type != TOKEN_EOF)
		{
			joined_token_values = ft_strjoin(current->value, next->value);
			free(current->value);
			current->value = joined_token_values;
			current->next = next->next;
			if (next->next)
				next->next->prev = current;
			free(next);
		}
		else
			current = current->next;
	}
}
