/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:42:40 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/01 16:42:40 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	execute_built_in(t_minishell *minishell, char **split_cmd)
{
	int	status;

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
		status = builtin_cd(minishell, split_cmd);
	else if (ft_strcmp(split_cmd[0], "exit") == 0)
		builtin_exit(minishell, split_cmd);
	return (status);
}

static int	manual_execution(char **full_cmd, t_fds *fd, int should_exit)
{
	int	status;

	if (!full_cmd)
		return (1);
	if (is_builtin(full_cmd[0]))
	{
		status = execute_built_in(fd->minishell, full_cmd);
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

void	exec_pathed_cmd(char **cmd, int in_fd, int out_fd, t_fds *fd)
{
	char	**new_argv;
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	new_argv = (char **)malloc(sizeof(char *) * (i + 1));
	new_argv[0] = split_cmd_after_slash(cmd[0]);
	i = 0;
	while (cmd[++i])
		new_argv[i] = ft_strdup(cmd[i]);
	new_argv[i] = NULL;
	if ((!new_argv[0]) | (dup2(in_fd, 0) == -1) | (dup2(out_fd, 1) == -1))
		perror("pipex");
	if (in_fd != -1 && in_fd != 0)
		close(in_fd);
	if (out_fd != -1 && out_fd != 1)
		close(out_fd);
	manual_execution(cmd, fd, 1);
	execve(cmd[0], new_argv, fd->env);
	ft_free_array((void **)new_argv);
	perror("pipex");
}
