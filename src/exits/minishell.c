/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:53:36 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:37:44 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Cleans up resources and exits the minishell program.
 * @param minishell Pointer to the minishell context.
 */
void	exit_minishell(t_minishell *minishell)
{
	int exit_status;

	exit_status = minishell->last_exit_status;
	free_minishell(minishell);
	minishell = NULL;
	write(STDOUT_FILENO, "exit\n", 5);
	rl_clear_history();
	exit(exit_status);
}
