/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:44:51 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/11 10:44:51 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Prints current working directory
 */
int	builtin_pwd(t_fds *fd)
{
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		// perror("minishell: pwd");
		printf("%s\n", fd->lastdir);
		return (1);
	}
	printf("%s\n", cwd);
	if (fd->lastdir)
		free(fd->lastdir);
	fd->lastdir = ft_strcpy(cwd);
	free(cwd);
	return (0);
}
