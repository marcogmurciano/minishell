/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:28:43 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/18 18:35:52 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_env(t_minishell *minishell, char **argv)
{
	int	i;

	if (argv[1] != NULL)
	{
		syntax_error("env", minishell);
		return (1);
	}
	i = 0;
	while (minishell->envp[i])
	{
		ft_putendl_fd(minishell->envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
