/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:36:32 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/27 15:36:35 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	*extract_var_name(char *str, int variable_start,
		int *variable_name_length)
{
	char	*temp;
	char	*variable_name;
	int		i;

	i = 0;
	temp = &str[variable_start + i];
	while (str[variable_start + i] && !ft_isspace(str[variable_start + i]) && 
		str[variable_start + i] != '|' &&
		str[variable_start + i] != '<' &&
		str[variable_start + i] != '>' &&
		str[variable_start + i] != '\'' &&
		str[variable_start + i] != '\"' &&
		str[variable_start + i] != '$')
		i++;
	variable_name = ft_substr(str, variable_start, i);
	*variable_name_length = ft_strlen(variable_name);
	return (variable_name);
}

char	*get_variable_value(t_minishell *minishell, char *variable_name)
{
	t_env *current;

	current = minishell->environment;
	while (current && current->next)
	{
		if (ft_strcmp(current->name, variable_name) == 0)
			return (current->value);
		else
			current = current->next;
	}
	return (NULL);
}