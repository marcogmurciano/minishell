/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regenerate_environment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:10:12 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:38:51 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Creates a new environment node from the given environment string.
 * @param arg The environment string in "NAME=VALUE" format.
 * @return Pointer to the newly created node, or NULL on failure.
 */
static t_env	*create_env_node(char *arg)
{
	t_env	*new_env;

	if (!ft_strchr(arg, '='))
		return (NULL);
	new_env = ft_calloc(1, sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	if (!new_env->key)
	{
		free(new_env);
		return (NULL);
	}
	new_env->value = ft_substr(arg, ft_strlen(new_env->key) + 1, ft_strchr(arg,
				'\0') - arg);
	if (!new_env->value)
	{
		free(new_env->key);
		free(new_env);
		return (NULL);
	}
	return (new_env);
}

/**
 * Appends a new environment node to the end of the linked list.
 * @param head Pointer to the head of the list.
 * @param new_env The new node to append.
 */
void	append_env_node(t_env **head, t_env *new_env)
{
	t_env	*current;

	if (!head || !new_env)
		return ;
	if (!*head)
	{
		*head = new_env;
		return ;
	}
	current = *head;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new_env;
}

/**
 * Builds a linked list of environment variables from envp.
 * @param envp The environment pointer array.
 * @return Pointer to the head of the linked list.
 */
t_env	*regenerate_environment(char **envp)
{
	t_env	*env_head;
	t_env	*new_env;
	int		i;

	env_head = NULL;
	i = 0;
	while (envp && envp[i])
	{
		new_env = create_env_node(envp[i]);
		if (new_env)
		{
			if (ft_strcmp(new_env->key, "SHLVL") == 0)
			{
				free(new_env->value);
				new_env->value = ft_itoa(ft_atoi(getenv(new_env->key)) + 1);
			}
			append_env_node(&env_head, new_env);
		}
		i++;
	}
	return (env_head);
}
