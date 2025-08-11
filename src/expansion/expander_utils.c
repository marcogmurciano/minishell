/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:36:32 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:37:01 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Find "$" character
 */
int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != '$')
			i++;
		if (str[i] == '$')
			return (i);
	}
	return (-1);
}

/**
 * Get the name of a variable
 */
char	*extract_var_name(char *str, int variable_start,
		int *variable_name_length)
{
	char	*variable_name;
	char	first_char;
	int		i;

	i = 0;
	first_char = str[variable_start];
	if (ft_isdigit(first_char))
		i = 1;
	else if (first_char == '?')
		i = 1;
	else
	{
		while (str[variable_start + i] && !ft_isspace(str[variable_start + i])
			&& str[variable_start + i] != '|' && str[variable_start + i] != '<'
			&& str[variable_start + i] != '>' && str[variable_start + i] != '\''
			&& str[variable_start + i] != '\"' && str[variable_start + i] != '$'
			&& (ft_isalnum(str[variable_start + i])
				|| str[variable_start + i] == '_'))
			i++;
	}
	variable_name = ft_substr(str, variable_start, i);
	*variable_name_length = ft_strlen(variable_name);
	return (variable_name);
}

/**
 * Get value of key
 */
char	*get_variable_value(t_minishell *minishell, char *variable_name)
{
	t_env	*current;

	current = minishell->environment;
	while (current)
	{
		if (ft_strcmp(variable_name, "?") == 0)
		{
			return (ft_itoa(minishell->last_exit_status));
		}
		else if (ft_strcmp(current->key, variable_name) == 0)
		{
			return (ft_strdup(current->value));
		}
		else
			current = current->next;
	}
	return (NULL);
}
