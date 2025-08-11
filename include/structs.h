/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:41:19 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/11 12:07:34 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/**
 * Types of tokens
 */
typedef enum e_token_type
{
	TOKEN_EOF,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_REDIR_IN_FILE,
	TOKEN_REDIR_OUT_FILE,
	TOKEN_HEREDOC_DELIM,
	TOKEN_APPEND_FILE,
	TOKEN_CMD,
	TOKEN_ARG
}						t_token_type;

/**
 * Types of quotes
 */
typedef enum e_quote_type
{
	NON_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}						t_quote_type;

/**
 * Command structure
 */
typedef struct s_cmd	t_cmd;
typedef struct s_cmd
{
	char				**argv;
	char				**infiles;
	char				**heredocs;
	char				*last_heredoc_filepath;
	int					expand_heredoc_content;
	int					last_in;
	char				**outfiles;
	int					append;
	t_cmd				*next;
}						t_cmd;

/**
 * Minishell structure
 * Dependencies:
 * - Environment structure
 * - Token structure
 */
typedef struct s_env	t_env;
typedef struct s_env
{
	char				*key;
	char				*value;
	t_env				*next;
}						t_env;

typedef struct s_token
{
	char				*value;
	t_quote_type		quote_type;
	t_token_type		token_type;
	int					spaced;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_minishell
{
	char				**envp;
	char				**argv;
	int					argc;
	char				*input;
	int					last_exit_status;
	int					duplicated_std_fds[2];
	pid_t				pid;
	t_token				*tokens_list;
	t_env				*environment;
	t_cmd				*cmd_pipelines;
}						t_minishell;

/**
 * Expansion auxiliary structure
 */
typedef struct s_expansion
{
	int					dollar_position;
	int					variable_start;
	int					variable_name_length;
	char				*variable_name;
	char				*variable_value;
	char				*preffix;
	char				*suffix;
	char				*new_word_value;
}						t_expansion;

/**
 * Segment structure
 */
typedef struct s_segment
{
	char				**token_value;
	int					next_segment_start;
}						t_segment;

#endif