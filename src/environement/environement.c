/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:26:23 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/13 18:31:09 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*key_finder(t_gc *gc, char *envp)
{
	int		i;
	char	*key;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i] && envp[i] != '=')
		i++;
	if (!envp[i])
		return (NULL);
	key = gc_strndup(gc, envp, i);
	if (!key)
		return (NULL);
	i = -1;
	while (key[++i])
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (NULL);
	return (key);
}

t_envp	*check_node(t_gc *gc, char *envp)
{
	t_envp	*node;

	if (!envp)
		return (NULL);
	node = gc_calloc(gc, sizeof(t_envp));
	if (!node)
		return (NULL);
	node->key = key_finder(gc, envp);
	if (!node->key)
		return (NULL);
	node->value = gc_strdup(gc, ft_strchr(envp, '=') + 1);
	node->next = NULL;
	return (node);
}

t_envp	*create_envp(t_gc *gc, char **envp)
{
	t_envp	*head;
	t_envp	*tail;
	t_envp	*node;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_isalpha(envp[i][0]))
		{
			node = check_node(gc, envp[i]);
			if (node)
			{
				if (!head)
					head = node;
				else
					tail->next = node;
				tail = node;
			}
		}
		i++;
	}
	return (head);
}
