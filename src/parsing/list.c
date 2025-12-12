/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 19:53:21 by pmalumba          #+#    #+#             */
/*   Updated: 2025/12/05 19:14:09 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lstnew_token(t_gc *gc, char *value, t_token_type type)
{
	t_token	*tok;
	char	*res;

	tok = gc_calloc(gc, sizeof(t_token));
	if (!tok)
		return (NULL);
	res = gc_strdup(gc, value);
	if (!res)
		return (NULL);
	tok->value = res;
	if (!tok->value)
		return (NULL);
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

t_redir	*lstnew_redir(t_gc *gc, char *value, t_redir_type type)
{
	t_redir	*tok;
	char	*res;

	tok = gc_calloc(gc, sizeof(t_redir));
	if (!tok)
		return (NULL);
	res = gc_strdup(gc, value);
	if (!res)
		return (NULL);
	tok->file = res;
	if (!tok->file)
		return (NULL);
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

void	lstadd_backredir(t_redir **lst, t_redir *new)
{
	t_redir	*temp;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	if (lst && new)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	lstadd_backtok(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	if (lst && new)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}


