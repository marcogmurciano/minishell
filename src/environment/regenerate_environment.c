/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regenerate_environment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:10:12 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/09 12:09:52 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Finds the position of the first equal sign '=' in the input string.
 * @param env_str The environment string.
 * @return Index of '=' if found, -1 otherwise.
 */
static int find_equal_sign(const char *env_str) 
{
    int i = 0;
    while (env_str[i] && env_str[i] != '=') 
	{
        i++;
    }
	if(env_str[i] == '=')
		return (i);
    else 
		return(-1);
}

/**
 * Creates a new environment node from the given environment string.
 * @param env_str The environment string in "NAME=VALUE" format.
 * @return Pointer to the newly created node, or NULL on failure.
 */
static t_env *create_env_node(char *env_str)
{
	int equal_position;
	t_env *new_env;

	equal_position = find_equal_sign(env_str);
	if (equal_position == -1) 
        return (NULL); // Invalid env string
	new_env = ft_calloc(1, sizeof(t_env));
	if (!new_env)
        return (NULL); // Handle allocation failure
	new_env->name = ft_substr(env_str, 0, equal_position);
    if (!new_env->name) 
	{
        free(new_env);
        return (NULL);
    }
    if(ft_strcmp(new_env->name, "SHLVL") == 0)
        new_env->value = ft_itoa(ft_atoi(getenv(new_env->name)) + 1);
	else
        new_env->value = ft_strdup(getenv(new_env->name));
	new_env->next = NULL;
    return (new_env);
}

/**
 * Appends a new environment node to the end of the linked list.
 * @param head Pointer to the head of the list.
 * @param new_env The new node to append.
 */
static void append_env_node(t_env **head, t_env *new_env) 
{
	t_env *current;

    if (!head || !new_env)
        return;

    if (!*head) 
	{
        *head = new_env;
        return;
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
t_env *regenerate_environment(char **envp) 
{
    t_env *env_head;
	t_env *new_env;
    int i;

	env_head = NULL;
	i = 0;

    while (envp && envp[i]) 
	{
        new_env = create_env_node(envp[i]);
        if (new_env) 
		{
            append_env_node(&env_head, new_env);
        }
        i++;
    }
    return (env_head);
}