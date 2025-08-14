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
 * Unsets a node on other than the first position of the environ linked list
 */
static void	unset_nonfirst(t_minishell *minishell, t_env *current)
{
	t_env	*temp_env;

	temp_env = current->next;
	current->next = temp_env->next;
	temp_env->next = NULL;
	free_environment(&temp_env);
	ft_free_array((void **)(minishell->envp));
	minishell->envp = get_environment_array(minishell->environment);
}

/**
 * Unsets node at first position of the linked list
 */
static void	unset_first(t_minishell *minishell, t_env *current)
{
	minishell->environment = current->next;
	current->next = NULL;
	free_environment(&current);
	ft_free_array((void **)(minishell->envp));
	minishell->envp = get_environment_array(minishell->environment);
}

/**
 * If environment variable exists, remove from environment
 */
int	builtin_unset(t_minishell *minishell, char **argv)
{
	t_env	*current_env;
	int		i;

	i = 0;
	while (argv[++i])
	{
		current_env = minishell->environment;
		if (current_env && ft_strcmp(current_env->key, argv[i]) == 0)
		{
			unset_first(minishell, current_env);
			continue ;
		}
		while (current_env)
		{
			if (current_env->next && ft_strcmp(current_env->next->key,
					argv[i]) == 0)
			{
				unset_nonfirst(minishell, current_env);
				break ;
			}
			current_env = current_env->next;
		}
	}
	return (0);
}
