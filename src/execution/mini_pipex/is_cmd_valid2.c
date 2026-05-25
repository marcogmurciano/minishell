/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd_valid2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:36:09 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/14 10:36:49 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * Checks if command path can be built and if result is executable
 */
static char	*has_command(char **paths, char *cmd_name, int *status)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_three(paths[i], "/", cmd_name);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) != 0)
			{
				p_error("minishell: ", cmd_name, NULL);
				if (errno == EACCES)
					return (*status = 126, NULL);
			}
			else
				return (*status = 0, full_path);
		}
		free(full_path);
		i++;
	}
	*status = 127;
	p_error("minishell: ", cmd_name, ": command not found");
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
	return (result);
}

static char	*is_in_dir(DIR *dir_stream, struct stat *st, char *cmd)
{
	struct dirent	*dir_entry;

	dir_entry = readdir(dir_stream);
	while (dir_entry != NULL)
	{
		if (strcmp(dir_entry->d_name, cmd) == 0)
		{
			if (stat(cmd, st) == 0 && S_ISDIR(st->st_mode))
				return ("-");
			if (access(cmd, X_OK) == 0)
				return (ft_strjoin("./", cmd));
		}
		dir_entry = readdir(dir_stream);
	}
	return (NULL);
}

/**
* Busca el comando aportado
*/
static char	*found_in_dir(char *cmd)
{
	DIR				*dir_stream;
	struct stat		st;
	char			*result;

	dir_stream = opendir(".");
	if (dir_stream == NULL)
	{
		perror("minishell: opendir");
		return (NULL);
	}
	result = is_in_dir(dir_stream, &st, cmd);
	closedir(dir_stream);
	if (result != NULL)
	{
		if (ft_strcmp(result, "-") == 0)
			return ("-");
		return (result);
	}
	if (access(cmd, F_OK | X_OK) != 0)
		return ("_");
	return (NULL);
}

/**
 * Check if command is a directory and if not if it is executable
 */
char	*get_cmd_path(char *cmd, char **env, int *status, int flag)
{
	int		i;
	char	*founded_in_dir;

	i = 0;
	if (ft_strlen(cmd) == 0)
		return (ft_strdup(""));
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (iterate_env(env[i], cmd, status));
		i++;
	}
	founded_in_dir = found_in_dir(cmd);
	if (founded_in_dir == NULL && flag)
	{
		*status = 126;
		return (p_error("minishell: ", cmd, ": Not such file or directory"));
	}
	if (ft_strcmp(founded_in_dir, "-") == 0 && flag)
		return (p_error("minishell: ", cmd, ": is a directory"));
	if (ft_strcmp(founded_in_dir, "_") == 0 && flag)
		return (p_error("minishell: ", cmd, NULL));
	return (founded_in_dir);
}
