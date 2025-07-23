/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:28:43 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/23 13:04:23 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
