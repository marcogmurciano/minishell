/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:39:41 by marcoga2          #+#    #+#             */
/*   Updated: 2025/07/10 15:05:52 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	manage_parent_fds(t_fds *fd, int *pipes, int i)
{
	if (pipes[1] != -1)
	{
		close(pipes[1]);
		pipes[1] = -1;
	}
	if (fd->buffer != -1)
	{
		close(fd->buffer);
		fd->buffer = -1;
	}
	if (i != fd->how_many_cmd - 1 && pipes[0] != -1)
		fd->buffer = pipes[0];
	else
		fd->buffer = -1;
}

void	setup_pipes(int *pipes, int i, int how_many_cmd)
{
	pipes[0] = -1;
	pipes[1] = -1;
	if (i == how_many_cmd)
		return ;
	if (i != how_many_cmd - 1)
		pipe(pipes);
}

static void	bad_command(t_fds *fd)
{
	if (fd->in != 0 && fd->in != -1)
	{
		close(fd->in);
		fd->in = -1;
	}
	if (fd->out != 1 && fd->out != -1)
	{
		close(fd->out);
		fd->out = -1;
	}
	if (fd->heredoc != -1)
	{
		close(fd->heredoc);
		fd->heredoc = -1;
	}
	cleanup(fd);
	exit(127);
}

static int	only_builtin_son(t_fds *fd, t_cmd *cmd_list, int *status)
{
	if (is_builtin(cmd_list->argv[0]))
	{
		fd->in = 0;
		fd->out = 1;
		fd->in = manage_infiles(cmd_list, fd);
		fd->out = manage_outfiles(cmd_list, fd);
		if (cmd_list->heredocs && cmd_list->heredocs[0])
			fd->heredoc = manage_heredocs(cmd_list, fd);
		fd->last_in = cmd_list->last_in;
		if (process_single_command(cmd_list->argv, fd) != 0)
			bad_command(fd);
		*status = exec_only_builtin((cmd_list->argv), fd->in, fd->out, fd);
		cleanup(fd);
		return (*status);
	}
	fd->minishell->pid = fork();
	ignore_signals();
	if (fd->minishell->pid == 0)
	{
		default_signals();
		only_child(fd, cmd_list);
	}
	waitpid(fd->minishell->pid, &(fd->status), 0);
	return (9999);
}

int	ft_pipex(int ac, t_cmd *cmd_list, t_minishell *minishell)
{
	t_fds	fd;
	int		returnvalue;
	int		status;

	fd.env = ft_strdup_arr(minishell->envp);
	fd.minishell = minishell;
	fd.buffer = -1;
	fd.status = -1;
	fd.how_many_cmd = ac;
	fd.pid_array = ft_calloc(ac, (sizeof(int *) + 1));
	if (fd.how_many_cmd == 1)
	{
		returnvalue = only_builtin_son(&fd, cmd_list, &status);
		if (returnvalue != 9999)
			return (returnvalue);
		if (WIFEXITED(fd.status))
			return (WEXITSTATUS(fd.status));
		if (WIFSIGNALED(fd.status))
			return (128 + WTERMSIG(fd.status));
		return (fd.status);
	}
	return (create_children(&fd, cmd_list));
}
