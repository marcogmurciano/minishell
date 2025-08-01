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

#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include "structs.h"

typedef struct s_fds
{
	int			out;
	int			in;
	int			heredoc;
	int			last_in;
	int			how_many_cmd;
	int			buffer;
	char		*is_pathed;
	char		*out_dir;
	char		*in_dir;
	char		**env;
	int			status;
	int			has_infile;
	int			has_outfile;
	t_minishell	*minishell;
}			t_fds;

void	exec_pathed_cmd(char **full_cmd, int input_fd, int output_fd, t_fds *fd);
void	exec_cmd(char **full_cmd, int input_fd, int output_fd, t_fds *fd);
int		exec_only_builtin(char **cmd, int input_fd, int output_fd, t_fds *fd);
int		cleanup(t_fds *fd);
int		create_children(t_fds *fd, t_cmd *cmds, char **env, int i);
char	*get_cmd_path(char *cmd, char **env);
void	free_bidimensional_array(char **arr);
char	*split_cmd_after_slash(const char *s);
char	**ft_strdup_arr(char **arr);
void	first_child(t_fds *fd, int *pipes, t_cmd *cmd);
void	middle_child(t_fds *fd, int *pipes, t_cmd *cmd);
void	last_child(t_fds *fd, int *pipes, t_cmd *cmd);
int		process_single_command(char **full_cmd, t_fds *fd);
void	setup_pipes(int *pipes, int i, int how_many_cmd);
void	manage_parent_fds(t_fds *fd, int *pipes, int i);
void	print_child_error(char *s, t_fds *fd);
void	only_child(t_fds *fd, t_cmd *cmd);
int		ft_pipex(int ac, t_cmd *cmd_list, t_minishell *minishell);
char	*join_cmd(char **full_cmd);
int 	is_builtin(char *cmd);
int		execute_built_in(t_minishell *minishell, char **split_cmd);
int		manage_infiles(t_cmd *cmd, t_fds *fd);
int		manage_outfiles(t_cmd *cmd, t_fds *fd);
int		manage_heredocs(t_cmd *cmd, t_fds *fd);
void 	restore_std_fds(t_minishell *minishell);

#endif