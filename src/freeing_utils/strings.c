/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:27:27 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/11 10:41:15 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Frees a list of string arguments
 */
void	free_strs(int count, ...)
{
	va_list	args;
	char	*str;
	int		i;

	va_start(args, count);
	i = 0;
	while (i < count)
	{
		str = va_arg(args, char *);
		free(str);
		i++;
	}
	va_end(args);
}
