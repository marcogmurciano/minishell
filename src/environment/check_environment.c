/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:16:17 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/10 11:40:31 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env *check_environment(t_minishell *minishell)
{
	t_env *new1;
	t_env *new2;
	t_env *new3;

	// NEEDS REFACTORING //
	if (minishell->environment == NULL)
	{
		new1 = ft_calloc(1, sizeof(t_env)); //
		new2 = ft_calloc(1, sizeof(t_env)); //
		new3 = ft_calloc(1, sizeof(t_env)); //
		new1->key = ft_strdup("SHLVL");
		new1->value = ft_strdup("1");
		new1->next = new2;
		new2->key = ft_strdup("PWD");
		new2->value = getcwd(NULL, 0);
		new2->next = new3;
		new3->key = ft_strdup("_");
		new3->value = ft_strdup(NULL);
		new3->next = NULL;
		return (new1);
	}
	return (minishell->environment);
}
