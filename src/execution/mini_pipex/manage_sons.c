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


char	*join_cmd(char **cmd)
{
	int i;
	char *t;
	char *r;

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

int	manage_outfiles(t_cmd *cmd, t_fds *fd)
{
	int i;

	i = 0;
	while (cmd->outfiles[i])
	{
		if (fd->out != -1 && fd->out != 1)
		{
			close(fd->out);
			fd->out = -1;
		}
		if (cmd->outfiles[i] != NULL && cmd->append)
		{
			fd->out = open(cmd->outfiles[i], O_WRONLY | O_CREAT | O_APPEND,
					0644);
		}
		if (cmd->outfiles[i] != NULL && !cmd->append)
		{
			fd->out = open(cmd->outfiles[i], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		}
		if (fd->out == -1)
		{
			print_child_error(cmd->outfiles[i], fd);
			exit(1);
		}
		i++;
	}
	return (fd->out);
}

int	manage_infiles(t_cmd *cmd, t_fds *fd)
{
	int i;

	i = 0;
	while (cmd->infiles[i])
	{
		if (fd->in != -1 && fd->out != 0)
		{
			close(fd->in);
			fd->in = -1;
		}
		if (cmd->infiles[i] != NULL && cmd->append)
		{
			fd->in = open(cmd->infiles[i], O_WRONLY | O_CREAT | O_APPEND,
					0644);
		}
		if (cmd->infiles[i] != NULL && !cmd->append)
		{
			fd->in = open(cmd->infiles[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (fd->in == -1)
		{
			print_child_error(cmd->infiles[i], fd);
			exit(1);
		}
		i++;
	}
	return (fd->in);
}

int	manage_heredocs(t_cmd *cmd, t_fds *fd)
{
	int i;
	char *line;
	char *filepath;
	char *filenum;
	char *final_line;
	char *last_filepath;

	i = 0;
	final_line = NULL;
	while (cmd->heredocs[i])
	{
		filenum = ft_itoa(i);
		filepath = ft_strjoin("/tmp/.heredoc_minishell", filenum);
		free(filenum);
		if (fd->heredoc != -1)
		{
			close(fd->heredoc);
			fd->heredoc = -1;
		}
		if (access(filepath, F_OK) == 0)
			unlink(filepath);
		fd->heredoc = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd->heredoc == -1)
			perror("");
		while (1)
		{
			line = readline("> ");
			if (line)
			{
				if (ft_strcmp(line, cmd->heredocs[i]) == 0)
				{
					free(line);
					close(fd->heredoc);
					fd->heredoc = -1;
					break ;
				}
				if (cmd->expand_heredoc_content)
				{
					final_line = expand_heredoc_line(fd->minishell, line);
				}
				else
				{
					final_line = ft_strdup(line);
				}
				ft_putendl_fd(line, fd->heredoc);
				free(line);
				free(final_line);
			}
			else
			{
				printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
					cmd->heredocs[i]);
				close(fd->heredoc);
				fd->heredoc = -1;
				break ;
			}
		}
		if (last_filepath)
			free(last_filepath);
		last_filepath = filepath;
		i++;
	}
	if (cmd->last_in == 0 && last_filepath)
	{
		if (fd->in != 0 && fd->in != -1)
			close(fd->in);
		fd->in = open(last_filepath, O_RDONLY);
		if (fd->in == -1)
			perror("Error opening heredoc file for reading");
	}
	if (last_filepath)
		free(last_filepath);
	return (fd->heredoc);
}

void	first_child(t_fds *fd, int *pipes, t_cmd *cmd)
{
	// char *joined_cmd;

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
	// joined_cmd = join_cmd(cmd->argv);
	// if (ft_strchr(joined_cmd, '/') != NULL)
	if (ft_strchr(cmd->argv[0], '/') != NULL)
		exec_pathed_cmd(cmd->argv, fd->in, fd->out, fd);
	else
		exec_cmd(cmd->argv, fd->in, fd->out, fd);
	cleanup(fd);
}

void	only_child(t_fds *fd, t_cmd *cmd)
{
	// char *joined_cmd;

	// joined_cmd = join_cmd(cmd->argv);
	fd->in = 0;
	fd->out = 1;
	fd->in = manage_infiles(cmd, fd);
	fd->out = manage_outfiles(cmd, fd);
	if (cmd->heredocs && cmd->heredocs[0])
		fd->heredoc = manage_heredocs(cmd, fd);
	fd->last_in = cmd->last_in;
	// debug
	// printf("llega a only child\n");
	//
	if (process_single_command(cmd->argv, fd) != 0)
	{
		if (fd->in != 0)
			close(fd->in);
		if (fd->out != 1)
			close(fd->out);
		cleanup(fd);
		exit(127);
	}
	// printf("   ... no fue el ultimo\n");
	// joined_cmd = join_cmd(cmd->argv);
	// if (ft_strchr(joined_cmd, '/') != NULL)
	if (ft_strchr(cmd->argv[0], '/') != NULL)
		exec_pathed_cmd(cmd->argv, fd->in, fd->out, fd);
	else
		exec_cmd(cmd->argv, fd->in, fd->out, fd);
	cleanup(fd);
}

void	middle_child(t_fds *fd, int *pipes, t_cmd *cmd)
{
	// char *joined_cmd;
	// joined_cmd = join_cmd(cmd->argv);
	fd->in = fd->buffer;
	fd->out = pipes[1];
	fd->in = manage_infiles(cmd, fd);
	fd->out = manage_outfiles(cmd, fd);
	if (cmd->heredocs && cmd->heredocs[0])
		fd->heredoc = manage_heredocs(cmd, fd);
	fd->last_in = cmd->last_in;
	if (process_single_command(cmd->argv, fd) != 0)
		exit(127);
	// joined_cmd = join_cmd(cmd->argv);
	// if (ft_strchr(joined_cmd, '/') != NULL)
	if (ft_strchr(cmd->argv[0], '/') != NULL)
		exec_pathed_cmd(cmd->argv, fd->in, fd->out, fd);
	else
		exec_cmd(cmd->argv, fd->in, fd->out, fd);
	cleanup(fd);
}

void	last_child(t_fds *fd, int *pipes, t_cmd *cmd)
{
	// char *joined_cmd;

	// joined_cmd = join_cmd(cmd->argv);
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
	// joined_cmd = join_cmd(cmd->argv);
	// if (ft_strchr(joined_cmd, '/') != NULL)
	if (ft_strchr(cmd->argv[0], '/') != NULL)
		exec_pathed_cmd(cmd->argv, fd->in, fd->out, fd);
	else
		exec_cmd(cmd->argv, fd->in, fd->out, fd);
	cleanup(fd);
}

static void	saturn_devours_children(int *pids)
{
	int i;

	i = 1;
	while (pids[i])
	{
		kill(pids[i], SIGKILL);
		i++;
	}
}

static int	wait_children(t_fds *fd)
{
	int i;
	int status;

	i = 0;
	status = 0;
	// metralleta:
	waitpid(fd->pid_array[i], &status, 0);
	i++;
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		saturn_devours_children(fd->pid_array);
	//
	while (i < fd->how_many_cmd)
	{
		waitpid(fd->pid_array[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

int	create_children(t_fds *fd, t_cmd *cmds, char **env)
{
	int i = 0;
	int pipes[2];
	t_cmd *cur = cmds;

	while (i < fd->how_many_cmd)
	{
		setup_pipes(pipes, i, fd->how_many_cmd);
		ignore_signals();
		fd->pid_array[i] = fork();
		fd->minishell->pid = fd->pid_array[i];
		if (fd->pid_array[i] == 0)
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
		manage_parent_fds(fd, pipes, i);
		cur = cur->next;
		i++;
	}
	return (0);
}
