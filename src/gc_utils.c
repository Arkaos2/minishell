/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:19:30 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/08 16:19:30 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_strdup(t_gc *gc, const char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = gc_calloc(gc, sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*gc_strndup(t_gc *gc, const char *s, int n)
{
	char	*dup;
	size_t	size;
	size_t	i;

	i = 0;
	if (n > (int)ft_strlen(s))
		size = ft_strlen(s) + 1;
	else
		size = n + 1;
	dup = (char *)gc_calloc(gc, sizeof(char) * (size));
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

char	*gc_strjoin(t_gc *gc, const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*out;

	if (!s1 && !s2)
		return (NULL);
	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	if (s2)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	out = gc_calloc(gc, sizeof(char) * (len1 + len2 + 1));
	if (!out)
		return (NULL);
	if (s1)
		ft_strlcpy(out, s1, len1 + 1);
	if (s2)
		ft_strlcat(out, s2, len1 + len2 + 1);
	return (out);
}

char	*gc_itoa(t_shell *shell, int n)
{
	char	*str;
	char	*result;

	str = ft_itoa(n);
	if (!str)
		return (NULL);
	result = gc_strdup(shell->gc, str);
	free(str);
	return (result);
}

char	*gc_substr(t_gc *gc, char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (gc_strdup(gc, ""));
	if (len > s_len - start)
		len = s_len - start;
	s2 = (char *)gc_calloc(gc, sizeof(char) * s_len);
	if (!s2)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s2[i] = s[start + i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
