/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:40:23 by marcoga2          #+#    #+#             */
/*   Updated: 2025/07/10 14:53:11 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

typedef struct s_fds
{
	int		out;
	int		in;
	int		how_many_cmd;
	int		buffer;
	char	*is_pathed;
	char	*out_dir;
	char	*in_dir;
	char	**env;
	int		status;
	int		has_infile;
	int		has_outfile;
}			t_fds;

int		process_cmds_errors(char *av[], int i, char **envp);
void	build_is_pathed(int ac, char *av[], char **is_pathed);
void	exec_pathed_cmd(char *cmd, int input_fd, int output_fd, t_fds *fd);
void	exec_cmd(char *cmd, int input_fd, int output_fd, t_fds *fd);
int		cleanup(t_fds *fd);
int		create_children(t_fds *fd, char **cmds, char **env, int i);
char	*get_cmd_path(char *cmd, char **env);
void	free_bidimensional_array(char **arr);
char	*split_cmd_after_slash(const char *s);
char	*has_command(char **paths, char *cmd);
char	**ft_strdup_arr(char **arr);
void	first_child(t_fds *fd, int *pipes, char **cmds, int i);
void	middle_child(t_fds *fd, int *pipes, char **cmds, int i);
void	last_child(t_fds *fd, int *pipes, char **cmds, int i);
int		process_single_command(char *cmd, t_fds *fd);
int		process_cmd_errors(char *cmd, char **env);
void	setup_pipes(int *pipes, int i, int how_many_cmd);
void	manage_parent_fds(t_fds *fd, int *pipes, int i);
void	print_child_error(t_fds *fd);
void	only_child(t_fds *fd, char *cmd);
int		ft_pipex(int ac, char *av[], char **envp, int has_files);