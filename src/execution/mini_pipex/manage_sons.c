/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/08/01 14:14:33 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/01 14:14:33 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * Files REDIR_OUT management   01 is O_WRONLY but line would be too long
 */
int	manage_outfiles(t_cmd *cmd, t_fds *fd)
{
	int	i;

	i = 0;
	while (cmd->outfiles[i])
	{
		if (fd->out != -1 && fd->out != 1)
		{
			close(fd->out);
			fd->out = -1;
		}
		if (cmd->outfiles[i] != NULL && cmd->append)
			fd->out = open(cmd->outfiles[i], O_CREAT | 01 | O_APPEND, 420);
		else if (cmd->outfiles[i] != NULL && !cmd->append)
			fd->out = open(cmd->outfiles[i], O_CREAT | 01 | O_TRUNC, 420);
		if (fd->out == -1)
		{
			print_child_error(cmd->outfiles[i], fd);
			exit(1);
		}
		i++;
	}
	return (fd->out);
}

/**
 * Files REDIR_IN management
 */
int	manage_infiles(t_cmd *cmd, t_fds *fd)
{
	int	i;

	i = 0;
	while (cmd->infiles[i])
	{
		if (fd->in != -1 && fd->out != 0)
		{
			close(fd->in);
			fd->in = -1;
		}
		if (cmd->infiles[i] != NULL)
			fd->in = open(cmd->infiles[i], O_RDONLY);
		if (fd->in == -1)
		{
			print_child_error(cmd->infiles[i], fd);
			exit(1);
		}
		i++;
	}
	return (fd->in);
}

/**
 * Wait for child processes  to end
 */
static int	wait_children(t_fds *fd)
{
	int		i;
	int		status;
	ssize_t	n_flag;

	i = 0;
	n_flag = 0;
	status = 0;
	while (i < fd->how_many_cmd)
	{
		waitpid(fd->pid_array[i], &status, 0);
		if (status == 2 && !n_flag)
			n_flag = write(1, "\n", 1);
		else if (status == 131 && !n_flag)
			n_flag = write(1, "Quit (core dumped)\n", 20);
		if (i == 0 && WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			saturn_devours_children(fd->pid_array);
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

/**
 * Distribution to different child functions
 */
static void	son(int i, t_fds *fd, t_cmd *cur, int *pipes)
{
	default_signals();
	if (i != fd->how_many_cmd - 1 && pipes[0] != -1)
		close(pipes[0]);
	if (i == 0)
		first_child(fd, pipes, cur);
	else if (i == fd->how_many_cmd - 1)
		last_child(fd, pipes, cur);
	else
		middle_child(fd, pipes, cur);
	close(pipes[1]);
	exit(1);
}

/**
 * Logic for multiple children
 */
int	create_children(t_fds *fd, t_cmd *cmds)
{
	int		i;
	int		pipes[2];
	t_cmd	*cur;

	cur = cmds;
	i = 0;
	while (i < fd->how_many_cmd)
	{
		setup_pipes(pipes, i, fd->how_many_cmd);
		ignore_signals();
		fd->pid_array[i] = fork();
		fd->minishell->pid = fd->pid_array[i];
		if (fd->pid_array[i] == 0)
			son(i, fd, cur, pipes);
		manage_parent_fds(fd, pipes, i);
		cur = cur->next;
		i++;
	}
	return (wait_children(fd));
}
