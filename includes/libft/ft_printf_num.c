/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:17:53 by saibelab          #+#    #+#             */
/*   Updated: 2025/11/14 16:18:56 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_hex_upper(va_list param, int *count)
{
	unsigned int	n;

	n = va_arg(param, unsigned int);
	putnbrhexa_up((unsigned long)n, count);
}

void	print_hex_lower(va_list param, int *count)
{
	unsigned int	n;

	n = va_arg(param, unsigned int);
	putnbrhexa_low((unsigned long)n, count);
}

void	print_percent(va_list param, int *count)
{
	(void)param;
	ft_putchar('%', count);
}

void	print_unsigned(va_list param, int *count)
{
	unsigned int	n;

	n = va_arg(param, unsigned int);
	unsigned_putnbr(n, count);
}

void	print_decimal(va_list param, int *count)
{
	int	n;

	n = va_arg(param, int);
	ft_putnbr(n, count);
}
