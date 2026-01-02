/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:53:35 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/22 18:15:10 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strdup(const char *src)
{
    int        i;
    char    *dest;

    i = 0;
    dest = ft_calloc(sizeof(char), ft_strlen(src) + 1);
    if (dest == NULL)
        return (0);
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char    *ft_strndup(const char *s, int n)
{
    char    *dup;
    size_t    size;
    size_t    i;

    i = 0;
    if (n > (int)ft_strlen(s))
        size = ft_strlen(s) + 1;
    else
        size = n + 1;
    dup = (char *)ft_calloc(sizeof(char), size);
    if (dup == NULL)
        return (NULL);
    while (i < size - 1)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}
