/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:33:54 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/08 16:33:54 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envp	*create_env_node(t_shell *shell, char *key, char *value)
{
	t_envp	*new;

	new = gc_calloc(shell->gc, sizeof(t_envp));
	if (!new)
		return (NULL);
	new->key = gc_strdup(shell->gc, key);
	new->value = gc_strdup(shell->gc, value);
	new->next = NULL;
	return (new);
}

void	add_env_var(t_shell *shell, char *key, char *value)
{
	t_envp	*tmp;
	t_envp	*new;

	if (!shell->env)
	{
		shell->env = create_env_node(shell, key, value);
		return ;
	}
	tmp = shell->env;
	while (tmp->next)
		tmp = tmp->next;
	new = create_env_node(shell, key, value);
	tmp->next = new;
}

int	upgrade_env(t_shell *shell)
{
	t_envp	*tmp;
	int		i;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strncmp("SHLVL", tmp->key, 6) == 0 && tmp->key[5] == '\0')
		{
			i = ft_atoi(tmp->value);
			i++;
			tmp->value = gc_itoa(shell, i);
			return (0);
		}
		tmp = tmp->next;
	}
	add_env_var(shell, "SHLVL", "1");
	return (0);
}
