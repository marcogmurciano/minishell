/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:44:47 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/14 13:59:15 by dbarba-v         ###   ########.fr       */
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

static int check_for_unsuported_characters(t_minishell *minishell, t_token* token)
{
	int i;

	i = 0;

	if (token->quote_type == DOUBLE_QUOTE ||
		token->quote_type == NON_QUOTE)
	{
		while (token->value[i])
		{
			if (token->value[i] == '\\' ||
				token->value[i] == ';' ||
				token->value[i] == '&' ||
				token->value[i] == '+' ||
				token->value[i] == '?' ||
				token->value[i] == '{' ||
				token->value[i] == '}' ||
				token->value[i] == ')' ||
				token->value[i] == '(' ||
				token->value[i] == '!')
				return(syntax_error(NULL, minishell));
			i++;
		}
	}
	return(0);
}

int	syntax_check(t_minishell *minishell)
{
	t_token	*token;
	int syntax_error;

	syntax_error = 0;
	token = minishell->tokens_list;
	while (token && token->next)
	{
		syntax_error = check_for_unsuported_characters(minishell, token);
		if (token->token_type == TOKEN_REDIR_IN || 
			token->token_type == TOKEN_REDIR_OUT && 
			!syntax_error)
			syntax_error = check_redirection(minishell, token);
		else if (token->token_type == TOKEN_HEREDOC || 
			token->token_type == TOKEN_APPEND && 
			!syntax_error)
			syntax_error = check_heredoc_append(minishell, token);
		else if (token->token_type == TOKEN_PIPE &&
			!syntax_error)
			syntax_error = check_pipe(minishell, token);
		token = token->next;
	}
	return (syntax_error);
}
