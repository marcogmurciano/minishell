/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:29:40 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/08 12:46:07 by marcoga2         ###   ########.fr       */
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
 * @brief Setup signal handlers
 */
void	setup_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Setup default signal handling for child processes
 */
void	default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * @brief Ignore signals when child processes running for parent processes
 */
void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
