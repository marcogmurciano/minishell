/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:13:13 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/11 10:30:43 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Swap pointers for ordering list
 */
void	ft_swap(char **first, char **second)
{
	char	*temp;

	temp = *first;
	*first = *second;
	*second = temp;
}
