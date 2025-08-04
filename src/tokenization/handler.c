/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:08:49 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/04 10:36:09 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Processes an operator at the given input index.
 *
 * Detects an operator in the input string at index `i`,
 * adds it to the token list, and returns the number of characters consumed.
 *
 * @param token_head Pointer to the token list head.
 * @param minishell Input source structure.
 * @param i Current input index.
 * @return Characters consumed by the operator.
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
 * @brief Processes a quoted word at the specified input index.
 *
 * Extracts a quoted word from the input at index `i`,
 * adds it as a word token (recording the quote type),
 * and returns its length including quotes.
 *
 * @param token_head Pointer to the token list head.
 * @param minishell Input source structure.
 * @param i Current input index (should be at a quote).
 * @return Characters consumed by the quoted word (including quotes).
 */
int	handle_quoted_word(t_token **token_head, t_minishell *minishell, int i)
{
	char	*quote;
	char	*word;
	int		len;

	quote = &(minishell->input[i]);
	if (ft_strncmp(quote + 1, "_EMPTY_", 15) == 0)
	{
		add_word_token(token_head, TOKEN_WORD, "", quote);
		return (15);
	}
	word = get_quoted_word(minishell, *quote, i);
	if (word == NULL)
		return (-1);
	add_word_token(token_head, TOKEN_WORD, word, quote);
	len = ft_strlen(word);
	free(word);
	return (len + 2);
}

int	handle_ansi_c_quoted_word(t_token **token_head, t_minishell *minishell,
		int i)
{
	t_token	*last;
	char	*word;
	char	*dollar_pos;
	int		len;

	dollar_pos = &(minishell->input[i]);
	word = get_quoted_word(minishell, dollar_pos[1], i + 1);
	if (word == NULL)
		return (-1);
	add_word_token(token_head, TOKEN_WORD, word, dollar_pos + 1);
	if (*token_head)
	{
		last = *token_head;
		while (last->next)
			last = last->next;
		if (dollar_pos[1] == '\'')
			last->quote_type = SINGLE_QUOTE;
		else
			last->quote_type = NON_QUOTE;
		if (i > 0 && ft_isspace(minishell->input[i - 1]))
			last->spaced = 1;
	}
	len = ft_strlen(word);
	free(word);
	return (len + 3);
}

/**
 * @brief Handles non-quoted word tokens in the input string.
 *
 * This function extracts word starting at the given index, adds it as a
 * word token to the token list, frees the temporary buffer, and returns
 * the length of the word.
 *
 * @param token_head Pointer to the head of the token list.
 * @param minishell Structure to retrieve the input from.
 * @param i The current index in the input string.
 * @return The number of characters consumed by the non-quoted word.
 */
int	handle_nonquoted_word(t_token **token_head, t_minishell *minishell, int i)
{
	char	*first_char;
	char	*word;
	int		len;

	first_char = &(minishell->input[i]);
	if (ft_strncmp(first_char, "_EMPTY_", 15) == 0)
	{
		add_word_token(token_head, TOKEN_WORD, "", first_char);
		return (15);
	}
	word = get_unquoted_word(minishell, first_char);
	add_word_token(token_head, TOKEN_WORD, word, first_char);
	len = ft_strlen(word);
	free(word);
	return (len);
}
