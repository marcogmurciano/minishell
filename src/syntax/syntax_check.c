/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:44:47 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/07 15:16:57 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Syntax checks related to redirections
 */
static int	check_redirection(t_minishell *minishell, t_token *token)
{
	if (token->token_type == TOKEN_REDIR_IN
		&& token->next->token_type != TOKEN_REDIR_IN_FILE)
		return (syntax_error(NULL, minishell, 1));
	else if (token->token_type == TOKEN_REDIR_OUT
		&& token->next->token_type != TOKEN_REDIR_OUT_FILE)
		return (syntax_error(NULL, minishell, 1));
	else if (token->token_type == TOKEN_APPEND
		&& token->next->token_type != TOKEN_APPEND_FILE)
		return (syntax_error(NULL, minishell, 1));
	else if (token->token_type == TOKEN_HEREDOC
		&& token->next->token_type != TOKEN_HEREDOC_DELIM)
		return (syntax_error(NULL, minishell, 2));
	return (0);
}

/**
 * Syntax checks for pipe tokens
 */
static int	check_pipe(t_minishell *minishell, t_token *token)
{
	if (token->next && (token->next->token_type != TOKEN_CMD
			&& token->next->token_type != TOKEN_REDIR_IN
			&& token->next->token_type != TOKEN_REDIR_OUT
			&& token->next->token_type != TOKEN_HEREDOC
			&& token->next->token_type != TOKEN_APPEND))
		return (syntax_error(NULL, minishell, 3));
	return (0);
}

/**
 * Syntax checks for unsupported characters
 */
static int	check_for_unsupported_characters(t_minishell *minishell,
		t_token *token)
{
	if (token->quote_type == DOUBLE_QUOTE || token->quote_type == NON_QUOTE)
	{
		if ((token->value[1] == '\0') && (token->value[0] == '\\'
				|| token->value[0] == ';' || token->value[0] == '&'
				|| token->value[0] == '?' || token->value[0] == '{'
				|| token->value[0] == '}' || token->value[0] == ')'
				|| token->value[0] == '(' || token->value[0] == '!'))
		{
			syntax_error(NULL, minishell, 0);
			return (1);
		}
	}
	return (0);
}

/**
 * Syntax checks distributor
 */
int	syntax_check(t_minishell *minishell)
{
	t_token	*token;
	int		syntax_error;

	syntax_error = 0;
	token = minishell->tokens_list;
	while (token && token->next)
	{
		syntax_error = check_for_unsupported_characters(minishell, token);
		if ((token->token_type == TOKEN_REDIR_IN
				|| token->token_type == TOKEN_REDIR_OUT
				|| token->token_type == TOKEN_APPEND) && !syntax_error)
			syntax_error = check_redirection(minishell, token);
		else if (token->token_type == TOKEN_HEREDOC && !syntax_error)
			syntax_error = check_heredoc(minishell, token);
		else if (token->token_type == TOKEN_PIPE && !syntax_error)
			syntax_error = check_pipe(minishell, token);
		if (syntax_error)
			break ;
		token = token->next;
	}
	return (syntax_error);
}
