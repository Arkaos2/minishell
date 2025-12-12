/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:51:17 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/12 15:58:15 by saibelab         ###   ########.fr       */
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

static char	**fill_envp(t_shell *shell, int size)
{
	char	**envp;
	int		i;
	t_envp	*tmp;

	i = 0;
	envp = gc_calloc(shell->gc, (size + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	tmp = shell->env;
	while (tmp)
	{
		if (tmp->value)
		{
			envp[i] = gc_strjoin(shell->gc, tmp->key, "=");
			if (!envp[i])
				return (NULL);
			envp[i] = gc_strjoin(shell->gc, envp[i], tmp->value);
			if (!envp[i])
				return (NULL);
		}
		else
		{
			envp[i] = gc_strdup(shell->gc, tmp->key);
			if (!envp[i])
				return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**env_to_char(t_shell *shell)
{
	int		size;
	char	**envp;

	if (!shell->env)
		return (NULL);
	size = count_env(shell->env);
	envp = fill_envp(shell, size);
	return (envp);
}
