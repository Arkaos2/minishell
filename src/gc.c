/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:53:16 by saibelab          #+#    #+#             */
/*   Updated: 2025/11/25 18:53:37 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gcnode	*new_node(void *ptr)
{
	t_gcnode	*n;

	n = malloc(sizeof(*n));
	if (!n)
		return (NULL);
	n->ptr = ptr;
	n->next = NULL;
	return (n);
}

t_gc	*gc_new(void)
{
	t_gc	*gc;

	gc = malloc(sizeof(*gc));
	if (!gc)
		return (NULL);
	gc->head = NULL;
	return (gc);
}

void	*gc_malloc(t_gc *gc, size_t size)
{
	void		*p;
	t_gcnode	*n;

	p = malloc(size);
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
	dup = gc_malloc(gc, len + 1);
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
