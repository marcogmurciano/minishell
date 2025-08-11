/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:13:13 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/11 16:09:05 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Swap pointers for ordering list
 */
void	ft_swap(char **first, char **second)
{
	char	*temp;

	temp = *first;
	*first = *second;
	*second = temp;
}


void	add_to_envp(t_env *current, char **export_envp, int env_count)
{
	char	*quoted_value;

	if (!current->value)
		export_envp[env_count] = ft_strdup(current->key);
	else
	{
		quoted_value = ft_strjoin_three("\"", current->value, "\"");
		export_envp[env_count] = ft_strjoin_three(current->key, "=",
				quoted_value);
		free(quoted_value);
	}
}
