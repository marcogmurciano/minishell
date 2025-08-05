/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:01:16 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/05 10:31:34 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void numeric_error_exit(t_minishell *minishell, char **argv)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(argv[1], STDERR_FILENO);
	ft_putendl_fd(" : numeric argument required", STDERR_FILENO);
	minishell->last_exit_status = 2;
	exit_minishell(minishell);
}

int	builtin_exit(t_minishell *minishell, char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
	{
		minishell->last_exit_status = 0;
		exit_minishell(minishell);
	}
	else if (i > 2)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		minishell->last_exit_status = 1;
		return (1);
	}
	i = 0;
	while(argv[1][i])
	{
		if(ft_isdigit(argv[1][i]) == 0 && ft_issign(argv[1][i]) == 0)
			numeric_error_exit(minishell, argv);
		i++;
	}
	if(ft_atol(argv[1]) > INT_MAX || ft_atol(argv[1]) < INT_MIN)
		numeric_error_exit(minishell, argv);
	else
		minishell->last_exit_status = ft_atoi(argv[1]) % 256;
	exit_minishell(minishell);
	return (0);
}
