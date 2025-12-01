/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:51:17 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/01 15:56:39 by saibelab         ###   ########.fr       */
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

static char	**fill_envp(t_envp *env, int size)
{
	char	**envp;
	int		i;
	t_envp	*tmp;
	char	*tmp1;

	i = 0;
	envp = ft_calloc(size + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
		{
			tmp1 = ft_strjoin(tmp->key, "=");
			envp[i] = ft_strjoin(tmp1, tmp->value);
			free(tmp1);
		}
		else
			envp[i] = ft_strdup(tmp->key);
		if (!envp[i])
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	return (envp[i] = NULL, envp);
}

char	**env_to_char(t_envp *env)
{
	int		size;
	char	**envp;

	if (!env)
		return (NULL);
	size = count_env(env);
	envp = fill_envp(env, size);
	return (envp);
}
