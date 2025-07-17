/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:57:28 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/17 15:49:26 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	while (current)
	{
		if (current->token_type == TOKEN_REDIR_IN)
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
		current = current->next;
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
