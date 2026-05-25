/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endpoint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:48:03 by marco             #+#    #+#             */
/*   Updated: 2025/04/23 15:01:34 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(char c, size_t *result)
{
	write(STDERR_FILENO, &c, 1);
	(*result)++;
}

void	print_str(const char *s, size_t *result)
{
	int	i;

	i = -1;
	if (s == NULL)
	{
		print_str("(null)", result);
		return ;
	}
	while (s[++i])
		print_char(s[i], result);
}
