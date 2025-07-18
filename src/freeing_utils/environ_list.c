/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:49:46 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:34:40 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Frees a linked list of environment nodes, releasing all associated memory.
 * @param env_head Double pointer to the head of the environment list.
 */
void	free_environment(t_env **env_head)
{
	t_env	*current_env;
	t_env	*temp_env;

	if (env_head == NULL || *env_head == NULL)
	{
		return ;
	}
	current_env = *env_head;
	while (current_env)
	{
		if (current_env->key)
			free(current_env->key);
		if (current_env->value)
			free(current_env->value);
		current_env->key = NULL;
		current_env->value = NULL;
		temp_env = current_env;
		current_env = current_env->next;
		free(temp_env);
		temp_env = NULL;
	}
	*env_head = NULL;
}
