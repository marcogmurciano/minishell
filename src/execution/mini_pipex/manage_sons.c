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

char *join_cmd(char **cmd)
{
	int i;
	char *t;
	char *r;

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

static int	cosasdelout(t_cmd *cmd, t_fds *fd)
{
	int i;

	i = 0;
	while (cmd->outfiles[i])
	{
		if (cmd->outfiles[i] != NULL && cmd->append)
			fd->out = open(cmd->outfiles[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->outfiles[i] != NULL && !cmd->append)
			fd->out = open(cmd->outfiles[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd->out == -1)
		{
			print_child_error(cmd->outfiles[i], fd);
			exit (1);
		}
		i++;
	}
	return (fd->out);
}

static int	cosasdelin(t_cmd *cmd, t_fds *fd)
{
	int i;

	i = 0;
	while (cmd->infiles[i])
	{
		if (cmd->infiles[i] != NULL && cmd->append)
			fd->in = open(cmd->infiles[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->infiles[i] != NULL && !cmd->append)
			fd->in = open(cmd->infiles[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd->in == -1)
		{
			print_child_error(cmd->infiles[i], fd);
			exit (1);
		}
		i++;
	}
	return (fd->in);
}

void	first_child(t_fds *fd, int *pipes, t_cmd *cmd)
{
	char *joined_cmd;

	fd->in = 0;
	fd->out = pipes[1];
	fd->in = cosasdelin(cmd, fd);
	fd->out = cosasdelout(cmd, fd);
	if (process_single_command(cmd->argv, fd) != 0)
	{
		if (fd->in != 0)
			close(fd->in);
		close(pipes[1]);
		cleanup(fd);
		exit(127);
	}
	joined_cmd = join_cmd(cmd->argv);
	if (ft_strchr(joined_cmd, '/') != NULL)
		exec_pathed_cmd(joined_cmd, fd->in, fd->out, fd);
	else
		exec_cmd(joined_cmd, fd->in, fd->out, fd);
	cleanup(fd);
}

void	only_child(t_fds *fd, t_cmd *cmd)
{
	char *joined_cmd;
	
	joined_cmd = join_cmd(cmd->argv);
	//debug
	// printf("joined cmd en only child: %s\n", joined_cmd);
	//
	fd->in = 0;
	fd->out = 1;
	fd->in = cosasdelin(cmd, fd);
	fd->out = cosasdelout(cmd, fd);
	if (process_single_command(cmd->argv, fd) != 0)
	{
		if (fd->in != 0)
			close(fd->in);
		if (fd->out != 1)
			close(fd->out);
		cleanup(fd);
		exit(127);
	}
	if (ft_strchr(joined_cmd, '/') != NULL)
		exec_pathed_cmd(joined_cmd, fd->in, fd->out, fd);
	else
		exec_cmd(joined_cmd, fd->in, fd->out, fd);
	cleanup(fd);
}

void	middle_child(t_fds *fd, int *pipes, t_cmd *cmd)
{
	char *joined_cmd;

	joined_cmd = join_cmd(cmd->argv);
	fd->in = fd->buffer;
	fd->out = pipes[1];
	fd->in = cosasdelin(cmd, fd);
	fd->out = cosasdelout(cmd, fd);
	if (process_single_command(cmd->argv, fd) != 0)
		exit(127);
	if (ft_strchr(joined_cmd, '/') != NULL)
		exec_pathed_cmd(joined_cmd, fd->in, fd->out, fd);
	else
		exec_cmd(joined_cmd, fd->in, fd->out, fd);
	cleanup(fd);
}

void	last_child(t_fds *fd, int *pipes, t_cmd *cmd)
{
	char *joined_cmd;

	joined_cmd = join_cmd(cmd->argv);
	if (pipes[1] != -1)
		close(pipes[1]);
	fd->in = fd->buffer;
	fd->out = 1;
	cosasdelout(cmd, fd);
	if (process_single_command(cmd->argv, fd) != 0)
	{
		cleanup(fd);
		exit(127);
	}
	if (ft_strchr(joined_cmd, '/') != NULL)
		exec_pathed_cmd(joined_cmd, fd->in, fd->out, fd);
	else
		exec_cmd(joined_cmd, fd->in, fd->out, fd);
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

int	create_children(t_fds *fd, t_cmd *cmds, char **env, int i)
{
	pid_t	pid;
	int		pipes[2];

	setup_pipes(pipes, i, fd->how_many_cmd);
	if (i == fd->how_many_cmd)
		return (cleanup(fd));
	pid = fork();
	if (pid == 0)
	{
		if (i != fd->how_many_cmd - 1 && pipes[0] != -1)
			close(pipes[0]);
		if (i == 0)
			first_child(fd, pipes, cmds);
		else if (i == fd->how_many_cmd - 1)
			last_child(fd, pipes, cmds);
		else
			middle_child(fd, pipes, cmds);
		close(pipes[1]);
		exit(1);
	}
	manage_parent_fds(fd, pipes, i);
	cmds = cmds->next;
	create_children(fd, cmds, env, (i + 1));
	return (wait_and_exit(fd, pid, i, &(fd->status)));
}