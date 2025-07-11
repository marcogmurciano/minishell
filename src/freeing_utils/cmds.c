/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:32:40 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/11 11:59:38 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_cmds(t_cmd **cmd_head)
{
	t_cmd *current;
	t_cmd *temp;

	if (cmd_head == NULL || *cmd_head == NULL) 
        return;
	current = *cmd_head;
	while (current)
	{
		ft_free_array((void **)(current->argv));
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		if (current->heredoc)
			free(current->heredoc);
		current->outfile = NULL;
		current->infile = NULL;
		current->heredoc = NULL;
		temp = current;
		current = current->next;
		free(temp);
		temp = NULL;
	}
	*cmd_head = NULL;
}
