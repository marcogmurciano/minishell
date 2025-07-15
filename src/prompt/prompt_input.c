/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:17:55 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:32:00 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
char	*get_prompt_input(void)
{
	char	*input;
	char	*user;
	char	*prompt;

	input = NULL;
	prompt = NULL;
	user = getenv("USER");
	if (user)
		prompt = ft_strjoin_three(user, "@", "minishell> ");
	else
		prompt = ft_strjoin_three("USER", "@", "minishell> ");
	input = readline(prompt);
	if (input)
	{
		add_history(input);
	}
	free(prompt);
	return (input);
}
