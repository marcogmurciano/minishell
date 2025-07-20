/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 11:54:42 by marcoga2          #+#    #+#             */
/*   Updated: 2025/07/20 20:00:17 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_echo(t_minishell *minishell, char **argv)
{
    int i;

    (void)minishell;
    i = 1;
    while (argv[i])
    {
        ft_putstr_fd(argv[i], STDIN_FILENO);
        ft_putstr_fd(" ", STDIN_FILENO);
        i++;
    }
    ft_putstr_fd("\n", STDIN_FILENO);
    return (0);
}