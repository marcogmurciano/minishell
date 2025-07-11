/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:44:47 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/11 15:42:08 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_redirection(t_minishell *minishell, t_token *token)
{
	if (token->token_type == TOKEN_REDIR_IN
		&& token->next->token_type != TOKEN_REDIR_IN_FILE)
		return (syntax_error(NULL, minishell));
	else if (token->token_type == TOKEN_REDIR_OUT
		&& token->next->token_type != TOKEN_REDIR_OUT_FILE)
		return (syntax_error(NULL, minishell));
	return (0);
}

static int	check_heredoc_append(t_minishell *minishell, t_token *token)
{
	if (token->token_type == TOKEN_HEREDOC
		&& token->next->token_type != TOKEN_HEREDOC_DELIM)
		return (syntax_error(NULL, minishell));
	else if (token->token_type == TOKEN_APPEND
		&& token->next->token_type != TOKEN_APPEND_FILE)
		return (syntax_error(NULL, minishell));
	return (0);
}

static int	check_pipe(t_minishell *minishell, t_token *token)
{
	if (token->next->token_type != TOKEN_CMD)
		return (syntax_error(NULL, minishell));
	return (0);
}

int	syntax_check(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->tokens_list;
	while (token && token->next)
	{
		if (token->token_type == TOKEN_REDIR_IN
			|| token->token_type == TOKEN_REDIR_OUT)
			check_redirection(minishell, token);
		else if (token->token_type == TOKEN_HEREDOC
			|| token->token_type == TOKEN_APPEND)
			check_heredoc_append(minishell, token);
		else if (token->token_type == TOKEN_PIPE)
			check_pipe(minishell, token);
		token = token->next;
	}
	return (0);
}
