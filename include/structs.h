/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:41:19 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/18 16:53:03 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

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
typedef struct s_cmd {
    char    **argv;                  // Array of command arguments; argv[0] is the command itself.
    char    **infiles;               // Array of input file paths (REDIR_IN_FILES).
    char    **heredocs;              // Array of heredoc delimiters.
    int     expand_heredoc_content;  // If 1, expand variables in heredoc content; if 0, do not expand.
    int     last_in;                 // If 0, last input redirection is infile; if 1, last input is heredoc.
    char    **outfiles;              // Array of output file paths (REDIR_OUT_FILES).
    int     append;                  // If 1, append to last output file; if 0, overwrite.
    t_cmd   *next;                   // Pointer to the next command in the pipeline.
} t_cmd;
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
	char			*input;
	int				last_exit_status;		// "$?"
	int				duplicated_std_fds[2];
	int				pid;
	t_token			*tokens_list;
	t_env			*environment;
	t_cmd			*cmd_pipelines;
} 					t_minishell;

/**
 * Expansion auxiliary structure
 */
typedef struct		s_expansion
{
	char			*word_value;
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