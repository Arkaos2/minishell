/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:02:37 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/23 16:32:22 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_var(t_envp *env, char *key)
{
	t_envp	*cur;
	t_envp	*prev;

	cur = env;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	unset(t_envp	*env, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->args[i])
		return ;
	while (!cmd->args[i])
	{
		unset_var(env, !cmd->args[i]);
		i++;
	}
}
