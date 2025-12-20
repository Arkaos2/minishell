/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:38:08 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/19 16:52:39 by pmalumba         ###   ########.fr       */
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
		if (!cur)
			continue ;
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

char	*gc_strjoin(t_gc *gc, char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	j = 0;
	s3 = gc_calloc(gc, sizeof(char) * len);
	if (!s3)
		return (NULL);
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}
