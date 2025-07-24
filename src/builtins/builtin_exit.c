/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:01:16 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/24 18:40:50 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_exit(t_minishell *minishell, char **argv)
{
	int argc;
	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
	{
		minishell->last_exit_status = 0;
		exit_minishell(minishell);
	}
	else if (argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		minishell->last_exit_status = 1;
	}
	if(ft_atol(argv[1]) > INT_MAX || ft_atol(argv[1]) < INT_MIN)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(" : numeric argument required", STDERR_FILENO);
		minishell->last_exit_status = 2;
	}
	else
		minishell->last_exit_status = ft_atoi(argv[1]);
	exit_minishell(minishell);
	return (0);
}
