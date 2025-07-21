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
	free_bidimensional_array(fd->env);
	return (0);
}

int	process_cmd_errors(char **full_cmd, char **env)
{
	char	*path_cmd;
	int		result;

	result = 0;
	path_cmd = get_cmd_path(join_cmd(full_cmd), env);
	if (path_cmd == NULL)
	{
		result = 1;
		printf("pipex: command not found: %s\n", full_cmd[0]);
	}
	else
		free(path_cmd);
	return (result);
}

int	process_single_command(char **full_cmd, t_fds *fd)
{
	int		result;
	char	*joined_cmd;

	joined_cmd = join_cmd(full_cmd);
	result = 0;
	if (is_builtin(full_cmd[0]) == 0)
		return (0);
	//debug
	// printf("processisnglecommand: %s", joined_cmd);
	//
	if (ft_strchr(joined_cmd, '/'))
	{
		if (access(joined_cmd, F_OK) != 0)
			result = printf("pipex: command not found: %s\n", full_cmd[0]);
	}
	else
		result = process_cmd_errors(full_cmd, fd->env);
	free(joined_cmd);
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