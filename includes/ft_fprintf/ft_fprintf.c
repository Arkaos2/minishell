/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:24:05 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/04 16:24:07 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_fprintf.h"

static int	check_char(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'x' || c == 'u' || c == 'X'
		|| c == '%')
		return (1);
	return (0);
}

int	distrib_fd(char type, va_list params, int fd)
{
	int	i;

	i = 0;
	if (type == 'c')
		i = type_c_fd(params, fd);
	if (type == 'd' || type == 'i')
		i = type_di_fd(params, fd);
	if (type == 'u')
		i = type_u_fd(params, fd);
	if (type == 's')
		i = type_s_fd(params, fd);
	if (type == 'p')
		i = type_p_fd(params, fd);
	if (type == 'x')
		i = type_x_fd(params, fd);
	if (type == 'X')
		i = type_xx_fd(params, fd);
	if (type == '%')
		i = type_percent_fd(fd);
	return (i);
}

int	print_str_fd(int fd, const char *format, va_list params)
{
	int	i;
	int	start;
	int	res;

	i = 0;
	start = 0;
	res = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] && check_char(format[i + 1]))
		{
			res += write_chunk(fd, format, start, i);
			res += process_format(fd, format, params, &i);
			start = i;
		}
		else
			i++;
	}
	res += write_chunk(fd, format, start, i);
	return (res);
}

static int	check_format(const char *format)
{
	int	i;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] && check_char(format[i + 1]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	int	count;

	if (!format)
		return (-1);
	count = 0;
	va_list(params);
	va_start(params, format);
	if (check_format(format) == 1)
	{
		va_end(params);
		return (0);
	}
	count = print_str_fd(fd, format, params);
	va_end(params);
	return (count);
}
