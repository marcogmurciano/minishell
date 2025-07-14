/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:54:45 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/14 11:04:32 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Iterates through the tokens in the minishell's tokens_list. For each token, 
 * it appends its value to a newly built string,
 * handling quoting by re-adding quotes to tokens of type 
 * SINGLE_QUOTE or DOUBLE_QUOTE.
 * Empty tokens and tokens with NULL values are skipped.
 *
 * @param minishell Pointer to the minishell struct containing the tokens list.
 * @return Newly allocated string containing the reconstructed input line.
 */
static char *retrieve_new_input(t_minishell *minishell)
{
    t_token *current;
    char *expanded_line = NULL;
    char *expanded_variable;
    char *line_to_free;

	
    current = minishell->tokens_list;
    while (current && current->token_type != TOKEN_EOF)
    {
        if (current->value == NULL || *(current->value) == 0)
        {
            current = current->next;
            continue;
        }
        if (current->quote_type == SINGLE_QUOTE)
            expanded_variable = ft_strjoin_three("'", ft_strdup(current->value), "'");
        else if (current->quote_type == DOUBLE_QUOTE)
            expanded_variable = ft_strjoin_three("\"", ft_strdup(current->value), "\"");
        else
            expanded_variable = ft_strdup(current->value);
        if (!expanded_variable)
        {
            free(expanded_line);
            return NULL;
        }
        if (!expanded_line)
            expanded_line = expanded_variable;
        else
        {
            line_to_free = expanded_line;
            expanded_line = ft_strjoin_three(expanded_line, " ", expanded_variable);
            free(line_to_free);
            free(expanded_variable);
            if (!expanded_line)
                return NULL; // Allocation failed
        }
        if (!line_to_free) // Only free if not transferred to expanded_line
            free(expanded_variable);
        current = current->next;
    }
    return (expanded_line);
}

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
	// if (!expander.variable_name)
	// 	malloc_error(minishell);
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
char *expand_tokens_list(t_minishell *minishell)
{
	t_token	*current;
	char	*new_expanded_input;

	current = minishell->tokens_list;
	while (current && current->next && current->token_type != TOKEN_EOF)
	{
		if (current->token_type == TOKEN_WORD && 
				(current->quote_type == NON_QUOTE || 
				current->quote_type == DOUBLE_QUOTE))
		{
			if (current->prev && current->prev->token_type == TOKEN_HEREDOC)
				;
			else if(ft_strcmp("$", current->value) == 0)
				;
			else if(strchr(current->value, '$'))
			{
				expand_each_variable(minishell, &(current->value));
			}
		}
		current = current->next;
	}
	new_expanded_input = retrieve_new_input(minishell);
	return (new_expanded_input);
}
