/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:58:22 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/17 21:18:21 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../../libft/include/libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include <signal.h>
#include "pipex.h"
#include "structs.h"

/**
 * Signals global variable
 */
extern volatile sig_atomic_t g_signal_status;

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

char	*get_prompt_input(t_minishell *minishell);
void	clear_line_and_newline(void);

///////////////////////////////////////////////////////////////////////////////
//
//    INITIALIZATION
//
//

void	initialize_minishell(t_minishell *minishell, char **envp);

///////////////////////////////////////////////////////////////////////////////
//
//    REGENERATE ENVIRONMENT
//
//

t_env	*regenerate_environment(char **envp);
char	**get_environment_array(t_env *env);
t_env 	*check_environment(t_minishell *minishell);
void 	append_env_node(t_env **head, t_env *new_env);
t_env	*create_env_node(char *arg);

///////////////////////////////////////////////////////////////////////////////
//
//    TOKENIZATION
//
//

void	tokenization(t_minishell *minishell);

int		handle_operator(t_token **token_head, t_minishell *minishell, int i);
int		handle_quoted_word(t_token **token_head, t_minishell *minishell, int i);
int		handle_nonquoted_word(t_token **token_head, t_minishell *minishell, int i);

char	*get_quoted_word(t_minishell *minishell, char delimiter, int i);

char	*get_unquoted_word(t_minishell *minishell, char *input);

int		add_word_token(t_token **token_head, t_token_type t_type, char *word, char *quote);
int		add_nonword_token(t_token **token_head, t_token_type t_type, char *value);
int		add_eof_token(t_token **token_head);

t_token	*create_eof_token(void);
t_token	*create_word_token(t_token_type t_type, char *word, char quote);
t_token	*create_nonword_token(t_token_type t_type, char *value);

void	join_tokens(t_token **tokens_head);

///////////////////////////////////////////////////////////////////////////////
//
//    EXPANDER
//
//

int		needs_expansion(t_token *tokens_list);
char	*expand_tokens_list(t_minishell *minishell);
int		find_dollar(char *str);
char	*retrieve_new_input(t_minishell *minishell);
char	*extract_var_name(char *str, int variable_start, int *variable_name_length);
char	*get_variable_value(t_minishell *minishell, char *variable_name);

///////////////////////////////////////////////////////////////////////////////
//
//    REFINE TOKENS
//
//

void	refine_token_roles(t_token *tokens_head);

///////////////////////////////////////////////////////////////////////////////
//
//    EXECUTION
//
//

int 	execution(t_minishell *minishell);
int		builtin_pwd(void);
int		builtin_env(t_minishell *minishell, char **argv);
int		builtin_export(t_minishell *minishell, char **argv);
int		builtin_echo(t_minishell *minishell, char **argv);
int		builtin_unset(t_minishell *minishell, char **argv);

///////////////////////////////////////////////////////////////////////////////
//
//    SYNTAX ANALYSIS
//
//

int		syntax_analysis(t_minishell *minishell);
int		syntax_check(t_minishell *minishell);

///////////////////////////////////////////////////////////////////////////////
//
//    SYNTAX ANALYSIS UTILITIES
//
//

char	**get_cmd_argv(t_minishell *minishell, t_token *segment);
char	**get_infile_array(t_minishell *minishell, t_token *segment);
char	**get_heredoc_array(t_minishell *minishell, t_token *segment);
char 	**get_outfile_array(t_minishell *minishell, t_token *segment);
char	**insert_into_array(char *infile, char **array, t_minishell *minishell);
int		get_append_status(t_token *token);
int		get_last_in_type(t_token *segment);

///////////////////////////////////////////////////////////////////////////////
//
//    FREEING UTILS
//
//

void	free_minishell(t_minishell *minishell);
void	free_environment(t_env **env_head);
void	free_tokens_list(t_token **token_head);
char	**free_array(char **array, int j);
void	free_cmds(t_cmd **cmd_head);

///////////////////////////////////////////////////////////////////////////////
//
//    ERRORS
//
//
void	malloc_error(t_minishell *minishell);
int		syntax_error(char *origin, t_minishell *minishell);

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

void	print_envp(char **envp);
void print_tokens(t_token *token_head);
void print_segment(t_token *token);
void print_cmd(t_cmd *cmd);
void	print_environ(t_env *env);

#endif