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

void	exec_cmd(char *cmd, int input_fd, int output_fd, t_fds *fd)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		if (args)
			free_bidimensional_array(args);
		printf("pipex: empty command");
		exit(1);
	}
	cmd_path = get_cmd_path(args[0], fd->env);
	if (dup2(input_fd, STDIN_FILENO) == -1)
		perror("pipex");
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		perror("pipex");
	if (input_fd != -1 && input_fd != 0)
		close(input_fd);
	if (output_fd != -1 && output_fd != 1)
		close(output_fd);
	execve(cmd_path, args, fd->env);
	free(cmd_path);
	free_bidimensional_array(args);
	perror("pipex");
}

void	exec_pathed_cmd(char *cmd, int input_fd, int output_fd, t_fds *fd)
{
	char	*cmd_and_args;
	char	**argv;

	cmd_and_args = split_cmd_after_slash(cmd);
	argv = ft_split(cmd_and_args, ' ');
	free(cmd_and_args);
	if (!argv)
		perror("pipex");
	if (dup2(input_fd, 0) == -1)
		perror("pipex");
	if (dup2(output_fd, 1) == -1)
		perror("pipex");
	if (input_fd != -1 && input_fd != 0)
		close(input_fd);
	if (output_fd != -1 && output_fd != 1)
		close(output_fd);
	execve(cmd, argv, fd->env);
	perror("pipex");
}

void	print_child_error(t_fds *fd)
{
	if (errno == ENOENT)
		printf("pipex: No such file or directory: %s\n", fd->in_dir);
	else if (errno == EACCES)
		printf("pipex: Permission denied: %s\n", fd->in_dir);
	else
		printf("pipex: Error opening file: %s\n", fd->in_dir);
	cleanup(fd);
}
