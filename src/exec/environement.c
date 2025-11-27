/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmalumba <pmalumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:26:23 by saibelab          #+#    #+#             */
/*   Updated: 2025/11/27 19:08:50 by pmalumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*key_finder(char *envp)
{
	int		i;
	char	*key;

	i = 0;
	while (envp[i] != '=')
		i++;
	key = ft_strndup(envp, i);
	i = -1;
	while (key[++i])
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (free(key), NULL);
	return (key);
}

t_envp	*check_node(char *envp)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	node->key = key_finder(envp);
	if (!node->key)
		return (free(node), NULL);
	node->value = ft_strdup(ft_strchr(envp, '='));
	node->next = NULL;
	return (node);
}

t_envp	*create_envp(char **envp)
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
			node = check_node(envp[i]);
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
