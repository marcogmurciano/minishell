/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:57:28 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/14 17:02:26 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Constructs an argument vector (argv) from a given token segment.
 *
 * This function scans the provided segment for tokens of type TOKEN_CMD or 
 * TOKEN_ARG, allocates a new null-terminated array of strings, and copies the 
 * corresponding token values into the array. Handles allocation errors 
 * gracefully.
 *
 * @param minishell Pointer to the minishell structure for error handling.
 * @param segment Pointer to the head of the token segment to process.
 * @return A newly allocated, null-terminated array of strings representing 
 * the command and its arguments, or NULL on allocation failure.
 */
char	**get_cmd_argv(t_minishell *minishell, t_token *segment)
{
	char	**new_strings_array;
	t_token	*token;
	int		i;

	i = 0;
	token = segment;
	while (token && token->token_type != TOKEN_EOF)
	{
		if (token->token_type == TOKEN_CMD || token->token_type == TOKEN_ARG)
			i++;
		token = token->next;
	}
	new_strings_array = ft_calloc(i + 1, sizeof(char *));
	if (!new_strings_array)
	{
		free_tokens_list(&segment);
		malloc_error(minishell);
	}
	i = 0;
	token = segment;
	while (token && token->token_type != TOKEN_EOF)
	{
		if (token->token_type == TOKEN_CMD || token->token_type == TOKEN_ARG)
		{
			new_strings_array[i] = ft_strdup(token->value);
			if (!new_strings_array[i])
			{
				free_array(new_strings_array, i);
				free_tokens_list(&segment);
				malloc_error(minishell);
			}
			i++;
		}
		token = token->next;
	}
	new_strings_array[i] = NULL;
	return (new_strings_array);
}

/**
 * @brief Retrieves the input file name from a segment of tokens.
 *
 * If the segment starts with an input redirection token (TOKEN_REDIR_IN),
 * this function duplicates and returns the value of the next token, which is
 * assumed to be the input file name. Handles allocation failures.
 *
 * @param minishell Pointer to the minishell structure for error handling.
 * @param segment Pointer to the head of the token segment.
 * @return Duplicated input file name string, or NULL if not found or on error.
 */
char	*get_infile(t_minishell *minishell, t_token *segment)
{
	t_token	*current;
	char	*infile;

	current = segment;
	if (current && current->token_type == TOKEN_REDIR_IN)
	{
		current = current->next;
		infile = ft_strdup(current->value);
		if (!infile)
		{
			free_tokens_list(&segment);
			malloc_error(minishell);
		}
		return (infile);
	}
	return (NULL);
}

/**
 * @brief Retrieves the output file name from a segment of tokens.
 *
 * This function traverses the given segment of tokens, searching for an output 
 * redirection token (TOKEN_REDIR_OUT_FILE or TOKEN_APPEND_FILE) at the end of
 * the segment. If found, it duplicates and returns the output file name. 
 * If memory allocation fails, it frees the token segment and calls the 
 * minishell's error handler.
 *
 * @param minishell Pointer to the minishell structure for error handling.
 * @param segment Pointer to the head of the token segment.
 * @return A duplicated string of the output file name, or NULL if not found 
 * or on error.
 */
char	*get_outfile(t_minishell *minishell, t_token *segment)
{
	t_token	*current;
	char	*outfile;

	current = segment;
	while (current->next && current->next->token_type != TOKEN_EOF)
	{
		current = current->next;
	}
	if (current && (current->next == NULL
			|| current->next->token_type == TOKEN_EOF)
		&& (current->token_type == TOKEN_REDIR_OUT_FILE
			|| current->token_type == TOKEN_APPEND_FILE))
	{
		outfile = ft_strdup(current->value);
		if (!outfile)
		{
			free_tokens_list(&segment);
			malloc_error(minishell);
		}
		return (outfile);
	}
	return (NULL);
}

/**
 * @brief Determines if the given segment ends with an append redirection.
 *
 * This function checks if the segment of tokens ends with a TOKEN_APPEND
 * (typically representing ">>" in shell syntax) just before the end-of-file 
 * token.
 *
 * @param segment Pointer to the head of the token segment.
 * @return 1 if the segment ends with an append redirection, 0 otherwise.
 */
int	get_append_status(t_token *segment)
{
	t_token	*current;

	current = segment;
	while (current && current->next != NULL
		&& current->next->token_type != TOKEN_EOF)
		current = current->next;
	if (current->prev && current->prev->token_type == TOKEN_APPEND)
	{
		return (1);
	}
	return (0);
}

/**
 * @brief Retrieves the heredoc delimiter string from a segment of tokens.
 *
 * If the segment starts with a TOKEN_HEREDOC, this function returns a
 * duplicated str of the next token's value, used as the heredoc delim.
 * Handles allocation failures and malformed token sequences.
 *
 * @param minishell Pointer to the minishell structure for error handling.
 * @param segment Pointer to the head of the token segment.
 * @return Duplicated delimiter string, or NULL if not found or on error.
 */
char	*get_heredoc_delimiter(t_minishell *minishell, t_token *segment)
{
	t_token	*current;
	char	*delimeter;

	current = segment;
	while (current && current->token_type != TOKEN_EOF)
	{
		if (current->token_type == TOKEN_HEREDOC_DELIM)
		{
			delimeter = ft_strdup(current->value);
			if (!delimeter)
			{
				free_tokens_list(&segment);
				malloc_error(minishell);
			}
			return (delimeter);
		}
		current = current->next;
	}
	return (NULL);
}
