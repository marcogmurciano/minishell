/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:24 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/10 20:45:38 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Tokenizes the given input string into a linked list of tokens.
 * Trims whitespace from input before processing.
 *
 * @param input The null-terminated input string to tokenize.
 * @return Pointer to the head of the linked list of tokens.
 *         Returns NULL if allocation for trimmed_input fails.
 */
static t_token *tokenizer(t_minishell *minishell)
{
	t_token 	*token_head;
	int i;

	token_head = NULL;
	i = 0;
	while(minishell->input && minishell->input[i])
	{
		if(ft_isspace(minishell->input[i]))
			i++;
		else if(ft_isoperator(minishell->input, i))
			i += handle_operator(&token_head, minishell, i);
		else if(ft_isquote(minishell->input, i))
			i += handle_quoted_word(&token_head, minishell, i);
		else
			i += handle_nonquoted_word(&token_head, minishell, i);
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
 * @param minishell Pointer to the minishell structure containing input and tokens list.
 */
void tokenization(t_minishell *minishell)
{
	minishell->tokens_list = tokenizer(minishell);
	if(needs_expansion(minishell->tokens_list))
	{
		free(minishell->input);
		minishell->input = NULL;
		minishell->input = expand_tokens_list(minishell);
		free_tokens_list(&(minishell->tokens_list));
		minishell->tokens_list = NULL;
		minishell->tokens_list = tokenizer(minishell);
	}
	refine_token_roles(minishell->tokens_list);
}
