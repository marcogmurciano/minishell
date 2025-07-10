/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:28:43 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/10 11:57:39 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int env(t_minishell *minishell, char *pathname, char **argv, char **envp)
{
	int i;

	if (argv[1] != '\0')
	{
		syntax_error(pathname);
		return (1);
	}
	i = 0;
	while(envp[i])
	{
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}