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

/**
 * Frees the arrays of a cmd structure
 */
static void free_arrays(t_cmd *cmd)
{
	if (cmd->argv)
	{
		ft_free_array((void **)(cmd->argv));
		cmd->argv = NULL;
	}
	if (cmd->infiles)
	{
		ft_free_array((void **)(cmd->infiles));
		cmd->infiles = NULL;
	}
	if (cmd->outfiles)
	{
		ft_free_array((void **)(cmd->outfiles));
		cmd->outfiles = NULL;
	}
	if (cmd->heredocs)
	{
		ft_free_array((void **)(cmd->heredocs));
		cmd->heredocs = NULL;
	}
}

/**
 * Frees the list of cmds
 */
void	free_cmds(t_cmd **cmd_head)
{
	t_cmd	*current;
	t_cmd	*temp;

	if (cmd_head == NULL || *cmd_head == NULL)
		return ;
	current = *cmd_head;
	while (current)
	{
		free_arrays(current);
		if (current->last_heredoc_filepath)
			free(current->last_heredoc_filepath);
		current->last_heredoc_filepath = NULL;
		temp = current;
		current = current->next;
		free(temp);
		temp = NULL;
	}
	*cmd_head = NULL;
}
