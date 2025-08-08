/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:02:24 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/08 10:53:05 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * Print errors on chil processes
 */
void	print_child_error(char *s, t_fds *fd)
{
	if (errno == ENOENT)
		ft_printf("minishell: No such file or directory: %s\n", s);
	else if (errno == EACCES)
		ft_printf("minishell: Permission denied: %s\n", s);
	else
		ft_printf("minishell: Error opening file: %s\n", s);
	cleanup(fd);
}

/**
 * Checks if provided cmd is a builtin
 */
int	is_builtin(char *split_cmd)
{
	if (ft_strcmp(split_cmd, "echo") == 0
		|| ft_strcmp(split_cmd, "export") == 0
		|| ft_strcmp(split_cmd, "pwd") == 0
		|| ft_strcmp(split_cmd, "unset") == 0
		|| ft_strcmp(split_cmd, "env") == 0
		|| ft_strcmp(split_cmd, "cd") == 0
		|| ft_strcmp(split_cmd, "exit") == 0)
		return (1);
	return (0);
}

/**
 * Restore standard FDs REQUIRED when executing builtin
 */
void restore_std_fds(t_minishell *minishell)
{
	dup2(minishell->duplicated_std_fds[0], STDIN_FILENO);
	dup2(minishell->duplicated_std_fds[1], STDOUT_FILENO);
}
