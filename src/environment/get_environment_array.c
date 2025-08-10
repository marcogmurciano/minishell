/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environment_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:07:09 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/30 13:17:10 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Counts the number of environment variables in the linked list.
 */
static int	env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/**
 * Converts the environment linked list to a NULL-terminated array
 */
char	**get_environment_array(t_env *env)
{
	char	**envp;
	int		i;

	envp = malloc(sizeof(char *) * (env_count(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			envp[i] = ft_strjoin_three(env->key, "=", env->value);
			if (!envp[i])
				return (free_array(envp, i), NULL);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
