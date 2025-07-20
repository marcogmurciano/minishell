/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-19 11:54:42 by user              #+#    #+#             */
/*   Updated: 2025-07-19 11:54:42 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_echo(char *s)
{
    if (ft_strchr(s, '$'))
    {
        printf("not implemented echo variables yet, relaja la raja\n");
        return (1);
    }
    printf("%s\n", s);
    return (0);
}