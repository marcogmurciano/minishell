/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:06:01 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:25:50 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Creates a new non-word token of the specified type.
 *
 * Allocates memory for a token, assigns the given token type,
 * and returns a pointer to the new token. Returns NULL if allocation fails.
 *
 * @param t_type The type of token to create.
 * @return Pointer to the newly created token, or NULL on failure.
 */
t_token	*create_nonword_token(t_token_type t_type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
	{
		return (NULL);
	}
	token->token_type = t_type;
	token->value = ft_strdup(value);
	return (token);
}

/**
 * @brief Creates a new word token with the provided value and quote type.
 *
 * Allocates memory for a token, assigns the given token type and dup word,
 * sets the quote type based on the provided character, and returns a pointer
 * to the new token.
 *
 * @param t_type The type of token to create.
 * @param word The string value for the token (will be duplicated).
 * @param quote The quote character type: '\0' for none, '\'' , '\"'.
 * @return Pointer to the newly created token, or NULL on failure.
 */
t_token	*create_word_token(t_token_type t_type, char *word, char quote)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
	{
		return (NULL);
	}
	token->token_type = t_type;
	token->value = ft_strdup(word);
	if (quote == '\0')
		token->quote_type = NON_QUOTE;
	if (quote == '\'')
		token->quote_type = SINGLE_QUOTE;
	if (quote == '\"')
		token->quote_type = DOUBLE_QUOTE;
	return (token);
}

/**
 * @brief Creates a new end-of-file (EOF) token.
 *
 * Allocates memory for a token, assigns the EOF token type,
 * and returns a pointer to the new token. Returns NULL if allocation fails.
 *
 * @return Pointer to the newly created EOF token, or NULL on failure.
 */
t_token	*create_eof_token(void)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
	{
		return (NULL);
	}
	token->token_type = TOKEN_EOF;
	return (token);
}
