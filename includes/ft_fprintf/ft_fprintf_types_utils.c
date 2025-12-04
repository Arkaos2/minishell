/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_types_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:23:52 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/04 16:23:55 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_fprintf.h"

int	ft_putnbr_hex_adr_fd(unsigned long nbr, int fd)
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

int	type_x_fd(va_list params, int fd)
{
	unsigned int	i;
	int				j;

	i = va_arg(params, int);
	j = ft_putnbr_hex_low_fd(i, fd);
	return (j);
}

int	type_xx_fd(va_list params, int fd)
{
	unsigned int	i;
	int				j;

	i = va_arg(params, int);
	j = ft_putnbr_hex_up_fd(i, fd);
	return (j);
}

int	type_percent_fd(int fd)
{
	ft_putchar_fd('%', fd);
	return (1);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
