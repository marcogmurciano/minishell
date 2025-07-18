/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_token_roles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:31:02 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:31:37 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_new_token_type(t_token *current, t_token *prev)
{
	if (prev == NULL)
		return (TOKEN_CMD);
	if (prev->token_type == TOKEN_HEREDOC)
		return (TOKEN_HEREDOC_DELIM);
	if (prev->token_type == TOKEN_PIPE
		|| prev->token_type == TOKEN_REDIR_IN_FILE
		|| prev->token_type == TOKEN_HEREDOC_DELIM)
		return (TOKEN_CMD);
	if (prev->token_type == TOKEN_CMD || prev->token_type == TOKEN_ARG)
		return (TOKEN_ARG);
	if (prev->token_type == TOKEN_REDIR_IN)
		return (TOKEN_REDIR_IN_FILE);
	if (prev->token_type == TOKEN_REDIR_OUT)
		return (TOKEN_REDIR_OUT_FILE);
	if (prev->token_type == TOKEN_APPEND)
		return (TOKEN_APPEND_FILE);
	return (current->token_type);
}

/**
 * Refines the roles of tokens in a linked list based on context.
 * @param tokens_head Pointer to the head of the token list.
 */
void	refine_token_roles(t_token *tokens_head)
{
	t_token	*current;

	current = tokens_head;
	while (current && current->token_type != TOKEN_EOF)
	{
		if (current->token_type == TOKEN_WORD)
		{
			current->token_type = get_new_token_type(current, current->prev);
		}
		current = current->next;
	}
}
