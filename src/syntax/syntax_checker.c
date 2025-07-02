/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:05:02 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/02 15:34:17 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Prints a syntax error message and exits the minishell.
 *
 * Depending on the origin of the error, prints an appropriate syntax error
 * message to standard error, then calls exit_minishell() to terminate the shell.
 *
 * @param origin String indicating the origin of the syntax error (e.g., "heredoc").
 * @param minishell Pointer to the minishell instance to exit from.
 */
void syntax_error(char *origin, t_minishell *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if(strcmp(origin, "heredoc") == 0)
		ft_putendl_fd("syntax error: invalid heredoc delimeter,", STDERR_FILENO);
	exit_minishell(minishell);
}

// int is_metacharacter(char *value)
// {
	
// }

/**
 * @brief Checks the syntax of tokens in the minishell's token list.
 *
 * Iterates through the tokens list of the given minishell instance and checks
 * for syntax errors. If a syntax error is found, the function calls syntax_error().
 *
 * @param minishell Pointer to the minishell instance containing the tokens list.
 */
void check_syntax(t_minishell *minishell)
{
	t_token *current;

	current = minishell->tokens_list;
	while (current && current->token_type != TOKEN_EOF)
	{
		// if (current->token_type == TOKEN_HEREDOC_DELIM &&
		// 		current->quote_type != NON_QUOTE &&
		// 		is_metacharacter(current->value))
		// 	syntax_error("heredoc", minishell);
		current = current->next;
	}
}