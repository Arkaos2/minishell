/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:47:50 by saibelab          #+#    #+#             */
/*   Updated: 2026/01/05 20:48:21 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export(t_cmd *cmd)
{
	int i;

	if (!cmd || !cmd->args)
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		if (!cmd->args[i][0])
			return (0);
		if (!ft_isalpha(cmd->args[i][0]) && cmd->args[i][0] != '_')
			return (ft_fprintf(2, "minishell: export: '%s': not a valid identifier\n", cmd->args[i]), 1);
		i++;
	}
	return (0);
}

int	handle_export(t_cmd *cmd, t_shell *s, t_gc *gc)
{
	int		i;
	char	*key;
	char	*value;
	char	*eq;

	i = 1;
	if (check_export(cmd))
		return (1);
	while (cmd->args[i])
	{
		eq = ft_strchr(cmd->args[i], '=');
		if (eq)
		{
			key = gc_strndup(gc, cmd->args[i], eq - cmd->args[i]);
			value = gc_strdup(gc, eq + 1);
			update_env(s->env, key, value, gc);
		}
		else
		{
			key = gc_strdup(gc, cmd->args[i]);
			if (!get_env_value(s->env, key))
				update_env(s->env, key, NULL, gc);
		}
		i++;
	}
	if (!cmd->args[1])
		handle_env(s, 1);
	return (0);
}

