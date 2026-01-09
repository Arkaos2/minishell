/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:53:16 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/02 17:25:03 by saibelab         ###   ########.fr       */
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

	if (!gc)
		return ;
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
