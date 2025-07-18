/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-18 08:50:42 by user              #+#    #+#             */
/*   Updated: 2025-07-18 08:50:42 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    builtin_pwd(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        // fprintf(stderr, "pwd: error: %s\n", strerror(errno));
        perror("pwd");
        return (1);
    }
    printf("%s\n", cwd);
    free(cwd);
    return (0);
}
