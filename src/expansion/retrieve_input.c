/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:55:30 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/07 16:37:13 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Assign quotes to expanded line to keep on retokenization
 */
static char	*expanded_token_value(t_token *token)
{
	if (token->value == NULL || *(token->value) == 0)
	{
		if (token->quote_type == DOUBLE_QUOTE || token->quote_type == SINGLE_QUOTE)
			return (ft_strdup("\"\""));
		else
			return (ft_strdup(""));
	}
	if (token->quote_type == SINGLE_QUOTE)
		return (ft_strjoin_three("'", ft_strdup(token->value), "'"));
	else if (token->quote_type == DOUBLE_QUOTE)
		return (ft_strjoin_three("\"", ft_strdup(token->value), "\""));
	else
		return (ft_strdup(token->value));
}

/**
 * Apend the expanded varialble to the already expanded part of line
 */
static char	*append_exp_variable(char *expanded_line,
		char *expanded_variable)
{
	char	*line_to_free;
	int		line_len;
	char	*result;

	line_to_free = expanded_line;
	if (strlen(expanded_variable) == 0)
		result = ft_strdup(expanded_line);
	else if (ft_strcmp(expanded_variable, "\"\"") == 0)
	{
		line_len = strlen(expanded_line);
		if (line_len >= 2 && 
			expanded_line[line_len-1] == '"' && 
			expanded_line[line_len-2] == '"')
			result = ft_strdup(expanded_line);
		else
			result = ft_strjoin_three(expanded_line, " ", expanded_variable);
	}
	else
		result = ft_strjoin_three(expanded_line, " ", expanded_variable);
	free(line_to_free);
	free(expanded_variable);
	return (result);
}

/**
 * Expands each tokens value, then builds a new input string to be retokenized
 */
char	*retrieve_new_input(t_minishell *minishell)
{
	t_token	*current;
	char	*exp_line;
	char	*exp_variable;

	current = minishell->tokens_list;
	exp_line = NULL;
	while (current && current->token_type != TOKEN_EOF)
	{
		exp_variable = expanded_token_value(current);
		if (!exp_line)
			exp_line = exp_variable;
		else
		{
			exp_line = append_exp_variable(exp_line, exp_variable);
			if (!exp_line)
				return (NULL);
		}
		current = current->next;
	}
	return (exp_line);
}
