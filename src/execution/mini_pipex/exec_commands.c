/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:45:31 by marcoga2          #+#    #+#             */
/*   Updated: 2025/07/11 15:57:32 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int execute_built_in(t_minishell *minishell, char **split_cmd)
{
	int		status;

	status = 0;
	if (ft_strcmp(split_cmd[0], "echo") == 0)
		status = builtin_echo(minishell, split_cmd);
	else if (ft_strcmp(split_cmd[0], "export") == 0)
		status = builtin_export(minishell, split_cmd);
	else if (ft_strcmp(split_cmd[0], "pwd") == 0)
		status = builtin_pwd();
	else if (strcmp(split_cmd[0], "unset") == 0)
		status = builtin_unset(minishell, split_cmd);
	else if (ft_strcmp(split_cmd[0], "env") == 0)
		status = builtin_env(minishell, split_cmd);
	else if (ft_strcmp(split_cmd[0], "cd") == 0)
	    builtin_cd(minishell, split_cmd);
	else if (ft_strcmp(split_cmd[0], "exit") == 0)
	    builtin_exit(minishell, split_cmd);
	
	return(status);
}

int	is_builtin(char *split_cmd)
{
	if (ft_strcmp(split_cmd, "echo") == 0
		|| ft_strcmp(split_cmd, "export") == 0
		|| ft_strcmp(split_cmd, "pwd") == 0
		|| ft_strcmp(split_cmd, "unset") == 0
		|| ft_strcmp(split_cmd, "env") == 0
		|| ft_strcmp(split_cmd, "cd") == 0
		|| ft_strcmp(split_cmd, "exit") == 0)
		return (1);
	return (0);
}

static int	manual_execution(char **full_cmd, t_fds *fd, int should_exit)
{
	int		status;

	if (!full_cmd)
		return (1);
	if (is_builtin(full_cmd[0]))
	{
		status = execute_built_in(fd->minishell, full_cmd);
		ft_free_array((void **)full_cmd);
		full_cmd = NULL;
		if (should_exit)
		{
			cleanup(fd);
			exit(status);
		}
		return (status);
	}
	return (0);
}

void	exec_cmd(char **full_cmd, int input_fd, int output_fd, t_fds *fd)
{
	char	*cmd_path;

	if (!full_cmd || !full_cmd[0])
	{
		printf("pipex: empty command");
		exit(1);
	}
	if (dup2(input_fd, STDIN_FILENO) == -1)
		perror("pipex");
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		perror("pipex");
	if (input_fd != -1 && input_fd != 0)
		close(input_fd);
	if (output_fd != -1 && output_fd != 1)
		close(output_fd);
	manual_execution(full_cmd, fd, 1);
	cmd_path = get_cmd_path(full_cmd[0], fd->env);
	execve(cmd_path, full_cmd, fd->env);
	perror("pipex");
}

int	exec_only_builtin(char **full_cmd, int input_fd, int output_fd, t_fds *fd)
{
	if (!full_cmd || !full_cmd[0])
	{
		printf("pipex: empty command");
		exit(1);
	}
	if (dup2(input_fd, STDIN_FILENO) == -1)
		perror("pipex");
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		perror("pipex");
	if (input_fd != -1 && input_fd != 0)
		close(input_fd);
	if (output_fd != -1 && output_fd != 1)
		close(output_fd);
	return (manual_execution(full_cmd, fd, 0));
}

//////////////////////////////////////

void print_execve_args(const char *path, char **args)
{
    int i;

    printf("\n----- EXECVE DEBUG INFO -----\n");
    printf("Path: [%s]\n", path);
    printf("Arguments:\n");
    
    i = 0;
    while (args[i])
    {
        printf("  args[%d]: [%s]\n", i, args[i]);
        i++;
    }
    printf("---------------------------\n\n");
}

/////////////////////////////////////////////////

void exec_pathed_cmd(char **full_cmd, int input_fd, int output_fd, t_fds *fd)
{
    char    **new_argv;
    int     i;

    i = 0;
    while (full_cmd[i])
        i++;
    new_argv = (char **)malloc(sizeof(char *) * (i + 1));
    new_argv[0] = split_cmd_after_slash(full_cmd[0]);
    i = 0;
    while (full_cmd[++i])
        new_argv[i] = full_cmd[i];
    new_argv[i] = NULL;
    if (!new_argv[0])
        perror("pipex");
    if (dup2(input_fd, 0) == -1)
        perror("pipex");
    if (dup2(output_fd, 1) == -1)
        perror("pipex");
    if (input_fd != -1 && input_fd != 0)
        close(input_fd);
    if (output_fd != -1 && output_fd != 1)
        close(output_fd);
    manual_execution(full_cmd, fd, 1);
	//debug
	print_execve_args(full_cmd[0], new_argv);
	//
    execve(full_cmd[0], new_argv, fd->env);
    free(new_argv);
    perror("pipex");
}

void	print_child_error(char *s, t_fds *fd)
{
	if (errno == ENOENT)
		printf("pipex: No such file or directory: %s\n", s);
	else if (errno == EACCES)
		printf("pipex: Permission denied: %s\n", s);
	else
		printf("pipex: Error opening file: %s\n", s);
	cleanup(fd);
}
