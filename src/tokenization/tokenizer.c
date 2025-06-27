/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:24 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/27 16:25:49 by dbarba-v         ###   ########.fr       */
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
t_token *tokenizer(char *input)
{
	char 		*trimmed_input;
	t_token 	*token_head;
	int i;

	trimmed_input = ft_strtrim(input, "\n\t ");
	if (!trimmed_input)
        return NULL; // Allocation failed.
	token_head = NULL;
	i = 0;
	while(input && input[i])
	{
		if(ft_isspace(input[i]))
			i++;
		else if(ft_isoperator(trimmed_input, i))
			i += handle_operator(&token_head, trimmed_input, i);
		else if(ft_isquote(trimmed_input, i))
			i += handle_quoted_word(&token_head, trimmed_input, i);
		else
			i += handle_nonquoted_word(&token_head, trimmed_input, i);
	}
	add_eof_token(&token_head);
	free(trimmed_input);
	return (token_head);
}
