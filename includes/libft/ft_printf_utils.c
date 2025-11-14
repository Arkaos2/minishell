/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:32:50 by saibelab          #+#    #+#             */
/*   Updated: 2025/11/14 16:19:01 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putnbrhexa_low(unsigned long n, int *count)
{
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
		putnbrhexa_low (n / 16, count);
	ft_putchar (base[n % 16], count);
}

void	putnbrhexa_up(unsigned long n, int *count)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (n >= 16)
		putnbrhexa_up (n / 16, count);
	ft_putchar (base[n % 16], count);
}

void	ft_putnbr(int n, int *count)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		*count += 11;
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-', count);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, count);
		ft_putnbr(n % 10, count);
	}
	if (n < 10)
		ft_putchar(n + '0', count);
}

void	unsigned_putnbr(unsigned int n, int *count)
{
	if (n >= 10)
		unsigned_putnbr(n / 10, count);
	ft_putchar((n % 10) + '0', count);
}

void	ft_putstr(char *str, int *count)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i], count);
		i++;
	}
}
