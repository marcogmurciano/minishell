/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:08:49 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/08 14:01:10 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Handles operator tokens in the input string.
 *
 * This function checks the character at the given index in the input string to determine
 * if it is an operator (pipe, redirection, heredoc, etc.), adds the appropriate token
 * to the token list, and returns the number of characters consumed by the operator.
 *
 * @param token_head Pointer to the head of the token list.
 * @param minishell Structure to get the input from.
 * @param i The current index in the input string.
 * @return The number of characters consumed by the operator.
 */
int	handle_operator(t_token **token_head, t_minishell *minishell, int i)
{
	if (minishell->input[i] == '|')
	{
		return (add_nonword_token(token_head, TOKEN_PIPE, "|"), 1);
	}
	if (minishell->input[i] == '<' && minishell->input[i + 1] == '<')
	{
		return (add_nonword_token(token_head, TOKEN_HEREDOC, "<<"), 2);
	}
	if (minishell->input[i] == '<')
	{
		return (add_nonword_token(token_head, TOKEN_REDIR_IN, "<"), 1);
	}
	if (minishell->input[i] == '>' && minishell->input[i + 1] == '>')
	{
		return (add_nonword_token(token_head, TOKEN_APPEND, ">>"), 2);
	}
	if (minishell->input[i] == '>')
	{
		return (add_nonword_token(token_head, TOKEN_REDIR_OUT, ">"), 1);
	}
	return (1);
}

/**
 * @brief Handles quoted word tokens in the input string.
 *
 * This function extracts a quoted word starting at the given index in the input string,
 * adds it as a word token to the token list (with the quote character recorded), frees
 * the temporary buffer, and returns the length of the quoted word including quotes.
 *
 * @param token_head Pointer to the head of the token list.
 * @param minishell Structure to retrieve the input from.
 * @param i The current index in the input string (expected to point to a quote).
 * @return The number of characters consumed by the quoted word (including quotes).
 */
int handle_quoted_word(t_token **token_head, t_minishell *minishell, int i)
{
	char	quote;
    char	*word;
	int		len;
	
	quote = minishell->input[i];
	word = get_quoted_word(minishell, quote);
    add_word_token(token_head, TOKEN_WORD, word, quote);
    len = ft_strlen(word);
    free(word);
    return (len + 2);
}

/**
 * @brief Handles non-quoted word tokens in the input string.
 *
 * This function extracts an unquoted word starting at the given index in the input string,
 * adds it as a word token to the token list, frees the temporary buffer, and returns
 * the length of the word.
 *
 * @param token_head Pointer to the head of the token list.
 * @param minishell Structure to retrieve the input from.
 * @param i The current index in the input string.
 * @return The number of characters consumed by the non-quoted word.
 */
int handle_nonquoted_word(t_token **token_head, t_minishell *minishell, int i)
{
    char	*word;
	int		len;
	
	word = get_unquoted_word(minishell, &(minishell->input[i]));
    add_word_token(token_head, TOKEN_WORD, word, '\0');
    len = ft_strlen(word);
    free(word);
    return (len);
}