/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:28:24 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/12 22:28:17 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int update_envvars(t_minishell *minishell, char **cwd)
{
	char	*getcwd_result;
	char	*new_cwd[3];

	getcwd_result = getcwd(NULL, 0);
	if (getcwd_result == NULL)
	{
		perror("minishell: cd: error retrieving current directory: getcwd");
		return (1);
	}
	if (minishell->lastdir)
		free(minishell->lastdir);
	minishell->lastdir = ft_strdup(getcwd_result);
	new_cwd[0] = "export";
	new_cwd[1] = ft_strjoin_three("PWD", "=", getcwd_result);
	new_cwd[2] = 0;
	free(getcwd_result);
	builtin_export(minishell, new_cwd);
	builtin_export(minishell, cwd);
	free(new_cwd[1]);
	return (0);
}

/**
 * Functionality that changes directory and updates PWD and OLDPWD variables
 */
int	change_directory(char *path, t_minishell *minishell)
{
	int		status;
	char	*cwd[3];
	char	*getcwd_result;

	status = 0;
	getcwd_result = getcwd(NULL, 0);
	cwd[0] = "export";
	if(getcwd_result == NULL)
		cwd[1] = ft_strjoin_three("OLDPWD", "=", "");
	else
		cwd[1] = ft_strjoin_three("OLDPWD", "=", getcwd_result);
	cwd[2] = 0;
	if (getcwd_result)
		free(getcwd_result);
	status = chdir(path);
	if (status == 0)
		status = update_envvars(minishell, cwd);
	else 
	{
		ft_printf("minishell: cd: %s", path);
		perror(" ");
	}
	free(cwd[1]);
	return (status);
}

static char *manual_getenv(t_minishell *minishell, char *variable)
{
	t_env *current;

	current = minishell->environment;
	while (current)
	{
		if (ft_strcmp(current->key, variable) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

/**
 * Function that replicates cd functionality
 */
int	builtin_cd(t_minishell *minishell, char **argv)
{
	int		argc;
	char	*home_dir;

	(void) minishell;
	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
	{
		home_dir = manual_getenv(minishell, "HOME");
		if (home_dir == NULL)
			return (ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO), 1);
		return(change_directory(home_dir, minishell));
	}
	else if (argc == 2)
		return(change_directory(argv[1], minishell));
	return (ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO), 1);
}
