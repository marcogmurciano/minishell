/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_token_roles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:31:02 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/02 11:39:04 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void refine_token_roles(t_token *tokens_head)
{
    t_token *current = tokens_head;
	
    while (current && current->token_type != TOKEN_EOF)
    {
        if (current->token_type == TOKEN_WORD && current->prev)
        {
            if (current->prev->token_type == TOKEN_HEREDOC)
                current->token_type = TOKEN_HEREDOC_DELIM;
            else if (current->prev->token_type == TOKEN_PIPE)
                current->token_type = TOKEN_CMD;
            else if (current->prev->token_type == TOKEN_CMD ||
                     current->prev->token_type == TOKEN_ARG)
                current->token_type = TOKEN_ARG;
            else if (current->prev->token_type == TOKEN_REDIR_IN)
                current->token_type = TOKEN_REDIR_IN_FILE;
            else if (current->prev->token_type == TOKEN_REDIR_OUT)
                current->token_type = TOKEN_REDIR_OUT_FILE;
            else if (current->prev->token_type == TOKEN_APPEND)
                current->token_type = TOKEN_APPEND_FILE;
        }
		if (current->token_type == TOKEN_WORD && current->prev == NULL)
			current->token_type = TOKEN_CMD;
        current = current->next;
    }
}

