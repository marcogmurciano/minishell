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

static char	*has_command(char **paths, char *cmd_name)
{
	int		i;
	char	*full_path;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd_name);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*iterate_env(char *env, char **cmd_parts)
{
	int		j;
	char	**paths;
	char	*result;

	paths = ft_split(env + 5, ':');
	result = has_command(paths, cmd_parts[0]);
	j = 0;
	while (paths[j])
		free(paths[j++]);
	free(paths);
	free_bidimensional_array(cmd_parts);
	return (result);
}

char	*get_cmd_path(char *cmd, char **env)
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
			return (iterate_env(env[i], cmd_parts));
		i++;
	}
	free_bidimensional_array(cmd_parts);
	return (NULL);
}

static int	process_cmd_errors(char **full_cmd, char **env)
{
	char	*path_cmd;
	int		result;

	result = 0;
	path_cmd = get_cmd_path(join_cmd(full_cmd), env);
	if (path_cmd == NULL)
	{
		result = 1;
		if (join_cmd(full_cmd) != NULL)
			printf("pipex: command not found: %s\n", full_cmd[0]);
	}
	else
		free(path_cmd);
	return (result);
}

int	process_single_command(char **full_cmd, t_fds *fd)
{
	int		result;

	result = 0;
	if (is_builtin(full_cmd[0]))
		return (0);
	if (ft_strchr(full_cmd[0], '/'))
	{
		if (access(full_cmd[0], F_OK) != 0)
			result = printf("pipex: command not found: %s\n", full_cmd[0]);
	}
	else
		result = process_cmd_errors(full_cmd, fd->env);
	return (result);
}

