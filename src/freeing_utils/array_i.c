/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_i.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:04:22 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/14 17:09:03 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Free an array of j pointers
 */
char	**free_array(char **array, int j)
{
	while (j >= 0)
	{
		free(array[j]);
		j--;
	}
	free(array);
	array = NULL;
	return (array);
}
