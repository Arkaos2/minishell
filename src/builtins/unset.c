/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:02:37 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/05 20:24:15 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envp *get_prev_for_key(t_envp *env, char *key)
{
	t_envp *prev;
	t_envp *cur;

	if (!env || !key)
		return (NULL);
	prev = NULL;
	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (prev);
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}

static int	remove_first_env(t_envp *env, char *key)
{
	if (env && ft_strcmp(env->key, key) == 0)
	{
		if (env->next)
		{
			env->key = env->next->key;
			env->value = env->next->value;
			env->next = env->next->next;
		}
		else
		{
			env->key = "";
			env->value = NULL;
		}
		return (1);
	}
	return (0);
}

static int	remove_env_key(t_envp *env, char *key)
{
	t_envp	*prev;
	t_envp	*cur;

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
	return (remove_first_env(env, key));
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
