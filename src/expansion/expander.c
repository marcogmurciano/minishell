/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:54:45 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/16 14:13:54 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Given a string containing a variable of the form $VAR, this function extracts
 * the prefix, variable name,
 * and suffix, expands the variable using the environment, and then rebuilds the
 * string with the variable's value.
 *
 * @param minishell Pointer to the minishell structure for environment access.
 * @param str Double pointer to the string to expand; only the first variable is
 * expanded per call.
 * @return Newly allocated string with the variable expanded.
 */
static char	*expansor(t_minishell *minishell, char **str)
{
	t_expansion	expander;

	expander.word_value = *str;
	expander.dollar_position = find_dollar(*str);
	if (expander.dollar_position < 0)
		return (ft_strdup(*str));
	expander.variable_start = expander.dollar_position + 1;
	expander.variable_name_length = 0;
	expander.variable_name = extract_var_name(*str, expander.variable_start,
			&(expander.variable_name_length));
	expander.variable_value = get_variable_value(minishell,
			expander.variable_name);
	if (!(expander.variable_value))
		expander.variable_value = ft_strdup("");
	expander.preffix = ft_substr(*str, 0, expander.dollar_position);
	expander.suffix = ft_substr(*str, expander.variable_start
			+ expander.variable_name_length, strlen(*str)
			- (expander.variable_start + expander.variable_name_length));
	expander.new_word_value = ft_strjoin_three(expander.preffix,
			expander.variable_value, expander.suffix);
	return (free(expander.variable_value), free(expander.preffix),
		free(expander.suffix), free(expander.variable_name),
		expander.new_word_value);
}

/**
 * Searches for the '$' character in the word value, and for each occurrence,
 * expands the corresponding variable using the expansor function, until no
 * more variables remain.
 *
 * @param minishell Pointer to the minishell structure for environment access.
 * @param word_value Double pointer to the string in which to expand variables.
 */
static void	expand_each_variable(t_minishell *minishell, char **word_value)
{
	char	*expanded;
	char	*old;

	if (!word_value || !*word_value)
		return ;
	while (ft_strchr(*word_value, '$'))
	{
		if (ft_strcmp(*word_value, "$?") == 0)
		{
			free(*word_value);
			*word_value = ft_itoa(minishell->last_exit_status);
		}
		old = *word_value;
		expanded = expansor(minishell, word_value);
		*word_value = expanded;
		free(old);
	}
}

/**
 * Iterates through the tokens_list of minishell, expanding all variables in
 * tokens of type TOKEN_WORD
 * that are either unquoted or double-quoted. After expanding, reconstructs
 * the new input string
 * by joining all tokens together.
 *
 * @param minishell Pointer to the minishell struct containing the tokens list.
 * @return Pointer to the newly allocated expanded input string.
 */
char	*expand_tokens_list(t_minishell *minishell)
{
	t_token	*current;
	char	*new_expanded_input;

	current = minishell->tokens_list;
	while (current && current->next && current->token_type != TOKEN_EOF)
	{
		if (current->token_type == TOKEN_WORD
			&& (current->quote_type == NON_QUOTE
				|| current->quote_type == DOUBLE_QUOTE))
		{
			if (current->prev && current->prev->token_type == TOKEN_HEREDOC)
				;
			else if (ft_strcmp("$", current->value) == 0)
				;
			else if (strchr(current->value, '$'))
				expand_each_variable(minishell, &(current->value));
		}
		current = current->next;
	}
	new_expanded_input = retrieve_new_input(minishell);
	return (new_expanded_input);
}
