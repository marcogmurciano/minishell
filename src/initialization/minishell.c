/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:01:27 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/04 11:47:08 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Initializes the minishell structure with environment variables.
 *
 * This function zeroes out the minishell structure, regenerates the environment
 * list from the provided environment pointer array, and populates the envp field.
 *
 * @param minishell Pointer to the t_minishell structure to initialize.
 * @param envp      The environment variable array from main().
 */
void initialize_minishell(t_minishell *minishell, char **envp)
{
	ft_bzero(minishell, sizeof(t_minishell));
	minishell->environment = regenerate_environment(envp);
	minishell->envp = get_environment_array(minishell->environment);
}