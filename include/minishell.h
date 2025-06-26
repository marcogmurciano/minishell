/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:58:22 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/26 17:00:47 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/include/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include <signal.h>

/**
 * Types of tokens
 */
typedef enum e_token_type
{
	TOKEN_WORD,           // 0
	TOKEN_PIPE,           // 1
	TOKEN_REDIR_IN,       // 2
	TOKEN_REDIR_IN_FILE,  // 2
	TOKEN_REDIR_OUT,      // 3
	TOKEN_REDIR_OUT_FILE, // 3
	TOKEN_HEREDOC,        // 4
	REDIR_HEREDOC_DELIM,  // 5
	TOKEN_APPEND,         // 6
	TOKEN_EOF,            // 7
	CMD,				  // 8
	ARG                   // 9
}						t_token_type;

/**
 * Types of quotes
 */
typedef enum e_quote_type
{
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	NON_QUOTE,
}						t_quote_type;

/**
 * Command structure
 */
typedef struct s_cmd
{
	char				*command;
	char				*pathname;
	char				**arguments;
	int					is_pathname;
}						t_cmd;

/**
 * Expansion auxiliary structure
 */
typedef struct s_expansion
{
	char			*word_value;
	int 			dollar_position;
	int 			variable_start;
	int 			variable_name_length;
	char			*variable_name;
	char			*variable_value;
	char			*preffix;
	char			*suffix;
	char			*new_word_value;
}					t_expansion;

/**
 * Minishell structure
 * Dependencies:
 * - Environment structure
 * - Token structure
 */
typedef struct s_env	t_env;
typedef struct s_env
{
	char				*name;
	char				*value;
	t_env				*next;
}						t_env;

typedef struct s_token
{
	char				*value;
	t_quote_type		quote_type;
	t_token_type		token_type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_minishell
{
	char				*input;
	char				*expanded_input;
	t_token				*tokens_list;
	t_env				*environment;
}						t_minishell;

//////////////////////////////////////////////
//
//    REGENERATE ENVIRONMENT
//
////////////

/**
 * Builds a linked list of environment variables from envp.
 * @param envp The environment pointer array.
 * @return Pointer to the head of the linked list.
 */
t_env *regenerate_environment(char **envp);

//////////////////////////////////////////////
//
//    PROMPT INPUT
//
////////////

/**
 * @brief Prompt the user for input using a custom prompt string.
 *
 * The prompt includes the user's name (from the $USER environment variable)
 * if available, followed by "@minishell> ". If $USER is not found, "USER"
 * is used as the default name.
 *
 * The function reads a line from standard input and adds it to the history
 * if not NULL. The caller is responsible for freeing the returned string.
 *
 * @return A pointer to the input string, or NULL if EOF is encountered.
 */
char	*get_prompt_input(void);

//////////////////////////////////////////////
//
//    SIGNALS
//
////////////

/**
 * @brief Signal handler for SIGINT (Ctrl+C).
 *
 * TODO: Send -SIGINT kill signal to each process/command PIDs in commands list.
 *
 * @param signal_number The signal number received.
 */
void sigint_handler(int signal_number);

//////////////////////////////////////////////
//
//    FREEING UTILS
//
////////////

/**
 * Frees all dynamically allocated fields within a t_minishell struct.
 * After freeing, all pointers are set to NULL to avoid dangling pointers.
 * @param minishell
 */
void free_minishell(t_minishell *minishell);

/**
 * Frees a linked list of environment nodes, releasing all associated memory.
 * @param env_head Double pointer to the head of the environment list.
 */
void free_environment(t_env **env_head);

/**
 * Frees a linked list of tokens, releasing all associated memory.
 * @param token_head Double pointer to the head of the token list.
 */
void free_tokens_list(t_token **token_head);

//////////////////////////////////////////////
//
//    EXIT
//
////////////

/**
 * Cleans up resources and exits the minishell program.
 * @param minishell Pointer to the minishell context.
 */
void exit_minishell(t_minishell *minishell);
#endif