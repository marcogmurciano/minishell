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
 * Checks if command path can be built and if result is executable
 */
char	*has_command(char **paths, char *cmd_name, int *status)
{
	int		i;
	char	*full_path;
	char	*temp;
	int		found_not_executable;

	i = 0;
	found_not_executable = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd_name);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (norminette_is_extremely_fucked_up(status, full_path));
		else if (access(full_path, F_OK) == 0)
			found_not_executable = 1;
		free(full_path);
		i++;
	}
	if (found_not_executable)
		*status = 126;
	else
		*status = 127;
	return (NULL);
}

/**
 * Splits PATH and traverses it's directories calling has_command
 */
static char	*iterate_env(char *env, char **cmd_parts, int *status)
{
	int		j;
	char	**paths;
	char	*result;

	paths = ft_split(env + 5, ':');
	result = has_command(paths, cmd_parts[0], status);
	j = 0;
	while (paths[j])
		free(paths[j++]);
	free(paths);
	free_bidimensional_array(cmd_parts);
	return (result);
}

/**
 * Check if command is a directory and if noot if it is executable
 */
char	*get_cmd_path(char *cmd, char **env, int *status)
{
	int		i;
	char	**cmd_parts;

	i = 0;
	if (ft_strlen(cmd) == 0)
		return (NULL);
	cmd_parts = ft_split(cmd, ' ');
	if (!cmd_parts)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (iterate_env(env[i], cmd_parts, status));
		i++;
	}
	free_bidimensional_array(cmd_parts);
	return (NULL);
}

/**
 * Checks if command can be found on path
 */
static int	process_cmd_errors(char **full_cmd, char **env)
{
	char	*path_cmd;
	int		status;

	status = 0;
	path_cmd = get_cmd_path(full_cmd[0], env, &status);
	if (path_cmd == NULL)
	{
		if (full_cmd[0] != NULL)
			ft_printf("minishell: %s: command not found\n", full_cmd[0]);
	}
	else
		free(path_cmd);
	return (status);
}

/**
 * Check if command is a directory and if noot if it is executable
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
			result = 126;
			ft_printf("minishell: %s: is a directory\n", full_cmd[0]);
		}
		else if (access(full_cmd[0], F_OK | X_OK) != 0)
		{
			result = 127;
			ft_printf("minishell: %s: No such file or \
directory\n", full_cmd[0]);
		}
	}
	else
		result = process_cmd_errors(full_cmd, fd->env);
	return (result);
}
