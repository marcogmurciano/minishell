/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025-07-14 12:52:31 by user              #+#    #+#             */
/*   Updated: 2025-07-14 12:52:31 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Get number of commands
 */
int	ft_cmdsize(t_cmd *lst)
{
	int	counter;

	counter = 0;
	while (lst != NULL)
	{
		counter++;
		lst = lst->next;
	}
	return (counter);
}

/**
 * Entry point to execution
 */
int	execution(t_minishell *minishell)
{
	t_cmd	*head;
	int		cmd_count;
	int		result;

	head = minishell->cmd_pipelines;
	if (!head)
		return (0);
	cmd_count = ft_cmdsize(head);
	if (!head)
		return (1);
	result = ft_pipex(cmd_count, head, minishell);
	setup_signal_handlers();
	return (result);
}
