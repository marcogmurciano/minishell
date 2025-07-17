/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:34:47 by marcoga2          #+#    #+#             */
/*   Updated: 2025/07/10 14:55:22 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	first_child(t_fds *fd, int *pipes, char **cmds, int i)
{
	fd->in = 0;
	if (fd->has_infile == 1)
		fd->in = open(fd->in_dir, O_RDONLY);
	if (fd->in == -1 || process_single_command(cmds[i], fd) != 0)
	{
		if (fd->in == -1)
			print_child_error(fd);
		else
		{
			if (fd->in != 0)
				close(fd->in);
			close(pipes[1]);
			cleanup(fd);
		}
		exit(1);
	}
	if (fd->is_pathed[i] == '1')
		exec_pathed_cmd(cmds[i], fd->in, pipes[1], fd);
	else
		exec_cmd(cmds[i], fd->in, pipes[1], fd);
	cleanup(fd);
}

void	only_child(t_fds *fd, char *cmd)
{
	fd->in = 0;
	fd->out = 1;
	if (fd->has_infile == 1)
		fd->in = open(fd->in_dir, O_RDONLY);
	if (fd->has_outfile == 1)
		fd->out = open(fd->out_dir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd->out == -1 || fd->in == -1 || process_single_command(cmd, fd) != 0)
	{
		if (fd->out == -1 || fd->in == -1)
			print_child_error(fd);
		else
		{
			if (fd->in != 0)
				close(fd->in);
			if (fd->out != 1)
				close(fd->out);
			cleanup(fd);
		}
		exit(1);
	}
	if (fd->is_pathed[0] == '1')
		exec_pathed_cmd(cmd, fd->in, fd->out, fd);
	else
		exec_cmd(cmd, fd->in, fd->out, fd);
	cleanup(fd);
}

void	middle_child(t_fds *fd, int *pipes, char **cmds, int i)
{
	if (process_single_command(cmds[i], fd) != 0)
		exit(1);
	if (fd->is_pathed[i] == '1')
		exec_pathed_cmd(cmds[i], fd->buffer, pipes[1], fd);
	else
		exec_cmd(cmds[i], fd->buffer, pipes[1], fd);
	cleanup(fd);
}

void	last_child(t_fds *fd, int *pipes, char **cmds, int i)
{
	if (pipes[1] != -1)
		close(pipes[1]);
	fd->out = 1;
	if (fd->has_outfile == 1)
		fd->out = open(fd->out_dir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (process_single_command(cmds[i], fd) != 0)
	{
		cleanup(fd);
		exit(127);
	}
	if (fd->out == -1)
	{
		printf("pipex: permission denied: %s\n", fd->out_dir);
		cleanup(fd);
		exit(1);
	}
	if (fd->is_pathed[i] == '1')
		exec_pathed_cmd(cmds[i], fd->buffer, fd->out, fd);
	else
		exec_cmd(cmds[i], fd->buffer, fd->out, fd);
	cleanup(fd);
}

static int	wait_and_exit(t_fds *fd, pid_t pid, int i, int *status)
{
	if (i != fd->how_many_cmd - 1)
	{
		waitpid(pid, NULL, 0);
		if (*status != -1)
			return (WEXITSTATUS(*status));
	}
	else
		waitpid(pid, status, 0);
	return (56);
}

int	create_children(t_fds *fd, char **cmds, char **env, int i)
{
	pid_t	pid;
	int		pipes[2];

	setup_pipes(pipes, i, fd->how_many_cmd);
	if (i == fd->how_many_cmd)
		return (cleanup(fd));
	printf("%dra vuelta comenzada\n", i);
	pid = fork();
	if (pid == 0)
	{
		if (i != fd->how_many_cmd - 1 && pipes[0] != -1)
			close(pipes[0]);
		if (i == 0)
			first_child(fd, pipes, cmds, i);
		else if (i == fd->how_many_cmd - 1)
			last_child(fd, pipes, cmds, i);
		else
			middle_child(fd, pipes, cmds, i);
		close(pipes[1]);
		exit(1);
	}
	manage_parent_fds(fd, pipes, i);
	printf("%dra vuelta terminada\n", i);
	create_children(fd, cmds, env, (i + 1));
	return (wait_and_exit(fd, pid, i, &(fd->status)));
}
