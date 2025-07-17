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

int	cleanup(t_fds *fd)
{
	if (fd->buffer != -1)
		close(fd->buffer);
	free(fd->is_pathed);
	free_bidimensional_array(fd->env);
	free(fd->in_dir);
	free(fd->out_dir);
	return (0);
}

int	process_cmd_errors(char *cmd, char **env)
{
	char	*path_cmd;
	int		result;

	result = 0;
	path_cmd = get_cmd_path(cmd, env);
	if (path_cmd == NULL)
	{
		result = 1;
		printf("pipex: command not found: %s\n", cmd);
	}
	else
		free(path_cmd);
	return (result);
}

int	process_single_command(char *cmd, t_fds *fd)
{
	int	result;

	result = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
			result = printf("pipex: command not found: %s\n", cmd);
	}
	else
		result = process_cmd_errors(cmd, fd->env);
	return (result);
}

char	**ft_strdup_arr(char **arr)
{
	size_t	count;
	char	**dup_arr;
	size_t	i;

	i = 0;
	count = 0;
	if (!arr)
		return (NULL);
	while (arr[count])
		count++;
	dup_arr = (char **)malloc((count + 1) * sizeof(char *));
	if (!dup_arr)
		return (NULL);
	while (i < count)
	{
		dup_arr[i] = ft_strdup(arr[i]);
		if (!dup_arr[i])
		{
			free_bidimensional_array(dup_arr);
			return (NULL);
		}
		i++;
	}
	dup_arr[count] = NULL;
	return (dup_arr);
}
