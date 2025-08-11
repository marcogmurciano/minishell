/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:05:01 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/11 10:37:52 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	add_word_token(t_token **token_head, char *word, char quote_char,
					int is_spaced)
{
	t_token	*new_token;
	t_token	*token_last;

	new_token = create_word_token(TOKEN_WORD, word, quote_char);
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
	if (is_spaced)
		new_token->spaced = 1;
	return (0);
}

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
