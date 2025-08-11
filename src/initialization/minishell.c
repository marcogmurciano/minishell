/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:01:27 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:32:10 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Initialize the minishell structure
 */
void	init_mini(t_minishell *minishell, int argc, char **argv, char **envp)
{
	ft_bzero(minishell, sizeof(t_minishell));
	minishell->environment = regenerate_environment(envp);
	minishell->environment = check_environment(minishell);
	minishell->envp = get_environment_array(minishell->environment);
	minishell->argv = argv;
	minishell->argc = argc;
	minishell->pid = -1;
	minishell->last_exit_status = 0;
	minishell->lastdir = getcwd(NULL, 0);
	minishell->duplicated_std_fds[0] = dup(STDIN_FILENO);
	minishell->duplicated_std_fds[1] = dup(STDOUT_FILENO);
}
