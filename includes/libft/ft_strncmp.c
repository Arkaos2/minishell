/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:09:02 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/22 18:15:49 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int    ft_strcmp(const char *s1, const char *s2)
{
    size_t i;

    if (!s1 && !s2)
        return (0);
    if (!s1)
        return (-(unsigned char)s2[0]);
    if (!s2)
        return ((unsigned char)s1[0]);
    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int    ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t    i;

    i = 0;
    while (i < n)
    {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        if (s1[i] == '\0')
            return (0);
        i++;
    }
    return (0);
}

int    ft_strncmp_custom(const char *s1, const char *s2, size_t n)
{
    size_t    i;

    while (*s2 && ft_is_whitespace(*s2))
        s2++;
    i = 0;
    while (i < n && s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    if (i < n)
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    return (0);
}

int    ft_strcmp_trim(const char *s1, const char *s2)
{
    size_t        i1;
    size_t        i2;

    i1 = 0;
    i2 = 0;
    while (s1[i1] && ft_is_whitespace(s1[i1]))
        i1++;
    while (s2[i2] && ft_is_whitespace(s2[i2]))
        i2++;
    while (s1[i1] && s2[i2] && s1[i1] == s2[i2])
    {
        i1++;
        i2++;
    }
    if (s1[i1] != '\0')
        return ((unsigned char)s1[i1] - (unsigned char)s2[i2]);
    while (s2[i2] && ft_is_whitespace(s2[i2]))
        i2++;
    if (s2[i2] == '\0')
        return (0);
    return ((unsigned char)s1[i1] - (unsigned char)s2[i2]);
}
