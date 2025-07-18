/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:34:30 by marcoga2          #+#    #+#             */
/*   Updated: 2025/07/11 15:53:41 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_bidimensional_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

char	*split_cmd_after_slash(const char *s)
{
	const char	*slash = strrchr(s, '/');

	if (slash)
		return (ft_strdup(slash + 1));
	else
		return (ft_strdup(s));
}

// char	*has_command(char **paths, char *cmd)
// {
// 	int		i;
// 	char	*full_path;
// 	char	*temp;
// 	char	**splitted_cmd;

// 	splitted_cmd = ft_split(cmd, ' ');
// 	i = 0;
// 	while (paths[i])
// 	{
// 		temp = ft_strjoin(paths[i], "/");
// 		full_path = ft_strjoin(temp, splitted_cmd[0]);
// 		free(temp);
// 		if (access(full_path, F_OK) == 0)
// 		{
// 			free_bidimensional_array(splitted_cmd);
// 			return (full_path);
// 		}
// 		free(full_path);
// 		i++;
// 	}
// 	free_bidimensional_array(splitted_cmd);
// 	return (NULL);
// }

char	*has_command(char **paths, char *cmd_name)
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
		{
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

// char	*get_cmd_path(char *cmd, char **env)
// {
// 	int		i;
// 	char	**paths;
// 	char	*result;
// 	int		j;

// 	i = 0;
// 	if (ft_strlen(cmd) == 0)
// 		return (NULL);
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], "PATH=", 5) == 0)
// 		{
// 			paths = ft_split(env[i] + 5, ':');
// 			result = has_command(paths, cmd);
// 			j = 0;
// 			while (paths[j])
// 				free(paths[j++]);
// 			free(paths);
// 			return (result);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

char	*get_cmd_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*result;
	int		j;
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
		{
			paths = ft_split(env[i] + 5, ':');
			result = has_command(paths, cmd_parts[0]);
			j = 0;
			while (paths[j])
				free(paths[j++]);
			free(paths);
			free_bidimensional_array(cmd_parts);
			return (result);
		}
		i++;
	}
	free_bidimensional_array(cmd_parts);
	return (NULL);
}
