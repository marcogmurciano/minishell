/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array2d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:16:00 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 18:13:40 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Frees a null-terminated array, its sub-arrays, and the array itself.
 * 
 * @param array Pointer to a null-terminated array of pointers to arrays.
 */
void	ft_free_array2d(void ***array)
{
	size_t	i;

	if (!array) 
	{
		return;
	}
	i = 0;
	while (array[i])
	{
		ft_free_array(array[i]);
		i++;
	}
	free(array);
}
