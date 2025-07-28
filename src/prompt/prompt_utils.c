/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:15:50 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:31:47 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_line_and_newline(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay(); // If commented out it doesn't display twice but CTRl+C broken
}

void	clear_line_and_newline_in_child(void) // NEEDS TO BE USED
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	//rl_redisplay(); // If commented out it doesn't display twice but CTRl+C broken
}
