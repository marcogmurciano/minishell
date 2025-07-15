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
 * Iterates through the input string and returns the index of the first '$'.
 * Returns -1 if no '$' is present.
 *
 * @param str The input string to search.
 * @return The index of the first '$', or -1 if not found.
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
 * Starting at variable_start, reads until a delimiter is found
 * (whitespace, pipe, redirect, quote, or another '$').
 * The resulting variable name is returned as a newly allocated string.
 * The length of the variable name is stored in variable_name_length.
 *
 * @param str The original string from which to extract the variable name.
 * @param variable_start The index to start extracting from.
 * @param variable_name_length Pointer to an int to store the name's length.
 * @return Newly allocated string containing the variable name.
 */
char	*extract_var_name(char *str, int variable_start,
		int *variable_name_length)
{
	char	*variable_name;
	int		i;

	i = 0;
	while (str[variable_start + i] && !ft_isspace(str[variable_start + i])
		&& str[variable_start + i] != '|' && str[variable_start + i] != '<'
		&& str[variable_start + i] != '>' && str[variable_start + i] != '\''
		&& str[variable_start + i] != '\"' && str[variable_start + i] != '$')
		i++;
	variable_name = ft_substr(str, variable_start, i);
	*variable_name_length = ft_strlen(variable_name);
	return (variable_name);
}

/**
 * Searches the minishell's environment linked list for the given variable name.
 * Returns the value if found, or NULL otherwise.
 *
 * @param minishell Pointer to the minishell structure containing the env.
 * @param variable_name The name of the variable to search for.
 * @return The value of the variable, or NULL if not found.
 */
char	*get_variable_value(t_minishell *minishell, char *variable_name)
{
	t_env	*current;

	current = minishell->environment;
	while (current && current->next)
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
