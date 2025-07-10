/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:03:58 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/10 14:40:09 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	syntax_error(char *origin)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if(origin)
		ft_putstr_fd(ft_strjoin(origin, ": "), STDERR_FILENO);
	ft_putendl_fd("Invalid syntax", STDERR_FILENO);
	return(1);
}

// int	too_many_error(char *origin)
// {
// 	ft_putstr_fd("minishell: ", STDERR_FILENO);
// 	if(origin)
// 		ft_putstr_fd(ft_strjoin(origin, ": "), STDERR_FILENO);
// 	ft_putendl_fd("too many arguments", STDERR_FILENO);
// 	return(-1);
// }