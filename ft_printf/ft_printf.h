/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:24:47 by user              #+#    #+#             */
/*   Updated: 2025/04/23 14:36:40 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// headers
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

// prototypes from all functions
void	printnbr(int n, size_t *result);
void	printunsigned(unsigned int n, size_t *result);
void	put_hex_recursive(uintptr_t n, size_t *result, int uppercase);
void	print_char(char c, size_t *result);
void	print_str(const char *s, size_t *result);
void	printd(int n, size_t *result);
void	printu(unsigned int n, size_t *result);
void	printp(void *ptr, size_t *result);
void	printx(unsigned int n, size_t *result, int specifier);
int		ft_printf(const char *format, ...);

#endif
