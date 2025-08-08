/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:28:24 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/08 14:41:29 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Functionality that changes directory and updates PWD and OLDPWD variables
 */
int change_directory(char *path, t_minishell *minishell)
{
	int status;
	char *cwd[3];
	char *new_cwd[3];
	char *getcwd_result;

	status = 0;
	ft_bzero(cwd, sizeof(char *)*3);
	ft_bzero(new_cwd, sizeof(char *)*3);
	cwd[0] = "export";
	getcwd_result = getcwd(NULL, 0);
	cwd[1] = ft_strjoin_three("OLDPWD", "=", getcwd_result);
	free(getcwd_result);
	status = chdir(path);
	if(status == 0)
	{
		new_cwd[0] = "export";
		getcwd_result = getcwd(NULL, 0);
		new_cwd[1] = ft_strjoin_three("PWD", "=", getcwd_result);
		free(getcwd_result);
		builtin_export(minishell, new_cwd);
		builtin_export(minishell, cwd);
		free(new_cwd[1]);
	}
	free(cwd[1]);
	return (status);
}

/**
 * Error printng
 */
static void cd_error(char **argv)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(argv[1], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror("");
}

/**
 * Function that replicates cd functionality
 */
int    builtin_cd(t_minishell *minishell, char **argv)
{
    int argc;
	int chdir_status;

	(void) minishell;
	argc = 0;
	chdir_status = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
		chdir_status = change_directory(getenv("HOME"), minishell);
	else if (argc == 2)
		chdir_status = change_directory(argv[1], minishell);
	else
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		chdir_status = 1;
	}
	if (chdir_status == -1)
		cd_error(argv);
	if(chdir_status < 0)
		chdir_status *= -1;
    return (chdir_status);
}
