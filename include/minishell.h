/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:58:22 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/02 16:51:40 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../../libft/include/libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include <signal.h>

/**
 * Signals global variable
 */
extern volatile sig_atomic_t g_signal_status;

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
typedef struct		s_cmd
{
	char			*command;
	char			*pathname;
	char			**arguments;
	int				is_pathname;
} 					t_cmd;

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
 * Minishell structure
 * Dependencies:
 * - Environment structure
 * - Token structure
 */
typedef struct		s_env t_env;
typedef struct		s_env
{
	char			*name;
	char			*value;
	t_env			*next;
} 					t_env;

typedef struct		s_token
{
	char			*value;
	t_quote_type	quote_type;
	t_token_type	token_type;
	struct s_token	*next;
	struct s_token	*prev;
} 					t_token;

typedef struct		s_minishell
{
	char			**envp;
	char			*input;
	char			*expanded_input;
	int				*last_exit_status;		// "$?"
	t_token			*tokens_list;
	t_env			*environment;
} 					t_minishell;

///////////////////////////////////////////////////////////////////////////////
//
//    REGENERATE ENVIRONMENT
//
//

t_env	*regenerate_environment(char **envp);
char	**get_environment_array(t_env *env);

///////////////////////////////////////////////////////////////////////////////
//
//    SIGNALS
//
//

void	sigint_handler(int signal_number);

///////////////////////////////////////////////////////////////////////////////
//
//    PROMPT INPUT
//
//

char	*get_prompt_input(void);

///////////////////////////////////////////////////////////////////////////////
//
//    INITIALIZATION
//
//

void initialize_minishell(t_minishell *minishell, char **envp);
void initialize_expanded_tokens_list(t_minishell *minishell);

///////////////////////////////////////////////////////////////////////////////
//
//    TOKENIZATION
//
//

t_token *tokenizer(char *input);

int		handle_operator(t_token **token_head, char *trimmed_input, int i);
int		handle_quoted_word(t_token **token_head, char *trimmed_input, int i);
int		handle_nonquoted_word(t_token **token_head, char *trimmed_input, int i);

t_token	*create_eof_token(void);
t_token	*create_word_token(t_token_type t_type, char *word, char quote);
t_token	*create_nonword_token(t_token_type t_type, char *value);

int		add_word_token(t_token **token_head, t_token_type t_type, char *word, char quote);
int		add_nonword_token(t_token **token_head, t_token_type t_type, char *value);
int		add_eof_token(t_token **token_head);

char	*get_quoted_word(char *trimmed_input, char delimiter);

char	*get_unquoted_word(char *trimmed_input);

///////////////////////////////////////////////////////////////////////////////
//
//    EXPANDER
//
//

int		needs_expansion(t_token *tokens_list);
char	*expand_tokens_list(t_minishell *minishell);
int		find_dollar(char *str);
char	*extract_var_name(char *str, int variable_start, int *variable_name_length);
char	*get_variable_value(t_minishell *minishell, char *variable_name);

///////////////////////////////////////////////////////////////////////////////
//
//    REFINE TOKENS
//
//

void refine_token_roles(t_token *tokens_head);

///////////////////////////////////////////////////////////////////////////////
//
//    CHECK SYNTAX
//
//
void check_syntax(t_minishell *minishell);

///////////////////////////////////////////////////////////////////////////////
//
//    FREEING UTILS
//
//

void	free_minishell(t_minishell *minishell);

void	free_environment(t_env **env_head);

void	free_tokens_list(t_token **token_head);

///////////////////////////////////////////////////////////////////////////////
//
//    EXIT
//
//

void	exit_minishell(t_minishell *minishell);

///////////////////////////////////////////////////////////////////////////////
//
//    DEBUG
//
//

void	print_tokens(t_token *token_head);

#endif