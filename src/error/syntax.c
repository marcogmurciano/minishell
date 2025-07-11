/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:03:58 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/11 15:50:54 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int syntax_error(char *origin, t_minishell *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if(strcmp(origin, "heredoc") == 0)
		ft_putendl_fd("syntax error: invalid heredoc delimeter", STDERR_FILENO);
	else
		ft_putendl_fd("syntax error: invalid syntax", STDERR_FILENO);
	minishell->last_exit_status = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return (1);
}


// int	too_many_error(char *origin)
// {
// 	ft_putstr_fd("minishell: ", STDERR_FILENO);
// 	if(origin)
// 		ft_putstr_fd(ft_strjoin(origin, ": "), STDERR_FILENO);
// 	ft_putendl_fd("too many arguments", STDERR_FILENO);
// 	return(-1);
// }