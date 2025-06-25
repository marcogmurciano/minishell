/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:53:36 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/06/25 18:09:12 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exit_minishell(t_minishell *minishell)
{
	free_minishell(&minishell);
	minishell = NULL;
	write(1, "exit\n", 5);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}