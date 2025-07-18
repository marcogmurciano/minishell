/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:49:53 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:34:27 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Frees a linked list of tokens, releasing all associated memory.
 * @param token_head Double pointer to the head of the token list.
 */
void	free_tokens_list(t_token **token_head)
{
	t_token	*current_token;
	t_token	*temp_token;

	if (token_head == NULL || *token_head == NULL)
	{
		return ;
	}
	current_token = *token_head;
	while (current_token)
	{
		if (current_token->value)
		{
			free(current_token->value);
			current_token->value = NULL;
		}
		temp_token = current_token;
		current_token = current_token->next;
		free(temp_token);
	}
	*token_head = NULL;
}
