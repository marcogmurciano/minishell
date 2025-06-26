/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:54:45 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/26 16:58:13 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (!expander.variable_name)
		return (ft_strdup(*str));
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

void	expand_token_list(t_minishell *minishell)
{
	t_token	*current;

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
}
