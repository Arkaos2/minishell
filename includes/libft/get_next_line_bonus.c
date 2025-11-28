/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:39:38 by saibelab          #+#    #+#             */
/*   Updated: 2025/11/28 15:02:11 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	gnl_clear(char **stock)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		free(stock[i]);
		stock[i] = NULL;
		i++;
	}
}

char	*extract_line(char *stock)
{
	char	*new;
	int		i;

	new = NULL;
	i = 0;
	if (!stock || stock[0] == '\0')
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
		i++;
	new = ft_calloc((i + 1), sizeof(char));
	if (!new)
		return (NULL);
	ft_strncpy(new, stock, i);
	new[i] = '\0';
	return (new);
}

char	*remove_line(char *stock)
{
	int		i;
	int		j;
	char	*new_stock;

	if (!stock || stock[0] == '\0')
		return (NULL);
	i = 0;
	j = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
		return (free(stock), NULL);
	i++;
	while (stock[i + j])
		j++;
	if (j == 0)
		return (free(stock), NULL);
	new_stock = ft_calloc((j + 1), sizeof(char));
	if (!new_stock)
		return (free(stock), NULL);
	ft_strncpy(new_stock, stock + i, j);
	new_stock[j] = '\0';
	return (free(stock), new_stock);
}

char	*read_to_stock(int fd, char *stock)
{
	char	*buf;
	ssize_t	bytes;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (find_newline(stock) == -1)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buf);
			if (stock)
				free(stock);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		buf[bytes] = '\0';
		stock = append(stock, buf);
		if (!stock)
			return (free(buf), NULL);
	}
	free(buf);
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*stock[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	if (fd == -42)
		gnl_clear(stock);
	if (!stock[fd])
	{
		stock[fd] = ft_calloc(1, sizeof(char));
		if (!stock[fd])
			return (NULL);
		stock[fd][0] = '\0';
	}
	stock[fd] = read_to_stock(fd, stock[fd]);
	if (!stock[fd])
		return (NULL);
	if (!*stock[fd])
		return (free(stock[fd]), stock[fd] = NULL, NULL);
	line = extract_line(stock[fd]);
	stock[fd] = remove_line(stock[fd]);
	return (line);
}
