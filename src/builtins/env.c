/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:28:43 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/09 17:16:43 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int env(t_minishell *minishell)
{
	int i;

	i = 0;
	while(minishell->envp[i])
	{
		ft_putendl_fd(minishell->envp[i], minishell->duplicated_std_fds[1]);
		i++;
	}
	return (0);
}