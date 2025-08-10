/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:46:18 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/10 19:22:30 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * Function that checks if fds should be closed and if so close them
 */
void fd_check_and_close(int a, int b)
{
	if (a != -1 && a != 0)
		close(a);
	if (b != -1 && b != 1)
		close(b);
}