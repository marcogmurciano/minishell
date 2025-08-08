/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:01:16 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/08 11:32:04 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Error for non numeric arguments
 */
static void numeric_error_exit(t_minishell *minishell, char **argv)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(argv[1], STDERR_FILENO);
	ft_putendl_fd(" : numeric argument required", STDERR_FILENO);
	minishell->last_exit_status = 2;
	exit_minishell(minishell);
}

/**
 * Modified atol that checks if number passed is not over the int limits
 */
long	mod_atol(char *nptr, int *error)
{
	int		sign;
	int		i;
	long	result;

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
		if (result * sign > 2147483647 || result * sign < -2147483648)
			return (*error = -1, -1);
		i++;
	}
	return (result * sign);
}

/**
 * Function that replicates exit (exit process with a specified code)
 */
int	builtin_exit(t_minishell *minishell, char **argv)
{
	int i;
	int error;

	i = 0;
	error = 0;
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
	if(mod_atol(argv[1], &error) == -1 && error == -1)
		numeric_error_exit(minishell, argv);
	else
		minishell->last_exit_status = ft_atoi(argv[1]) % 256;
	exit_minishell(minishell);
	return (0);
}
