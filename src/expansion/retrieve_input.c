/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:55:30 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/16 12:15:24 by dbarba-v         ###   ########.fr       */
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

static char	*append_exp_variable(char *expanded_line,
		char *expanded_variable)
{
	char	*line_to_free;

	line_to_free = expanded_line;
	expanded_line = ft_strjoin_three(expanded_line, " ", expanded_variable);
	free(line_to_free);
	free(expanded_variable);
	return (expanded_line);
}

char	*retrieve_new_input(t_minishell *minishell)
{
	t_token	*current;
	char	*exp_line;
	char	*exp_variable;

	current = minishell->tokens_list;
	exp_line = NULL;
	while (current && current->token_type != TOKEN_EOF)
	{
		exp_variable = expand_token_value(current);
		if (!exp_variable)
		{
			current = current->next;
			continue ;
		}
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
