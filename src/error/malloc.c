/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:52:00 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/14 17:09:16 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void malloc_error(t_minishell *minishell)
{
	free_minishell(minishell);
    minishell = NULL;
    write(STDERR_FILENO, "malloc error", 12);
    rl_clear_history();
    exit(EXIT_SUCCESS);
}
