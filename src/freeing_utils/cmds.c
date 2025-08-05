/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:32:40 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:33:39 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_cmds(t_cmd **cmd_head)
{
	t_cmd	*current;
	t_cmd	*temp;

	if (cmd_head == NULL || *cmd_head == NULL)
		return ;
	current = *cmd_head;
	while (current)
	{
		if (current->argv)
			ft_free_array((void **)(current->argv));
		if (current->infiles)
			ft_free_array((void **)(current->infiles));
		if (current->outfiles)
			ft_free_array((void **)(current->outfiles));
		if (current->heredocs)
			ft_free_array((void **)(current->heredocs));
		if (current->last_heredoc_filepath)
			free(current->last_heredoc_filepath);
		current->outfiles = NULL;
		current->infiles = NULL;
		current->heredocs = NULL;
		current->last_heredoc_filepath = NULL;
		temp = current;
		current = current->next;
		free(temp);
		temp = NULL;
	}
	*cmd_head = NULL;
}
