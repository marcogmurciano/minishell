/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:28:46 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/11 10:22:05 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Finds and replaces an environment variable in the linked list.
 */
static int	replace_env_node(t_env *env_head, t_env *new_node)
{
	t_env	*previous;
	t_env	*current;

	previous = env_head;
	current = previous;
	while (current)
	{
		if (ft_strcmp(current->key, new_node->key) == 0)
		{
			previous->next = new_node;
			new_node->next = current->next;
			current->next = NULL;
			free_environment(&current);
			return (1);
		}
		previous = current;
		current = current->next;
	}
	return (0);
}

/**
 * Check if arguments correctly formated
 */
static int	check_key_syntax(char *key)
{
	int	i;

	i = 0;
	if (ft_isalpha(key[i]) == 0)
	{
		return (1);
	}
	while (key[i] && key[i] != '=')
	{
		if (ft_isalnum(key[i]) || key[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

/**
 * Create an array of strings with only environment values keys that have value
 */
char	**get_export_envp(t_minishell *minishell)
{
	t_env	*current;
	char	**export_envp;
	int		env_count;

	env_count = 0;
	current = minishell->environment;
	while (current)
	{
		current = current->next;
		env_count++;
	}
	export_envp = ft_calloc(env_count + 1, sizeof(char *));
	if (!export_envp)
		malloc_error(minishell);
	current = minishell->environment;
	env_count = 0;
	while (current)
	{
		if (!current->value)
			export_envp[env_count++] = ft_strdup(current->key);
		else
			export_envp[env_count++] = ft_strjoin_three(current->key, "=",
					current->value);
		current = current->next;
	}
	return (export_envp);
}

/**
 * Sorts the export envp and prints it
 */
void	print_ordered_envp(t_minishell *minishell)
{
	char	**sorted_envp;
	int		j;
	int		i;

	sorted_envp = get_export_envp(minishell);
	i = 0;
	while (sorted_envp[i])
	{
		j = i + 1;
		while (sorted_envp[j])
		{
			if (ft_strcmp(sorted_envp[i], sorted_envp[j]) > 0)
				ft_swap(&sorted_envp[i], &sorted_envp[j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (sorted_envp[i])
	{
		printf("declare -x %s\n", sorted_envp[i]);
		i++;
	}
	ft_free_array((void **)sorted_envp);
}

/**
 * @brief Adds new or replaces existing environment variables as needed.
 */
int	builtin_export(t_minishell *minishell, char **argv)
{
	t_env	*new_node;
	int		i;
	int		exit_status;

	i = 0;
	exit_status = 0;
	while (argv[++i])
	{
		if (check_key_syntax(argv[i]) == 1)
		{
			exit_status = syntax_error("export", minishell, 4);
			continue ;
		}
		new_node = create_env_node(argv[i]);
		if (!new_node)
			malloc_error(minishell);
		if (replace_env_node(minishell->environment, new_node) == 0)
			append_env_node(&(minishell->environment), new_node);
		ft_free_array((void **)(minishell->envp));
		minishell->envp = get_environment_array(minishell->environment);
	}
	if (i == 1)
		print_ordered_envp(minishell);
	return (exit_status);
}
