/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:16:17 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:38:19 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Creates a new environment variable node.
 *
 * @param key The key/name of the environment variable.
 * @param value The value of the environment variable.
 * @param minishell Pointer to the minishell structure (used for errors).
 * @return Pointer to the newly created t_env node.
 */
static t_env	*create_env_node2(const char *key, const char *value,
		t_minishell *minishell)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		malloc_error(minishell);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

/**
 * @brief Checks and initializes the environment list for minishell.
 *
 * If the environment is not set, creates a minimal environment
 * with PWD, SHLVL, and _.
 *
 * @param minishell Pointer to the minishell structure.
 * @return Pointer to the head of the environment list.
 */
t_env	*check_environment(t_minishell *minishell)
{
	t_env	*pwd;
	t_env	*shlvl;
	t_env	*last_cmd;
	char	*pwd_value;

	if (minishell->environment == NULL)
	{
		pwd_value = getcwd(NULL, 0);
		if (!pwd_value)
			malloc_error(minishell);
		pwd = create_env_node2("PWD", pwd_value, minishell);
		shlvl = create_env_node2("SHLVL", "1", minishell);
		last_cmd = create_env_node2("_", "", minishell);
		pwd->next = shlvl;
		shlvl->next = last_cmd;
		last_cmd->next = NULL;
		free(pwd_value);
		return (pwd);
	}
	return (minishell->environment);
}
