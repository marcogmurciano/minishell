/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:24:59 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 18:39:41 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Iterates the list and applies the function 'f' on the content
 *        of each node, creating a new list with the results.
 * @param lst Pointer to a node of the original list.
 * @param f Function to apply to each node's content.
 * @param del Function to delete the content of a node if needed.
 * @return The new list, or NULL if allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list_start;
	t_list	*temp;
	void	*new_content;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	new_list_start = NULL;
	while (lst != NULL)
	{
		new_content = f(lst->content);
		temp = ft_lstnew(new_content);
		if (temp == NULL)
		{
			del(new_content);
			ft_lstclear(&new_list_start, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list_start, temp);
		lst = lst->next;
	}
	return (new_list_start);
}
