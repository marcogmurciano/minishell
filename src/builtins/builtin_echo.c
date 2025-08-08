/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 11:54:42 by marcoga2          #+#    #+#             */
/*   Updated: 2025/08/08 11:23:57 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function that replicates echo functionality
 */
int builtin_echo(t_minishell *minishell, char **argv)
{
    int i = 1;
    int newline = 1;

    (void)minishell;
    if (argv[i] && strcmp(argv[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (argv[i])
    {
        ft_putstr_fd(argv[i], STDOUT_FILENO);
        if (argv[i + 1])
            ft_putstr_fd(" ", STDOUT_FILENO);
        i++;
    }
    if (newline)
        ft_putstr_fd("\n", STDOUT_FILENO);
    return (0);
}