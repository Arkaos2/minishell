/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:47:50 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/22 17:32:39 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export(t_cmd *cmd, t_envp *env)
{
	t_cmd *tmp;
	int i;

	i = 0;
	tmp = cmd;
	while (tmp->args[i])
	{
		if(!ft_isalpha(tmp->args[i][0]) || tmp->args[i][0] == '_')
			return (ft_fprintf(2, "minishell: export: '%s': not a valid identifier\n", tmp->args[i]), 1);
		
	}

}

void	handle_export(t_cmd *cmd, t_envp *env, t_gc *gc)
{
	int		i;
	char	*key;
	char	*value;
	char	*eq;

	i = 1;
	while (cmd->args[i])
	{
		eq = ft_strchr(cmd->args[i], '=');
		if (eq)
		{
			key = gc_strndup(gc, cmd->args[i], eq - cmd->args[i]);
			value = gc_strdup(gc, eq + 1);
			update_env(env, key, value, gc);
		}
		else
		{
			key = gc_strdup(gc, cmd->args[i]);
			if (!get_env_value(env, key))
				update_env(env, key, NULL, gc);
		}
		i++;
	}
	if(!cmd->args[1])
		print_export(env, 1);
}

