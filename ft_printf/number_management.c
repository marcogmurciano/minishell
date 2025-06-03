/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:39:14 by marco             #+#    #+#             */
/*   Updated: 2025/04/23 14:35:51 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printnbr(int n, size_t *result)
{
	if (n == -2147483648)
	{
		print_str("-2147483648", result);
		return ;
	}
	if (n < 0)
	{
		print_char('-', result);
		n = -n;
	}
	if (n >= 10)
		printnbr(n / 10, result);
	print_char((n % 10) + '0', result);
}

void	printunsigned(unsigned int n, size_t *result)
{
	if (n == 4294967295)
	{
		print_str("4294967295", result);
		return ;
	}
	if (n >= 10)
		printunsigned(n / 10, result);
	print_char((n % 10) + '0', result);
}

void	put_hex_recursive(uintptr_t n, size_t *result, int uppercase)
{
	char	*hex_digits;

	if (uppercase)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	if (n >= 16)
		put_hex_recursive(n / 16, result, uppercase);
	print_char(hex_digits[n % 16], result);
}
