/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:24:22 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/04 16:24:24 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_fprintf.h"

int	type_c_fd(va_list params, int fd)
{
	char	c;

	c = (char)va_arg(params, int);
	ft_putchar_fd(c, fd);
	return (1);
}

int	type_di_fd(va_list params, int fd)
{
	int	i;
	int	j;

	i = va_arg(params, int);
	j = size_calcu(i);
	ft_putnbr_fd(i, fd);
	return (j);
}

int	type_s_fd(va_list params, int fd)
{
	char	*dup;
	int		i;

	dup = va_arg(params, char *);
	if (!dup)
	{
		ft_putstrs_fd("(null)", fd);
		return (6);
	}
	i = ft_strlens(dup);
	ft_putstrs_fd(dup, fd);
	return (i);
}

int	type_u_fd(va_list params, int fd)
{
	unsigned int	i;
	int				j;

	i = va_arg(params, unsigned int);
	j = size_calcu(i);
	ft_put_unsigned_nbr_fd(i, fd);
	return (j);
}

int	type_p_fd(va_list params, int fd)
{
	void			*arg;
	unsigned long	ptr;
	int				i;

	arg = va_arg(params, void *);
	if (arg == 0)
	{
		ft_putstrs_fd("(nil)", fd);
		return (5);
	}
	ptr = (unsigned long)arg;
	ft_putstrs_fd("0x", fd);
	i = 2;
	i = i + ft_putnbr_hex_adr_fd(ptr, fd);
	return (i);
}
