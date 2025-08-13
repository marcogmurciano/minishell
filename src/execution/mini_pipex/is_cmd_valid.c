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
			if (access(full_path, X_OK) != 0)
			{
				err_temp = ft_strjoin("minishell11: ", cmd_name);
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
	if (*status == 127)
	{
		err_temp = ft_strjoin_three("minishell: ", cmd_name, ": command not found");
		ft_putendl_fd(err_temp, STDERR_FILENO);
		free(err_temp);
		// err_temp = ft_strjoin("minishell22: ", cmd_name);
		// perror(err_temp);
		// free(err_temp);
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
	return (result);
}

/**
* Busca el comando aportado
*/
static char	*found_in_dir(char *cmd)
{
	DIR				*dir_stream;
	struct dirent	*dir_entry;
	char			*path;
	struct stat		st;

	dir_stream = opendir(".");
	if (dir_stream == NULL)
	{
		perror("minishell: opendir");
		return (NULL);
	}
	dir_entry = readdir(dir_stream);
	while (dir_entry != NULL)
	{
		if (strcmp(dir_entry->d_name, cmd) == 0)
		{
			if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
				return ("-");
			if (access(cmd, X_OK) == 0)
			{
				closedir(dir_stream);
				path = ft_strjoin("./", cmd);
				return (path);
			}
		}
		dir_entry = readdir(dir_stream);
	}
	closedir(dir_stream);
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
	char	*etmp;
	char	*full_path;

	i = 0;
	if (ft_strlen(cmd) == 0)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (iterate_env(env[i], cmd, status));
		i++;
	}
	founded_in_dir = found_in_dir(cmd);
	if (founded_in_dir == NULL && flag)
	{
		etmp = ft_strjoin_three("minishell12: ", cmd, ": Not such file or directory");
		printf("%s\n", etmp);
		free(etmp);
		// etmp = ft_strjoin("minishell22: ", cmd);
		// perror(etmp);
		// free(etmp);
		*status = 126;
		return (NULL);
	}
	if (ft_strcmp(founded_in_dir, "-") == 0 && flag)
	{
		etmp = ft_strjoin_three("minishell13: ", cmd, ": is a directory");
		ft_putendl_fd(etmp, STDERR_FILENO);
		free(etmp);
		return (NULL);
	}
	if (ft_strcmp(founded_in_dir, "_") == 0 && flag)
	{
		etmp = ft_strjoin("minishell14: ", cmd);
		perror(etmp);
		free(etmp);
		return (NULL);
	}
	etmp = ft_strjoin(founded_in_dir, "/");
	full_path = ft_strjoin(etmp, cmd);
	free(etmp);
	return (founded_in_dir);
}

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
	char		*err_temp;

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
