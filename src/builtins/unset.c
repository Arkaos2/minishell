/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:02:37 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/23 17:12:42 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* return the previous node for the node matching key, or NULL if the
   head matches or not found */
static t_envp *get_prev_for_key(t_envp *env, const char *key)
{
	t_envp *prev;
	t_envp *cur;

	if (!env || !key)
		return (NULL);
	prev = NULL;
	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->key, (char *)key) == 0)
			return (prev);
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}

static int remove_env_key(t_envp *env, const char *key)
{
	t_envp *prev;
	t_envp *cur;

	if (!env || !key)
		return (0);
	prev = get_prev_for_key(env, key);
	if (prev)
	{
		cur = prev->next;
		if (cur)
			prev->next = cur->next;
		return (1);
	}
	cur = env;
	if (cur && ft_strcmp(cur->key, (char *)key) == 0)
	{
		if (cur->next)
		{
			cur->key = cur->next->key;
			cur->value = cur->next->value;
			cur->next = cur->next->next;
		}
		else
		{
			cur->key = "";
			cur->value = NULL;
		}
		return (1);
	}
	return (0);
}

int	handle_unset(t_cmd *cmd, t_envp *env, t_gc *gc)
{
	int i;

	(void)gc;
	if (!cmd || !cmd->args)
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		remove_env_key(env, cmd->args[i]);
		i++;
	}
	return (0);
}
