/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:13:13 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/08/10 19:13:42 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Swap pointers for ordering list
 */
void ft_swap(char **first, char **second)
{
	char *temp;

	temp = *first;
	*first = *second;
	*second = temp;
}