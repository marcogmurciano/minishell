/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:11:45 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/27 15:55:29 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Extracts a quoted word from the input string using the given delimiter.
 *
 * The word is extracted starting from index 1 up to (but not including) the next occurrence of the delimiter.
 *
 * @param trimmed_input The input string, with the first character assumed to be the opening quote.
 * @param delimiter The quote character that marks the end of the quoted word.
 * @return A pointer to the newly allocated string containing the quoted word, or NULL on allocation failure.
 */
char *get_quoted_word(char *trimmed_input, char delimiter)
{
	char *word;
	int word_length;

	word = NULL;
	word_length = 0;
	while(trimmed_input[1 + word_length] && 
		trimmed_input[1 + word_length] != delimiter)
	{
		word_length++;
	}
	word = ft_substr(trimmed_input, 1, word_length);
	if (!word) 
		return (NULL); // Handle allocation failure
	return (word);
}

/**
 * @brief Extracts an unquoted word from the input string.
 *
 * The word is extracted starting from index 0 up to the first whitespace,
 * operator ('|', '<', '>'), quote ('\'', '\"'), or '$' character.
 *
 * @param trimmed_input The input string to extract the word from.
 * @return A pointer to the newly allocated string containing the unquoted word, or NULL on allocation failure.
 */
char *get_unquoted_word(char *trimmed_input)
{
	char *word;
	int word_length;

	word = NULL;
	word_length = 1;
	while(trimmed_input[word_length] && 
		!ft_isspace(trimmed_input[word_length]) &&
		trimmed_input[word_length] != '|' &&
		trimmed_input[word_length] != '<' &&
		trimmed_input[word_length] != '>' &&
		trimmed_input[word_length] != '\'' &&
		trimmed_input[word_length] != '\"' &&
		trimmed_input[word_length] != '$')
	{
		word_length++;
	}
	word = ft_substr(trimmed_input, 0, word_length);
	if (!word) 
		return (NULL); // Handle allocation failure
	return (word);
}