/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:44:47 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/08 14:58:45 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void syntax_check(t_minishell *minishell)
{
	t_token *token;

	token = minishell->tokens_list;
	while(token && token->next)
	{
		if(token->token_type == TOKEN_REDIR_IN)
		{
			if (token->next->token_type != TOKEN_REDIR_IN_FILE)
				syntax_error(minishell);
		}
		else if(token->token_type == TOKEN_REDIR_OUT)
		{
			if (token->next->token_type != TOKEN_REDIR_OUT_FILE)
				syntax_error(minishell);
		}
		else if(token->token_type == TOKEN_HEREDOC)
		{
			if (token->next->token_type != TOKEN_HEREDOC_DELIM)
				syntax_error(minishell);
		}
		token = token->next;
	}
}