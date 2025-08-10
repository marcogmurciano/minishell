/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:06:01 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/10 18:20:53 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Function to create non-word tokens
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
 * Function to create empty quoted and non-quoted word tokens
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
	if (quote != '\'' && quote != '\"')
		token->quote_type = NON_QUOTE;
	if (quote == '\'')
		token->quote_type = SINGLE_QUOTE;
	if (quote == '\"')
		token->quote_type = DOUBLE_QUOTE;
	return (token);
}

/**
 * Function to create EOF tokens for the end of the tokens list
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
