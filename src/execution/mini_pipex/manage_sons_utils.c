/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sons_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:03:50 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/04 11:05:54 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	first_child(t_fds *fd, int *pipes, t_cmd *cmd)
{
	fd->in = 0;
	fd->out = pipes[1];
	fd->in = manage_infiles(cmd, fd);
	fd->out = manage_outfiles(cmd, fd);
	if (cmd->heredocs && cmd->heredocs[0])
		fd->heredoc = manage_heredocs(cmd, fd);
	fd->last_in = cmd->last_in;
	if (process_single_command(cmd->argv, fd) != 0)
	{
		if (fd->in != 0)
			close(fd->in);
		close(pipes[1]);
		cleanup(fd);
		exit(127);
	}
	if (ft_strchr(cmd->argv[0], '/') != NULL)
		exec_pathed_cmd(cmd->argv, fd->in, fd->out, fd);
	else
		exec_cmd(cmd->argv, fd->in, fd->out, fd);
	cleanup(fd);
}

void	only_child(t_fds *fd, t_cmd *cmd)
{
	fd->in = 0;
	fd->out = 1;
	fd->in = manage_infiles(cmd, fd);
	fd->out = manage_outfiles(cmd, fd);
	if (cmd->heredocs && cmd->heredocs[0])
		fd->heredoc = manage_heredocs(cmd, fd);
	fd->last_in = cmd->last_in;
	if (process_single_command(cmd->argv, fd) != 0)
	{
		if (fd->in != 0)
			close(fd->in);
		if (fd->out != 1)
			close(fd->out);
		cleanup(fd);
		exit(127);
	}
	if (ft_strchr(cmd->argv[0], '/') != NULL)
		exec_pathed_cmd(cmd->argv, fd->in, fd->out, fd);
	else
		exec_cmd(cmd->argv, fd->in, fd->out, fd);
	cleanup(fd);
}

void	middle_child(t_fds *fd, int *pipes, t_cmd *cmd)
{
	fd->in = fd->buffer;
	fd->out = pipes[1];
	fd->in = manage_infiles(cmd, fd);
	fd->out = manage_outfiles(cmd, fd);
	if (cmd->heredocs && cmd->heredocs[0])
		fd->heredoc = manage_heredocs(cmd, fd);
	fd->last_in = cmd->last_in;
	if (process_single_command(cmd->argv, fd) != 0)
		exit(127);
	if (ft_strchr(cmd->argv[0], '/') != NULL)
		exec_pathed_cmd(cmd->argv, fd->in, fd->out, fd);
	else
		exec_cmd(cmd->argv, fd->in, fd->out, fd);
	cleanup(fd);
}

void	last_child(t_fds *fd, int *pipes, t_cmd *cmd)
{
	if (pipes[1] != -1)
		close(pipes[1]);
	fd->in = fd->buffer;
	fd->out = 1;
	if (cmd->heredocs && cmd->heredocs[0])
		fd->heredoc = manage_heredocs(cmd, fd);
	fd->last_in = cmd->last_in;
	manage_outfiles(cmd, fd);
	if (process_single_command(cmd->argv, fd) != 0)
	{
		cleanup(fd);
		exit(127);
	}
	if (ft_strchr(cmd->argv[0], '/') != NULL)
		exec_pathed_cmd(cmd->argv, fd->in, fd->out, fd);
	else
		exec_cmd(cmd->argv, fd->in, fd->out, fd);
	cleanup(fd);
}

char	*join_cmd(char **cmd)
{
	int		i;
	char	*t;
	char	*r;

	r = NULL;
	i = 0;
	while (cmd[i])
	{
		if (i == 0)
			r = ft_strdup(cmd[i]);
		else
		{
			t = r;
			r = ft_strjoin(t, " ");
			free(t);
			t = r;
			r = ft_strjoin(t, cmd[i]);
			free(t);
		}
		i++;
	}
	return (r);
}
