/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:45 by saibelab          #+#    #+#             */
/*   Updated: 2025/09/23 15:20:40 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	len_num(long nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*tab;
	long	nb;
	int		len;

	nb = (long)n;
	len = len_num(nb);
	tab = malloc(sizeof(char) * len + 1);
	if (!tab)
		return (NULL);
	tab[len] = '\0';
	if (nb < 0)
	{
		tab[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		tab[0] = '0';
	while (nb > 0)
	{
		len--;
		tab[len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (tab);
}
