/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:05:01 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:28:26 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Adds a non-word token to the end of the token list.
 *
 * Creates a new token of the specified type using create_nonword_token()
 * and appends it to the end of the linked list pointed to by token_head.
 *
 * @param token_head Pointer to the head pointer of the token list.
 * @param t_type The type of the non-word token to be added.
 * @return 0 on success, 1 on allocation failure.
 */
int	add_nonword_token(t_token **token_head, t_token_type t_type, char *value)
{
	t_token	*new_token;
	t_token	*token_last;

	new_token = create_nonword_token(t_type, value);
	if (!new_token)
	{
		return (1);
	}
	if (!*token_head)
	{
		*token_head = new_token;
	}
	else
	{
		token_last = *token_head;
		while (token_last->next)
		{
			token_last = token_last->next;
		}
		token_last->next = new_token;
		new_token->prev = token_last;
	}
	return (0);
}

/**
 * @brief Adds a word token to the end of the token list.
 *
 * Creates a new token of the specified type, word, and quote using
 * create_word_token() and appends it to the end of the linked list
 * pointed to by token_head.
 *
 * @param token_head Pointer to the head pointer of the token list.
 * @param t_type The type of the word token to be added.
 * @param word The word string to assign to the token.
 * @param quote The quote character associated with the word (if any).
 * @return 0 on success, 1 on allocation failure.
 */
int	add_word_token(t_token **token_head, t_token_type t_type, char *word,
		char quote)
{
	t_token	*new_token;
	t_token	*token_last;

	new_token = create_word_token(t_type, word, quote);
	if (!new_token)
	{
		return (1);
	}
	if (!*token_head)
	{
		*token_head = new_token;
	}
	else
	{
		token_last = *token_head;
		while (token_last && token_last->next)
		{
			token_last = token_last->next;
		}
		token_last->next = new_token;
		new_token->prev = token_last;
	}
	return (0);
}

/**
 * @brief Adds an EOF (end-of-file) token to the end of the token list.
 *
 * Creates a new EOF token using create_eof_token() and appends it to the
 * end of the linked list pointed to by token_head.
 *
 * @param token_head Pointer to the head pointer of the token list.
 * @return 0 on success, 1 on allocation failure.
 */
int	add_eof_token(t_token **token_head)
{
	t_token	*new_token;
	t_token	*token_last;

	new_token = create_eof_token();
	if (!new_token)
	{
		return (1);
	}
	if (!*token_head)
	{
		*token_head = new_token;
	}
	else
	{
		token_last = *token_head;
		while (token_last && token_last->next)
		{
			token_last = token_last->next;
		}
		token_last->next = new_token;
		new_token->prev = token_last;
	}
	return (0);
}
