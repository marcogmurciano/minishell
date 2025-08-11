/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:28:43 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/11 10:21:42 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Function that prints envp line by line
 */
void	print_envp(char **envp)
{
	int	i;
	i = 0;

	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

/**
 * Function that prints the environment variables and values
 */
int	builtin_env(t_minishell *minishell, char **argv)
{
	if (argv[1] != NULL)
	{
		syntax_error("env", minishell, 4);
		return (1);
	}
	print_envp(minishell->envp);
	return (0);
}
