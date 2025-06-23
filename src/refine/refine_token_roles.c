/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_token_roles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:31:02 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/11 16:07:51 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * For word tokens assign a more specific token type
 */
static int	get_new_token_type(t_token *current, t_token *prev)
{
	(void)current;
	if (prev == NULL)
		return (TOKEN_CMD);
	if (prev->token_type == TOKEN_HEREDOC)
		return (TOKEN_HEREDOC_DELIM);
	if (prev->token_type == TOKEN_PIPE)
		return (TOKEN_CMD);
	if (prev->token_type == TOKEN_REDIR_IN)
		return (TOKEN_REDIR_IN_FILE);
	if (prev->token_type == TOKEN_REDIR_OUT)
		return (TOKEN_REDIR_OUT_FILE);
	if (prev->token_type == TOKEN_APPEND)
		return (TOKEN_APPEND_FILE);
	while (prev->prev && prev->prev->token_type != TOKEN_PIPE)
	{
		if (prev->token_type == TOKEN_CMD || prev->token_type == TOKEN_ARG)
			return (TOKEN_ARG);
		prev = prev->prev;
	}
	return (TOKEN_CMD);
}

/**
 * For word tokens call a refinement function
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
