/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:18:08 by saibelab          #+#    #+#             */
/*   Updated: 2025/09/23 15:20:57 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*noeud;

	new = NULL;
	while (lst)
	{
		noeud = malloc(sizeof(t_list));
		if (!noeud)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		noeud->content = f(lst->content);
		noeud->next = NULL;
		if (!new)
			new = noeud;
		else
			ft_lstlast(new)->next = noeud;
		lst = lst->next;
	}
	return (new);
}
