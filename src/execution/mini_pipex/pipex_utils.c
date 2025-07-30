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

int	cleanup(t_fds *fd)
{
	if (fd->buffer != -1)
		close(fd->buffer);
	free_bidimensional_array(fd->env);
	return (0);
}

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

char	*split_cmd_after_slash(const char *s)
{
	const char	*slash = strrchr(s, '/');

	if (slash)
		return (ft_strdup(slash + 1));
	else
		return (ft_strdup(s));
}
