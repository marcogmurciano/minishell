/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:29:40 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/11 10:31:01 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Signal handler for SIGINT (Ctrl+C).
 *
 * TODO: Send -SIGINT kill signal to each process/command PIDs in commands list.
 *
 * @param signal_number The signal number received.
 */
void sigint_handler(int signal_number)
{
    if(signal_number == SIGINT)
    {
		g_signal_status = 130;
		clear_line_and_newline();
    }
	else if(signal_number == SIGQUIT)
    {
		g_signal_status = 131;
    }
}