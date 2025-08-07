/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sons_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:03:50 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/07 17:21:32 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * Distribute to execution based on pathed state and input redirection type
 */
static void execute(t_cmd *cmd, t_fds *fd)
{
	if (ft_strchr(cmd->argv[0], '/') != NULL)
	{
		if(fd->last_in == 0 || fd->last_in == -1)
		{
			if (fd->heredoc != -1)
				close(fd->heredoc);
			exec_pathed_cmd(cmd->argv, fd->in, fd->out, fd);
		}
		if(fd->last_in == 1)
		{
			if (fd->in != 0 && fd->in != -1)
				close(fd->in);
			exec_pathed_cmd(cmd->argv, fd->heredoc, fd->out, fd);
		}
	}
	else
	{
		if(fd->last_in == 0 || fd->last_in == -1)
		{
			if (fd->heredoc != -1)
				close(fd->heredoc);
			exec_cmd(cmd->argv, fd->in, fd->out, fd);
		}
		if(fd->last_in == 1)
		{
			if (fd->in != 0 && fd->in != -1)
				close(fd->in);
			exec_cmd(cmd->argv, fd->heredoc, fd->out, fd);
		}
	}
}

/**
 * First child logic
 */
void	first_child(t_fds *fd, int *pipes, t_cmd *cmd)
{
	int	exit_code;

	fd->in = 0;
	fd->out = pipes[1];
	fd->last_in = cmd->last_in;
	fd->heredoc = manage_heredocs(cmd, fd);
	fd->in = manage_infiles(cmd, fd);
	fd->out = manage_outfiles(cmd, fd);
	exit_code = process_single_command(cmd->argv, fd);
	if (exit_code != 0)
	{
		if (fd->in != 0 && fd->in != -1)
			close(fd->in);
		if (fd->out != 0 && fd->out != -1)
			close(fd->out);
		if (fd->heredoc != -1)
			close(fd->heredoc);
		close(pipes[1]);
		cleanup(fd);
		exit(exit_code);
	}
	execute(cmd, fd);
	cleanup(fd);
}

/**
 * Only child logic
 */
void	only_child(t_fds *fd, t_cmd *cmd)
{
	int	exit_code;

	fd->in = 0;
	fd->out = 1;
	fd->last_in = cmd->last_in;
	fd->heredoc = manage_heredocs(cmd, fd);
	fd->in = manage_infiles(cmd, fd);
	fd->out = manage_outfiles(cmd, fd);
	exit_code = process_single_command(cmd->argv, fd);
	if (exit_code != 0)
	{
		if (fd->in != 0 && fd->in != -1)
			close(fd->in);
		if (fd->out != 0 && fd->out != -1)
			close(fd->out);
		if (fd->heredoc != -1)
			close(fd->heredoc);
		cleanup(fd);
		exit(exit_code);
	}
	execute(cmd, fd);
	cleanup(fd);
}

/**
 * Middle child logic
 */
void	middle_child(t_fds *fd, int *pipes, t_cmd *cmd)
{
	int	exit_code;

	fd->in = fd->buffer;
	fd->out = pipes[1];
	fd->last_in = cmd->last_in;
	fd->heredoc = manage_heredocs(cmd, fd);
	fd->in = manage_infiles(cmd, fd);
	fd->out = manage_outfiles(cmd, fd);
	exit_code = process_single_command(cmd->argv, fd);
	if (exit_code != 0)
	{
		if (fd->in != 0 && fd->in != -1)
			close(fd->in);
		if (fd->out != 0 && fd->out != -1)
			close(fd->out);
		if (fd->heredoc != -1)
			close(fd->heredoc);
		cleanup(fd);
		exit(exit_code);
	}
	execute(cmd, fd);
	cleanup(fd);
}

/**
 * Last child logic
 */
void	last_child(t_fds *fd, int *pipes, t_cmd *cmd)
{
	int	exit_code;

	if (pipes[1] != -1)
		close(pipes[1]);
	fd->in = fd->buffer;
	fd->out = 1;
	fd->last_in = cmd->last_in;
	fd->heredoc = manage_heredocs(cmd, fd);
	fd->in = manage_infiles(cmd, fd);
	fd->out = manage_outfiles(cmd, fd);
	exit_code = process_single_command(cmd->argv, fd);
	if (exit_code != 0)
	{
		if (fd->in != 0 && fd->in != -1)
			close(fd->in);
		if (fd->out != 0 && fd->out != -1)
			close(fd->out);
		if (fd->heredoc != -1)
			close(fd->heredoc);
		cleanup(fd);
		exit(exit_code);
	}
	execute(cmd, fd);
	cleanup(fd);
}
