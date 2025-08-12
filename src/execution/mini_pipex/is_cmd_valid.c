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
	char	*err_temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd_name);
		free(temp);
		if (access(full_path, F_OK) == 0)
		{
			if(access(full_path, X_OK) != 0)
			{
				err_temp = ft_strjoin("minishell: ", cmd_name);
				perror(err_temp);
				free(err_temp);
				if (errno == EACCES)
					return (*status = 126, NULL);
			}
			else
				return (*status = 0, full_path);
		}
		else
			*status = 127;
		free(full_path);
		i++;
	}
	return (NULL);
}

/**
 * Splits PATH and traverses it's directories calling has_command
 */
static char	*iterate_env(char *env, char *cmd, int *status)
{
	int		j;
	char	**paths;
	char	*result;

	paths = ft_split(env + 5, ':');
	result = has_command(paths, cmd, status);
	j = 0;
	while (paths[j])
		free(paths[j++]);
	free(paths);
	// free_bidimensional_array(cmd_parts);
	return (result);
}

/**
 * Check if command is a directory and if noot if it is executable
 */
char	*get_cmd_path(char *cmd, char **env, int *status)
{
	int		i;
	// char	**cmd_parts;

	i = 0;
	if (ft_strlen(cmd) == 0)
		return (NULL);
	// cmd_parts = ft_split(cmd, ' ');
	// if (!cmd_parts)
	// 	return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (iterate_env(env[i], cmd, status));
		i++;
	}
	// free_bidimensional_array(cmd_parts);
	return (NULL);
}

/**
 * Checks if command can be found on path
 */
static int	process_cmd_errors(char **full_cmd, char **env)
{
	char	*path_cmd;
	int		status;
	// char	*tmp;

	status = 0;
	path_cmd = get_cmd_path(full_cmd[0], env, &status);
	if(path_cmd)
		free(path_cmd);
	// if (path_cmd == NULL)
	// {
	// 	if (full_cmd[0] != NULL)
	// 	{
	// 		tmp = ft_strjoin("minishell: ", full_cmd[0]);
	// 		perror(tmp);
	// 		free(tmp);
	// 	}
	// }
	// else
	// 	free(path_cmd);
	return (status);
}

/**
 * Check if command is a directory and if noot if it is executable
 */
int	process_single_command(char **full_cmd, t_fds *fd)
{
	int			result;
	struct stat	st;
	char	*err_temp;

	result = 0;
	if (is_builtin(full_cmd[0]))
		return (0);
	if (ft_strchr(full_cmd[0], '/'))
	{
		if (stat(full_cmd[0], &st) == 0 && S_ISDIR(st.st_mode))
		{
			err_temp = ft_strjoin_three("minishell: ", full_cmd[0], ": is a directory");
			ft_putendl_fd(err_temp, STDERR_FILENO);
			free(err_temp);
			return (126);
		}
		else if (access(full_cmd[0], F_OK | X_OK) != 0)
		{
			err_temp = ft_strjoin("minishell: ", full_cmd[0]);
			perror(err_temp);
			free(err_temp);
			if (errno == EACCES)
				return (126);
			return (127);
		}
	}
	else
		result = process_cmd_errors(full_cmd, fd->env);
	return (result);
}
