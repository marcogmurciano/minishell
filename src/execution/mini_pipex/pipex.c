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

int	process_cmds_errors(char *av[], int i, char **envp)
{
	char	*path_cmd;
	int		f_exit;

	f_exit = 0;
	path_cmd = get_cmd_path(av[2 + i], envp);
	if (path_cmd == NULL)
		f_exit = printf("pipex: command not found: %s\n", av[2 + i]);
	else
		free(path_cmd);
	return (f_exit);
}

void	build_is_pathed(int ac, char *av[], char **is_pathed, int has_infile)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < ac)
	{
		if (ft_strchr(av[has_infile + i], '/'))
		{
			tmp = *is_pathed;
			*is_pathed = ft_strjoin(tmp, "1");
			free(tmp);
		}
		else
		{
			tmp = *is_pathed;
			*is_pathed = ft_strjoin(tmp, "0");
			free(tmp);
		}
	}
}

int	ft_pipex(int ac, char *av[], t_minishell *minishell, int has_files)
{
	t_fds	fd;
	pid_t	pid;

	fd.has_infile = (has_files / 10) - 1;
    fd.has_outfile = (has_files % 10) - 1;
	fd.env = ft_strdup_arr(minishell->envp);
	fd.is_pathed = ft_strdup("");
	build_is_pathed(ac, av, &fd.is_pathed, fd.has_infile);
	fd.minishell = minishell;
	fd.in_dir = ft_strdup(av[0]);
	fd.out_dir = ft_strdup(av[(ac + fd.has_infile + fd.has_outfile) - 1]);
	fd.buffer = -1;
	fd.status = -1;
	if (!fd.is_pathed)
		return(1);
	fd.how_many_cmd = ac;
	if (fd.how_many_cmd == 1)
	{
		pid = fork();
		if (pid == 0)
			only_child(&fd, av[fd.has_infile]);
		waitpid(pid, &(fd.status), 0);
		return (WEXITSTATUS(fd.status));
	}
	return (create_children(&fd, &av[fd.has_infile], fd.env, 0));
}
