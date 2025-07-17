/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:29:40 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/17 22:25:52 by dbarba-v         ###   ########.fr       */
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
