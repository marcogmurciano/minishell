/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:58:22 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/25 17:11:13 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../../libft/include/libft.h"

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
	CMD,				  // 7
	ARG,                  // 8
	TOKEN_EOF             // 9
}						t_token_type;

typedef enum e_quote_type
{
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	NO_QUOTE,
}						t_quote_type;

/**
 * Command structure
 */

typedef struct s_cmd	t_cmd;
typedef struct s_cmd
{
	char				*command;
	char				*pathname;
	char				**arguments;
	int					is_pathname;
}						t_cmd;

/**
 * Minishell structure
 * Dependencies:
 * - Environment structure
 * - Token structure
 */

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
	char				**envp;
	char				*input;
	char				*expanded_input;
	t_token				*tokens_list;
	t_env				*environment;
}						t_minishell;

#endif