/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:04:35 by saibelab          #+#    #+#             */
/*   Updated: 2025/11/14 16:06:40 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, int *count, int fd)
{
	write (fd, &c, 1);
	(*count)++;
}

t_conversion	*init_table(void)
{
	static t_conversion	table[] = {
	{'d', print_decimal},
	{'s', print_string},
	{'i', print_decimal},
	{'c', print_char},
	{'u', print_unsigned},
	{'x', print_hex_lower},
	{'X', print_hex_upper},
	{'p', print_pointer},
	{'%', print_percent},
	{'\0', NULL}
	};

	return (table);
}

t_conversion	*find_key(char cle, t_conversion *table)
{
	int	i;

	i = 0;
	while (table[i].c)
	{
		if (table[i].c == cle)
			return (&table[i]);
		i++;
	}
	return (NULL);
}

int	process(const char *str, va_list param, int fd)
{
	int				i;
	int				count;
	t_conversion	*table;
	t_conversion	*conv;

	i = 0;
	count = 0;
	table = init_table();
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			conv = find_key(str[i], table);
			if (!conv || !conv->f)
				return (-1);
			conv->f(param, &count);
		}
		else
			ft_putchar(str[i], &count, fd);
		i++;
	}
	return (count);
}

int	ft_printf(const char *str, int fd, ...)
{
	va_list			param;
	int				count;

	if (!str)
		return (-1);
	va_start(param, str);
	count = process(str, param, fd);
	va_end(param);
	return (count);
}
