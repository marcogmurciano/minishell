/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:55:30 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 14:52:50 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_token_value(t_token *token)
{
	if (token->value == NULL || *(token->value) == 0)
		return (NULL);
	if (token->quote_type == SINGLE_QUOTE)
		return (ft_strjoin_three("'", ft_strdup(token->value), "'"));
	else if (token->quote_type == DOUBLE_QUOTE)
		return (ft_strjoin_three("\"", ft_strdup(token->value), "\""));
	else
		return (ft_strdup(token->value));
}

static char *append_expanded_variable(char *expanded_line, char *expanded_variable)
{
    char *line_to_free;

	line_to_free = expanded_line;
    expanded_line = ft_strjoin_three(expanded_line, " ", expanded_variable);
    free(line_to_free);
    free(expanded_variable);
    return (expanded_line);
}

char	*retrieve_new_input(t_minishell *minishell)
{
	t_token	*current;
	char	*expanded_line;
	char	*expanded_variable;

	current = minishell->tokens_list;
	expanded_line = NULL;
	while (current && current->token_type != TOKEN_EOF)
	{
		expanded_variable = expand_token_value(current);
		if (!expanded_variable)
		{
			current = current->next;
			continue ;
		}
		if (!expanded_line)
			expanded_line = expanded_variable;
		else
		{
			expanded_line = append_expanded_variable(expanded_line, expanded_variable);
			if (!expanded_line)
				return (NULL);
		}
		current = current->next;
	}
	return (expanded_line);
}
