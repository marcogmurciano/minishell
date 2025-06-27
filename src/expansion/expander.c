/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:54:45 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/27 16:26:59 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *retrieve_new_input(t_minishell *minishell)
{
	t_token *current;
	char *expanded_line;
	char *expanded_variable;
	char *line_to_free;

	expanded_line = NULL;
	current = minishell->tokens_list;
	while (current->token_type != TOKEN_EOF)
	{
		if(current->value == NULL || *(current->value) == 0)
		{
			current = current->next;
			continue;
		}
		if (current->token_type == SINGLE_QUOTE)
			expanded_variable = ft_strjoin_three("\'",ft_strdup(current->value),"\'");
		else if(current->token_type == DOUBLE_QUOTE)
			expanded_variable = ft_strjoin_three("\"",ft_strdup(current->value),"\"");
		else
			expanded_variable = ft_strdup(current->value);
		if (!expanded_line)
			expanded_line = expanded_variable;
		else
		{
			line_to_free = expanded_line;
			expanded_line = ft_strjoin_three(expanded_line, " ", expanded_variable);
			free(line_to_free);
		}
		free(expanded_variable);
		expanded_variable = NULL;
		current = current->next;
	}
	return(expanded_line);
}

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
	if (!expander.variable_value)
		expander.variable_value = ft_strdup("");
	expander.preffix = ft_substr(*str, 0, expander.dollar_position);
	expander.suffix = ft_substr(*str, expander.variable_start
			+ expander.variable_name_length, strlen(*str)
			- (expander.variable_start + expander.variable_name_length));
	expander.new_word_value = ft_strjoin_three(expander.preffix,
			expander.variable_value, expander.suffix);
	return (free(expander.preffix), free(expander.suffix), free(expander.variable_name),
		expander.new_word_value);
}

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

char *expand_tokens_list(t_minishell *minishell)
{
	t_token	*current;
	char	*new_expanded_input;

	current = minishell->tokens_list;
	while (current && current->token_type != TOKEN_EOF && current->next)
	{
		if (current->token_type == TOKEN_WORD && (current->quote_type == NON_QUOTE
				|| current->quote_type == DOUBLE_QUOTE))
		{
			if (strchr(current->value, '$'))
			{
				expand_each_variable(minishell, &(current->value));
			}
		}
		current = current->next;
	}
	new_expanded_input = retrieve_new_input(minishell);
	return (new_expanded_input);
}
