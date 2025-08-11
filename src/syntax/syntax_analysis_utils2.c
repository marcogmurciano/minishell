/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:57:28 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/11 10:38:21 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Retrive if last out redirection is append
 */
int	get_append_status(t_token *segment)
{
	t_token	*current;

	current = segment;
	while (current && current->next != NULL
		&& current->next->token_type != TOKEN_EOF)
	{
		current = current->next;
	}
	while (current && current->prev != NULL)
	{
		if (current->token_type == TOKEN_APPEND_FILE
			|| current->token_type == TOKEN_REDIR_OUT_FILE)
		{
			if (current->token_type == TOKEN_APPEND_FILE)
				return (1);
			else
				return (0);
		}
		current = current->prev;
	}
	return (0);
}

/**
 * Retrive last type of input redirection. 0 -> FILE // 1-> HEREDOC // -1 NON
 */
int	get_last_in_type(t_token *segment)
{
	t_token	*current;
	int		i;

	i = -1;
	current = segment;
	while (current)
	{
		if (current->token_type == TOKEN_REDIR_IN)
			i = 0;
		else if (current->token_type == TOKEN_HEREDOC)
			i = 1;
		current = current->next;
	}
	return (i);
}

/**
 * Get status of wether expansion of heredoc contents is needed
 */
int	get_heredoc_expansion_status(t_token *segment)
{
	t_token	*current;
	int		last_heredoc;

	current = segment;
	last_heredoc = 0;
	while (current && current->next)
	{
		if (current->token_type == TOKEN_HEREDOC)
		{
			current = current->next;
			if (current->quote_type == NON_QUOTE)
				last_heredoc = 1;
			else
				last_heredoc = 0;
		}
		current = current->next;
	}
	return (last_heredoc);
}

/**
 * Detaches token from previous nodes
 */
void	unlink_token(t_token *token)
{
	if (token->prev)
		token->prev->next = NULL;
	token->prev = NULL;
}
