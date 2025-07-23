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

int execute_built_in(t_minishell *minishell, char **split_cmd)
{
	int		status;

	// printf("comando builtineado");
	status = 0;
	if (ft_strcmp(split_cmd[0], "echo") == 0)
		status = builtin_echo(minishell, split_cmd);
	else if (ft_strcmp(split_cmd[0], "export") == 0)
		status = builtin_export(minishell, split_cmd);
	else if (ft_strcmp(split_cmd[0], "pwd") == 0)
		status = builtin_pwd();
	else if (strcmp(split_cmd[0], "unset") == 0)
		status = builtin_unset(minishell, split_cmd);
	else if (ft_strcmp(split_cmd[0], "env") == 0)
		status = builtin_env(minishell, split_cmd);
	else if (ft_strcmp(split_cmd[0], "cd") == 0)
	    builtin_cd(split_cmd);
	else if (ft_strcmp(split_cmd[0], "exit") == 0)
	    builtin_exit(minishell, split_cmd);
	
	return(status);
}

int	is_builtin(char *split_cmd)
{
	if (ft_strcmp(split_cmd, "echo") == 0
		|| ft_strcmp(split_cmd, "export") == 0
		|| ft_strcmp(split_cmd, "pwd") == 0
		|| ft_strcmp(split_cmd, "unset") == 0
		|| ft_strcmp(split_cmd, "env") == 0
		|| ft_strcmp(split_cmd, "cd") == 0
		|| ft_strcmp(split_cmd, "exit") == 0)
		return (1);
	return (0);
}

static int	manual_execution(char *cmd, t_fds *fd)
{
	char	**split_cmd;
	int		status;

	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		return (1);
	if (is_builtin(split_cmd[0]))
	{
		status = execute_built_in(fd->minishell, split_cmd);
		ft_free_array((void **)split_cmd);
		split_cmd = NULL;
		cleanup(fd);
		exit(status);
	}
	ft_free_array((void **)split_cmd);
	return (0);
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
	if (dup2(input_fd, STDIN_FILENO) == -1)
		perror("pipex");
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		perror("pipex");
	if (input_fd != -1 && input_fd != 0)
		close(input_fd);
	if (output_fd != -1 && output_fd != 1)
		close(output_fd);
	manual_execution(cmd, fd);
	cmd_path = get_cmd_path(args[0], fd->env);
	execve(cmd_path, args, fd->env);
	perror("pipex");
}

int	exec_only_builtin(char *cmd, int input_fd, int output_fd, t_fds *fd)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		if (args)
			free_bidimensional_array(args);
		printf("pipex: empty command");
		exit(1);
	}
	if (dup2(input_fd, STDIN_FILENO) == -1)
		perror("pipex");
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		perror("pipex");
	if (input_fd != -1 && input_fd != 0)
		close(input_fd);
	if (output_fd != -1 && output_fd != 1)
		close(output_fd);
	return (manual_execution(cmd, fd));
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

void	print_child_error(char *s, t_fds *fd)
{
	if (errno == ENOENT)
		printf("pipex: No such file or directory: %s\n", s);
	else if (errno == EACCES)
		printf("pipex: Permission denied: %s\n", s);
	else
		printf("pipex: Error opening file: %s\n", s);
	cleanup(fd);
}
