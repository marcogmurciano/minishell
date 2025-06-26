/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:11:45 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/26 16:11:48 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_operator(char *trimmed_input, int i)
{
	if(trimmed_input[i] == '|' || trimmed_input[i] == '<' || trimmed_input[i] == '>')
		return (1);
	return (0);
}

int is_quote(char *trimmed_input, int i)
{
	if(trimmed_input[i] == '\'' || trimmed_input[i] == '\"')
		return (1);
	return (0);
}

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