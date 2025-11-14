/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:49 by miltavar          #+#    #+#             */
/*   Updated: 2025/08/22 16:34:04 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_fprintf.h"

void	fill_hex(char *dest, char *str)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
}

int	size_calcu(long n)
{
	int				size;
	unsigned int	nb;

	size = 0;
	if (n == 0)
		return (++size);
	if (n < 0)
	{
		nb = -n;
		size++;
	}
	else
	nb = n;
	while (nb != 0)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

void	ft_put_unsigned_nbr_fd(unsigned int nbr, int fd)
{
	if (nbr >= 10)
	{
		ft_put_unsigned_nbr_fd(nbr / 10, fd);
		ft_put_unsigned_nbr_fd(nbr % 10, fd);
	}
	else
		ft_putchar_fd(nbr + 48, fd);
}

int	ft_putnbr_hex_low_fd(unsigned int nbr, int fd)
{
	char	hex[17];
	char	buffer[16];
	int		i;
	int		count;

	fill_hex(hex, "0123456789abcdef");
	if (nbr == 0)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	i = 0;
	while (nbr > 0)
	{
		buffer[i++] = hex[nbr % 16];
		nbr /= 16;
	}
	count = i;
	while (--i >= 0)
		ft_putchar_fd(buffer[i], fd);
	return (count);
}

int	ft_putnbr_hex_up_fd(unsigned int nbr, int fd)
{
	char	hex[17];
	char	buffer[16];
	int		i;
	int		count;

	fill_hex(hex, "0123456789ABCDEF");
	if (nbr == 0)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	i = 0;
	while (nbr > 0)
	{
		buffer[i++] = hex[nbr % 16];
		nbr /= 16;
	}
	count = i;
	while (--i >= 0)
		ft_putchar_fd(buffer[i], fd);
	return (count);
}
