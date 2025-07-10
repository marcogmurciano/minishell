/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:44:47 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/10 15:58:55 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int syntax_check(t_minishell *minishell)
{
	t_token *token;

	token = minishell->tokens_list;
	while(token && token->next)
	{
		if(token->token_type == TOKEN_REDIR_IN)
		{
			if (token->next->token_type != TOKEN_REDIR_IN_FILE)
				return(syntax_error(NULL));
		}
		else if(token->token_type == TOKEN_REDIR_OUT)
		{
			if (token->next->token_type != TOKEN_REDIR_OUT_FILE)
				return(syntax_error(NULL));
		}
		else if(token->token_type == TOKEN_APPEND)
		{
			if (token->next->token_type != TOKEN_APPEND_FILE)
				return(syntax_error(NULL));
		}
		else if(token->token_type == TOKEN_HEREDOC)
		{
			if (token->next->token_type != TOKEN_HEREDOC_DELIM)
				return(syntax_error(NULL));
		}
		else if(token->token_type == TOKEN_PIPE)
		{
			if (token->next->token_type != TOKEN_CMD)
				return(syntax_error(NULL));
		}
		token = token->next;
	}
	return (0);
}
