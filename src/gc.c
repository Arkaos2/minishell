/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:53:16 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/23 17:38:18 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gcnode	*new_node(void *ptr)
{
	t_gcnode	*n;

	n = ft_calloc(1, sizeof(*n));
	if (!n)
		return (NULL);
	n->ptr = ptr;
	n->next = NULL;
	return (n);
}

t_gc	*gc_new(void)
{
	t_gc	*gc;

	gc = ft_calloc(1, sizeof(*gc));
	if (!gc)
		return (NULL);
	gc->head = NULL;
	return (gc);
}

void	*gc_calloc(t_gc *gc, size_t size)
{
	void		*p;
	t_gcnode	*n;

	p = ft_calloc(1, size);
	if (!p)
		return (NULL);
	n = new_node(p);
	if (!n)
	{
		free(p);
		return (NULL);
	}
	n->next = gc->head;
	gc->head = n;
	return (p);
}

void	gc_destroy(t_gc *gc)
{
	t_gcnode	*cur;
	t_gcnode	*next;

	cur = gc->head;
	while (cur)
	{
		next = cur->next;
		free(cur->ptr);
		free(cur);
		cur = next;
	}
	free(gc);
}

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
