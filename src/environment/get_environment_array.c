/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environment_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:25:22 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/02 16:53:55 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Counts the number of environment variables in the linked list.
 *
 * @param env Pointer to the head of the environment variable linked list.
 * @return The number of environment variables in the list.
 */
static int env_count(t_env *env)
{
    int		count;

    count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return (count);
}

/**
 * @brief Frees the environment array and its elements up to index i.
 *
 * @param envp The environment array to free.
 * @param i The number of elements to free in the array.
 */
static void free_envp(char **envp, int i)
{
    while (i > 0)
    {
        free(envp[--i]);
    }
    free(envp);
}

/**
 * @brief Converts the environment linked list to a NULL-terminated array of strings.
 *
 * Each string is in the format NAME=VALUE. The returned array must be freed by the caller.
 *
 * @param env Pointer to the head of the environment variable linked list.
 * @return A newly allocated NULL-terminated array of environment strings, or NULL on failure.
 */
char **get_environment_array(t_env *env)
{
    char	**envp;
    int		i;

    envp = malloc(sizeof(char *) * (env_count(env) + 1));
    if (!envp)
        return (NULL);
    i = 0;
    while (env)
    {
        envp[i] = ft_strjoin_three(env->name, "=", env->value);
        if (!envp[i])
            return (free_envp(envp, i), NULL);
        i++;
        env = env->next;
    }
    envp[i] = NULL;
    return (envp);
}