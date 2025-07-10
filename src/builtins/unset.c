/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:28:49 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/10 23:05:41 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int unset(t_minishell *minishell, char *pathname, const char **argv, char **envp)
{
	t_env *new_env;
	t_env *current_env;
	t_env *temp_env;
	int i;

	(void **)envp;
	i = 1;
	while (argv[i])
	{
		current_env = minishell->environment;
		while(current_env)
		{	
			if(current_env->next && 
				ft_strcmp(current_env->next->key, argv[i]) == 0)
			{
				temp_env = current_env->next;
				current_env->next = temp_env->next;
				temp_env->next = NULL;
				free_environment(&temp_env);
				minishell->envp = get_environment_array(minishell->environment);
				return(0);
			}
			current_env = current_env->next;
		}
	}
	return (0);
}
