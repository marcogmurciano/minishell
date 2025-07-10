/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:28:46 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/10 10:33:17 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int export(t_minishell *minishell, char *argument)
{
	t_env *new_env;
	char *name;
	int name_len;
	char *value;
	int value_len;

	new_env = ft_calloc(1, sizeof(t_env));
	if (!new_env)
		malloc_error(minishell);
	if(!ft_strchr(argument, '='))
	{
		minishell->last_exit_status = 1;
		return (1);
	}
	name_len = ft_strchr(argument, '=') - argument;
	value_len = ft_strchr(argument, '\0') - ft_strchr(argument, '=');
	new_env->name = ft_substr(argument, 0, name_len);
	new_env->value = ft_substr(argument, name_len + 1, value_len); 
	append_env_node(minishell->environment, new_env);
}
