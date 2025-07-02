/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_tokens_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:01:05 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/02 16:17:29 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Tokenizes the input and expands tokens if needed.
 *
 * This function tokenizes the minishell input and, if expansion is required,
 * frees the old input, expands the tokens, and retokenizes the input.
 *
 * @param minishell Pointer to the minishell structure containing input and tokens list.
 */
void initialize_expanded_tokens_list(t_minishell *minishell)
{
	minishell->tokens_list = tokenizer(minishell->input);
	if(needs_expansion(minishell->tokens_list))
	{
		printf("%s\n", minishell->input);
		free(minishell->input);
		minishell->input = NULL;
		minishell->input = expand_tokens_list(minishell);
		printf("%s\n", minishell->input);
		free_tokens_list(&(minishell->tokens_list));
		minishell->tokens_list = NULL;
		minishell->tokens_list = tokenizer(minishell->input);
	}
}