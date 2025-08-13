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
 * for errors
 */
char	*p_error(char *s1, char *s2, char *s3)
{
	char	*temp;

	if (s3 == NULL)
	{
		temp = ft_strjoin(s1, s2);
		perror(temp);
	}
	else
	{
		temp = ft_strjoin_three(s1, s2, s3);
		ft_putendl_fd(temp, STDERR_FILENO);
	}
	free(temp);
	return (NULL);
}

/**
 * Checks if command path can be built and if result is executable
 */
char	*has_command(char **paths, char *cmd_name, int *status)
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
			// ft_strjoin no es necesario aquí, ya que stat funciona con el nombre del fichero
			// en el directorio actual.
			if (stat(cmd, st) == 0 && S_ISDIR(st->st_mode))
				return ("-");
			if (access(cmd, X_OK) == 0)
				return (ft_strjoin("./", cmd)); // Asumiendo que ft_strjoin existe
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
	closedir(dir_stream); // Es buena práctica cerrar el stream tan pronto como no se necesite.
	if (result != NULL)
	{
		// Comprobamos primero si el resultado no es NULL
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
