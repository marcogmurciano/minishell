/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:50:40 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:33:49 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Closes the duplicated STDIN and STDOUT file descriptors
 */
void	close_dup_stds(t_minishell *minishell)
{
	if (minishell->duplicated_std_fds[0] != -1)
	{
		close(minishell->duplicated_std_fds[0]);
		minishell->duplicated_std_fds[0] = -1;
	}
	if (minishell->duplicated_std_fds[1] != -1)
	{
		close(minishell->duplicated_std_fds[1]);
		minishell->duplicated_std_fds[1] = -1;
	}
}

/**
 * Frees the environment list
 */
static void	free_env(t_minishell *minishell)
{
	if (minishell->envp)
	{
		ft_free_array((void **)minishell->envp);
		minishell->envp = NULL;
	}
	if (minishell->environment)
	{
		free_environment(&(minishell->environment));
		minishell->environment = NULL;
	}
}

/**
 * Frees the minishell structure
 */
void	free_minishell(t_minishell *minishell)
{
	if (minishell->input)
	{
		free(minishell->input);
		minishell->input = NULL;
	}
	if (minishell->tokens_list)
	{
		free_tokens_list(&(minishell->tokens_list));
		minishell->tokens_list = NULL;
	}
	if (minishell->cmd_pipelines)
	{
		free_cmds(&(minishell->cmd_pipelines));
		minishell->cmd_pipelines = NULL;
	}
	free_env(minishell);
	close_dup_stds(minishell);
}
