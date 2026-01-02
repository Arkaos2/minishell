/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:24:15 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/04 16:24:18 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_fprintf.h"

size_t	ft_strlens(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstrs_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlens(s));
}

void	ft_putnbr_fd(int nb, int fd)
{
	long	nbr;

	nbr = nb;
	if (nbr < 0)
	{
		nb = -nb;
		nbr = -nbr;
		ft_putchar_fd('-', fd);
	}
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putnbr_fd(nbr % 10, fd);
	}
	else
		ft_putchar_fd(nbr + '0', fd);
}

int	write_chunk(int fd, const char *format, int start, int end)
{
	int	len;

	len = end - start;
	if (len > 0)
		write(fd, &format[start], len);
	return (len);
}

int	process_format(int fd, const char *format, va_list params,
				int *i)
{
	int	res;

	res = distrib_fd(format[*i + 1], params, fd);
	*i += 2;
	return (res);
}
