/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:28:49 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 18:50:18 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * If environment variable exists, remove from environment
 */
int	builtin_unset(t_minishell *minishell, char **argv)
{
	t_env	*current_env;
	t_env	*temp_env;
	int		i;

	i = 1;
	while (argv[i])
	{
		current_env = minishell->environment;
		while (current_env)
		{
			if (current_env->next && ft_strcmp(current_env->next->key,
					argv[i]) == 0)
			{
				temp_env = current_env->next;
				current_env->next = temp_env->next;
				temp_env->next = NULL;
				free_environment(&temp_env);
				ft_free_array((void **)(minishell->envp));
				minishell->envp = get_environment_array(minishell->environment);
			}
			current_env = current_env->next;
		}
		i++;
	}
	return (0);
}
