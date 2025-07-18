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

int	syntax_error(char *origin, t_minishell *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (ft_strcmp(origin, "heredoc") == 0)
		ft_putendl_fd("syntax error: invalid heredoc delimeter", STDERR_FILENO);
	else
		ft_putendl_fd("syntax error: invalid syntax", STDERR_FILENO);
	minishell->last_exit_status = 1;
	return (1);
}
