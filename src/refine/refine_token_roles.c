/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_token_roles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:31:02 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/09 09:58:08 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Refines the roles of tokens in a linked list based on context.
 * @param tokens_head Pointer to the head of the token list.
 */
void refine_token_roles(t_token *tokens_head)
{
    t_token *current = tokens_head;

    while (current && current->token_type != TOKEN_EOF) {
        if (current->token_type == TOKEN_WORD) 
        {
            if (current->prev == NULL)
                current->token_type = TOKEN_CMD;
            else 
            {
                t_token *prev = current->prev;
                if (prev->token_type == TOKEN_HEREDOC) 
                    current->token_type = TOKEN_HEREDOC_DELIM;
                else if (prev->token_type == TOKEN_PIPE ||
                         prev->token_type == TOKEN_REDIR_IN_FILE ||
                         prev->token_type == TOKEN_HEREDOC_DELIM) 
                    current->token_type = TOKEN_CMD;
                else if (prev->token_type == TOKEN_CMD ||
                         prev->token_type == TOKEN_ARG)
                    current->token_type = TOKEN_ARG;
                else if (prev->token_type == TOKEN_REDIR_IN)
                    current->token_type = TOKEN_REDIR_IN_FILE;
                else if (prev->token_type == TOKEN_REDIR_OUT)
                    current->token_type = TOKEN_REDIR_OUT_FILE;
                else if (prev->token_type == TOKEN_APPEND)
                    current->token_type = TOKEN_APPEND_FILE;
            }
        }
        current = current->next;
    }
}

