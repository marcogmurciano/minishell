/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:28:24 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/22 12:39:42 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    builtin_cd(char **argv)
{
    int argc;
	int chdir_status;

	argc = 0;
	chdir_status = 0;
	while (argv[argc])
		argc++;
	if(argc == 1)
		return (0);
	if(argc > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	chdir_status = chdir(argv[1]);
	if(chdir_status == -1)
	{
		perror("minishell: cd: ");
		return (1);
	}
    return (0);
}