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

int	ft_pipex(int ac, t_cmd *cmd_list, t_minishell *minishell)
{
	t_fds	fd;
	pid_t	pid;

	fd.env = ft_strdup_arr(minishell->envp);
	fd.minishell = minishell;
	fd.buffer = -1;
	fd.status = -1;
	fd.how_many_cmd = ac;
	//debug
	// int i = 0;
	// printf("minishell envp en ft_pipex: \n");
	// while(minishell->envp[i])
	// {
	// 	printf("%s \n", minishell->envp[i]);
	// 	i++;
	// }
	//
	if (fd.how_many_cmd == 1)
	{
		pid = fork();
		if (pid == 0)
			only_child(&fd, cmd_list);
		waitpid(pid, &(fd.status), 0);
		return (WEXITSTATUS(fd.status));
	}
	return (create_children(&fd, cmd_list, fd.env, 0));
}