/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:50:40 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/30 12:11:24 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Frees all dynamically allocated fields within a t_minishell struct.
 * After freeing, all pointers are set to NULL to avoid dangling pointers.
 * @param minishell
 */
void free_minishell(t_minishell *minishell)
{
	if (minishell->input)
	{
		free(minishell->input);
		minishell->input = NULL;
	}
	if (minishell->expanded_input)
	{
		free(minishell->expanded_input);
		minishell->expanded_input = NULL;
	}
	if (minishell->tokens_list)
	{
		free_tokens_list(&(minishell->tokens_list));
		minishell->tokens_list = NULL;
	}
	if (minishell->environment)
	{
		free_environment(&(minishell->environment));
		minishell->environment = NULL;
	}
}
