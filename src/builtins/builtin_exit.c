/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:01:16 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/14 11:07:53 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Error for non numeric arguments
 */
static void	numeric_error_exit(t_minishell *minishell, t_fds *fd, char **argv)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(argv[1], STDERR_FILENO);
	ft_putendl_fd(" : numeric argument required", STDERR_FILENO);
	minishell->last_exit_status = 2;
	cleanup(fd);
	exit_minishell(minishell);
}

/**
 * Modified atol that checks if number passed is not over the int limits
 */
static long	mod_atol(char *nptr, int *error)
{
	int			sign;
	int			i;
	long long	result;

	sign = 1;
	i = 0;
	result = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (ft_issign(nptr[i]))
	{
		if (ft_issign(nptr[i]) == 2)
			sign *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		result = result * 10;
		result += (nptr[i] - '0');
		if (result * sign > LLONG_MAX 
			|| result * sign < LLONG_MIN)
			return (*error = -1, -1);
		i++;
	}
	return (result * sign);
}

/**
 * Check early exit conditions
 */
static int	early_exits(t_minishell *minishell, t_fds *fd, int i)
{
	if (i == 1)
	{
		minishell->last_exit_status = 0;
		cleanup(fd);
		exit_minishell(minishell);
	}
	else if (i > 2)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		minishell->last_exit_status = 1;
		return (1);
	}
	return (0);
}

/**
 * Function that replicates exit (exit process with a specified code)
 */
int	builtin_exit(t_minishell *minishell, t_fds *fd, char **argv)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (argv[i])
		i++;
	if (early_exits(minishell, fd, i))
		return (1);
	i = 0;
	while (argv[1][i])
	{
		if (ft_isdigit(argv[1][i]) == 0 && ft_issign(argv[1][i]) == 0)
			numeric_error_exit(minishell, fd, argv);
		i++;
	}
	if (mod_atol(argv[1], &error) == -1 && error == -1)
		numeric_error_exit(minishell, fd, argv);
	else
		minishell->last_exit_status = (unsigned char)ft_atoi(argv[1]);
	cleanup(fd);
	exit_minishell(minishell);
	return (0);
}
