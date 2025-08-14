/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:21:05 by marcoga2          #+#    #+#             */
/*   Updated: 2025/07/10 12:38:56 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * Checks if command can be found on path
 */
static int	process_cmd_errors(char **full_cmd, char **env)
{
	char	*path_cmd;
	int		status;

	status = 0;
	path_cmd = get_cmd_path(full_cmd[0], env, &status, 1);
	if (path_cmd != NULL)
		free(path_cmd);
	return (status);
}

/**
 * Check if command is a directory and if not if it is executable
 */
int	process_single_command(char **full_cmd, t_fds *fd)
{
	int			result;
	struct stat	st;

	result = 0;
	if (is_builtin(full_cmd[0]))
		return (0);
	if (ft_strchr(full_cmd[0], '/'))
	{
		if (stat(full_cmd[0], &st) == 0 && S_ISDIR(st.st_mode))
		{
			p_error("minishell: ", full_cmd[0], ": is a directory");
			return (126);
		}
		else if (access(full_cmd[0], F_OK | X_OK) != 0)
		{
			p_error("minishell: ", full_cmd[0], NULL);
			if (errno == EACCES)
				return (126);
			return (127);
		}
	}
	else
		result = process_cmd_errors(full_cmd, fd->env);
	return (result);
}
