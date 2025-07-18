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

////////////////////////////////////////////
//     hay que liberar así tras los execve?
	// free(cmd_path);
	// free_bidimensional_array(args);
////////////////////////////////////

//recordar exit y cleanup al final de cada builtin

static void	manual_execution(char *cmd, t_fds *fd)
{
	char **split_cmd;

	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		exit(1);
	// if (ft_strcmp(split_cmd[0], "echo") == 0)
    // 	// builtin_echo();
	if (ft_strcmp(split_cmd[0], "export") == 0)
	    builtin_export(fd->minishell, split_cmd);
	// if (ft_strcmp(split_cmd[0], "cd") == 0)
	//     // builtin_cd();
	if (ft_strcmp(split_cmd[0], "pwd") == 0)
	    builtin_pwd();
	// if (ft_strcmp(split_cmd[0], "unset") == 0)
	//     // builtin_unset();
	if (ft_strcmp(split_cmd[0], "env") == 0)
	    builtin_env(fd->minishell, split_cmd);
	// if (ft_strcmp(split_cmd[0], "exit") == 0)
	//     // builtin_exit();

	// cleanup
	// exit
}

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
	manual_execution(cmd, fd);
	execve(cmd_path, args, fd->env);
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
	manual_execution(cmd, fd);
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
