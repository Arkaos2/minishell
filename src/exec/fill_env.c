/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:53:08 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/22 15:53:56 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env(t_envp *env)
{
	int	i = 0;

	while (env)
	{
		if (env->value != NULL)
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
	char	*tmp2;

	envp = gc_calloc(shell->gc, sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = shell->env;
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			tmp2 = gc_strjoin(shell->gc, tmp->key, "=");
			if (!tmp2)
				return (NULL);
			envp[i] = gc_strjoin(shell->gc, tmp2, tmp->value);
			if (!envp[i])
				return (NULL);

			i++;
		}
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**env_to_char(t_shell *shell)
{
	int	size;

	if (!shell->env)
		return (NULL);

	size = count_env(shell->env);
	return fill_envp(shell, size);
}
