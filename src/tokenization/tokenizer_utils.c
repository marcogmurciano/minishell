/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:11:45 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 12:42:10 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Extracts a quoted word from the input using the given delimiter.
 *
 * The word is extracted starting from index 1 up to (but not including)
 * the next occurrence of the delimiter.
 *
 * @param minishell The structure to get minishell->input.
 * @param delimiter The quote character that marks the end of the quoted word.
 * @return A pointer to the newly allocated string containing the quoted word,
 * or NULL on allocation failure.
 */
char	*get_quoted_word(t_minishell *minishell, char delimiter, int i)
{
	char	*word;
	int		word_length;

	word = NULL;
	word_length = 0;
	while (minishell->input[(i + 1) + word_length] && minishell->input[(i + 1)
			+ word_length] != delimiter)
	{
		word_length++;
	}
	if (minishell->input[(i + 1) + word_length] == '\0')
		return (syntax_error(NULL, minishell, 4), NULL);
	word = ft_substr(minishell->input, i + 1, word_length);
	if (!word)
		malloc_error(minishell);
	return (word);
}

/**
 * @brief Extracts an unquoted word from the input string.
 *
 * The word is extracted starting from index 0 up to the first whitespace,
 * operator ('|', '<', '>'), quote ('\'', '\"'), or '$' character.
 *
 * @param minishell Structure from which to retrieve the input
 * @param input Pointer to the start of the word within the imput
 * @return A pointer to the newly allocated string containing the unquoted word,
 * or NULL on allocation failure.
 */
char	*get_unquoted_word(t_minishell *minishell, char *input)
{
	char	*word;
	int		word_length;

	word = NULL;
	word_length = 1;
	while (input[word_length] && !ft_isspace(input[word_length])
		&& input[word_length] != '|' && input[word_length] != '<'
		&& input[word_length] != '>' && input[word_length] != '\''
		&& input[word_length] != '\"' && input[word_length] != '$')
	{
		word_length++;
	}
	word = ft_substr(input, 0, word_length);
	if (!word)
		malloc_error(minishell);
	return (word);
}
