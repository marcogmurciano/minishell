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



///////////////////////////////////////

typedef enum		e_token_type
{
	TOKEN_EOF,			  // 0
	TOKEN_WORD,			  // 1
	TOKEN_PIPE,			  // 2
	TOKEN_REDIR_IN,		  // 3
	TOKEN_REDIR_OUT,	  // 4
	TOKEN_HEREDOC,		  // 5
	TOKEN_APPEND,		  // 6
	//
	// 	v EXTRAS ASSIGNED DURING REFINING PHASE v
	//
	TOKEN_REDIR_IN_FILE,  // 7
	TOKEN_REDIR_OUT_FILE, // 8
	TOKEN_HEREDOC_DELIM,  // 9
	TOKEN_APPEND_FILE,    // 10
	TOKEN_CMD,			  // 11
	TOKEN_ARG			  // 12
} 					t_token_type;

/**
 * Types of quotes
 */
typedef enum		e_quote_type
{
	NON_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
} 					t_quote_type;

typedef struct		s_cmd t_cmd;
typedef struct		s_cmd
{
	char			**argv;		// Array of arguments, [0] is command itshelf
	char			*infile;	// If REDIR_IN present
	char			*outfile;	// If REDIR_OUT present
	int				append;     // If APPEND present
	char			*heredoc;	// If HEREDOC present // This is the path to temp file
	t_cmd			*next;
} 					t_cmd;

typedef struct		s_env t_env;
typedef struct		s_env
{
	char			*key;
	char			*value;
	t_env			*next;
} 					t_env;

typedef struct		s_token
{
	char			*value;
	t_quote_type	quote_type;
	t_token_type	token_type;
	int             spaced;
	struct s_token	*next;
	struct s_token	*prev;
} 					t_token;

typedef struct		s_minishell
{
	char			**envp;
	char			*input;
	int				last_exit_status;		// "$?"
	int				duplicated_std_fds[2];
	int				pid;
	t_token			*tokens_list;
	t_env			*environment;
	t_cmd			*cmd_pipelines;
} 					t_minishell;


///////////////////////////////////////////////
typedef struct s_fds
{
	int			out;
	int			in;
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


int		process_cmds_errors(char *av[], int i, char **envp);
void	build_is_pathed(int ac, char *av[], char **is_pathed, int has_infile);
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
int		ft_pipex(int ac, char *av[], t_minishell *minishell, int has_files);