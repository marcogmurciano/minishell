/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:28:24 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/28 11:44:35 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    builtin_cd(t_minishell *minishell, char **argv)
int    builtin_cd(t_minishell *minishell, char **argv)
{
	char *directory;
	char *directory;
    int argc;
	int chdir_status;
	int i;
	int i;

	(void) minishell;
	(void) minishell;
	argc = 0;
	chdir_status = 0;
	i = 0;
	i = 0;
	while (argv[argc])
		argc++;
	directory = ft_strjoin(getenv("PWD"), getenv("HOME"));
	directory = ft_strjoin(getenv("PWD"), getenv("HOME"));
	if(argc == 1)
		chdir_status = chdir(getenv("HOME"));
	else
		chdir_status = chdir(getenv("HOME"));
	else
	{
		while (argv[i])
		{
			chdir_status = chdir(argv[i]);
			i++;
		}
	}

	if(chdir_status == -1)
		perror("minishell: cd1");
	free(directory);
    return ((unsigned int)chdir_status);
		perror("minishell: cd1");
	free(directory);
    return ((unsigned int)chdir_status);
}
