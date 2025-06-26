/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:06:01 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/26 16:07:27 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *create_nonword_token(t_token_type t_type) 
{
    t_token *token;

	token = calloc(1, sizeof(t_token));
    if (!token) 
	{
        return (NULL); // Handle allocation failure
    }
    token->token_type = t_type;
    return (token);
}

t_token *create_word_token(t_token_type t_type, char *word, char quote) 
{
    t_token *token;

	token = calloc(1, sizeof(t_token));
    if (!token) 
	{
        return (NULL); // Handle allocation failure
    }
    token->token_type = t_type;
	token->value = ft_strdup(word);
	if(quote == '\0')
		token->quote_type = NON_QUOTE;
	if(quote == '\'')
		token->quote_type = SINGLE_QUOTE;
	if(quote == '\"')
		token->quote_type = DOUBLE_QUOTE;
    return (token);
}

t_token *create_eof_token() 
{
    t_token *token;

	token = calloc(1, sizeof(t_token));
    if (!token) 
	{
        return (NULL); // Handle allocation failure
    }
    token->token_type = TOKEN_EOF;
    return (token);
}