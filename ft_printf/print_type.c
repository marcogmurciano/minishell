/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:50:58 by marco             #+#    #+#             */
/*   Updated: 2025/04/23 14:59:50 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printd(int n, size_t *result)
{
	printnbr(n, result);
}

void	printu(unsigned int n, size_t *result)
{
	printunsigned(n, result);
}

void	printp(void *ptr, size_t *result)
{
	uintptr_t	addr;

	addr = (uintptr_t)ptr;
	if (addr == 0)
	{
		print_str("(nil)", result);
		return ;
	}
	print_str("0x", result);
	put_hex_recursive(addr, result, 0);
}

void	printx(unsigned int n, size_t *result, int specifier)
{
	int	uppercase;

	uppercase = 0;
	if (specifier == 'X')
		uppercase = 1;
	put_hex_recursive(n, result, uppercase);
}
