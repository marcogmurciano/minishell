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

char	*build_prompt(t_minishell *minishell)
{
	char *user;
	char cwd1[1024];
	char *colored_cwd;
	char *prompt;
	char *new_prompt;

	
	user = getenv("USER");
	if(!user)
		user = "USER";
	user = ft_strjoin_three("\001\033[0;32m\002", user, "\001\033[0m\002");
	if(!user)
		malloc_error(minishell);
	getcwd(cwd1, sizeof(cwd1));
	colored_cwd = ft_strjoin_three("\001\033[0;33m\002", cwd1, "\001\033[0m\002");
	if(!colored_cwd)
		malloc_error(minishell);
	prompt = ft_strjoin_three(user, "\001\033[0;90m@\033[0m\002", cwd1);
	if(!prompt)
		malloc_error(minishell);
	new_prompt = ft_strjoin(prompt, "$ ");
	if(!new_prompt)
		malloc_error(minishell);
	free(prompt);
	return(new_prompt);
}

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
char	*get_prompt_input(t_minishell *minishell)
{
	char	*input;
	char	*prompt;

	input = NULL;
	prompt = NULL;
	prompt = build_prompt(minishell);
	input = readline(prompt);
	if (input)
		add_history(input);
	free(prompt);
	return (input);
}