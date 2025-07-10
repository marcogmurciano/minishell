/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:28:46 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/10 15:45:02 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int export(t_minishell *minishell, char *pathname, const char **argv, char **envp)
{
	t_env	*new_env;
	t_env	*current_env;
	t_env	*temp_env;
	int		i;

	(void **)envp;
	i = 1;
	while (argv[i])
	{
		new_env = create_env_node(argv[i]);
		current_env = minishell->environment;
		while (current_env)
		{
			if(ft_strcmp(current_env->next->key, new_env->key) == 0)
			{
				temp_env = current_env->next;
				current_env->next = new_env;
				new_env->next = temp_env->next;
				temp_env->next = NULL;
				free_environment(&temp_env);
				return(0);
			}
			current_env = current_env->next;
		}
		append_env_node(minishell->environment, new_env);
	}
	return(0);
}
