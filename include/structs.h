/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:41:19 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/05 15:34:34 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/**
 * Types of tokens
 */
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

/**
 * Command structure
 */
typedef struct		s_cmd t_cmd;
typedef struct		s_cmd
{
	char			**argv;		              // Array of arguments, [0] is command itshelf
	char			**infiles;	              // Array of REDIR_IN_FILES
	char			**heredocs;	              // Array of HEREDOC delimiters
	char			*last_heredoc_filepath;	  // Path to last heredoc
	int				expand_heredoc_content;   // 0 If content doesn't expand, 1 expand variables of heredoc content
	int				last_in;                  // 0 = Last redir_in is infile, 1 = last redir_in is heredoc
	char			**outfiles;	              // Array of REDIR_OUT_FILES
	int				append;                   // Append status of last (valid) outfile redirection: 0 or 1
	t_cmd			*next;
} 					t_cmd;

/**
 * Minishell structure
 * Dependencies:
 * - Environment structure
 * - Token structure
 */
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
	int				spaced;
	struct s_token	*next;
	struct s_token	*prev;
} 					t_token;

typedef struct		s_minishell
{
	char			**envp;
	char			**argv;
	int				argc;
	char			*input;
	int				last_exit_status;		// "$?"
	int				duplicated_std_fds[2];
	pid_t			pid;
	t_token			*tokens_list;
	t_env			*environment;
	t_cmd			*cmd_pipelines;
} 					t_minishell;

/**
 * Expansion auxiliary structure
 */
typedef struct		s_expansion
{
	int				dollar_position;
	int				variable_start;
	int				variable_name_length;
	char			*variable_name;
	char			*variable_value;
	char			*preffix;
	char			*suffix;
	char			*new_word_value;
} 					t_expansion;

/**
 * Segment structure
 */
typedef struct		s_segment
{
	char			**token_value;
	int				next_segment_start;
} 					t_segment;

#endif