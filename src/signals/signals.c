/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:29:40 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/25 13:36:09 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Signal handler for SIGINT (Ctrl+C).
 *
 * @param signal_number The signal number received.
 */
void	sigint_handler(int signal_number)
{
   if (signal_number == SIGINT) 
   {
      clear_line_and_newline();
	   g_signal_status = SIGINT;
   }
}

/**
 * @brief Signal handler for SIGQUIT (Ctrl+\).
 *
 * @param signal_number The signal number received.
 */
void	sigquit_handler(int signal_number)
{
   if (signal_number == SIGQUIT)
	{
      g_signal_status = SIGQUIT;
	}
}

void	setup_signal_handlers(void)
{
   signal(SIGINT, sigint_handler);
   signal(SIGQUIT, sigquit_handler);
}

void	default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}