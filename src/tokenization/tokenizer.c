/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:24 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/04 10:35:54 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_next_token(t_token **token_head, t_minishell *minishell,
								int i, int *e)
{
	if (ft_isspace(minishell->input[i]))
		(*e) = 1;
	else if (ft_isoperator(minishell->input, i))
		(*e) = handle_operator(token_head, minishell, i);
	else if (minishell->input[i] == '$' && minishell->input[i + 1]
		&& ft_isquote(minishell->input, i + 1))
		(*e) = handle_ansi_c_quoted_word(token_head, minishell, i);
	else if (ft_isquote(minishell->input, i))
		(*e) = handle_quoted_word(token_head, minishell, i);
	else
		(*e) = handle_nonquoted_word(token_head, minishell, i);
	return (*e);
}

static t_token	*handle_tokenizer_error(t_minishell *minishell)
{
	free_tokens_list(&(minishell->tokens_list));
	free(minishell->input);
	minishell->input = NULL;
	return (NULL);
}

/**
 * Tokenizes the given input string into a linked list of tokens.
 * Trims whitespace from input before processing.
 *
 * @param input The null-terminated input string to tokenize.
 * @return Pointer to the head of the linked list of tokens.
 *         Returns NULL if allocation for trimmed_input fails.
 */
static t_token	*tokenizer(t_minishell *minishell)
{
	t_token	*token_head;
	int		i;
	int		e;

	token_head = NULL;
	i = 0;
	while (minishell->input && minishell->input[i])
	{
		e = 0;
		if (handle_next_token(&token_head, minishell, i, &e) == -1)
		{
			handle_tokenizer_error(minishell);
			return (NULL);
		}
		i += e;
	}
	add_eof_token(&token_head);
	free(minishell->input);
	minishell->input = NULL;
	return (token_head);
}

/**
 * @brief Tokenizes the input and expands tokens if needed.
 *
 * This function tokenizes the minishell input, if expansion is required,
 * frees the old input, expands the tokens, and retokenizes the input.
 * Then it refines the token roles.
 *
 * @param minishell Pointer to the minishell structure containing needed info.
 */
int	tokenization(t_minishell *minishell)
{
	minishell->tokens_list = tokenizer(minishell);
	if (minishell->tokens_list == NULL)
		return (1);
	if (needs_expansion(minishell->tokens_list))
	{
		free(minishell->input);
		minishell->input = NULL;
		minishell->input = expand_tokens_list(minishell);
		free_tokens_list(&(minishell->tokens_list));
		minishell->tokens_list = NULL;
		minishell->tokens_list = tokenizer(minishell);
	}
	join_tokens(&(minishell->tokens_list));
	refine_token_roles(minishell->tokens_list);
	return (0);
}
