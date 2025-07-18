/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:28:46 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/18 18:20:58 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Finds and replaces an environment variable in the linked list.
 *        If the key matches, replaces the node and frees the old one.
 * @param env_head Pointer to the head node of the environment list.
 * @param new_node The new environment variable node to insert.
 * @return 1 if replaced, 0 otherwise.
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

static int check_key_syntax(char *key)
{
	int i;

	i = 0;
	if (ft_isdigit(key[i]))
	{
		return(1);
	}
	while (key[i])
	{
		if(ft_isalnum(key[i]) || key[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

void ft_swap(char **first, char **second)
{
	char *temp;

	temp = *first;
	*first = *second;
	*second = temp;
}

void print_ordered_envp(t_minishell *minishell)
{
	int		env_count;
	int		i;
	int		j;
	char	**sorted_envp;

	env_count = 0;
	while(minishell->envp[env_count])
		env_count++;
	sorted_envp = ft_calloc(env_count, sizeof(char *));
	i = 0;
	while (i++ < env_count)
		sorted_envp[i] = ft_strdup(minishell->envp[i]);
	i = 0;
	while (i++ < env_count - 1)
	{
		j = 0;
		while(j++ < env_count - 1)
		{
			if (ft_strcmp(sorted_envp[i], sorted_envp[i + 1]) > 0)
				ft_swap(&sorted_envp[i], &sorted_envp[i + 1]);
		}
	}
	i = 0;
	while (sorted_envp[i++])
		printf("declare -x %s\n", sorted_envp[i]);
	ft_free_array((void **)sorted_envp);
}

/**
 * @brief Exports environment variables to the minishell environment.
 *        Adds new or replaces existing environment variables as needed.
 * @param minishell Pointer to the minishell structure.
 * @param pathname Not used.
 * @param argv Null-terminated array of arguments. argv[0] is the command name.
 * @param envp Not used.
 * @return 0 on success, calls malloc_error() on allocation error.
 */
int	builtin_export(t_minishell *minishell, char **argv)
{
	t_env	*new_node;
	int		i;

	i = 1;
	while (argv[i])
	{
		if(check_key_syntax(argv[i]) == 1)
		{
			i++;
			continue;
		}
		new_node = create_env_node(argv[i]);
		if (!new_node)
			malloc_error(minishell);
		if (replace_env_node(minishell->environment, new_node) == 0)
			append_env_node(&(minishell->environment), new_node);
		minishell->envp = get_environment_array(minishell->environment);
		i++;
	}
	if (i == 1)
		print_ordered_envp(minishell);
	return (0);
}
