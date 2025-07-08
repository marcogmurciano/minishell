/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:03:58 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/08 12:53:54 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void syntax_error(t_minishell *minishell)
{
	ft_putstr_fd("minishell: ", minishell->duplicated_std_fds[1]);
	ft_putendl_fd("Invalid syntax", minishell->duplicated_std_fds[1]);
	exit_minishell(minishell);
}