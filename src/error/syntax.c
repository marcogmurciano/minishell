/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:03:58 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/15 11:37:51 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Printing of syntax errors
 */
int	syntax_error(char *origin, t_minishell *minishell, int code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (origin)
	{
		ft_putstr_fd(origin, STDERR_FILENO);
		ft_putstr_fd(":  ", STDERR_FILENO);
	}
	if (code == 0)
		ft_putstr_fd("\033[0;31msyntax error\033[0m: unsupported character",
			STDERR_FILENO);
	else if (code == 1)
		ft_putstr_fd("\033[0;31msyntax error\033[0m: invalid file redirection",
			STDERR_FILENO);
	else if (code == 2)
		ft_putstr_fd(
			"\033[0;31msyntax error\033[0m: invalid token after heredoc",
			STDERR_FILENO);
	else if (code == 3)
		ft_putstr_fd("\033[0;31msyntax error\033[0m: invalid token after pipe",
			STDERR_FILENO);
	else if (code == 4)
		ft_putstr_fd("\033[0;31msyntax error\033[0m: invalid argument syntax",
			STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	minishell->last_exit_status = 1;
	return (1);
}
