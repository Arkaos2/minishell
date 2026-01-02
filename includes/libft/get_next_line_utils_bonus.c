/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:39:34 by saibelab          #+#    #+#             */
/*   Updated: 2025/11/28 15:02:48 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*create_new_stock(char *stock, char *new_stock, char *buf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (stock)
	{
		while (stock[i] != '\0')
		{
			new_stock[i] = stock[i];
			i++;
		}
	}
	while (buf[j] != '\0')
	{
		new_stock[i + j] = buf[j];
		j++;
	}
	new_stock[i + j] = '\0';
	free (stock);
	return (new_stock);
}

char	*append(char *stock, char *buf)
{
	char	*new_stock;
	int		len_stock;

	len_stock = 0;
	if (!buf)
		return (NULL);
	if (stock)
		len_stock = ft_strlen(stock);
	new_stock = ft_calloc((ft_strlen(buf) + len_stock + 1), sizeof(char));
	if (!new_stock)
		return (NULL);
	new_stock = create_new_stock(stock, new_stock, buf);
	if (!new_stock)
		return (NULL);
	return (new_stock);
}

int	find_newline(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
