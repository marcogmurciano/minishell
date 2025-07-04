/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarba-v <dbarba-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:21:03 by dbarba-v          #+#    #+#             */
/*   Updated: 2025/07/03 18:05:06 by dbarba-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * Computes the power of an integer base to a non-negative integer exponent.
 * @param base The base integer.
 * @param exp The exponent (must be >= 0).
 * @return The result of base raised to the power exp.
 */
static int	ft_pow(int base, int exp)
{
	int	result;

	result = 1;
	while (exp > 0)
	{
		result *= base;
		exp--;
	}
	return (result);
}

/**
 * Iterates through the digits in the string, accumulating the integer value
 * and counting decimals if a decimal point is encountered.
 * 
 * @param nptr The string to parse.
 * @param decimal_count Pointer to the decimal count variable.
 * @param accumulated_value Pointer to the result value.
 */
void	digit_iterator(const char *nptr, int *decimal_count, int *accum_value)
{
	while (ft_isdigit(*nptr) || (*decimal_count < 0 && *nptr == '.'))
	{
		if (*nptr == '.')
		{
			nptr++;
			*decimal_count = 0;
			continue ;
		}
		*accum_value = *accum_value * 10 + (*nptr - '0');
		if (*decimal_count >= 0)
			*decimal_count = (*decimal_count) + 1;
		nptr++;
	}
}

/**
 * Converts an ASCII string to a floating-point value.
 * Handles optional leading whitespace, sign, integer and fractional parts.
 * 
 * @param nptr The string to convert.
 * @return The converted float value.
 */
float	ft_atof(const char *nptr)
{
	int	sign;
	int	decimal_count;
	int	accum_value;

	sign = 1;
	decimal_count = -1;
	accum_value = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (ft_issign(*nptr))
	{
		if (ft_issign(*nptr) == 2)
			sign = -1;
		nptr++;
	}
	digit_iterator(nptr, &decimal_count, &accum_value);
	if (decimal_count > 0)
		return ((float)(accum_value * sign) / ft_pow(10, decimal_count));
	return ((float)accum_value * sign);
}
