/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:22:00 by saibelab          #+#    #+#             */
/*   Updated: 2025/06/09 15:50:13 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_string(va_list param, int *count)
{
	char	*str;

	str = va_arg(param, char *);
	if (!str)
		str = "(null)";
	ft_putstr(str, count);
}

void	print_char(va_list param, int *count)
{
	char	c;

	c = va_arg(param, int);
	ft_putchar(c, count);
}

void	print_pointer(va_list param, int *count)
{
	unsigned long	ptr;

	ptr = (unsigned long)va_arg(param, void *);
	if (!ptr)
	{
		ft_putstr("(nil)", count);
		return ;
	}
	ft_putchar('0', count);
	ft_putchar('x', count);
	putnbrhexa_low(ptr, count);
}
