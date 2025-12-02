/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:51:17 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/02 17:24:38 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env(t_envp *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static char	**fill_envp(t_gc *gc, t_envp *env, int size)
{
	char	**envp;
	int		i;
	t_envp	*tmp;

	i = 0;
	envp = gc_calloc(gc, (size + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
		{
			envp[i] = gc_strjoin(gc, tmp->key, "=");
			if (!envp[i])
				return (NULL);
			envp[i] = gc_strjoin(gc, envp[i], tmp->value);
			if (!envp[i])
				return (NULL);
		}
		else
		{
			envp[i] = gc_strdup(gc, tmp->key);
			if (!envp[i])
				return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**env_to_char(t_gc *gc, t_envp *env)
{
	int		size;
	char	**envp;

	if (!env)
		return (NULL);
	size = count_env(env);
	envp = fill_envp(gc, env, size);
	return (envp);
}
