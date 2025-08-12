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
 * Build basic prompt for when XTERM variable is NOT set
 */
char *basic_prompt(t_minishell *minishell, char *user)
{
	char	*prompt;
	char	*new_prompt;
	char	*lastdir;

	if (minishell->lastdir) 
    	lastdir = minishell->lastdir;
	else 
		lastdir = "/";
	prompt = ft_strjoin_three(user, "@", lastdir);
	if (!prompt)
		malloc_error(minishell);
	new_prompt = ft_strjoin(prompt, "$ ");
	if (!new_prompt)
		malloc_error(minishell);
	free(prompt);
	return (new_prompt);
}

/**
 * Function to colorize username
 */
char *colorize(char *text, char *color_code, t_minishell *minishell)
{
    char *colored;

    colored = ft_strjoin_three(color_code, text, "\001\033[0m\002");
    if (!colored)
        malloc_error(minishell);
    return (colored);
}

/**
 * Function to build prompt using the colored username and cwd
 */ 
char *color_prompt(t_minishell *minishell, char *user)
{
    char    *prompt;
    char    *new_prompt;
    char    *cwd1;
    char    *colored_user;
    char    *lastdir;

    colored_user = colorize(user, "\001\033[0;32m\002", minishell);
    if (minishell->lastdir) 
    	lastdir = minishell->lastdir;
	else 
		lastdir = "/";
    cwd1 = ft_strdup(lastdir);
    if (!cwd1)
        malloc_error(minishell);
    prompt = ft_strjoin_three(colored_user, "\001\033[0;90m@\033[0m\002", cwd1);
    if (!prompt)
        malloc_error(minishell);
    new_prompt = ft_strjoin(prompt, "$ ");
    if (!new_prompt)
        malloc_error(minishell);
    free_strs(3, cwd1, colored_user, prompt);
    return (new_prompt);
}

char	*build_prompt(t_minishell *minishell)
{
	char	*user;

	user = getenv("USER");
	if (!user)
		user = "USER";
	if (!getenv("TERM"))
		return (basic_prompt(minishell, user));
	return (color_prompt(minishell, user));
}

/**
 * Calls function that builds the prompt, displays it, waits for input 
 * and adds input to history.
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