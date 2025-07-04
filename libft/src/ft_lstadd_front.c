/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:05:16 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 18:36:19 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Adds a new element at the beginning of a linked list.
 * 
 * @param lst The address of a pointer to the first element of the list.
 * @param new The element to be added to the front of the list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
        return ;
	new->next = *lst;
    *lst = new;
}
