/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:46:40 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 18:51:41 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Write a single character to a specified file descriptor.
 * @param c The character to be written.
 * @param fd File descriptor that points to the file to write into.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
